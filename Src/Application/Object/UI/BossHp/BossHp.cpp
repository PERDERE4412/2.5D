#include "BossHp.h"

void BossHp::Update()
{
	// テクスチャの幅を取得
	int w = m_bar.pTex->GetWidth();
	// HP１の時に幅いくつの領域を表示するのか
	float singleW = (float)w / m_status.lock()->GetMaxHp();
	m_bar.rect = { 0,0,(long)(singleW * m_status.lock()->GetHp()),(long)m_bar.pTex->GetHeight() };
}

void BossHp::DrawSprite()
{
	// フレーム
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_frame.pTex, (int)m_frame.pos.x, (int)m_frame.pos.y, m_frame.pTex->GetWidth(), m_frame.pTex->GetHeight(), &m_frame.rect);

	// バー
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_bar.pTex, (int)m_bar.pos.x, (int)m_bar.pos.y,m_bar.rect.width,m_bar.rect.height, &m_bar.rect, nullptr, {0.0f,0.5f});
}

void BossHp::Init()
{
	// フレーム
	m_frame.pTex = AssetManager::Instance().GetTex("bossHpFrame");
	m_frame.pos = { 0.0f,280.0f };
	m_frame.rect = { 0,0,(int)m_frame.pTex->GetWidth(),(int)m_frame.pTex->GetHeight() };
	
	// バー
	m_bar.pTex = AssetManager::Instance().GetTex("bossHpBar");
	m_bar.pos = { -223.0f,280.0f };
	m_bar.rect = { 0,0,(int)m_bar.pTex->GetWidth(),(int)m_bar.pTex->GetHeight() };
}
