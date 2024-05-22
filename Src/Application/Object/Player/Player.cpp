#include "Player.h"

#include "../../Debug/ImGuiManager.h"

#include "../../Lib/Utility.h"
#include "../../Status/Status.h"

void Player::Update()
{
	// 方向ベクトルの作成
	Math::Vector3 moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState('W') & 0x8000)moveVec.z = 1.0f;
	if (GetAsyncKeyState('A') & 0x8000)moveVec.x = -1.0f;
	if (GetAsyncKeyState('S') & 0x8000)moveVec.z = -1.0f;
	if (GetAsyncKeyState('D') & 0x8000)moveVec.x = 1.0f;

	moveVec.Normalize();	// 正規化
	moveVec *= MOVE_POW;
	m_pos += moveVec;

	// 壁との当たり判定
	if (m_pos.x > Screen::MapMaxX)m_pos.x = Screen::MapMaxX;
	if (m_pos.x < Screen::MapMinX)m_pos.x = Screen::MapMinX;
	if (m_pos.z > Screen::MapMaxZ)m_pos.z = Screen::MapMaxZ;
	if (m_pos.z < Screen::MapMinZ)m_pos.z = Screen::MapMinZ;

	m_world = Math::Matrix::CreateTranslation(m_pos);

	// デバッグ
	ImGuiManager::Instance().SetPlayerPos(m_pos);
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_player, m_world);
}

void Player::Init()
{
	m_objType = ObjType::Player;

	// ステータス
	m_pStatus = std::make_shared<Status>();
	m_pStatus->Init(100, 100, 10, 10);

	// 本体
	m_player.Load("Asset/Models/human.gltf");
	m_pos = {};
	m_world = Math::Matrix::CreateTranslation(m_pos);
}
