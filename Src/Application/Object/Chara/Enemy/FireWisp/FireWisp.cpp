#include "FireWisp.h"

#include "../../../../Map/MapManager.h"
#include "../../Player/Player.h"
#include "../../../../Scene/GameScene/GameScene.h"
#include "../../../Drop/DropGold.h"
#include "../../../../Scene/SceneManager.h"
#include "FireWispBullet.h"

void FireWisp::Update()
{
	BaseEnemy::Update();

	// 弾生成
	if (m_anim->GetState() == EnemyAnimation::State::Attack && m_anim->GetUVRect() == 7)
	{
		if (!m_bBullet)
		{
			m_bBullet = true;

			// 弾生成
			m_vec = m_player.lock()->GetPos() - m_pos;
			m_vec.Normalize();
			std::shared_ptr<FireWispBullet> bullet = std::make_shared<FireWispBullet>();
			if (!m_player.expired())bullet->SetPlayer(m_player.lock());
			bullet->Set(m_pos, m_vec, m_status->GetAtk());
			SceneManager::Instance().AddObject(bullet);
			MapManager::Instance().AddObject(bullet);
		}
	}

	// 消滅
	if (m_anim->GetKill())
	{
		std::shared_ptr<DropGold> drop = std::make_shared<DropGold>();
		drop->Set(m_player, m_pos, 10);
		SceneManager::Instance().AddObject(drop);
		m_isExpired = true;
	}
}

void FireWisp::PostUpdate()
{
	BaseEnemy::PostUpdate();

	// 行列作成
	Math::Matrix rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	m_world = rotX * Math::Matrix::CreateTranslation(m_pos);
}

void FireWisp::Init()
{
	BaseEnemy::Init();

	m_status->Init("FireWisp");

	m_polygon = AssetManager::Instance().GetMaterial("FireWispIdle");
	m_polygon.SetUVRect(0);

	m_movePow = 0.15f;

	m_setAttackWait = 120;

	m_setDamageWait = 10;

	m_setInvWait = 30;

	m_bBullet = false;

	// デバッグ用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_pCollider->RegisterCollisionShape("FireWispCollision", { 0.0f,3.0f,0.0f }, 2.0f, KdCollider::TypeBump | KdCollider::TypeEnemy);
}

void FireWisp::Move()
{
	m_state = EnemyAnimation::State::Idle;

	m_movePow = 0.15f;

	// 方向ベクトル初期化
	m_vec = Math::Vector3::Zero;

	Math::Vector3 dist = m_player.lock()->GetPos() - m_pos;

	if (m_vec.x > 0.0f)
	{
		if (m_dir == Utility::CharaDir::Left)
		{
			m_dir = Utility::CharaDir::Right;
			m_polygon.TurnScale();
		}
	}
	else if (m_vec.x < 0.0f)
	{
		if (m_dir == Utility::CharaDir::Right)
		{
			m_dir = Utility::CharaDir::Left;
			m_polygon.TurnScale();
		}
	}

	if (dist.Length() < 25.0f && dist.Length() > 15.0f)
	{
		m_vec.Normalize();
		m_vec *= m_movePow;
		m_pos += m_vec;
	}
	else if (dist.Length() <= 15.0f)
	{
		Attack();
	}

	if (m_attackWait > 0)m_attackWait--;

	if (m_vec != Math::Vector3::Zero && m_state != EnemyAnimation::State::Attack)
	{
		m_state = EnemyAnimation::State::Run;
	}
}

void FireWisp::Attack()
{
	if (m_attackWait <= 0)m_bBullet = false;

	BaseEnemy::Attack();
}