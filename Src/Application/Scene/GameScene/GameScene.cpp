#include "GameScene.h"
#include"../SceneManager.h"

#include "../../Object/Map/Map.h"
#include "../../Object/PlayerHp/PlayerHp.h"

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

	/*if (GetAsyncKeyState('W') & 0x8000)m_pos.z += 0.1f;
	if (GetAsyncKeyState('A') & 0x8000)m_pos.x -= 0.1f;
	if (GetAsyncKeyState('S') & 0x8000)m_pos.z -= 0.1f;
	if (GetAsyncKeyState('D') & 0x8000)m_pos.x += 0.1f;

	if (GetAsyncKeyState('U') & 0x8000)m_pos.y += 0.1f;*/

	// どこに配置されるか
	Math::Matrix _mTrans = Math::Matrix::CreateTranslation(0.0f,5.0f,0.0f);

	// カメラの「ワールド行列」を作成し、適応させる
	Math::Matrix _worldMat = _mRotationX * _mTrans;
	m_camera->SetCameraMatrix(_worldMat);
}

void GameScene::Init()
{
	// カメラ
	m_camera = std::make_unique<KdCamera>();

	// 仮マップ
	std::shared_ptr<Map> map = std::make_shared<Map>();
	AddObject(map);

	// HPバー
	std::shared_ptr<PlayerHp> hp = std::make_shared<PlayerHp>();
	AddObject(hp);
}
