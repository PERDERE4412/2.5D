#include "Heal.h"
#include "../../Chara/Player/Player.h"

void Heal::PostUpdate()
{
	// アニメーション
	m_animeCnt += m_animeSpeed;

	if ((int)m_animeCnt > (int)(m_polygon.GetSplitX() - 1))
	{
		m_isExpired = true;
	}

	m_polygon.SetUVRect((int)m_animeCnt);

	// 行列作成
	Math::Matrix rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	m_world = rotX * Math::Matrix::CreateTranslation(m_player.lock()->GetPos());
}

void Heal::Init()
{
	m_polygon = AssetManager::Instance().GetMaterial("heal");

	m_animeCnt = 0.0f;
	m_animeSpeed = 0.2f;
}
