#include "PlayerSwordEffect1.h"

#include "../../../Scene/SceneManager.h"

void PlayerSwordEffect1::Update()
{
	m_animeCnt += m_animeSpeed;
	if ((int)m_animeCnt > (int)m_polygon.GetSplitX() - 1)
	{
		m_isExpired = true;
	}

	m_polygon.SetUVRect((int)m_animeCnt);
}

void PlayerSwordEffect1::PostUpdate()
{
	// =====================
	// 攻撃判定
	// =====================
	// 球判定用の変数を作成
	KdCollider::SphereInfo sphere;

	// 球の中心点を設定
	Math::Vector3 pos = {0.0f,0.0f,2.5f};
	sphere.m_sphere.Center = m_pos+pos;

	// 球の半径を設定
	sphere.m_sphere.Radius = 2.0f;

	// 当たり判定をしたいタイプを設定
	sphere.m_type = KdCollider::TypeEnemy;

	// 球に当たったオブジェクトの情報を格納
	std::list<KdCollider::CollisionResult> retSphereList;

	// 当たり判定だよ！！！！！！！！！！！！！！！！！！！！！
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		if (obj->Intersects(sphere, &retSphereList))
		{
			obj->Hit(m_atk);
		}
	}

	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, 2.0f, kGreenColor);
}

void PlayerSwordEffect1::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world, m_color);
}

void PlayerSwordEffect1::DrawBright()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world, m_color);
}

void PlayerSwordEffect1::SetPos(Math::Vector3 _pos, bool _right,int _atk)
{
	m_pos = _pos;
	m_pos.z -= 0.5f;

	if (_right)
	{
		// 右向き
		m_polygon.TurnScale();
		m_pos.x += 4.5f;
	}
	else if (!_right)
	{
		// 左向き
		m_pos.x -= 4.5f;
	}

	m_world = Math::Matrix::CreateTranslation(m_pos);

	m_atk = _atk;
}

void PlayerSwordEffect1::Init()
{
	m_polygon = AssetManager::Instance().GetMaterial("playerSwordEffect1");
	m_color = { 5.0f,5.0f,5.0f,1.0f };

	m_animeCnt = 0.0f;
	m_animeSpeed = 0.4f;

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}
