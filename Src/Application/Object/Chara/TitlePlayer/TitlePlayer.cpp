#include "TitlePlayer.h"

void TitlePlayer::PostUpdate()
{
	Math::Matrix rotX=Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(40));
	Math::Matrix scaleMat=Math::Matrix::CreateScale(3.0f);
	Math::Matrix transMat=Math::Matrix::CreateTranslation({ -9.5f, 0.0f, 38.9f });
	m_world = scaleMat * rotX * transMat;
}

void TitlePlayer::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world);
}

void TitlePlayer::Init()
{
	m_polygon = AssetManager::Instance().GetMaterial("playerIdle");
	m_polygon.SetUVRect(2);

	m_world = Math::Matrix::CreateTranslation({ -8.5f, 0.0f, 48.9f });
}
