#include "Gold.h"

#include "../../../Lib/AssetManager/AssetManager.h"
#include "../../../Data/Item/Item.h"

void Gold::Update()
{
	// 数字(仮 後に変更)
	int digit[NUM] = { 0,0,0 };
	if (m_currentGold >= 100)
	{
		digit[0] = m_currentGold / 100;
		digit[1] = (m_currentGold / 10) % 10;
		digit[2] = m_currentGold % 10;
	}
	else if (m_currentGold >= 10)
	{
		digit[1] = m_currentGold / 10;
		digit[2] = m_currentGold % 10;
	}
	else
	{
		digit[2] = m_currentGold;
	}

	m_number[0].rect = { 8 * digit[0],0,8,8 };
	m_number[1].rect = { 8 * digit[1],0,8,8 };
	m_number[2].rect = { 8 * digit[2],0,8,8 };

	if (m_currentGold > Item::Instance().GetGold())m_currentGold--;
	else if (m_currentGold < Item::Instance().GetGold())m_currentGold++;
}

void Gold::DrawSprite()
{
	// ゴールド
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_gold.mat);
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_gold.pTex, 0, 0, m_gold.pTex->GetWidth(), m_gold.pTex->GetHeight(), &m_gold.rect);

	// 数字
	for (int i = 0; i < NUM; i++)
	{
		KdShaderManager::Instance().m_spriteShader.SetMatrix(m_number[i].mat);
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_number[i].pTex, 0, 0, 8, 8, &m_number[i].rect);
	}
}

void Gold::Init()
{
	// ゴールド
	m_gold.pTex = AssetManager::Instance().GetTex("gold");
	m_gold.pos = { -550.0f,-250.0f,0.0f };
	m_gold.mat = Math::Matrix::CreateTranslation(m_gold.pos);
	m_gold.rect = { 0,0,(int)m_gold.pTex->GetWidth(),(int)m_gold.pTex->GetHeight() };

	// 数字
	for (int i = 0; i < NUM; i++)
	{
		m_number[i].pTex = AssetManager::Instance().GetTex("number");
		m_number[i].pos = { -530.0f + 10.0f * i,-250.0f,0.0f };
		m_number[i].mat = Math::Matrix::CreateTranslation(m_number[i].pos);
		m_number[i].rect = { 0,0,8,8 };
	}

	m_currentGold = 0;
}
