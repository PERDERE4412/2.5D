﻿#include "PlayerHp.h"

#include "../../Scene/SceneManager.h"
#include "../../Data/Status/PlayerStatus.h"

void PlayerHp::Update()
{
	// オブジェクトリストを取得
	std::list<std::shared_ptr<KdGameObject>> objList;
	objList = SceneManager::Instance().GetObjList();

	int hp = 0, maxHp = 0;

	// プレイヤーのHPと最大HPを取得
	hp = PlayerStatus::Instance().GetValue("HP");
	maxHp = PlayerStatus::Instance().GetValue("MAXHP");

	// 切り取り範囲の変更
	rectX = m_bar.tex.GetWidth() * ((float)hp / maxHp);
	m_bar.rect.width = rectX;

	// 座標の移動
	m_bar.pos.x = -450.0f - 146.0f * (1 - (float)hp / maxHp);
	m_bar.mat = Math::Matrix::CreateTranslation(m_bar.pos);
}

void PlayerHp::DrawSprite()
{
	// フレーム
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_frame.mat);
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_frame.tex, 0, 0, m_frame.tex.GetWidth(), m_frame.tex.GetHeight(), &m_frame.rect);

	// バー
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_bar.mat);
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_bar.tex, 0, 0, rectX, m_bar.tex.GetHeight(), &m_bar.rect);
}

void PlayerHp::Init()
{
	m_objType = ObjType::none;

	// フレーム
	m_frame.tex.Load("Asset/Textures/hp.png");
	m_frame.pos = { -450.0f,-300.0f,0.0f };
	m_frame.mat = Math::Matrix::CreateTranslation(m_frame.pos);
	m_frame.rect = { 0,0,(int)m_frame.tex.GetWidth(),(int)m_frame.tex.GetHeight() };

	// バー
	m_bar.tex.Load("Asset/Textures/hpBar.png");
	m_bar.pos = { -450.0f,-300.0f,0.0f };
	m_bar.mat = Math::Matrix::CreateTranslation(m_bar.pos);
	m_bar.rect = { 0,0,(int)m_bar.tex.GetWidth(),(int)m_bar.tex.GetHeight() };
}