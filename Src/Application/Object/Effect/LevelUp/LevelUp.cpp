#include "LevelUp.h"

#include "../../../Object/Chara/Player/Player.h"

void LevelUp::PostUpdate()
{
	m_adjustPos.y += m_addAdjust;
	if (m_adjustPos.y > 4.0f)
	{
		m_adjustPos.y = 4.0f;
		m_alpha += m_addAlpha;
		if (m_alpha <= 0.0f)m_isExpired = true;
	}

	m_color.w = m_alpha;

	m_pos = m_player.lock()->GetPos() + m_adjustPos;

	// 行列作成
	Math::Matrix rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	m_world = rotX * Math::Matrix::CreateTranslation(m_pos);
}

void LevelUp::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world, m_color);
}

void LevelUp::Init()
{
	m_polygon = AssetManager::Instance().GetMaterial("levelUp");

	m_pos = {};
	m_alpha = 1.0f;
	m_addAlpha = -0.03f;
	m_color = { 1,1,1,m_alpha };

	m_adjustPos = {};
	m_addAdjust = 0.1f;

	m_animeCnt = 0.0f;
	m_animeSpeed = 0.0f;

	KdAudioManager::Instance().Play("Asset/Sounds/levelUp.wav", false, 0.1f);
}
