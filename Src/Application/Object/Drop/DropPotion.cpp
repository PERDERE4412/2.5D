#include "DropPotion.h"

#include "../../Object/UI/ActionManager/ActionManager.h"
#include "../Chara/Player/Player.h"
#include "../UI/GetPotion/GetPotion.h"
#include "../Item/ItemManager.h"
#include "../../Map/MapManager.h"

void DropPotion::Update()
{
	// 拾う
	if (!m_player.expired())
	{
		Math::Vector3 dist = m_player.lock()->GetPos() - m_pos;
		
		// 範囲内なら
		if (dist.Length() < 5.0f)
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
					ActionManager::Instance().OnKey();
					ActionManager::Instance().OffAction();
					m_isExpired = true;		// 消滅

					// ポーション獲得
					ItemManager::Instance().GetItem("Potion");
					std::shared_ptr<GetPotion> potion = std::make_shared<GetPotion>();
					SceneManager::Instance().AddObject(potion);
					MapManager::Instance().AddObject(potion);
					KdAudioManager::Instance().Play("Asset/Sounds/get.wav", false, 0.2f);
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

void DropPotion::PostUpdate()
{
	Math::Matrix rotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(45));
	Math::Matrix rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	m_world = rotX * rotY * Math::Matrix::CreateTranslation(m_pos);
}

void DropPotion::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world, m_color);
}

void DropPotion::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world, m_color);
}

void DropPotion::DrawBright()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world, m_color);
}

void DropPotion::DrawSprite()
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
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pTex, (int)pos.x, (int)pos.y, m_pTex->GetWidth(), m_pTex->GetHeight(), &rect);
}

void DropPotion::Set(std::weak_ptr<Player> _player, Math::Vector3 _pos)
{
	m_player = _player;
	m_pos = _pos;
}

void DropPotion::Init()
{
	m_polygon = AssetManager::Instance().GetMaterial("drop");

	m_pTex = AssetManager::Instance().GetTex("get");

	m_color = { 1.0f,1.0f,1.0f,1.0f };
	m_addAlpha = 0.015f;

	m_bGet = false;
}
