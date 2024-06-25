#include "Warrior.h"

#include "../../Player/Player.h"
#include "../../../../Scene/GameScene/GameScene.h"
#include "../../../../Map/MapManager.h"
#include "../../../Drop/DropPotion.h"
#include "WarriorAttack.h"

void Warrior::Update()
{
	BaseEnemy::Update();

	// 攻撃生成
	if (m_anim->GetState() == EnemyAnimation::State::Attack && m_anim->GetUVRect() == 7)
	{
		if (!m_bAttack)
		{
			m_bAttack = true;

			// 攻撃生成
			m_vec = m_player.lock()->GetPos() - m_pos;
			m_vec.Normalize();
			std::shared_ptr<WarriorAttack> attack = std::make_shared<WarriorAttack>();
			if (!m_player.expired())attack->SetPlayer(m_player.lock());
			attack->Set(m_pos, m_vec, m_status->GetAtk());
			SceneManager::Instance().AddObject(attack);
			MapManager::Instance().AddObject(attack);
		}
	}
}

void Warrior::PostUpdate()
{
	BaseEnemy::PostUpdate();

	// 行列作成
	Math::Matrix rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	m_world = rotX * Math::Matrix::CreateTranslation(m_pos);
}

void Warrior::Init()
{
	BaseEnemy::Init();

	m_status->Init("Warrior");

	m_polygon = AssetManager::Instance().GetMaterial("WarriorIdle");
	m_polygon.SetUVRect(0);

	m_movePow = 0.15f;

	m_setAttackWait = 120;

	m_setDamageWait = 10;

	m_setInvWait = 30;

	// デバッグ用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_pCollider->RegisterCollisionShape("WarriorCollision", { 0.0f,3.0f,0.0f }, 2.0f, KdCollider::TypeBump|KdCollider::TypeEnemy);
}

void Warrior::Move()
{
	m_state = EnemyAnimation::State::Idle;

	m_movePow = 0.15f;

	// 方向ベクトル初期化
	m_vec = Math::Vector3::Zero;
	
	Math::Vector3 dist= m_player.lock()->GetPos() - m_pos;

	if (dist.Length() < 25.0f && dist.Length() > 6.0f)
	{
		m_vec = dist;
		
		m_vec.Normalize();
		m_vec *= m_movePow;
		m_pos += m_vec;

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
	}
	else if (dist.Length() <= 6.0f)
	{
		Attack();
	}

	if (m_attackWait > 0)m_attackWait--;

	if (m_vec != Math::Vector3::Zero && m_state != EnemyAnimation::State::Attack)
	{
		m_state = EnemyAnimation::State::Run;
	}
}