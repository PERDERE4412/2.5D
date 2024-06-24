#include "StageClear.h"

#include "../../../Fade/Fade.h"

void StageClear::Update()
{
	m_alpha += m_addAlpha;
	if (m_alpha > 1.0f)
	{
		m_alpha = 1.0f;
		m_bAlpha = true;
	}

	if (m_bAlpha)
	{
		m_wait--;
		if (m_wait <= 0)
		{
			Fade::Instance().BootChangeTitle();
		}
	}

	m_color.w = m_alpha;
}

void StageClear::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pTex, 0.0f, 100.0f,nullptr,&m_color);
}

void StageClear::Init()
{
	m_pTex = AssetManager::Instance().GetTex("clear");

	m_alpha = 0.0f;
	m_addAlpha = 0.01f;
	m_color = { 1,1,1,m_alpha };

	m_bAlpha = false;
	m_wait = 180;

	KdAudioManager::Instance().StopAllSound();
	KdAudioManager::Instance().Play("Asset/Sounds/clear.wav", false, 0.2f);
}
