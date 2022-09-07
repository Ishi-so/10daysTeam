#include "DebugCamera.h"
#include "../Base/WindowsApp.h"

// コンストラクタ
DebugCamera::DebugCamera(){}
// デストラクタ
DebugCamera::~DebugCamera(){}
// 初期化
void DebugCamera::_Initialize(float lookatrange, float rotaterad, float moverange)
{
	data.phi = Math::ConvertToRadians(-90.0f);

	this->lookatrange = lookatrange;
	this->rotaterad = rotaterad;
	this->moverange = moverange;

	range = 0.0f;

	data.rad = 0.0f;
	data.position = { 0.0f, 0.0f, 0.0f };
	data.lookat = { 0,2.5f,0 };

	// 視点座標
	eye.x = data.position.x;
	eye.y = data.position.y;
	eye.z = data.position.z;
	// 注視点座標
	target.x = data.lookat.x;
	target.y = data.lookat.y;
	target.z = data.lookat.z;

	// 上方向ベクトル
	up = { 0.0f, 1.0f, 0.0f };

	myView = Math::MatrixLookAtLH(eye,target,up);

	//myView.Transposed();

	c_fov = 60.0f;
	c_near = 0.1f;
	c_far = 1000.0f;

	myProjection = Math::MatrixPerspectiveFovLH(Math::ConvertToRadians(c_fov),
		(float)(WindowsApp::window_width / WindowsApp::window_height), c_near, c_far);
}

void DebugCamera::MyMatrixUpdate()
{
	//myView = Math::MatrixLookAtLH(eye, target, up);

	myProjection = Math::MatrixPerspectiveFovLH(Math::ConvertToRadians(c_fov),
		(float)(WindowsApp::window_width / WindowsApp::window_height), c_near, c_far);

	Math::Vector3 cameraAxisZ = target - eye;
	cameraAxisZ.normalize();

	Math::Vector3 cameraAxisX = up.cross(cameraAxisZ);
	cameraAxisX.normalize();

	Math::Vector3 cameraAxisY = cameraAxisZ.cross(cameraAxisX);
	cameraAxisY.normalize();

	Math::Matrix4 myCameraRot;
	myCameraRot.r[0] = Math::VECTOR(cameraAxisX);
	myCameraRot.r[1] = Math::VECTOR(cameraAxisY);
	myCameraRot.r[2] = Math::VECTOR(cameraAxisZ);
	myCameraRot.r[3] = Math::VECTOR(0,0,0,1);

	myCameraRot.Transposed();
	myView = myCameraRot;

	Math::Vector3 reverseEyePosition = eye * -1.0f;
	myView.r[3] = Math::VECTOR(
		cameraAxisX.dot(reverseEyePosition),
		cameraAxisY.dot(reverseEyePosition),
		cameraAxisZ.dot(reverseEyePosition),1.0f
	);

	// ビルボード行列
	myBillboard.r[0] = cameraAxisX;
	myBillboard.r[1] = cameraAxisY;
	myBillboard.r[2] = cameraAxisZ;
	myBillboard.r[3] = Math::VECTOR();

	// カメラX軸,Y軸,Z軸
	Math::VECTOR ybillCameraAxisX, ybillCameraAxisY, ybillCameraAxisZ;

	// X軸は共通
	ybillCameraAxisX = cameraAxisX;
	// Y軸はワールド座標系のY軸
	ybillCameraAxisY = Math::VECTOR(Math::Vector3(up).normalize());
	// Z軸はX軸→Y軸の外積で求まる
	ybillCameraAxisZ = Math::CrossVector(ybillCameraAxisX,ybillCameraAxisY);

	// Y軸回りビルボード行列
	myBillboardY.r[0] = ybillCameraAxisX;
	myBillboardY.r[1] = ybillCameraAxisY;
	myBillboardY.r[2] = ybillCameraAxisZ;
	myBillboardY.r[3] = Math::VECTOR();
}

void DebugCamera::_Update()
{
	// 視点座標
	eye.x = data.position.x;
	eye.y = data.position.y;
	eye.z = data.position.z;
	// 注視点座標
	target.x = data.lookat.x;
	target.y = data.lookat.y;
	target.z = data.lookat.z;

	MyMatrixUpdate();
}

void DebugCamera::SetPhi(float s_phi)
{
	data.phi = s_phi;
}

void DebugCamera::SetAdderPhi(float adder_phi)
{
	data.phi += adder_phi;
}

void DebugCamera::SetTheta(float s_theta)
{
	data.theta = s_theta;
}

void DebugCamera::SetAdderTheta(float adder_theta)
{
	data.theta += adder_theta;
}

void DebugCamera::SetLookAtRange(float s_lookat_x,float s_lookat_y, float s_lookat_z)
{
	data.lookat = Math::Vector3(s_lookat_x,s_lookat_y,s_lookat_z);
}

void DebugCamera::SetAdderLookAt(float adder_lookat_x, float adder_lookat_y, float adder_lookat_z)
{
	data.lookat += Math::Vector3(adder_lookat_x, adder_lookat_y, adder_lookat_z);
}

void DebugCamera::SetPosition(float s_pos_x, float s_pos_y, float s_pos_z)
{
	data.position = Math::Vector3(s_pos_x, s_pos_y, s_pos_z);
}

void DebugCamera::SetMoveRange(float move_range)
{
	moverange = move_range;
}

void DebugCamera::SetAt(float s_at_x, float s_at_y, float s_at_z)
{
	at = Math::Vector3(s_at_x, s_at_y, s_at_z);
}

void DebugCamera::SetUpVector(float x, float y, float z)
{
	up = { x,y,z };
}

float DebugCamera::GetRotaterad()
{
	return rotaterad;
}