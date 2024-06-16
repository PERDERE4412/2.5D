#include "FireWispBullet.h"

#include "../../../../Lib/AssetManager/AssetManager.h"
#include "../../../../Scene/SceneManager.h"
#include "../../../../Animation/Animation.h"

void FireWispBullet::Update()
{
	m_pos += m_move;
}

void FireWispBullet::PostUpdate()
{
	// デバッグ表示
	Math::Vector3 pos = { -1.0f,2.5f,1.0f };
	m_pDebugWire->AddDebugSphere(m_pos + pos, 1.5f);

	//========================================
	// 攻撃判定
	//========================================
	// 球判定用の変数を作成
	KdCollider::SphereInfo sphere;

	// 球の中心点を設定
	sphere.m_sphere.Center = m_pos + pos;

	// 球の半径を設定
	sphere.m_sphere.Radius = 1.5f;

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
				m_isExpired = true;
			}
		}
	}

	// 壁との当たり判定
	retSphereList.clear();
	sphere.m_type = KdCollider::TypeGround;
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		if (obj->Intersects(sphere, &retSphereList))m_isExpired = true;
	}

	// 行列作成
	Math::Matrix rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	m_world = rotX * Math::Matrix::CreateTranslation(m_pos);
}

void FireWispBullet::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world);
}

void FireWispBullet::Set(Math::Vector3 _pos, Math::Vector3 _dir, int _atk)
{
	m_pos = _pos;
	m_move = _dir * m_speed;
	m_atk = _atk;
}

void FireWispBullet::Init()
{
	m_polygon = AssetManager::Instance().GetMaterial("fireWispBullet");

	m_speed = 0.3f;

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}
