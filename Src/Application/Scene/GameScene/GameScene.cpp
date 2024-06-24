#include "GameScene.h"
#include"../SceneManager.h"

#include "../../Object/Chara/Player/Player.h"
#include "../../Object/UI/PlayerHp/PlayerHp.h"
#include "../../Object/UI/Slot/Slot.h"
#include "../../Object/UI/LevelBar/LevelBar.h"
#include "../../Object/UI/MiniMap/MiniMap.h"
#include "../../Object/Map/Back/Back.h"
#include "../../Map/MapManager.h"
#include "../../Object/Item/ItemManager.h"
#include "../../Object/Chara/Enemy/EnemyManager.h"
#include "../../Movie/Movie.h"
#include "../../Inventory/Inventory.h"

void GameScene::Event()
{
	if(!Movie::Instance().GetStart())UpdateCamera();

	Inventory::Instance().Update();

	if (!m_bCreateMap)
	{
		m_bCreateMap = true;
		MapManager::Instance().ChangeMap();
		KdAudioManager::Instance().StopAllSound();
		KdAudioManager::Instance().Play("Asset/Sounds/stage.wav", true, 0.02f);
	}
}

void GameScene::Init()
{
	// カメラ
	m_camera = std::make_shared<KdCamera>();
	m_pos = { 0.0f,25.0f,-25.0f };
	Movie::Instance().SetCamera(m_camera);

	Movie::Instance().Init();

	// キャラクター==================================================
	// プレイヤー
	std::shared_ptr<Player> player = std::make_shared<Player>();
	AddObject(player);
	m_player = player;
	EnemyManager::Instance().SetPlayer(player);
	MapManager::Instance().SetPlayer(player);
	ItemManager::Instance().SetPlayer(player);
	Movie::Instance().SetPlayer(player);
	Animation::Instance().Init();
	Inventory::Instance().SetPlayer(player);

	// マップ========================================================
	// 背景
	std::shared_ptr<Back> back = std::make_shared<Back>();
	AddObject(back);

	// UI============================================================
	// HPバー
	std::shared_ptr<PlayerHp> hp = std::make_shared<PlayerHp>();
	hp->SetPlayer(player);
	AddObject(hp);

	// スロット
	std::shared_ptr<Slot> slot = std::make_shared<Slot>();
	AddObject(slot);

	// レベル
	std::shared_ptr<LevelBar> level = std::make_shared<LevelBar>();
	level->SetPlayer(player);
	AddObject(level);

	// ミニマップ
	std::shared_ptr<MiniMap> miniMap = std::make_shared<MiniMap>();
	AddObject(miniMap);
	MapManager::Instance().SetMiniMap(miniMap);

	m_bCreateMap = false;
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
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos + playerPos);

	// カメラの「ワールド行列」を作成し、適応させる
	Math::Matrix worldMat = rotX * transMat;
	m_camera->SetCameraMatrix(worldMat);
}