#include "LevelBar.h"

#include "../../../Data/Status/Player/PlayerStatus.h"

void LevelBar::Update()
{
	int level = 0;
	// レベル表示
	// 現在のレベルを取得
	if (!m_status.expired())
	{
		level = m_status.lock()->GetValue("LEVEL");
	}

	int digit[NUM] = { 0,0 };
	if (level > 9)
	{
		digit[0] = level / 10;
		digit[1] = level % 10;
	}
	else
	{
		digit[1] = level;
	}
	for (int i = 0; i < NUM; i++)m_value[i].rect.x = 8 * digit[i];

	// 経験値バー
	// テクスチャの幅を取得
	int w = m_bar.pTex->GetWidth();
	// 経験値１の時に幅いくつの領域を表示するのか
	int nextExp, exp;
	if (!m_status.expired())
	{
		float singleW = (float)w / m_status.lock()->GetValue("NEXTEXP");
		m_bar.rect.width = (long)(singleW * m_status.lock()->GetValue("EXP"));
	}
}

void LevelBar::DrawSprite()
{
	// 数値
	for (int i = 0; i < NUM; i++)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_value[i].pTex, (int)m_value[i].pos.x, (int)m_value[i].pos.y, m_value[i].rect.width * 2.5,m_value[i].rect.height*2.5, &m_value[i].rect);
	}

	// フレーム
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_frame.pTex, (int)m_frame.pos.x, (int)m_frame.pos.y, m_frame.pTex->GetWidth(), m_frame.pTex->GetHeight(), &m_frame.rect);

	// バー
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_bar.pTex, (int)m_bar.pos.x, (int)m_bar.pos.y,m_bar.rect.width, m_bar.rect.height, &m_bar.rect,nullptr,{0.0f,0.5f});

	// レベル
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_level.pTex, m_level.pos.x, m_level.pos.y);
}

void LevelBar::Init()
{
	// 数値
	for (int i = 0; i < NUM; i++)
	{
		m_value[i].pTex = AssetManager::Instance().GetTex("number");
		m_value[i].pos = { -520.0f + 24.0f * i,-157.0f };
		m_value[i].rect = { 0,0,(int)m_value[i].pTex->GetWidth() / 10,(int)m_value[i].pTex->GetHeight() };
	}

	// フレーム
	m_frame.pTex = AssetManager::Instance().GetTex("levelFrame");
	m_frame.pos = { -450.0f,-200.0f };
	m_frame.rect = { 0,0,(int)m_frame.pTex->GetWidth(),(int)m_frame.pTex->GetHeight() };

	// バー
	m_bar.pTex = AssetManager::Instance().GetTex("levelBar");
	m_bar.pos = { -597.0f,-200.0f };
	m_bar.rect = { 0,0,(int)m_bar.pTex->GetWidth(),(int)m_bar.pTex->GetHeight() };

	// レベル
	m_level.pTex = AssetManager::Instance().GetTex("level");
	m_level.pos = { -550,-156 };
}