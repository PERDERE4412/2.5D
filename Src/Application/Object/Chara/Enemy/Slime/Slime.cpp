﻿#include "Slime.h"

#include "../../../../Lib/AssetManager/AssetManager.h"
#include "../../../../Animation/SlimeAnimation.h"
#include "../../Player/Player.h"
#include "../../../../Scene/GameScene/GameScene.h"
#include "../../../../Data/Status/Player/PlayerStatus.h"
#include "../../../DropGold/DropGold.h"
#include "../../../../Scene/SceneManager.h"

void Slime::PreUpdate()
{
	if (m_damageWait > 0)m_damageWait--;
	if (m_damageWait <= 0)
	{
		m_color = { 1,1,1,1 };
	}
}

void Slime::Update()
{
	// デバッグ用
	if (GetAsyncKeyState('P') & 0x8000)m_status->Damage(5);

	if (m_status->GetHp() <= 0)
	{
		if (m_state != SlimeAnimation::State::Death)
		{
			PlayerStatus::Instance().SetExp(10);
			m_state = SlimeAnimation::State::Death;
		}
	}

	if (!m_player.expired())m_playerPos = m_player.lock()->GetPos();
	else return;

	if (m_state != SlimeAnimation::State::Death)
	{
		if (m_anim->GetAction())Move();
	}

	// アニメーション作成
	m_anim->CreateAnime(m_dir, m_state, &m_polygon);

	// 消滅
	if (m_anim->GetKill())
	{
		std::shared_ptr<DropGold> drop = std::make_shared<DropGold>();
		drop->Set(m_player, m_pos, 10);
		SceneManager::Instance().AddObject(drop);
		m_isExpired = true;
	}

	if (m_invWait > 0)m_invWait--;
}

void Slime::PostUpdate()
{
	// 敵の当たり判定を可視化
	m_pDebugWire->AddDebugSphere(m_pos + Math::Vector3(0, 3.0f, 0), 2.0f, kGreenColor);

	//========================================
	// 球判定
	//========================================
	{
		// 球判定用の変数を作成
		KdCollider::SphereInfo sphere;

		// 球の中心点を設定
		Math::Vector3 pos = { 0.0f,0.5f,0.0f };
		sphere.m_sphere.Center = m_pos + pos;

		// 球の半径を設定
		sphere.m_sphere.Radius = 2.0f;

		// 当たり判定をしたいタイプを設定
		sphere.m_type = KdCollider::TypeGround | KdCollider::TypeBump;

		//球に当たったオブジェクトの状態を格納
		std::list<KdCollider::CollisionResult> retSphereList;

		// 当たり判定(sphere)
		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			// 自分だったら処理を飛ばす
			if (obj.get() == this)
			{
				continue;
			}

			obj->Intersects(sphere, &retSphereList);
		}

		// 球に当たったリストから一番近い
		float maxOverLap = 0;		// はみ出たレイの長さ
		Math::Vector3 hitDir;		// 当たった方法
		bool isHit = false;			// 当たっていたらtrue

		for (auto& ret : retSphereList)
		{
			// 球にめり込んで、オーバーした長さが一番長いものを探す
			if (maxOverLap < ret.m_overlapDistance)
			{
				maxOverLap = ret.m_overlapDistance;
				hitDir = ret.m_hitDir;
				isHit = true;
			}
		}

		if (isHit)
		{
			// 地面にめり込ませない
			hitDir.y = 0;

			// 正規化(長さを1にする)
			// 方向は絶対長さが1
			hitDir.Normalize();

			// 地面に当たっている
			m_pos += hitDir * maxOverLap;
		}
	}

	//========================================
	// 攻撃判定
	//========================================
	if (m_state == SlimeAnimation::State::Attack1)
	{
		if (m_anim->GetUVrect() == 4)
		{

			// 球判定用の変数を作成
			KdCollider::SphereInfo sphere;

			// 球の中心点を設定
			Math::Vector3 dir = m_playerPos - m_pos;
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

void Slime::Hit(int _damage)
{
	if (m_invWait <= 0)
	{
		m_status->Damage(_damage);
		m_invWait = 30;
		m_damageWait = 10;
		m_color = { 10,10,10,1 };
	}
}

void Slime::Init()
{
	m_anim = std::make_shared<SlimeAnimation>();

	m_state = SlimeAnimation::State::Idle;

	m_dir = SlimeAnimation::Dir::Right;

	m_status = std::make_shared<SlimeStatus>();

	m_color = { 1,1,1,1 };

	m_damageWait = 0;

	m_polygon = AssetManager::Instance().GetMaterial("slimeIdle");
	m_polygon.SetUVRect(0);

	m_movePow = 0.15f;

	m_attackWait = 0;

	m_invWait = 0;

	// デバッグ用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("SlimeCollision", { 0.0f,3.0f,0.0f }, 2.0f, KdCollider::TypeBump | KdCollider::TypeEnemy);
}

void Slime::Move()
{
	m_state = SlimeAnimation::State::Idle;

	m_movePow = 0.15f;

	// 方向ベクトル初期化
	m_vec = Math::Vector3::Zero;

	float dist = Math::Vector3::Distance(m_playerPos, m_pos);
	if (dist < 15.0f && dist > 6.0f)
	{
		m_vec = m_playerPos - m_pos;

		m_vec.Normalize();
		m_vec *= m_movePow;
		m_pos += m_vec;

		if (m_vec.x > 0.0f)
		{
			if (m_dir == SlimeAnimation::Dir::Left)
			{
				m_dir = SlimeAnimation::Dir::Right;
				m_polygon.TurnScale();
			}
		}
		else if (m_vec.x < 0.0f)
		{
			if (m_dir == SlimeAnimation::Dir::Right)
			{
				m_dir = SlimeAnimation::Dir::Left;
				m_polygon.TurnScale();
			}
		}
	}
	else if (dist <= 6.0f)
	{
		Attack();
	}

	if (m_attackWait > 0)m_attackWait--;

	if (m_vec != Math::Vector3::Zero && m_state != SlimeAnimation::State::Attack1)
	{
		m_state = SlimeAnimation::State::Run;
	}
}

void Slime::Attack()
{
	m_movePow = 0.0f;

	if (m_attackWait <= 0)
	{
		m_state = SlimeAnimation::State::Attack1;
		m_attackWait = 120;
	}
}