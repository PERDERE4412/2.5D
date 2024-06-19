#include "LichBulletExp.h"

#include "../../../../Lib/AssetManager/AssetManager.h"

void LichBulletExp::Update()
{
	m_animeCnt += m_animeSpeed;
	if (int(m_animeCnt) > (int)m_polygon.GetSplitX() - 1)
	{
		m_isExpired = true;
	}

	m_polygon.SetUVRect(int(m_animeCnt));
}

void LichBulletExp::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world);
}

void LichBulletExp::DrawBright()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world);
}

void LichBulletExp::SetPos(Math::Vector3 _pos)
{
	m_world = Math::Matrix::CreateTranslation(_pos);
}

void LichBulletExp::Init()
{
	m_polygon = AssetManager::Instance().GetMaterial("lichBulletExp");
	m_polygon.SetUVRect(0);

	m_animeCnt = 0.0f;
	m_animeSpeed = 0.3f;
}
