#include "DropGold.h"

#include "../../Object/UI/ActionManager/ActionManager.h"
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

		// 範囲内なら
		if (dist < 5.0f)
		{
			// UIを表示
			if (!ActionManager::Instance().GetAction())
			{
				ActionManager::Instance().OnAction();
				m_bGet = true;
			}

			// 取得
			if (GetAsyncKeyState('F') & 0x8000)
			{
				// UIが表示されてる && キーが押されていなければ
				if (m_bGet && !ActionManager::Instance().GetKey())
				{
					Item::Instance().ChangeGold(m_gold);
					ActionManager::Instance().OnKey();
					ActionManager::Instance().OffAction();
					m_isExpired = true;		// 消滅
				}
			}
			// 長押し制御
			else ActionManager::Instance().OffKey();
		}
		// 範囲外なら
		else
		{
			if (m_bGet)
			{
				m_bGet = false;
				ActionManager::Instance().OffAction();
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
	if (!m_bGet)return;

	m_camera = SceneManager::Instance().GetCamera();

	Math::Vector3 pos = Math::Vector3::Zero;
	if (!m_player.expired())
	{
		m_camera.lock()->ConvertWorldToScreenDetail(m_player.lock()->GetPos(), pos);
		pos.x += 100.0f;
		pos.y += 30.0f;
	}
	Math::Rectangle rect = { 0,0,(int)m_pTex->GetWidth(),(int)m_pTex->GetHeight() };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pTex, pos.x, pos.y, m_pTex->GetWidth(), m_pTex->GetHeight(), &rect);
}

void DropGold::Set(std::weak_ptr<Player> _player, Math::Vector3 _pos, int _gold)
{
	m_player = _player;
	m_pos = _pos;
	m_gold = _gold;
}

void DropGold::Init()
{
	m_polygon = AssetManager::Instance().GetMaterial("drop");

	m_pTex = AssetManager::Instance().GetTex("get");

	m_pos = {};
	m_gold = 0;
	m_color = { 1.0f,1.0f,1.0f,1.0f };
	m_addAlpha = 0.015f;

	m_bGet = false;
}
