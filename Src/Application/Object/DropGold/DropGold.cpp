#include "DropGold.h"

#include "../../Lib/AssetManager/AssetManager.h"
#include "../Chara/Player/Player.h"
#include "../../Data/Item/Item.h"

void DropGold::Update()
{
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
}

void DropGold::PostUpdate()
{
	Math::Matrix rotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(45));
	Math::Matrix rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	m_world = rotX * rotY * Math::Matrix::CreateTranslation(m_pos);
}

void DropGold::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world);
}

void DropGold::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world);
}

void DropGold::DrawBright()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world);
}

void DropGold::Set(Math::Vector3 _pos, int _gold)
{
	m_pos = _pos;
	m_gold = _gold;
}

void DropGold::Init()
{
	m_polygon = AssetManager::Instance().GetMaterial("drop");

	m_pos = {};
	m_gold = 0;
}
