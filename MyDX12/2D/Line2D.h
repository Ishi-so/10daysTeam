#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include "../Base/DirectX12.h"
#include "../Struct/Math.h"
#include "../Struct/Math/Vector2.h"
#include "../Struct/Math/Vector3.h"
#include "../Struct/Math/Matrix4.h"

class Line2D
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using Vector3 = Math::Vector3;
private:
	// 頂点数
	static const int vertNum = 2;

public: // サブクラス
	struct VertexPosUv
	{
		Math::Vector3 pos; // xyz座標
	};

	struct CbData
	{
		Math::Matrix4 myMat;		// 3D変換行列
		Math::Vector2 xm_start;
		Math::Vector2 xm_end;
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

	static Line2D* Create(Math::Vector2 start, Math::Vector2 end);

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Line2D(Math::Vector2 start, Math::Vector2 end);

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

	void SetStP(const Math::Vector2 st) { start = st; TransferVertices(); }
	void SetStP(const float x, const float y) { start = { x,y }; TransferVertices(); }

	void SetEdP(const Math::Vector2 ed) { end = ed; TransferVertices(); }
	void SetEdP(const float x, const float y) { end = { x,y }; TransferVertices(); }

private:
	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	// Z軸回りの回転角
	float rotation = 0.0f;
	// 座標
	Math::Vector2 position{};

	Math::Vector2 start = Math::Vector2(100, 400);
	Math::Vector2 end = Math::Vector2(1000, 400);
	// ワールド行列
	Math::Matrix4 myWorld{};
};