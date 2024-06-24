#include "LichThunder.h"

void LichThunder::PostUpdate()
{
	Math::Vector3 pos = { 0.0f,0.0f,3.0f };
	
	//========================================
	// 攻撃判定
	//========================================
	// 球判定用の変数を作成
	KdCollider::SphereInfo sphere;

	// 球の中心点を設定
	sphere.m_sphere.Center = m_world.Translation() + pos;

	// 球の半径を設定
	sphere.m_sphere.Radius = 5.0f;

	// 当たり判定をしたいタイプを設定
	sphere.m_type = KdCollider::TypePlayer;

	//球に当たったオブジェクトの状態を格納
	std::list<KdCollider::CollisionResult> retSphereList;

	// 当たり判定(sphere)
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		if (obj->Intersects(sphere, &retSphereList))
		{
			obj->Hit(m_atk);
		}
	}

	// アニメーション
	m_animeCnt += m_animeSpeed;

	if ((int)m_animeCnt > (int)(m_polygon.GetSplitX() - 1))
	{
		m_isExpired = true;
	}

	m_polygon.SetUVRect((int)m_animeCnt);

	// 行列作成
	Math::Matrix rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	m_world = rotX * Math::Matrix::CreateTranslation(m_world.Translation());
}

void LichThunder::Set(Math::Vector3 _pos, int _atk)
{
	_pos.z -= 4.0f;

	m_world.Translation(_pos);
	m_atk = _atk;
}

void LichThunder::Init()
{
	m_polygon = AssetManager::Instance().GetMaterial("lichThunder");

	m_animeCnt = 0.0f;
	m_animeSpeed = 0.2f;

	KdAudioManager::Instance().Play("Asset/Sounds/thunder.wav", false, 0.2f);

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}
