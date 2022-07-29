
// ディレクションライト
struct DirectionLight
{
    float3 direction; // ライトの方向
    float3  color; // ライトのカラー
};

// ポイントライト
struct PointLight
{
    float3  position; //位置
    float3  color; //カラー
    float   range; //影響範囲
};

//スポットライト
struct SpotLight
{
    float3  position;   //位置
    float3  color;      //カラー
    float   range;      //影響範囲
    float3  direction;  //方向
    float   angle;      //角度
};

// モデル用の定数バッファー
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

// ライト用の定数バッファー
cbuffer LightCb : register(b1)
{
    DirectionLight directionLight;
    PointLight pointLight;
    SpotLight spotLight;
    //アンビエントライト。
    float3 ambientLight; //環境光。

    float3 eyePos; //視点の位置。

    float4x4 mLVP;

    float3 targetPosition;

    float red;
};

// 頂点シェーダーへの入力
struct SVSIn
{
    float4 pos : POSITION;  // モデルの頂点座標
    float3 normal : NORMAL; // 法線

    float3 tangent:TANGENT;
    float3 biNormal:BINORMAL;
    float2 uv : TEXCOORD0;  // UV座標
};

// ピクセルシェーダーへの入力
struct SPSIn
{
    float4 pos      : SV_POSITION;  // スクリーン空間でのピクセルの座標
    float3 normal   : NORMAL;       // 法線
    float2 uv 		: TEXCOORD0;	//uv座標。
    float3 worldPos : TEXCOORD1;

    float3 normalInView : TEXCOORD2;     //カメラ空間の法線

    float3 tangent  : TANGENT;
    float3 biNormal : BINORMAL;
    float2 uv       : TEXCOORD3;    // UV座標
    float3 worldPos : TEXCOORD4;    // ワールド空間でのピクセルの座標
};

// モデルテクスチャ
Texture2D<float4> g_texture : register(t0);

Texture2D<float4> g_normalMap:register(t1);
// サンプラーステート
sampler g_sampler : register(s0);

// 頂点シェーダー
SPSIn VSMain(SVSIn vsIn)
{
    SPSIn psIn;
    psIn.pos = mul(mWorld, vsIn.pos);
    psIn.worldPos = psIn.pos;
    psIn.pos = mul(mView, psIn.pos);
    psIn.pos = mul(mProj, psIn.pos);
    psIn.normal = normalize(mul(mWorld, vsIn.normal));

    // step-4 接ベクトルと従ベクトルをワールド空間に変換する
    psIn.tengent = normalize(mul(mWorld, vsIn.tangent));
    psIn.biNormal = normalize(mul(mWorld, vsIn.biNormal));

    psIn.uv = vsIn.uv;
    return psIn;
}

// テクスチャなしプリミティブ描画用のピクセルシェーダー
float4 PSMain(SPSIn psIn) : SV_Target0
{
    // ディフューズマップをサンプリング
    float4 diffuseMap = g_texture.Sample(g_sampler, psIn.uv);

    float3 normal = psIn.normal;

    float3 localNormal = g_normalMap.Sample(g_sampler, psIn.cv).xyz;
    //タンジェントスペースの法線を0～1の範囲から-1～1の範囲に復元する
    localNormal = (localNormal - 0.5f) * 2.0f;

    //タンジェントスペースの法線をワールドスペースに変換する
    normal = psIn.tangent * localNormal.x
           + psIn.biNormal * localNormal.y
           + normal * localNormal.z;

    // 拡散反射光を計算する
    float3 lig = 0.0f;
    lig += max(0.0f, dot(normal, -dirLigDirection)) * dirLigColor;
    lig += ambientLight;

    float4 finalColor = diffuseMap;
    finalColor.xyz *= lig;

    return finalColor;
}