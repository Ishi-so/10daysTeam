#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include "../Base/DirectX12.h"
#include "../Struct/Math.h"
#include "../Struct/Math/Vector3.h"
#include "../Struct/Math/Vector4.h"
#include "../Struct/Math/Matrix4.h"

class DebugCamera;

class CollisionCapsule
{
public: // �T�u�N���X
	struct VertexPosUv
	{
		Math::Vector3 pos; // xyz���W
	};

	struct CbData
	{
		Math::Matrix4 myMat;		// 3D�ϊ��s��
		Math::Matrix4 viewproj;
		Math::Vector4 color;
	};

private:
	// �f�o�C�X
	static ID3D12Device* device;
	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;
	// ���[�g�V�O�l�`��
	static Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	// �f�X�N���v�^�q�[�v
	static Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeap;
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
		CollisionCapsule::d_camera = d_camera;
	}

	/// <summary>
	/// �`��O����
	/// </summary>
	static void PreDraw();

	/// <summary>
	/// �`��㏈��
	/// </summary>
	static void PostDraw();

	static CollisionCapsule* Create(const Math::Vector3& start, const Math::Vector3& end, float radius, int slices);

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CollisionCapsule(const Math::Vector3& start, const Math::Vector3& end, float radius, int slices, int stacks_1_2);

	void CreateVertexBuffer();

	void CreateConstBuffer();

	/// <summary>
	/// ������
	/// </summary>
	bool Initialize();

	void Update();

	/// <summary>
	/// �`��R�}���h�̔��s
	/// </summary>
	void Draw();

	void TransferVertices();

	void CreateIndexBuffer();

	void SetPosition(float x, float y, float z) { position = { x,y,z }; }

	void SetStP(const Math::Vector3& st) { start = st; TransferVertices(); }
	void SetStP(const float x, const float y, const float z) { start = { x,y,z }; TransferVertices(); }

	void SetEdP(const Math::Vector3& ed) { end = ed; TransferVertices(); }
	void SetEdP(const float x, const float y, const float z) { end = { x,y ,z }; TransferVertices(); }

	void SetColor(float r, float g, float b, float a) { color = { r,g,b,a }; }

	Math::Vector3 GetStartPoint()const { return start + position; }
	Math::Vector3 GetEndPoint()const { return end + position;}
	float GetSlices()const { return slices; }
	float GetRadius()const { return radius; }

private:
	// ���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	// �C���f�b�N�X�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> indexBuff;
	// �萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff;
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// �C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView = {};

	// ���W
	Math::Vector3 position{};

	Math::Vector3 start = Math::Vector3();
	Math::Vector3 end = Math::Vector3();
	Math::Vector4 color;
	int slices;
	int stacks_1_2;
	float radius = 0.0f;
	// ���[���h�s��
	Math::Matrix4 myWorld{};
};
