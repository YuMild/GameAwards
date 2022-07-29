
// �f�B���N�V�������C�g
struct DirectionLight
{
    float3 direction; // ���C�g�̕���
    float3  color; // ���C�g�̃J���[
};

// �|�C���g���C�g
struct PointLight
{
    float3  position; //�ʒu
    float3  color; //�J���[
    float   range; //�e���͈�
};

//�X�|�b�g���C�g
struct SpotLight
{
    float3  position;   //�ʒu
    float3  color;      //�J���[
    float   range;      //�e���͈�
    float3  direction;  //����
    float   angle;      //�p�x
};

// ���f���p�̒萔�o�b�t�@�[
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

// ���C�g�p�̒萔�o�b�t�@�[
cbuffer LightCb : register(b1)
{
    DirectionLight directionLight;
    PointLight pointLight;
    SpotLight spotLight;
    //�A���r�G���g���C�g�B
    float3 ambientLight; //�����B

    float3 eyePos; //���_�̈ʒu�B

    float4x4 mLVP;

    float3 targetPosition;

    float red;
};

// ���_�V�F�[�_�[�ւ̓���
struct SVSIn
{
    float4 pos : POSITION;  // ���f���̒��_���W
    float3 normal : NORMAL; // �@��

    float3 tangent:TANGENT;
    float3 biNormal:BINORMAL;
    float2 uv : TEXCOORD0;  // UV���W
};

// �s�N�Z���V�F�[�_�[�ւ̓���
struct SPSIn
{
    float4 pos      : SV_POSITION;  // �X�N���[����Ԃł̃s�N�Z���̍��W
    float3 normal   : NORMAL;       // �@��
    float2 uv 		: TEXCOORD0;	//uv���W�B
    float3 worldPos : TEXCOORD1;

    float3 normalInView : TEXCOORD2;     //�J������Ԃ̖@��

    float3 tangent  : TANGENT;
    float3 biNormal : BINORMAL;
    float2 uv       : TEXCOORD3;    // UV���W
    float3 worldPos : TEXCOORD4;    // ���[���h��Ԃł̃s�N�Z���̍��W
};

// ���f���e�N�X�`��
Texture2D<float4> g_texture : register(t0);

Texture2D<float4> g_normalMap:register(t1);
// �T���v���[�X�e�[�g
sampler g_sampler : register(s0);

// ���_�V�F�[�_�[
SPSIn VSMain(SVSIn vsIn)
{
    SPSIn psIn;
    psIn.pos = mul(mWorld, vsIn.pos);
    psIn.worldPos = psIn.pos;
    psIn.pos = mul(mView, psIn.pos);
    psIn.pos = mul(mProj, psIn.pos);
    psIn.normal = normalize(mul(mWorld, vsIn.normal));

    // step-4 �ڃx�N�g���Ə]�x�N�g�������[���h��Ԃɕϊ�����
    psIn.tengent = normalize(mul(mWorld, vsIn.tangent));
    psIn.biNormal = normalize(mul(mWorld, vsIn.biNormal));

    psIn.uv = vsIn.uv;
    return psIn;
}

// �e�N�X�`���Ȃ��v���~�e�B�u�`��p�̃s�N�Z���V�F�[�_�[
float4 PSMain(SPSIn psIn) : SV_Target0
{
    // �f�B�t���[�Y�}�b�v���T���v�����O
    float4 diffuseMap = g_texture.Sample(g_sampler, psIn.uv);

    float3 normal = psIn.normal;

    float3 localNormal = g_normalMap.Sample(g_sampler, psIn.cv).xyz;
    //�^���W�F���g�X�y�[�X�̖@����0�`1�͈̔͂���-1�`1�͈̔͂ɕ�������
    localNormal = (localNormal - 0.5f) * 2.0f;

    //�^���W�F���g�X�y�[�X�̖@�������[���h�X�y�[�X�ɕϊ�����
    normal = psIn.tangent * localNormal.x
           + psIn.biNormal * localNormal.y
           + normal * localNormal.z;

    // �g�U���ˌ����v�Z����
    float3 lig = 0.0f;
    lig += max(0.0f, dot(normal, -dirLigDirection)) * dirLigColor;
    lig += ambientLight;

    float4 finalColor = diffuseMap;
    finalColor.xyz *= lig;

    return finalColor;
}