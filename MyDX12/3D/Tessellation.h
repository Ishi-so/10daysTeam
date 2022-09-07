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

public: // �T�u�N���X
	struct VertexPosUv
	{
		Vector3 pos; // xyz���W
		Vector2 uv; // uv���W
	};

	struct CbData
	{
		Math::Vector4 cameraPos;
		Math::Matrix4 myMat;		// 3D�ϊ��s��
		Math::Matrix4 viewproj;
		Math::Vector4 tessRange;
	};

private:
	// �f�o�C�X
	static ID3D12Device* device;
	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootSignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelineState;
	// �J����
	static DebugCamera* d_camera;

public: // �ÓI�����o�֐�
	/// <summary>
	/// �ÓI������
	/// </summary>
	static bool StaticInitialize();

	/// <summary>
	/// �p�C�v���C������
	/// </summary>
	static void CreateGraphicsPipelineState();

	/// <summary>
	/// �J�����̃Z�b�g
	/// </summary>
	static void SetDebugCamera(DebugCamera* d_camera)
	{
		Tessellation::d_camera = d_camera;
	}

	/// <summary>
	/// �`��O����
	/// </summary>
	static void PreDraw();

	/// <summary>
	/// �`��㏈��
	/// </summary>
	static void PostDraw();

	static Tessellation* Create();

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Tessellation();

	void CreateVertexBuffer();
	void CreateIndexBuffer();

	void CreateConstBuffer();

	ComPtr<ID3D12Resource> LoadTextureFromFile(std::string& texPath);

	void CreateTexture();
	void CreateSRV();

	/// <summary>
	/// ������
	/// </summary>
	bool Initialize();

	void Update();

	/// <summary>
	/// �`��R�}���h�̔��s
	/// </summary>
	void Draw();

	void VerticesStream();

	void TransferVertices();

	void IndexStream();

private:
	// ���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	// �C���f�b�N�X�o�b�t�@
	ComPtr<ID3D12Resource> indexBuff;
	// �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// �C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView = {};

	// �e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texBuff0;
	ComPtr<ID3D12Resource> texBuff1;

	// SRV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;

	std::vector<VertexPosUv> vertices;
	std::vector<UINT> indices;

	// ���W
	Math::Vector3 position{};

	// ���[���h�s��
	Math::Matrix4 myWorld{};

};