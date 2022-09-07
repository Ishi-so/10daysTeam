#include "Object3D.h"
#include "../Camera/DebugCamera.h"
#include "../Struct/Math/Vector4.h"
#include <fstream>
#include <sstream>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace std;

ID3D12Device* Object3D::device = nullptr;
ID3D12GraphicsCommandList* Object3D::cmdList = nullptr;
Object3D::PipelineSet Object3D::pipelineSet;
DebugCamera* Object3D::d_camera = nullptr;
LightGroup* Object3D::lightGroup = nullptr;

XMFLOAT3 TransXMF3(Math::Vector3 vec)
{
	XMFLOAT3 p = { vec.x,vec.y,vec.z };
	return p;
}

void Object3D::StaticInitialize()
{
	Object3D::device = DirectX12::GetDevice();
	Object3D::d_camera = d_camera;

	// �O���t�B�b�N�p�C�v���C���̐���
	CreateGraphicsPipeline();

	// ���f���̐ÓI������
	Model::StaticInitialize();
}

void Object3D::CreateGraphicsPipeline()
{
	XIIlib::GraphicsPipeline* plData = new XIIlib::GraphicsPipeline();
	plData->AddInputLayout({ "POSITION",XIIlib::RGB_FLOAT });
	plData->AddInputLayout({ "NORMAL",XIIlib::RGB_FLOAT });
	plData->AddInputLayout({ "TEXCOORD",XIIlib::RG_FLOAT });

	plData->AddShader(XIIlib::VS, "OBJVertexShader.hlsl");
	plData->AddShader(XIIlib::PS, "OBJPixelShader.hlsl");
	plData->AddRange(XIIlib::SRV, 1, 0);

	plData->AddRootParam(0, XIIlib::CBV);
	plData->AddRootParam(1, XIIlib::CBV);
	plData->AddRootParam(1, XIIlib::SRV,XIIlib::SRV_MULTI_ONE);
	plData->AddRootParam(2, XIIlib::CBV);

	plData->Init();

	pipelineSet.rootsignature = plData->GetRootSignature();
	pipelineSet.pipelinestate = plData->GetPipelineState();

	delete plData;
}

void Object3D::PreDraw()
{
	// PreDraw��PostDraw���y�A�ŌĂ΂�Ă��Ȃ���΃G���[
	assert(Object3D::cmdList == nullptr);

	// �R�}���h���X�g���Z�b�g
	Object3D::cmdList = DirectX12::GetCmdList();

	// �v���~�e�B�u�`���ݒ�
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Object3D::PostDraw()
{
	// �R�}���h���X�g������
	Object3D::cmdList = nullptr;
}

Object3D* Object3D::Create(Model* model, float elec_is)
{
	// 3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	Object3D* object3D = new Object3D();
	if (object3D == nullptr)
	{return nullptr;}

	// ������
	if (!object3D->Initialize())
	{
		delete object3D;
		assert(0);
	}

	object3D->SetShaderType(elec_is);

	if (model)
	{object3D->SetModel(model);}

	return object3D;
}

Object3D::~Object3D()
{
}

bool Object3D::Initialize()
{
	// nullptr�`�F�b�N
	assert(device);

	HRESULT result;

	// �N���X���̕�������擾
	name = typeid(*this).name();

	// �萔�o�b�t�@�̐���
	result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), 	// �A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB0) + 0xff)&~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffB0));

	return true;
}

