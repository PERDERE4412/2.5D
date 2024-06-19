#include "Door.h"

#include "../../../Lib/AssetManager/AssetManager.h"

#include "../../../Scene/SceneManager.h"
#include "../../UI/ActionManager/ActionManager.h"
#include "../../../Map/MapManager.h"
#include "../../Chara/Player/Player.h"
#include "../../../Fade/Fade.h"

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

			// 移動
			if (GetAsyncKeyState('F') & 0x8000)
			{
				// UIが表示されてる && キーが押されていなければ
				if (m_bEnter && !ActionManager::Instance().GetKey())
				{
					ActionManager::Instance().OnKey();
					ActionManager::Instance().OffAction();
					Fade::Instance().BootChangeMap(m_type);
					//MapManager::Instance().SetPlayerPos(m_type);
					//MapManager::Instance().ChangeMap(m_type);
				}
			}
			// 長押し制御
			else ActionManager::Instance().OffKey();
		}
		// 範囲外なら
		else
		{
			//if (m_bEnter)
			//{
				m_bEnter = false;
				ActionManager::Instance().OffAction();
			//}
		}
	}
}

void Door::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model, m_world);
}

void Door::DrawSprite()
{
	if (!m_bEnter)return;	// 早期リターン

	m_camera = SceneManager::Instance().GetCamera();

	Math::Vector3 pos = Math::Vector3::Zero;
	if (!m_camera.expired())
	{
		if (!m_player.expired())
		{
			m_camera.lock()->ConvertWorldToScreenDetail(m_player.lock()->GetPos(), pos);
			pos.x += 100.0f;
			pos.y += 30.0f;
		}
	}

	// 描画
	Math::Rectangle rect = { 0,0,(int)m_pTex->GetWidth(),(int)m_pTex->GetHeight() };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pTex, (int)pos.x, (int)pos.y, m_pTex->GetWidth(), m_pTex->GetHeight(), &rect);
}

void Door::Set(std::string _type)
{
	m_type = _type;
	m_pos = m_doorList[_type].pos;
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_doorList[m_type].deg));
	m_world = rotMat * transMat;
}

void Door::Init()
{
	m_model = AssetManager::Instance().GetModel("door");

	m_pTex = AssetManager::Instance().GetTex("enter");
	m_bEnter = false;

	// ドアデータの読みこみ==================================================
	{
		std::ifstream ifs("Asset/Data/Map/Door.csv"); //ファイル操作用の変数

		std::string lineString; //ファイルから1文字列読み取る変数

		std::getline(ifs, lineString);	// 1行目を飛ばす

		//①ファイルが終わるまでファイルから1文字列ずつ読み取る
		while (std::getline(ifs, lineString))
		{
			std::istringstream iss(lineString); // 文字列を操作する変数にファイルから読み取った文字列を格納
			std::string doorType;				// ドアタイプを格納
			std::string doorPos;				// ドア座標を格納
			std::string doorDeg;				// ドア角度を格納

			std::getline(iss, doorType, ',');
			std::getline(iss, doorPos, ',');
			std::getline(iss, doorDeg, ',');

			// ドア座標
			std::istringstream iss2(doorPos);
			std::string pos;

			std::getline(iss2, pos, '/');
			m_doorList[doorType].pos.x = (float)atof(pos.c_str());
			std::getline(iss2, pos, '/');
			m_doorList[doorType].pos.y = (float)atof(pos.c_str());
			std::getline(iss2, pos, '/');
			m_doorList[doorType].pos.z = (float)atof(pos.c_str());

			// ドア角度
			m_doorList[doorType].deg = (float)atof(doorDeg.c_str());
		}

		ifs.close();
	}
}
