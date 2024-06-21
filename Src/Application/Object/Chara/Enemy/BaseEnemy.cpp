﻿#include "BaseEnemy.h"

#include "../../../Scene/SceneManager.h"
#include "../../../Data/Status/Player/PlayerStatus.h"

void BaseEnemy::PreUpdate()
{
	if (m_invWait > 0)m_invWait--;
	if (m_damageWait > 0)m_damageWait--;
	if (m_damageWait <= 0)
	{
		m_color = { 1,1,1,1 };
	}
}

void BaseEnemy::Update()
{
	// デバッグ用
	if (GetAsyncKeyState('P') & 0x8000)m_status->Damage(5);

	if (m_status->GetHp() <= 0)
	{
		if (m_state != EnemyAnimation::State::Death)
		{
			PlayerStatus::Instance().SetExp(m_status->GetExp());
			m_state = EnemyAnimation::State::Death;
		}
	}

	if (m_state != EnemyAnimation::State::Death)
	{
		if (m_anim->GetAction())Move();
	}

	// アニメーション作成
	m_anim->CreateAnime(m_status->GetName(),m_dir, m_state, &m_polygon);
}

void BaseEnemy::PostUpdate()
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
}

void BaseEnemy::Hit(int _damage)
{
	if (m_invWait <= 0)
	{
		m_status->Damage(_damage);
		m_invWait = m_setInvWait;
		m_damageWait = m_setDamageWait;
		m_color = { 10,10,10,1 };
	}
}

void BaseEnemy::Init()
{
	m_anim = std::make_shared<EnemyAnimation>();

	m_state = EnemyAnimation::State::Idle;

	m_dir = Utility::CharaDir::Right;

	m_status = std::make_shared<EnemyStatus>();

	m_color = { 1,1,1,1 };

	m_damageWait = 0;

	m_attackWait = 0;

	m_invWait = 0;

	m_pCollider = std::make_unique<KdCollider>();
}

void BaseEnemy::Attack()
{
	if (m_attackWait <= 0)
	{
		m_state = EnemyAnimation::State::Attack;
		m_attackWait = m_setAttackWait;
	}
}
