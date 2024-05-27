#include "LevelBar.h"

#include "../../Lib/AssetManager/AssetManager.h"

void LevelBar::Update()
{
}

void LevelBar::DrawSprite()
{
	// フレーム
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_frame.mat);
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_frame.pTex, 0, 0, m_frame.width, m_frame.height, &m_frame.rect);

	// バー
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_bar.mat);
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_bar.pTex, 0, 0, m_bar.width, m_bar.height, &m_bar.rect);
}

void LevelBar::Init()
{
	// フレーム
	m_frame.pTex = AssetManager::Instance().GetTex("levelFrame");
	m_frame.pos = { 0,0,0 };
	m_frame.Set();

	// バー
	m_bar.pTex = AssetManager::Instance().GetTex("levelBar");
	m_bar.pos = { 0,0,0 };
	m_bar.Set();
}

void LevelBar::TexData::Set()
{
	mat = Math::Matrix::CreateTranslation(pos);
	width = pTex->GetWidth();
	height = pTex->GetHeight();
	rect = { 0,0,width,height };
}