#include "WallHit.h"

#include "../../../Lib/AssetManager/AssetManager.h"

void WallHit::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model);
}

void WallHit::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/wall_hit.gltf");

	// 当たり判定用のコライダーを作成
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("StageCollision", m_model, KdCollider::TypeGround);
}
