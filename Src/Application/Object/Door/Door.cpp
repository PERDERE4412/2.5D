#include "Door.h"

#include "../../Lib/AssetManager/AssetManager.h"

#include "../../Scene/SceneManager.h"
#include "../UI/ActionManager/ActionManager.h"
#include "../Chara/Player/Player.h"

void Door::Update()
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
				m_bEnter = true;
			}

			// 取得
			if (GetAsyncKeyState('F') & 0x8000)
			{
				// UIが表示されてる && キーが押されていなければ
				if (m_bEnter && !ActionManager::Instance().GetKey())
				{
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
			if (m_bEnter)
			{
				m_bEnter = false;
				ActionManager::Instance().OffAction();
			}
		}
	}
}

void Door::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model, m_world);
}

void Door::DrawSprite()
{
	if (!m_bEnter)return;

	m_camera = SceneManager::Instance().GetCamera();
	
	Math::Vector3 pos = Math::Vector3::Zero;
	if (!m_camera.expired())
	{
		m_camera.lock()->ConvertWorldToScreenDetail(GetPos(), pos);
		pos.x += 80.0f;
		pos.y += 100.0f;
	}
	Math::Rectangle rect = { 0,0,(int)m_pTex->GetWidth(),(int)m_pTex->GetHeight() };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pTex, pos.x, pos.y, m_pTex->GetWidth(), m_pTex->GetHeight(), &rect);
}

void Door::SetPos(Math::Vector3 _pos, int _deg)
{
	m_pos = _pos;
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(_deg));
	m_world = rotMat * transMat;
}

void Door::Init()
{
	m_model = AssetManager::Instance().GetModel("door");

	m_pTex = AssetManager::Instance().GetTex("enter");
	m_bEnter = false;
}
