#include "GameScene.h"
#include"../SceneManager.h"

#include "../../Object/Chara/Player/Player.h"
#include "../../Object/UI/PlayerHp/PlayerHp.h"
#include "../../Object/UI/Slot/Slot.h"
#include "../../Object/UI/Gold/Gold.h"
#include "../../Object/UI/LevelBar/LevelBar.h"
#include "../../Object//Back/Back.h"

#include "../../Map/MapManager.h"
#include "../../Object/Chara/Enemy/EnemyManager.h"

void GameScene::Event()
{
	UpdateCamera();

	// デバッグ用
	static bool a = false;
	//if (GetAsyncKeyState('U') & 0x8000)
	//{
		if (!a)
		{
			MapManager::Instance().ChangeMap();
			a = true;
			//MapManager::Instance().ChangeMap(0);
			
		}
	//}
	//else a = false;
}

void GameScene::Init()
{
	// カメラ
	m_camera = std::make_shared<KdCamera>();
	m_pos = { 0.0f,25.0f,-25.0f };

	// キャラクター==================================================
	// プレイヤー
	std::shared_ptr<Player> player = std::make_shared<Player>();
	AddObject(player);
	m_player = player;
	EnemyManager::Instance().SetPlayer(player);
	MapManager::Instance().SetPlayer(player);

	// マップ========================================================
	// 背景
	std::shared_ptr<Back> back = std::make_shared<Back>();
	AddObject(back);	

	// UI============================================================
	// HPバー
	std::shared_ptr<PlayerHp> hp = std::make_shared<PlayerHp>();
	AddObject(hp);

	// スロット
	std::shared_ptr<Slot> slot = std::make_shared<Slot>();
	AddObject(slot);

	// ゴールド
	std::shared_ptr<Gold> gold = std::make_shared<Gold>();
	AddObject(gold);

	// レベル
	std::shared_ptr<LevelBar> level = std::make_shared<LevelBar>();
	AddObject(level);
}

void GameScene::UpdateCamera()
{
	Math::Vector3 playerPos;
	if (!m_player.expired())
	{
		playerPos = m_player.lock()->GetPos();
	}

	// どれだけ傾けているか
	Math::Matrix rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(40));
	
	// どこに配置されるか
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos+playerPos);
	
	// カメラの「ワールド行列」を作成し、適応させる
	Math::Matrix worldMat = rotX* transMat;
	m_camera->SetCameraMatrix(worldMat);
}
