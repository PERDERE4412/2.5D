#include "TitleScene.h"
#include "../SceneManager.h"
#include "../../Fade/Fade.h"

#include "../../Object/Map/Floor/Floor.h"
#include "../../Object/Map/Wall/Wall.h"
#include "../../Object/Map/Door/Door.h"
#include "../../Object/UI/ClickStart/ClickStart.h"
#include "../../Object/UI/Title/Title.h"
#include "../../Object/Chara/TitlePlayer/TitlePlayer.h"

void TitleScene::Event()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (!m_bKey)
		{
			m_bKey = true;
			Fade::Instance().BootChangeGame();
			KdAudioManager::Instance().Play("Asset/Sounds/titleButton.wav", false, 0.2f);
		}
	}
	else m_bKey = false;

	// カメラ
	// どれだけ傾けているか
	Math::Matrix rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(40));

	// どこに配置されるか
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	// カメラの「ワールド行列」を作成し、適応させる
	Math::Matrix worldMat = rotX * transMat;
	m_camera->SetCameraMatrix(worldMat);

	// 床
	if (!m_bCreate)
	{
		m_bCreate = true;
		std::shared_ptr<Floor> floor = std::make_shared<Floor>();
		SceneManager::Instance().AddObject(floor);

		// 壁生成
		std::shared_ptr<Wall> wall = std::make_shared<Wall>();;
		wall->SetWall(6);
		SceneManager::Instance().AddObject(wall);
		m_objList.push_back(wall);

		// ドア
		{
			std::shared_ptr<Door> door = std::make_shared<Door>();
			door->Set("L");
			SceneManager::Instance().AddObject(door);
			m_objList.push_back(door);
		}

		{
			std::shared_ptr<Door> door = std::make_shared<Door>();
			door->Set("U");
			SceneManager::Instance().AddObject(door);
			m_objList.push_back(door);
		}

		// スタート
		std::shared_ptr<ClickStart> start = std::make_shared<ClickStart>();
		SceneManager::Instance().AddObject(start);

		// プレイヤー
		std::shared_ptr<TitlePlayer> player = std::make_shared<TitlePlayer>();
		SceneManager::Instance().AddObject(player);

		// タイトル
		std::shared_ptr<Title> title = std::make_shared<Title>();
		SceneManager::Instance().AddObject(title);
	}
}

void TitleScene::Init()
{
	// カメラ
	m_camera = std::make_shared<KdCamera>();
	m_pos = { -0.1f,16.5f,26.8f };

	m_bCreate = false;
	m_bKey = false;

	KdAudioManager::Instance().Play("Asset/Sounds/title.wav", false, 0.02f);
}
