#include "Player.h"

#include "../../Status/Status.h"

void Player::Update()
{
	Math::Vector3 moveVec = Math::Vector3::Zero;

	if (GetAsyncKeyState('U') & 0x8000)m_pos.y += 0.1f;

	if (GetAsyncKeyState('W') & 0x8000)moveVec.z = 1.0f;
	if (GetAsyncKeyState('A') & 0x8000)moveVec.x = -1.0f;
	if (GetAsyncKeyState('S') & 0x8000)moveVec.z = -1.0f;
	if (GetAsyncKeyState('D') & 0x8000)moveVec.x = 1.0f;

	moveVec.Normalize();
	moveVec *= MOVE_POW;
	m_pos += moveVec;

	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = m_scaleMat * m_transMat;
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_player, m_mWorld);
}

void Player::Init()
{
	m_objType = ObjType::Player;

	// ステータス
	m_pStatus = std::make_shared<Status>();
	m_pStatus->Init(100, 100, 10, 10);

	// 本体
	m_player.Load("Asset/Models/human.gltf");
	m_scaleMat = Math::Matrix::CreateScale(0.5f, 0.5f, 0.5f);
	m_pos = {};
	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = m_scaleMat * m_transMat;
}
