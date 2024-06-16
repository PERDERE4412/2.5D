#include "LichBullet.h"

#include "../../../../Lib/AssetManager/AssetManager.h"
#include "../../../../Scene/SceneManager.h"
#include "../../../../Map/MapManager.h"
#include "../../../../Animation/Animation.h"
#include "../../Player/Player.h"
#include "LichBulletExp.h"

void LichBullet::Update()
{
	m_pos += m_move;

	m_animeCnt += m_animeSpeed;
	if (int(m_animeCnt) > m_polygon.GetSplitX() - 1)
	{
		m_animeCnt = 0;
	}

	m_polygon.SetUVRect(int(m_animeCnt));
}

void LichBullet::PostUpdate()
{
	// デバッグ表示
	Math::Vector3 pos = { 0.0f,2.5f,1.0f };
	m_pDebugWire->AddDebugSphere(m_pos + pos, 2.0f);

	//========================================
	// 攻撃判定
	//========================================
	// 球判定用の変数を作成
	KdCollider::SphereInfo sphere;

	// 球の中心点を設定
	sphere.m_sphere.Center = m_pos + pos;

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

	// 壁との当たり判定
	retSphereList.clear();
	sphere.m_type = KdCollider::TypeGround;
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		if (obj->Intersects(sphere, &retSphereList))Hit();
	}

	// 行列作成
	Math::Matrix rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	m_world = rotX * Math::Matrix::CreateTranslation(m_pos);
}

void LichBullet::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world);
}

void LichBullet::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world);
}

void LichBullet::DrawBright()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world);
}

void LichBullet::Hit()
{
	// 爆発エフェクト
	std::shared_ptr<LichBulletExp> exp = std::make_shared<LichBulletExp>();
	exp->SetPos(m_pos);
	SceneManager::Instance().AddObject(exp);
	MapManager::Instance().AddObject(exp);

	// 消滅
	m_isExpired = true;
}

void LichBullet::Set(Math::Vector3 _pos, Math::Vector3 _dir, int _atk)
{
	m_pos = _pos;
	m_pos.z += 3.0f;
	Math::Vector3 dir;

	if (_dir.x > 0)
	{
		// 右向き
		m_polygon.TurnScale();
		m_pos.x += 5.0f;
	}
	else
	{
		// 左向き
		m_pos.x -= 5.0f;
	}

	if (!m_player.expired())
	{
		dir = m_player.lock()->GetPos() - m_pos;
		dir.Normalize();
	}

	m_move = dir * m_speed;

	m_atk = _atk;
}

void LichBullet::Init()
{
	m_polygon = AssetManager::Instance().GetMaterial("lichBullet");
	m_polygon.SetUVRect(0);
	m_pos = {};

	m_speed = 0.4f;

	m_animeCnt = 0.0f;
	m_animeSpeed = 0.2f;

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}