#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include "../Base/DirectX12.h"
#include "../Struct/Math.h"
#include "../Struct/Math/Vector2.h"
#include "../Struct/Math/Vector3.h"
#include "../Struct/Math/Vector4.h"
#include "../Struct/Math/Matrix4.h"

class Point2D
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
private:
	// 頂点数
	static const int vertNum = 1;

public: // サブクラス
	struct VertexPosUv
	{
		Math::Vector3 pos; // xyz座標
	};

	struct CbData
	{
		Math::Matrix4 myMat;		// 3D変換行列
		Math::Vector4 color;
		unsigned int active;
	};

	static const int dataIndexCount = 500;

	struct CBVIDParameter
	{
		CbData data[dataIndexCount];
	};

	struct PointData
	{
		Math::Vector2 position{};
		Math::Vector4 color{};
	};

private:
	// デバイス
	static ID3D12Device* device;
	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootSignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelineState;
	// 射影行列
	static Math::Matrix4 myProjection;
	// デスクリプタヒープ
	static ComPtr<ID3D12DescriptorHeap> descHeap;

public: // 静的メンバ関数
	/// <summary>
	/// 静的初期化
	/// </summary>
	static bool StaticInitialize();

	/// <summary>
	/// パイプライン生成
	/// </summary>
	static void CreateGraphicsPipelineState();

	/// <summary>
	/// 描画前処理
	/// </summary>
	static void PreDraw();

	/// <summary>
	/// 描画後処理
	/// </summary>
	static void PostDraw();

	static Point2D* Create();

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Point2D();

	void AddPoint(float x, float y, float r, float g, float b, float a)
	{
		pDatas.push_back({ { x,y }, { r,g,b,a } });
	}

	void CreateVertexBuffer();

	void CreateConstBuffer();

	/// <summary>
	/// 初期化
	/// </summary>
	bool Initialize();

	/// <summary>
	/// 描画コマンドの発行
	/// </summary>
	void Draw();

	void TransferVertices();
	void TransferCBVInstance();
	void ClearPoint() { pDatas.clear(); }

private:
	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	// 定数バッファ(Instance用)
	ComPtr<ID3D12Resource> constBuff;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	Math::Vector3 point = Math::Vector3();

	// 座標
	std::vector<PointData> pDatas;
	// ワールド行列
	Math::Matrix4 myWorld{};
};