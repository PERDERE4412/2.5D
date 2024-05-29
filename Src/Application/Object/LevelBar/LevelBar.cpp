#include "LevelBar.h"

#include "../../Lib/AssetManager/AssetManager.h"
#include "../../Data/Status/PlayerStatus.h"

void LevelBar::Update()
{
	// レベル表示
	// 現在のレベルを取得
	int level = PlayerStatus::Instance().GetValue("LEVEL");

	int digit[NUM] = { 0,0 };
	if (level > 9)
	{
		digit[0]=level/10;
		digit[1]=level%10;
	}
	else
	{
		digit[1] = level;
	}
	for (int i = 0; i < NUM; i++)m_level[i].rect = { digit[i]*8,0,8,8};

	// 経験値バー
	// 経験値・次のレベルまでの経験値を取得
	int exp = PlayerStatus::Instance().GetValue("EXP");
	int nextExp = PlayerStatus::Instance().GetValue("NEXTEXP");

	// サイズ変更
	m_bar.size = { (float)exp / nextExp,1.0f,1.0f };

	// 座標をずらす
	m_bar.pos.x = -450.0f - 147.0f * (1 - (float)exp / nextExp);

	// 行列作成
	Math::Matrix scaleMat = Math::Matrix::CreateScale(m_bar.size);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_bar.pos);
	m_bar.mat = scaleMat * transMat;
}

void LevelBar::DrawSprite()
{
	// レベル
	for (int i = 0; i < NUM; i++)
	{
		KdShaderManager::Instance().m_spriteShader.SetMatrix(m_level[i].mat);
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_level[i].pTex, 0, 0, m_level[i].width, m_level[i].height, &m_level[i].rect);
	}

	// フレーム
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_frame.mat);
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_frame.pTex, 0, 0, m_frame.width, m_frame.height, &m_frame.rect);

	// バー
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_bar.mat);
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_bar.pTex, 0, 0, m_bar.width, m_bar.height, &m_bar.rect);
}

void LevelBar::Init()
{
	// レベル
	for (int i = 0; i < NUM; i++)
	{
		m_level[i].pTex = AssetManager::Instance().GetTex("number");
		m_level[i].pos = { -550.0f+12.0f*i,-160.0f,0.0f };
		m_level[i].mat = Math::Matrix::CreateTranslation(m_level[i].pos);
		m_level[i].width = 8;
		m_level[i].height = 8;
		m_level[i].rect = { 0,0,8,8 };
	}

	// フレーム
	m_frame.pTex = AssetManager::Instance().GetTex("levelFrame");
	m_frame.pos = { -450.0f,-200.0f,0.0f };
	m_frame.Set();

	// バー
	m_bar.pTex = AssetManager::Instance().GetTex("levelBar");
	m_bar.pos = { -450.0f,-200.0f,0.0f };
	m_bar.Set();
}

void LevelBar::TexData::Set()
{
	mat = Math::Matrix::CreateTranslation(pos);
	width = pTex->GetWidth();
	height = pTex->GetHeight();
	rect = { 0,0,width,height };
}