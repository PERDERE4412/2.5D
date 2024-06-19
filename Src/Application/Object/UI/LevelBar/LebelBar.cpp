#include "LevelBar.h"

#include "../../../Lib/AssetManager/AssetManager.h"
#include "../../../Data/Status/Player/PlayerStatus.h"

void LevelBar::Update()
{
	// レベル表示
	// 現在のレベルを取得
	int level = PlayerStatus::Instance().GetValue("LEVEL");

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
	// 経験値・次のレベルまでの経験値を取得
	int exp = PlayerStatus::Instance().GetValue("EXP");
	int nextExp = PlayerStatus::Instance().GetValue("NEXTEXP");

	// 切り取り範囲の変更
	rectX = (int)(m_bar.pTex->GetWidth() * ((float)exp / nextExp));
	m_bar.rect.width = rectX;

	// 座標の移動
	m_bar.pos.x = -450.0f - 147.0f * (1 - (float)exp / nextExp);
}

void LevelBar::DrawSprite()
{
	// レベル
	for (int i = 0; i < NUM; i++)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_level[i].pTex, (int)m_level[i].pos.x, (int)m_level[i].pos.y, m_level[i].pTex->GetWidth() / 10, m_level[i].pTex->GetHeight(), &m_level[i].rect);
	}

	// フレーム
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_frame.pTex, (int)m_frame.pos.x, (int)m_frame.pos.y, m_frame.pTex->GetWidth(), m_frame.pTex->GetHeight(), &m_frame.rect);

	// バー
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_bar.pTex, (int)m_bar.pos.x, (int)m_bar.pos.y, rectX, m_bar.pTex->GetHeight(), &m_bar.rect);
}

void LevelBar::Init()
{
	// レベル
	for (int i = 0; i < NUM; i++)
	{
		m_level[i].pTex = AssetManager::Instance().GetTex("number");
		m_level[i].pos = { -550.0f + 12.0f * i,-160.0f };
		m_level[i].rect = { 0,0,(int)m_level[i].pTex->GetWidth() / 10,(int)m_level[i].pTex->GetHeight() };
	}

	// フレーム
	m_frame.pTex = AssetManager::Instance().GetTex("levelFrame");
	m_frame.pos = { -450.0f,-200.0f };
	m_frame.rect = { 0,0,(int)m_frame.pTex->GetWidth(),(int)m_frame.pTex->GetHeight() };

	// バー
	m_bar.pTex = AssetManager::Instance().GetTex("levelBar");
	m_bar.pos = { -450.0f,-200.0f };
	m_bar.rect = { 0,0,(int)m_bar.pTex->GetWidth(),(int)m_bar.pTex->GetHeight() };
}