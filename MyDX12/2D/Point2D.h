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
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
private:
	// ���_��
	static const int vertNum = 1;

public: // �T�u�N���X
	struct VertexPosUv
	{
		Math::Vector3 pos; // xyz���W
	};

	struct CbData
	{
		Math::Matrix4 myMat;		// 3D�ϊ��s��
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
	// �f�o�C�X
	static ID3D12Device* device;
	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootSignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelineState;
	// �ˉe�s��
	static Math::Matrix4 myProjection;
	// �f�X�N���v�^�q�[�v
	static ComPtr<ID3D12DescriptorHeap> descHeap;

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
	/// �`��O����
	/// </summary>
	static void PreDraw();

	/// <summary>
	/// �`��㏈��
	/// </summary>
	static void PostDraw();

	static Point2D* Create();

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Point2D();

	void AddPoint(float x, float y, float r, float g, float b, float a)
	{
		pDatas.push_back({ { x,y }, { r,g,b,a } });
	}

	void CreateVertexBuffer();

	void CreateConstBuffer();

	/// <summary>
	/// ������
	/// </summary>
	bool Initialize();

	/// <summary>
	/// �`��R�}���h�̔��s
	/// </summary>
	void Draw();

	void TransferVertices();
	void TransferCBVInstance();
	void ClearPoint() { pDatas.clear(); }

private:
	// ���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	// �萔�o�b�t�@(Instance�p)
	ComPtr<ID3D12Resource> constBuff;
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	Math::Vector3 point = Math::Vector3();

	// ���W
	std::vector<PointData> pDatas;
	// ���[���h�s��
	Math::Matrix4 myWorld{};
};