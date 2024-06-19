#include "Movie.h"

#include "../Scene/SceneManager.h"
#include "../Object/Chara/Player/Player.h"
#include "../Object/Chara/Enemy/Lich/Lich.h"
#include "../Object/Effect/LichSpawn/Lightning.h"
#include "../Object/Effect/LichSpawn/LightExp.h"

void Movie::Update()
{
	if (!m_bStart)return;

	// スポーン中じゃなければカメラ移動
	if(!m_bSpawn)MoveCamera();

	// スポーン演出
	if(m_bSpawn)BossSpawn();
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
}

void Movie::MoveCamera()
{
	float speed = 0.15f;

	Math::Vector3 dir;
	if (m_bMove)dir=m_lichSpawnPos - m_cameraPos;
	else dir=m_playerPos - m_cameraPos;

	if (dir.Length() < speed)
	{
		speed = dir.Length();
		m_bSpawn = true;		// スポーン演出を始める
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
	static bool bLight=false;
	if (!bLight)
	{
		bLight = true;
		std::shared_ptr<Lightning> lightning = std::make_shared<Lightning>();
		lightning->SetPos(m_lichSpawnPos);
		SceneManager::Instance().AddObject(lightning);

		std::shared_ptr<LightExp> lightExp = std::make_shared<LightExp>();
		lightExp->SetPos(m_lichSpawnPos);
		SceneManager::Instance().AddObject(lightExp);

		std::shared_ptr<Lich> lich = std::make_shared<Lich>();
		lich->SetPos(m_lichSpawnPos);
		SceneManager::Instance().AddObject(lich);
	}
}