void Object3D::Update()
{
	HRESULT result;
	
	// �s��̍X�V
	UpdateWorldMatrix();

	Math::Matrix4 myViewProjection = d_camera->GetMyView() * d_camera->GetMyProjection();

	Math::Matrix4 my_lightTran = Math::Matrix4();
	my_lightTran = Math::Translation(lightGroup->GetLightPos().x, lightGroup->GetLightPos().y, lightGroup->GetLightPos().z);

	Math::Matrix4 m_my = Math::Matrix4();
	m_my = Math::RotX(Math::ConvertToRadians(90.0f));
	m_my = m_my * my_lightTran;

	Math::Matrix4 my_lightView = m_my;
	my_lightView.Inverse();

	shaderTimer += (1.0f / 60.0f);
	if (shaderTimer > 1.0f) {
		shaderTimer = 0.0f;
	}

	// �萔�o�b�t�@�փf�[�^�]��
	ConstBufferDataB0* constMap = nullptr;
	result = constBuffB0->Map(0, nullptr, (void**)&constMap);
	//constMap->mat = matWorld * matViewProjection;	// �s��̍���
	constMap->color = { color.x,color.y,color.z,alpha };
	constMap->viewproj = myViewProjection;
	constMap->world = myWorld;
	constMap->cameraPos = Math::Vector3(d_camera->GetPos_X(), d_camera->GetPos_Y(), d_camera->GetPos_Z());
	constMap->lightpos = Math::Vector4(lightGroup->GetLightPos().x, lightGroup->GetLightPos().y, lightGroup->GetLightPos().z, 1);
	//constMap->wlp = XMMatrixTranspose(matWorld * m_lightView * matProjection);
	Math::Matrix4 wlp = myWorld * my_lightView * myViewProjection;
	wlp.Transposed();
	constMap->wlp = wlp;

	constMap->_time = shaderTimer;
	constMap->isElec = _isElec;

	Math::Matrix4 mClip;
	mClip.r[0].r[0] = 0.5;
	mClip.r[1].r[1] = -0.5;
	mClip.r[2].r[2] = 1;
	mClip.r[3].r[0] = 0.5;
	mClip.r[3].r[1] = 0.5;
	mClip.r[3].r[3] = 1;
	wlp = myWorld * my_lightView * myViewProjection * mClip;
	wlp.Transposed();

	constMap->wlpt = wlp;
	constBuffB0->Unmap(0, nullptr);

}

void Object3D::Draw()
{
	// nullptr�`�F�b�N
	assert(Object3D::cmdList);

	// ���f���̊��蓖�Ă��Ȃ���Ε`�悵�Ȃ�
	if (model == nullptr) {
		return;
	}

	// �p�C�v���C���X�e�[�g�̐ݒ�
	cmdList->SetPipelineState(pipelineSet.pipelinestate.Get());
	// ���[�g�V�O�l�`���̐ݒ�
	cmdList->SetGraphicsRootSignature(pipelineSet.rootsignature.Get());
	// �萔�o�b�t�@�r���[���Z�b�g
	cmdList->SetGraphicsRootConstantBufferView(0, constBuffB0->GetGPUVirtualAddress());
	//// ���C�g�̕`��
	lightGroup->Draw(cmdList, 3);
	// ���f���`��
	model->Draw();
}

void Object3D::UpdateWorldMatrix()
{
	assert(d_camera);

	// �X�P�[���A��]�A���s�ړ��s��̌v�Z
	Math::Matrix4 myScale, myRot, myTrans;
	myScale = Math::Scaling(scale.x, scale.y, scale.z);
	myRot.Identity();
	myRot *= Math::RotZ(rotation.z);
	myRot *= Math::RotX(rotation.x);
	myRot *= Math::RotY(rotation.y);
	myTrans = Math::Translation(position.x, position.y, position.z);

	// ���[���h�s��̍���
	if (isBillboard && d_camera) {
		const Math::Matrix4& myBillboard = d_camera->GetMyBillboard();

		myWorld.Identity();
		myWorld *= myScale;
		myWorld *= myRot;
		myWorld *= myBillboard;
		myWorld *= myTrans;
	}
	else {
		myWorld.Identity();
		myWorld *= myScale;
		myWorld *= myRot;
		myWorld *= myTrans;
	}

	// �e�I�u�W�F�N�g�������
	if (parent != nullptr) {
		// �e�I�u�W�F�N�g�̃��[���h�s����|����
		myWorld *= parent->myWorld;
	}
}