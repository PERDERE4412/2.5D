#include "LichThunderCircle.h"

#include "../../../../Scene/SceneManager.h"
#include "../../../../Map/MapManager.h"
#include "LichThunder.h"

void LichThunderCircle::PostUpdate()
{
	m_size += m_sizeSpeed;

	if (m_size > 10)
	{
		m_isExpired = true;

		// 雷生成
		std::shared_ptr<LichThunder> thunder = std::make_shared<LichThunder>();
		thunder->Set(m_pos,m_atk);
		SceneManager::Instance().AddObject(thunder);
		MapManager::Instance().AddObject(thunder);
	}

	m_polygon.SetScale(m_size);

	// 行列作成
	Math::Matrix rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90));
	m_world = rotX * Math::Matrix::CreateTranslation(m_pos);
}

void LichThunderCircle::Set(Math::Vector3 _pos, int _atk)
{
	m_pos = _pos;
	m_pos.y += 0.5f;

	m_atk = _atk;
}

void LichThunderCircle::Init()
{
	m_polygon = AssetManager::Instance().GetMaterial("lichThunderCircle");

	m_animeCnt = 0.0f;
	m_animeSpeed = 0.0f;

	m_atk = 0;

	m_size = 0.0f;
	m_sizeSpeed = 0.2f;
}
