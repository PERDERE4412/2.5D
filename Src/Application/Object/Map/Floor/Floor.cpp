#include "Floor.h"

void Floor::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model);
}

void Floor::Init()
{
	m_model = AssetManager::Instance().GetModel("floor");
}
