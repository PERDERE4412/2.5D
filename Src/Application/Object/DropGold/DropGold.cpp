﻿#include "DropGold.h"

#include "../../Scene/SceneManager.h"
#include "../../Lib/AssetManager/AssetManager.h"
#include "../Chara/Player/Player.h"
#include "../../Data/Item/Item.h"

void DropGold::Update()
{
	// 拾う
	if (!m_player.expired())
	{
		Math::Vector3 playerPos = m_player.lock()->GetPos();

		float dist = Math::Vector3::Distance(playerPos, m_pos);

		if (dist < 5.0f)
		{
			if (GetAsyncKeyState('F') & 0x8000)
			{
				Item::Instance().ChangeGold(m_gold);
				m_isExpired = true;		// 消滅
			}
		}
	}

	// 点滅
	m_color.w += m_addAlpha;
	if (m_color.w > 1.0f)
	{
		m_color.w = 1.0f;
		m_addAlpha *= -1;
	}
	if (m_color.w < 0.2f)
	{
		m_color.w = 0.2f;
		m_addAlpha *= -1;
	}
}

void DropGold::PostUpdate()
{
	Math::Matrix rotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(45));
	Math::Matrix rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	m_world = rotX * rotY * Math::Matrix::CreateTranslation(m_pos);
}

void DropGold::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world, m_color);
}

void DropGold::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world, m_color);
}

void DropGold::DrawBright()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world, m_color);
}

void DropGold::DrawSprite()
{
	Math::Vector3 pos = Math::Vector3::Zero;
	if (!m_camera.expired())
	{
		m_camera.lock()->ConvertWorldToScreenDetail(GetPos(), pos);
	}
	Math::Rectangle rect = { 0,0,(int)m_pTex->GetWidth(),(int)m_pTex->GetHeight() };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pTex, pos.x, pos.y, 128, 40, &rect);
}

void DropGold::Set(std::weak_ptr<Player> _player, Math::Vector3 _pos, int _gold)
{
	m_player = _player;
	m_pos = _pos;
	m_gold = _gold;
}

void DropGold::Init()
{
	m_camera = SceneManager::Instance().GetCamera();

	m_polygon = AssetManager::Instance().GetMaterial("drop");

	m_pTex = AssetManager::Instance().GetTex("get");

	m_pos = {};
	m_gold = 0;
	m_color = { 1.0f,1.0f,1.0f,1.0f };
	m_addAlpha = 0.015f;
}
