#include "Lich.h"

#include "../../Player/Player.h"
#include "../../../../Data/Status/Player/PlayerStatus.h"
#include "../../../../Map/MapManager.h"
#include "../../../UI/BossHp/BossHp.h"
#include "LichBullet.h"
#include "LichThunderCircle.h"
#include "../../../UI/StageClear/StageClear.h"

void Lich::PreUpdate()
{
	if (m_damageWait > 0)m_damageWait--;
	if (m_damageWait <= 0)
	{
		m_color = { 1,1,1,1 };
	}
}

void Lich::Update()
{
	// デバッグ用
	if (GetAsyncKeyState('P') & 0x8000)m_status->Damage(5);

	if (m_status->GetHp() <= 0)
	{
		if (m_state != LichAnimation::State::Death)
		{
			m_player.lock()->GetStatus()->SetExp(10);
			m_state = LichAnimation::State::Death;
		}
	}

	if (!m_player.expired())m_playerPos = m_player.lock()->GetPos();

	if (m_state != LichAnimation::State::Death)
	{
		if (m_anim->GetAction())Move();
	}

	// アニメーション作成
	m_anim->CreateAnime(m_dir, m_state, &m_polygon);

	// 弾生成
	if (m_anim->GetState() == LichAnimation::State::Attack1 && m_anim->GetUVRect() == 9)
	{
		if (!m_bBullet)
		{
			m_bBullet = true;

			// 弾生成
			std::shared_ptr<LichBullet> bullet = std::make_shared<LichBullet>();
			if (!m_player.expired())bullet->SetPlayer(m_player.lock());
			bullet->Set(m_pos, m_vec, m_status->GetAtk());
			SceneManager::Instance().AddObject(bullet);
			MapManager::Instance().AddObject(bullet);
		}
	}

	// 雷生成
	if (m_anim->GetState() == LichAnimation::State::Attack2 && m_anim->GetUVRect() == 8)
	{
		if (!m_bThunder)
		{
			m_bThunder = true;

			// 雷範囲生成
			std::shared_ptr<LichThunderCircle> circle = std::make_shared<LichThunderCircle>();
			circle->Set(m_playerPos, m_status->GetAtk());
			SceneManager::Instance().AddObject(circle);
			MapManager::Instance().AddObject(circle);
		}
	}

	// 消滅
	if (m_anim->GetKill())
	{
		// HPバー消滅
		m_hpBar->Expired();

		// クリア画面
		std::shared_ptr<StageClear> clear = std::make_shared<StageClear>();
		SceneManager::Instance().AddObject(clear);

		m_isExpired = true;
	}

	if (m_invWait > 0)m_invWait--;
}

void Lich::PostUpdate()
{
	//========================================
	// 球判定
	//========================================
	{
		// 球判定用の変数を作成
		KdCollider::SphereInfo sphere;

		// 球の中心点を設定
		Math::Vector3 pos = { 0.0f,3.0f,4.0f };
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

	// 行列作成
	Math::Matrix rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	m_world = rotX * Math::Matrix::CreateTranslation(m_pos);
}

void Lich::GenerateDepthMapFromLight()
{
	// ディゾルブ
	static float d = 1.0f;
	d -= 0.02f;
	if (d < 0.0f)
	{
		d = 0.0f;
	}

	KdShaderManager::Instance().m_StandardShader.SetDissolve(d);

	KdShaderManager::Instance().OffPixelArt();
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world, m_color);
	KdShaderManager::Instance().OnPixelArt();
}

void Lich::DrawLit()
{
	// ディゾルブ
	static float d = 1.0f;
	d -= 0.02f;
	if (d < 0.0f)
	{
		d = 0.0f;
	}

	KdShaderManager::Instance().m_StandardShader.SetDissolve(d);

	KdShaderManager::Instance().OffPixelArt();
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world, m_color);
	KdShaderManager::Instance().OnPixelArt();
}

void Lich::Hit(int _damage)
{
	if (m_invWait <= 0)
	{
		// ダメージ計算
		int damage;
		if (_damage <= m_status->GetDef())damage = 1;
		else damage = _damage - m_status->GetDef();
		m_status->Damage(damage);
		
		KdAudioManager::Instance().Play("Asset/Sounds/enemyHit.wav", false, 0.2f);

		m_invWait = 30;
		m_damageWait = 10;
		m_color = { 10,10,10,1 };
	}
}

void Lich::Init()
{
	m_anim = std::make_shared<LichAnimation>();

	m_state = LichAnimation::State::Idle;

	m_dir = LichAnimation::Dir::Left;

	m_status = std::make_shared<LichStatus>();

	m_color = { 1,1,1,1 };

	m_damageWait = 0;

	m_polygon = AssetManager::Instance().GetMaterial("lichIdle");
	m_polygon.SetUVRect(0);
	m_polygon.TurnScale();

	m_movePow = 0.15f;

	m_attackWait = 0;

	m_bBullet = false;
	m_bThunder = false;

	m_invWait = 0;

	std::shared_ptr<BossHp> hpBar = std::make_shared<BossHp>();
	hpBar->SetStatus(m_status);
	SceneManager::Instance().AddObject(hpBar);
	m_hpBar = hpBar;

	// デバッグ用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("LichCollision", { 0.0f,3.0f,4.0f }, 2.0f, KdCollider::TypeBump | KdCollider::TypeEnemy);
}

void Lich::Move()
{
	m_state = LichAnimation::State::Idle;

	m_movePow = 0.15f;

	// 方向ベクトル初期化
	m_vec = Math::Vector3::Zero;
	m_vec = m_playerPos - m_pos;

	if (m_vec.x > 0.0f)
	{
		if (m_dir == LichAnimation::Dir::Left)
		{
			m_dir = LichAnimation::Dir::Right;
			m_polygon.TurnScale();
		}
	}
	else if (m_vec.x < 0.0f)
	{
		if (m_dir == LichAnimation::Dir::Right)
		{
			m_dir = LichAnimation::Dir::Left;
			m_polygon.TurnScale();
		}
	}

	if (m_vec.Length() < 30.0f && m_vec.Length() > 20.0f)
	{
		m_vec.Normalize();
		m_vec *= m_movePow;
		m_pos += m_vec;
	}
	else if (m_vec.Length() <= 20.0f)
	{
		Attack();
	}

	if (m_attackWait > 0)m_attackWait--;
}

void Lich::Attack()
{
	m_movePow = 0.0f;

	if (m_attackWait > 0)return;

	AtkType atkType = (AtkType)(rand() % 2);

	switch (atkType)
	{
	case AtkType::FireBall:
		m_state = LichAnimation::State::Attack1;
		m_attackWait = 120;
		m_bBullet = false;
		break;
	case AtkType::Thunder:
		m_state = LichAnimation::State::Attack2;
		m_attackWait = 300;
		m_bThunder = false;
		break;
	}
}
