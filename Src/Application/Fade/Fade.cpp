#include "Fade.h"

#include "../Map/MapManager.h"
#include "../Movie/Movie.h"

void Fade::Update()
{
	if (m_bMapFade)UpdateMapChange(m_type);

	if (m_bTitleFade)UpdateTitleChange();

	if (m_bGameFade)UpdateGameChange();

	m_color.w = m_alpha;
}

void Fade::UpdateMapChange(std::string _type)
{
	if (m_bInOut)
	{
		m_alpha += m_addAlpha;

		if (m_alpha > 1.0f)
		{
			m_bInOut = false;
			m_alpha = 1.0f;
			MapManager::Instance().SetPlayerPos(_type);
			MapManager::Instance().ChangeMap(_type);
		}
	}
	else if (!m_bInOut)
	{
		m_alpha -= m_addAlpha;

		if (m_alpha < 0.0f)
		{
			m_bMapFade = false;
			m_alpha = 0.0f;
			if (Movie::Instance().GetMovie())Movie::Instance().StartMovie();
		}
	}
}

void Fade::UpdateTitleChange()
{
	if (m_bInOut)
	{
		m_alpha += m_addAlpha;

		if (m_alpha > 1.0f)
		{
			m_bInOut = false;
			m_alpha = 1.0f;
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
		}
	}
	else if (!m_bInOut)
	{
		m_alpha -= m_addAlpha;

		if (m_alpha < 0.0f)
		{
			m_bTitleFade = false;
			m_alpha = 0.0f;
		}
	}
}

void Fade::UpdateGameChange()
{
	if (m_bInOut)
	{
		m_alpha += m_addAlpha;

		if (m_alpha > 1.0f)
		{
			m_bInOut = false;
			m_alpha = 1.0f;
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
		}
	}
	else if (!m_bInOut)
	{
		m_alpha -= m_addAlpha;

		if (m_alpha < 0.0f)
		{
			m_bGameFade = false;
			m_alpha = 0.0f;
		}
	}
}

void Fade::BootChangeMap(std::string _type)
{
	m_bMapFade = true;
	m_bInOut = true;
	m_type = _type;
	m_pTex = AssetManager::Instance().GetTex("black");
}

void Fade::BootChangeTitle()
{
	m_bTitleFade = true;
	m_bInOut = true;
	m_pTex = AssetManager::Instance().GetTex("white");
	m_addAlpha = 0.01f;
	KdAudioManager::Instance().StopAllSound();
}

void Fade::BootChangeGame()
{
	m_bGameFade = true;
	m_bInOut = true;
	m_pTex = AssetManager::Instance().GetTex("black");
	m_addAlpha = 0.015f;
}

bool Fade::GetMapFade()
{
	bool fade = false;
	if (m_bMapFade)fade = true;
	return fade;
}

bool Fade::GetGameFade()
{
	bool fade = false;
	if (m_bGameFade)fade = true;
	return fade;
}

void Fade::DrawSprite()
{
	if (!m_bMapFade && !m_bTitleFade && !m_bGameFade)return;

	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pTex, 0, 0, m_pTex->GetWidth(), m_pTex->GetHeight(), nullptr, &m_color);
}

void Fade::Init()
{
	m_alpha = 0.0f;

	m_color = { 1,1,1,m_alpha };

	m_bMapFade = false;
	m_bTitleFade = false;
	m_bGameFade = false;
}