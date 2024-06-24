#include "Title.h"

void Title::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pTex,245,140);
}

void Title::Init()
{
	m_pTex = AssetManager::Instance().GetTex("title");
}
