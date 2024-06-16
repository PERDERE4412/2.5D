#include "MiniMap.h"

#include "../../../Lib/AssetManager/AssetManager.h"

void MiniMap::DrawSprite()
{
	// フレーム
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_frameTex, 470, 220);

	// マップ
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_mapTex, 470, 220);

	// プレイヤー
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_playerTex, m_nowPlayerPos.x, m_nowPlayerPos.y);
}

void MiniMap::Set(int _mapId)
{
	m_nowPlayerPos = m_playerPosList[_mapId];
}

void MiniMap::Init()
{
	m_frameTex = AssetManager::Instance().GetTex("miniMapFrame");
	m_mapTex = AssetManager::Instance().GetTex("miniMap");

	m_playerTex = AssetManager::Instance().GetTex("mapPlayer");

	m_playerPosList[1] = { 463, 169 };
	m_playerPosList[2] = { 439,193 };
	m_playerPosList[3] = { 487,193 };
	m_playerPosList[4] = { 415,217 };
	m_playerPosList[5] = { 463,217 };
	m_playerPosList[6] = { 511,217 };
	m_playerPosList[7] = { 439,241 };
	m_playerPosList[8] = { 487,241 };
	m_playerPosList[9] = { 463,265 };
	m_playerPosList[10] = { 511,265 };

	m_nowPlayerPos = m_playerPosList[1];

	m_bKey = false;
}
