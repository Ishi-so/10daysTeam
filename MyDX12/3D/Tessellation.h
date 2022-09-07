#pragma once
#include <d3d12.h>
#include <d3dx12.h>
#include <string>
#include "../Base/DirectX12.h"
#include "../Struct/Math/Vector2.h"
#include "../Struct/Math/Vector3.h"
#include "../Struct/Math/Vector4.h"
#include "../Struct/Math/Matrix4.h"

class DebugCamera;

class Tessellation
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using Vector3 = Math::Vector3;
	using Vector2 = Math::Vector2;

private:
	const float edge = 200.0f;
	const int divide = 10;

public: // サブクラス
	struct VertexPosUv
	{
		Vector3 pos; // xyz座標
		Vector2 uv; // uv座標
	};

	struct CbData
	{
		Math::Vector4 cameraPos;
		Math::Matrix4 myMat;		// 3D変換行列
		Math::Matrix4 viewproj;
		Math::Vector4 tessRange;
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
	// カメラ
	static DebugCamera* d_camera;

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
	/// カメラのセット
	/// </summary>
	static void SetDebugCamera(DebugCamera* d_camera)
	{
		Tessellation::d_camera = d_camera;
	}

	/// <summary>
	/// 描画前処理
	/// </summary>
	static void PreDraw();

	/// <summary>
	/// 描画後処理
	/// </summary>
	static void PostDraw();

	static Tessellation* Create();

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Tessellation();

	void CreateVertexBuffer();
	void CreateIndexBuffer();

	void CreateConstBuffer();

	ComPtr<ID3D12Resource> LoadTextureFromFile(std::string& texPath);

	void CreateTexture();
	void CreateSRV();

	/// <summary>
	/// 初期化
	/// </summary>
	bool Initialize();

	void Update();

	/// <summary>
	/// 描画コマンドの発行
	/// </summary>
	void Draw();

	void VerticesStream();

	void TransferVertices();

	void IndexStream();

private:
	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	// インデックスバッファ
	ComPtr<ID3D12Resource> indexBuff;
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW ibView = {};

	// テクスチャバッファ
	ComPtr<ID3D12Resource> texBuff0;
	ComPtr<ID3D12Resource> texBuff1;

	// SRV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;

	std::vector<VertexPosUv> vertices;
	std::vector<UINT> indices;

	// 座標
	Math::Vector3 position{};

	// ワールド行列
	Math::Matrix4 myWorld{};

};