#include "PostEffectTest.hlsli"

Texture2D<float4> tex0 : register(t0);	// 0番スロットに設定されたテクスチャ
Texture2D<float> tex1 : register(t1);	// 0番スロットに設定されたテクスチャ
//Texture2D<float> shadowMap : register(t2);	// 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);		// 0番スロットに設定されたサンプラー

float rand(float co)
{
	return frac(sin(co * 12.9898) * 43758.5453);
}

float rand(float2 co)
{
	return frac(sin(dot(co.xy, float2(12.9898, 78.233))) * 43758.5453);
}

float rand(float3 co)
{
	return frac(sin(dot(co.xyz, float3(12.9898, 78.233, 56.787))) * 43758.5453);
}

float2 mod(float2 a, float2 b)
{
	return a - floor(a / b) * b;
}

float4 HighLumi(float2 uv)
{
	float4 col = tex0.Sample(smp, uv);
	float grayScale = col.r * 0.299 + col.g * 0.587 + col.b * 0.114;
	float extract = smoothstep(0.6, 0.9, grayScale);
	return col * extract;
}

float Gaussian(float2 drawUV, float2 pickUV, float sigma)
{
	float d = distance(drawUV, pickUV);
	return exp(-(d * d) / (2 * sigma * sigma));
}

float4 GaussianBlur(float2 uv, float sG, float sW)
{
	float totalWeight = 0, sigma = sG, stepWidth = sW;
	float4 col = float4(0, 0, 0, 0);

	for (float py = -sigma * 2; py <= sigma * 2; py += stepWidth)
	{
		for (float px = -sigma * 2; px <= sigma * 2; px += stepWidth)
		{
			float2 pickUV = uv + float2(px, py);
			float weight = Gaussian(uv, pickUV, sigma);
			col += tex0.Sample(smp, pickUV) * weight;
			totalWeight += weight;
		}
	}

	col.rgb = col.rgb / totalWeight;
	return col;
}

float4 GaussianGX(Texture2D<float4> tex, SamplerState smp, float2 uv, float d)
{
	float pixel_u;
	float pixel_v;

	if (d == 0.0f)
	{
		pixel_u = 0.0f;
		pixel_v = 0.0f;
	}
	else
	{
		pixel_u = 1.0f / d;
		pixel_v = 1.0f / d;
	}

	float4 dcolor = { 0,0,0,0 };

	for (int i = -1; i < 2; i++)
	{
		// 左上ピクセルの色をサンプリングし、合計に足す(U: -1pixel V:-1pixel)
		dcolor += tex.Sample(smp, uv + float2(-pixel_u, pixel_v * i));

		// 中上ピクセルの色をサンプリングし、合計に足す(U: +-0 V:-1pixel)
		dcolor += tex.Sample(smp, uv + float2(0.0f, pixel_v * i));

		// 右上ピクセルの色をサンプリングし、合計に足す(U: +1pixel V:-1pixel)
		dcolor += tex.Sample(smp, uv + float2(pixel_u, pixel_v * i));
	}

	return float4(dcolor.rgb / 9, 1);
}

float4 InverseColor(Texture2D<float4> tex, SamplerState smp, float2 uv)
{
	float4 texcolor = tex.Sample(smp,uv);
	return float4(1 - texcolor.rgb, 1);
}

float2 randomVec(float2 fact)
{
	float2 angle = float2(
		dot(fact, float2(127.1, 311.7)),
		dot(fact, float2(269.5, 183.3))
		);
	return frac(sin(angle) * 43758.5453123) * 2 - 1;
}

// ノイズの密度をdensityデ設定、uvにi.uvを代入
float PerlinNoise(float density, float2 uv)
{
	float2 uvFloor = floor(uv * density* float2(1280.0f/2,960.0f/2));
	float2 uvFrac = frac(uv * density * float2(1280.0f / 2, 960.0f / 2));

	float2 v00 = randomVec(uvFloor + float2(0, 0)); // ②各頂点のランダムなベクトルを取得
	float2 v01 = randomVec(uvFloor + float2(0, 1));
	float2 v10 = randomVec(uvFloor + float2(1, 0));
	float2 v11 = randomVec(uvFloor + float2(1, 1));

	float c00 = dot(v00, uvFrac - float2(0, 0)); // ②と③の内積を取って、④を作成
	float c01 = dot(v01, uvFrac - float2(0, 1));
	float c10 = dot(v10, uvFrac - float2(1, 0));
	float c11 = dot(v11, uvFrac - float2(1, 1));

	float2 u = uvFrac * uvFrac * (3 - 2 * uvFrac);

	float v0010 = lerp(c00, c10, u.x); // 描画するピクセルから⑤を求める
	float v0111 = lerp(c01, c11, u.x);

	return lerp(v0010, v0111, u.y) / 2 + 0.5;
}

float FractalSumNoise(float density, float2 uv)
{
	float fn;
	fn = PerlinNoise(density * 1, uv) * 1.0 / 2;
	fn += PerlinNoise(density * 2, uv) * 1.0 / 4;
	fn += PerlinNoise(density * 4, uv) * 1.0 / 8;
	fn += PerlinNoise(density * 8, uv) * 1.0 / 16;
	return fn;
}

float4 main(VSOutput input) : SV_TARGET
{
	float4 result = float4(1, 1, 1, 1);
	float4 col = tex0.Sample(smp, input.uv);
	result = col;

	return result;
}