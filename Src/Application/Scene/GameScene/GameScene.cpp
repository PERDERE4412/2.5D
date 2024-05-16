#include "GameScene.h"
#include"../SceneManager.h"

#include "../../Object/Player/Player.h"
#include "../../Object/Map/Map.h"
#include "../../Object/PlayerHp/PlayerHp.h"
#include "../../Object/Slot/Slot.h"

#include "../../Debug/ImGuiManager.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

	// どれだけ傾けているか
	Math::Matrix _mRotationX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));

	if (GetAsyncKeyState('W') & 0x8000)m_pos.z += 0.1f;
	if (GetAsyncKeyState('A') & 0x8000)m_pos.x -= 0.1f;
	if (GetAsyncKeyState('S') & 0x8000)m_pos.z -= 0.1f;
	if (GetAsyncKeyState('D') & 0x8000)m_pos.x += 0.1f;

	if (GetAsyncKeyState('U') & 0x8000)m_pos.y += 0.1f;

	Math::Matrix _mRotationY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(-45));

	// どこに配置されるか
	Math::Matrix _mTrans = Math::Matrix::CreateTranslation(m_pos);

	// カメラの「ワールド行列」を作成し、適応させる
	Math::Matrix _worldMat = _mRotationX * _mTrans*_mRotationY;
	m_camera->SetCameraMatrix(_worldMat);

	ImGuiManager::Instance().SetCameraPos(m_pos);
}

void GameScene::Init()
{
	// カメラ
	m_camera = std::make_unique<KdCamera>();
	m_pos = { 0.0f,5.0f,-5.0f };

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
}
