#include "WarriorAttack.h"

#include "../../Player/Player.h"

void WarriorAttack::PostUpdate()
{
	//========================================
	// 攻撃判定
	//========================================
	// 球判定用の変数を作成
	KdCollider::SphereInfo sphere;

	// 球の中心点を設定
	sphere.m_sphere.Center = m_pos;
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
			if (Animation::Instance().GetState() != Animation::PlayerState::Roll)
			{
				obj->Hit(m_atk);
				Hit();
			}
		}
	}

	if (m_time > 0)m_time--;
	if (m_time <= 0)m_isExpired = true;
}

void WarriorAttack::Hit()
{
	// 消滅
	m_isExpired = true;
}

void WarriorAttack::Set(Math::Vector3 _pos, Math::Vector3 _dir, int _atk)
{
	m_pos = _pos + (_dir * 4.0f);

	m_atk = _atk;
}

void WarriorAttack::Init()
{
	KdAudioManager::Instance().Play("Asset/Sounds/attack1.wav", false, 0.1f);

	m_time = 10;

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}
