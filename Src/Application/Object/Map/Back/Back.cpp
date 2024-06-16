#include "Back.h"

#include "../../../Lib/AssetManager/AssetManager.h"

void Back::Update()
{
	Math::Matrix rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	Math::Matrix trasnMat = Math::Matrix::CreateTranslation(100.0f, 0.0f, 100.0f);
	m_world = rotX * trasnMat;
}

void Back::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world);
}

void Back::Init()
{
	m_polygon = AssetManager::Instance().GetMaterial("back");
	m_polygon.SetScale(1000.0f);
}
