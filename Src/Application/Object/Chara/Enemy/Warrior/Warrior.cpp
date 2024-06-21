#include "Warrior.h"

#include "../../Player/Player.h"
#include "../../../../Scene/GameScene/GameScene.h"
#include "../../../../Map/MapManager.h"
#include "../../../Drop/DropPotion.h"
#include "../../../../Scene/SceneManager.h"

void Warrior::Update()
{
	BaseEnemy::Update();

	// 消滅
	if (m_anim->GetKill())
	{
		std::shared_ptr<DropPotion> drop = std::make_shared<DropPotion>();
		drop->Set(m_player, m_pos);
		SceneManager::Instance().AddObject(drop);
		MapManager::Instance().AddObject(drop);
		m_isExpired = true;
	}
}

void Warrior::PostUpdate()
{
	BaseEnemy::PostUpdate();

	//========================================
	// 攻撃判定
	//========================================
	if (m_state == EnemyAnimation::State::Attack)
	{
		if (m_anim->GetUVRect() >= 6 && m_anim->GetUVRect() <= 8)
		{
			// 球判定用の変数を作成
			KdCollider::SphereInfo sphere;

			// 球の中心点を設定
			//Math::Vector3 dir = m_playerPos - m_pos;
			Math::Vector3 dir = m_player.lock()->GetPos() - m_pos;
			dir.Normalize();
			float attackRange = 4.0f;
			sphere.m_sphere.Center = m_pos + (dir * attackRange);
			sphere.m_sphere.Center.z += 2.0f;

			// 球の半径を設定
			sphere.m_sphere.Radius = 2.0f;

			// 当たり判定をしたいタイプを設定
			sphere.m_type = KdCollider::TypePlayer;

			//球に当たったオブジェクトの状態を格納
			std::list<KdCollider::CollisionResult> retSphereList;

			// 当たり判定(sphere)
			for (auto& obj : SceneManager::Instance().GetObjList())
			{
				if (obj->Intersects(sphere, &retSphereList))
				{
					obj->Hit(m_status->GetAtk());
				}
			}

			m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, 2.0f, kGreenColor);
		}
	}

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

	if (dist.Length() < 15.0f && dist.Length() > 6.0f)
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