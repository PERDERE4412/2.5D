#include "Fade.h"

#include "../Lib/AssetManager/AssetManager.h"
#include "../Map/MapManager.h"
#include "../Movie/Movie.h"

void Fade::Update()
{
	if (m_bFade)UpdateMapChange(m_type);

	m_color = { 1,1,1,m_alpha };
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
	else if(!m_bInOut)
	{
		m_alpha -= m_addAlpha;

		if (m_alpha < 0.0f)
		{
			m_bFade = false;
			m_alpha = 0.0f;
			if (Movie::Instance().GetMovie())Movie::Instance().StartMovie();
		}
	}	
}

void Fade::BootChangeMap(std::string _type)
{
	m_bFade = true;
	m_bInOut = true;
	m_type = _type;
}

void Fade::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_blackTex, 0, 0, m_rect.width, m_rect.height, &m_rect, &m_color);
}

void Fade::Init()
{
	m_blackTex = AssetManager::Instance().GetTex("black");
	m_rect = { 0,0,(int)m_blackTex->GetWidth(),(int)m_blackTex->GetHeight() };

	m_alpha = 0.0f;
	m_addAlpha = 0.015f;
	m_color = { 1,1,1,m_alpha };

	m_bFade = false;
}