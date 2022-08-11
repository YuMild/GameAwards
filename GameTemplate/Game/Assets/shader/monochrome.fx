cbuffer cb : register(b0)
{
    float4x4 mvp;
    float4 mulColor;
};

struct VSInput
{
    float4 pos : POSITION;
    float2 uv : TEXCOORD0;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};

Texture2D<float4> sceneTexture : register(t0);
sampler Sampler : register(s0);

PSInput VSMain(VSInput In)
{
    PSInput psIn;
    psIn.pos = mul(mvp, In.pos);
    psIn.uv = In.uv;
    return psIn;
}

float4 PSMain(PSInput In) : SV_Target0
{
    float4 color = sceneTexture.Sample(Sampler, In.uv);

    float Y = 0.299f * color.r + 0.587f * color.b + 0.114f * color.b;
    color.r = Y;
    color.g = Y;
    color.b = Y;

    return color;
}