#include "PlayerHp.h"

void PlayerHp::Update()
{
}

void PlayerHp::DrawSprite()
{
	// フレーム
	//KdShaderManager::Instance().m_spriteShader.SetMatrix(m_frame.mat);
	//KdShaderManager::Instance().m_spriteShader.DrawTex(&m_frame.tex, 0, 0, 308, 42, &m_frame.rect);
}

void PlayerHp::Init()
{
	// フレーム
	m_frame.tex.Load("Asset/Textures/hp.png");
	m_frame.mat = Math::Matrix::CreateTranslation(-450.0f, -300.0f, 0.0f);
	m_frame.rect = { 0,0,308,42 };
}
