static const int INSTANCE_NUM = 500;

struct InstanceData
{
	matrix mat;
	float4 color;
	uint active;
};

cbuffer cbuff0 : register(b0)
{
	matrix viewproj;
	matrix matbillboard;
	InstanceData data[INSTANCE_NUM];
};

struct VSOutput
{
	float4 svpos : SV_POSITION; // �V�X�e���p���_���W
	float2 uv  :TEXCOORD; // uv�l
	float4 color : COLOR;
};