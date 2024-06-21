#include "Movie.h"

#include "../Scene/SceneManager.h"
#include "../Map/MapManager.h"
#include "../Object/Chara/Player/Player.h"
#include "../Object/Chara/Enemy/Lich/Lich.h"
#include "../Object/Effect/LichSpawn/LichSpawn1.h"
#include "../Object/Effect/LichSpawn/LichSpawn2.h"
#include "../Object/Effect/LichSpawn/LichSpawn3.h"
#include "../Object/Effect/LichSpawn/LichSpawn4.h"

void Movie::Update()
{
	if (!m_bStart)return;

	// スポーン中じゃなければカメラ移動
	if (!m_bSpawn)MoveCamera();

	// スポーン演出
	if (m_bSpawn)BossSpawn();
}

void Movie::Init()
{
	m_bMovie = false;
	m_bStart = false;
	m_bMove = true;
	m_bSpawn = false;

	m_cameraDistPos = { 0.0f,25.0f,-25.0f };
	m_playerPos = { -17.0f,0.0f,20.0f };
	m_cameraPos = { -17.0f,0.0f,20.0f };
	m_lichSpawnPos = { 5.4f, 0.0f, 39.6f };

	m_cnt = 0;
	m_wait = 0;
	m_moveWait = 120;
}

void Movie::MoveCamera()
{
	float speed = 0.15f;

	Math::Vector3 dir;
	if (m_bMove)dir = m_lichSpawnPos - m_cameraPos;
	else dir = m_playerPos - m_cameraPos;

	// カメラ移動完了
	if (dir.Length() < speed)
	{
		speed = dir.Length();
		if (m_bMove)
		{
			m_bSpawn = true;		// スポーン演出を始める
			m_bMove = false;
		}
		else if (!m_bMove)
		{
			m_bStart = false;
		}
	}

	dir.Normalize();

	m_cameraPos += dir * speed;

	// どこに配置されるか
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_cameraPos + m_cameraDistPos);

	// どれだけ傾けているか
	Math::Matrix rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(40));

	// カメラの「ワールド行列」を作成し、適応させる
	Math::Matrix worldMat = rotX * transMat;
	if (!m_camera.expired())m_camera.lock()->SetCameraMatrix(worldMat);
}

void Movie::BossSpawn()
{
	if (m_wait > 0)m_wait--;

	if (m_wait <= 0 && m_cnt < 10)
	{
		m_cnt++;
		m_wait = 15;

		Math::Vector3 pos = Math::Vector3::Zero;
		pos = { (rand() % 41 - 20) / 10.0f,0.0f,4.0f+(rand() % 41 - 20) / 10.0f };

		std::shared_ptr<LichSpawn3> spawn3 = std::make_shared<LichSpawn3>();
		spawn3->SetPos(m_lichSpawnPos + pos);
		SceneManager::Instance().AddObject(spawn3);

		pos = { ((rand() % 41 - 20) / 10.0f) * -1.0f,0.0f,4.0f+((rand() % 41 - 20) / 10.0f) * -1.0f };

		std::shared_ptr<LichSpawn4> spawn4 = std::make_shared<LichSpawn4>();
		spawn4->SetPos(m_lichSpawnPos + pos);
		SceneManager::Instance().AddObject(spawn4);
	}

	static bool bExp = false;
	if (!bExp && m_cnt >= 10)
	{
		bExp = true;
		std::shared_ptr<LichSpawn1> spawn1 = std::make_shared<LichSpawn1>();
		spawn1->SetPos(m_lichSpawnPos);
		SceneManager::Instance().AddObject(spawn1);

		std::shared_ptr<LichSpawn2> spawn2 = std::make_shared<LichSpawn2>();
		spawn2->SetPos(m_lichSpawnPos);
		SceneManager::Instance().AddObject(spawn2);

		std::shared_ptr<Lich> lich = std::make_shared<Lich>();
		lich->SetPos(m_lichSpawnPos);
		lich->SetPlayer(m_player);
		SceneManager::Instance().AddObject(lich);
		MapManager::Instance().AddObject(lich);
	}

	if (bExp)
	{
		m_moveWait--;
		if (m_moveWait < 0)
		{
			m_bSpawn = false;
		}
	}
}