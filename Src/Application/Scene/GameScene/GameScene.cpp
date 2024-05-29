#include "GameScene.h"
#include"../SceneManager.h"

#include "../../Object/Player/Player.h"
#include "../../Object/Map/Map.h"
#include "../../Object/PlayerHp/PlayerHp.h"
#include "../../Object/Slot/Slot.h"
#include "../../Object/Gold/Gold.h"
#include "../../Object/LevelBar/LevelBar.h"
#include "../../Object//Back/Back.h"

#include "../../Data/Status/PlayerStatus.h"

void GameScene::Event()
{
	UpdateCamera();

	static bool a = false;
	if (GetAsyncKeyState('U') & 0x8000)
	{
		if (!a)
		{
			a = true;
			PlayerStatus::Instance().SetExp(3);
		}
	}
	else a = false;
}

void GameScene::Init()
{
	// カメラ
	m_camera = std::make_unique<KdCamera>();
	m_pos = { -12.0f,13.0f,-12.0f };

	// プレイヤー
	std::shared_ptr<Player> player = std::make_shared<Player>();
	AddObject(player);

	// 仮マップ
	std::shared_ptr<Map> map = std::make_shared<Map>();
	AddObject(map);

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

	// 背景
	std::shared_ptr<Back> back = std::make_shared<Back>();
	AddObject(back);
}

void GameScene::UpdateCamera()
{
	std::list<std::shared_ptr<KdGameObject>> objList;
	objList = SceneManager::Instance().GetObjList();

	Math::Matrix playerMat;
	for (auto& obj : objList)
	{
		if (obj->GetObjType() == KdGameObject::ObjType::Player)
		{
			playerMat = obj->GetMatrix();
			break;
		}
	}
	Math::Matrix playerTransMat = Math::Matrix::CreateTranslation(playerMat.Translation());

	// どれだけ傾けているか
	Math::Matrix rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(30));
	Math::Matrix rotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(45));

	// どこに配置されるか
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	// カメラの「ワールド行列」を作成し、適応させる
	Math::Matrix worldMat = rotX * rotY * transMat * playerTransMat;
	m_camera->SetCameraMatrix(worldMat);
}
