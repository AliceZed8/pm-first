cbuffer mycbuffer: register(b0)
{
    float4x4 mat;
};



struct VS_INPUT
{
    float3 inPos : POSITION;
    float2 inTexCoord : TEXCOORD;
};
struct VS_OUTPUT
{
    float4 OutPosition : SV_POSITION;
    float2 OutTexCoord : TEXCOORD;
};




VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;
    output.OutPosition = mul(float4(input.inPos, 1.0f), mat);
    output.OutTexCoord = input.inTexCoord;
    return output;
};
