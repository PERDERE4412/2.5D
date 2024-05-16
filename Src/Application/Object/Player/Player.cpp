#include "Player.h"

#include "../../Status/Status.h"

void Player::Update()
{

}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_player,m_mat);
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
	m_transMat = Math::Matrix::CreateTranslation(0, 0, 0);
	m_mat = m_scaleMat * m_transMat;
}
