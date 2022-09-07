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

	// グラフィックパイプラインの生成
	CreateGraphicsPipeline();

	// モデルの静的初期化
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
	// PreDrawとPostDrawがペアで呼ばれていなければエラー
	assert(Object3D::cmdList == nullptr);

	// コマンドリストをセット
	Object3D::cmdList = DirectX12::GetCmdList();

	// プリミティブ形状を設定
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Object3D::PostDraw()
{
	// コマンドリストを解除
	Object3D::cmdList = nullptr;
}

Object3D* Object3D::Create(Model* model, float elec_is)
{
	// 3Dオブジェクトのインスタンスを生成
	Object3D* object3D = new Object3D();
	if (object3D == nullptr)
	{return nullptr;}

	// 初期化
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
	// nullptrチェック
	assert(device);

	HRESULT result;

	// クラス名の文字列を取得
	name = typeid(*this).name();

	// 定数バッファの生成
	result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), 	// アップロード可能
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
	
	// 行列の更新
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

	// 定数バッファへデータ転送
	ConstBufferDataB0* constMap = nullptr;
	result = constBuffB0->Map(0, nullptr, (void**)&constMap);
	//constMap->mat = matWorld * matViewProjection;	// 行列の合成
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
	// nullptrチェック
	assert(Object3D::cmdList);

	// モデルの割り当てがなければ描画しない
	if (model == nullptr) {
		return;
	}

	// パイプラインステートの設定
	cmdList->SetPipelineState(pipelineSet.pipelinestate.Get());
	// ルートシグネチャの設定
	cmdList->SetGraphicsRootSignature(pipelineSet.rootsignature.Get());
	// 定数バッファビューをセット
	cmdList->SetGraphicsRootConstantBufferView(0, constBuffB0->GetGPUVirtualAddress());
	//// ライトの描画
	lightGroup->Draw(cmdList, 3);
	// モデル描画
	model->Draw();
}

void Object3D::UpdateWorldMatrix()
{
	assert(d_camera);

	// スケール、回転、平行移動行列の計算
	Math::Matrix4 myScale, myRot, myTrans;
	myScale = Math::Scaling(scale.x, scale.y, scale.z);
	myRot.Identity();
	myRot *= Math::RotZ(rotation.z);
	myRot *= Math::RotX(rotation.x);
	myRot *= Math::RotY(rotation.y);
	myTrans = Math::Translation(position.x, position.y, position.z);

	// ワールド行列の合成
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

	// 親オブジェクトがあれば
	if (parent != nullptr) {
		// 親オブジェクトのワールド行列を掛ける
		myWorld *= parent->myWorld;
	}
}