#include "PlayerHp.h"

#include "../../../Data/Status/Player/PlayerStatus.h"

void PlayerHp::Update()
{
	int hp = 0, maxHp = 0;

	// プレイヤーのHPと最大HPを取得
	if (!m_status.expired())
	{
		hp = m_status.lock()->GetValue("HP");
		maxHp = m_status.lock()->GetValue("MAXHP");
	}

	// 切り取り範囲の変更
	rectX = (int)(m_bar.pTex->GetWidth() * ((float)hp / maxHp));
	m_bar.rect.width = rectX;

	// 座標の移動
	m_bar.pos.x = -450.0f - 146.0f * (1 - (float)hp / maxHp);
}

void PlayerHp::DrawSprite()
{
	// フレーム
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_frame.pTex, (int)m_frame.pos.x, (int)m_frame.pos.y, m_frame.pTex->GetWidth(), m_frame.pTex->GetHeight(), &m_frame.rect);

	// バー
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_bar.pTex, (int)m_bar.pos.x, (int)m_bar.pos.y, rectX, m_bar.pTex->GetHeight(), &m_bar.rect);

	// ハート
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_hurt.pTex, m_hurt.pos.x, m_hurt.pos.y,m_hurt.rect.width/13,m_hurt.rect.height/13,&m_hurt.rect);
}

void PlayerHp::Init()
{
	// フレーム
	m_frame.pTex = AssetManager::Instance().GetTex("hpFrame");
	m_frame.pos = { -450.0f,-300.0f};
	m_frame.rect = { 0,0,(int)m_frame.pTex->GetWidth(),(int)m_frame.pTex->GetHeight() };

	// バー
	m_bar.pTex = AssetManager::Instance().GetTex("hpBar");
	m_bar.pos = { -450.0f,-300.0f};
	m_bar.rect = { 0,0,(int)m_bar.pTex->GetWidth(),(int)m_bar.pTex->GetHeight() };

	// ハート
	m_hurt.pTex = AssetManager::Instance().GetTex("hurt");
	m_hurt.pos = { -555,-265 };
	m_hurt.rect = { 0,0,(int)m_hurt.pTex->GetWidth(),(int)m_hurt.pTex->GetHeight() };
}