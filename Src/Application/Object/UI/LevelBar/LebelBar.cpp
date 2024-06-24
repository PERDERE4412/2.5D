#include "LevelBar.h"

#include "../../../Data/Status/Player/PlayerStatus.h"
#include "../../Chara/Player/Player.h"

void LevelBar::Update()
{
	// レベル表示
	// 現在のレベルを取得
	int level = m_player.lock()->GetStatus()->GetValue("LEVEL");

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
	for (int i = 0; i < NUM; i++)m_level[i].rect.x = 8 * digit[i];

	// 経験値バー
	// テクスチャの幅を取得
	int w = m_bar.pTex->GetWidth();
	// 経験値１の時に幅いくつの領域を表示するのか
	float singleW = (float)w / m_player.lock()->GetStatus()->GetValue("NEXTEXP");
	m_bar.rect.width = (long)(singleW * m_player.lock()->GetStatus()->GetValue("EXP"));
}

void LevelBar::DrawSprite()
{
	// レベル
	for (int i = 0; i < NUM; i++)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_level[i].pTex, (int)m_level[i].pos.x, (int)m_level[i].pos.y, m_level[i].rect.width * 2,m_level[i].rect.height*2, &m_level[i].rect);
	}

	// フレーム
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_frame.pTex, (int)m_frame.pos.x, (int)m_frame.pos.y, m_frame.pTex->GetWidth(), m_frame.pTex->GetHeight(), &m_frame.rect);

	// バー
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_bar.pTex, (int)m_bar.pos.x, (int)m_bar.pos.y,m_bar.rect.width, m_bar.rect.height, &m_bar.rect,nullptr,{0.0f,0.5f});
}

void LevelBar::Init()
{
	// レベル
	for (int i = 0; i < NUM; i++)
	{
		m_level[i].pTex = AssetManager::Instance().GetTex("number");
		m_level[i].pos = { -550.0f + 16.0f * i,-160.0f };
		m_level[i].rect = { 0,0,(int)m_level[i].pTex->GetWidth() / 10,(int)m_level[i].pTex->GetHeight() };
	}

	// フレーム
	m_frame.pTex = AssetManager::Instance().GetTex("levelFrame");
	m_frame.pos = { -450.0f,-200.0f };
	m_frame.rect = { 0,0,(int)m_frame.pTex->GetWidth(),(int)m_frame.pTex->GetHeight() };

	// バー
	m_bar.pTex = AssetManager::Instance().GetTex("levelBar");
	m_bar.pos = { -597.0f,-200.0f };
	m_bar.rect = { 0,0,(int)m_bar.pTex->GetWidth(),(int)m_bar.pTex->GetHeight() };
}