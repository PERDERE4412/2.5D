#include "Player.h"

#include "../../../Data/Status/Player/PlayerStatus.h"
#include "../../../Map/MapManager.h"
#include "../../Item/ItemManager.h"
#include "PlayerSwordEffect1.h"
#include "PlayerSwordEffect2.h"
#include "PlayerSwordEffect3.h"
#include "../../Effect/Hurt/Hurt.h"

void Player::PreUpdate()
{
	if (Animation::Instance().GetAction())
	{
		// 移動量初期化
		if (Animation::Instance().GetState() != Animation::PlayerState::Roll)m_movePow = 0.3f;

		// 状態を初期化
		m_state = Animation::PlayerState::Idle;
	}

	if (m_damageWait > 0)m_damageWait--;
	if (m_damageWait <= 0)
	{
		m_color = { 1,1,1,1 };
	}
}

void Player::Update()
{
	Action();

	if (m_invWait > 0)m_invWait--;
}

void Player::PostUpdate()
{
	// =====================
	// 球判定
	// =====================
	{
		// 球判定用の変数を作成
		KdCollider::SphereInfo sphere;
		// 球の中心点を設定
		sphere.m_sphere.Center = m_pos;
		sphere.m_sphere.Center.y += 2.0f;
		// 球の半径を設定
		sphere.m_sphere.Radius = 2.0f;
		// 当たり判定をしたいタイプを設定
		sphere.m_type = KdCollider::TypeGround | KdCollider::TypeBump;

		// 球に当たったオブジェクトの情報を格納
		std::list<KdCollider::CollisionResult> retSphereList;

		// 当たり判定だよ！！！！！！！！！！！！！！！！！！！！！
		for (auto& obj : SceneManager::Instance().GetObjList())
		{
			obj->Intersects(sphere, &retSphereList);
		}

		// 球に当たったリストから一番近いオブジェクトを検出
		float maxOverLap = 0;	// はみでたレイの長さ
		Math::Vector3 hitDir;	// 当たった方向
		bool isHit = false;		// 当たっていたらtrue
		for (auto& ret : retSphereList)
		{
			// 球にめりこんで、オーバーした長さが一番長いものを探す
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

			// 正規化(長さを１にする)
			// 方向は絶対長さ１
			hitDir.Normalize();

			// 地面に当たっている
			m_pos += hitDir * maxOverLap;
		}
	}

	// アニメーション作成
	Animation::Instance().CreateAnime(m_dir, m_state, &m_polygon);

	// 行列作成
	Math::Matrix rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	m_world = rotX * Math::Matrix::CreateTranslation(m_pos);
}

void Player::Hit(int _damage)
{
	if (m_invWait <= 0 && m_state != Animation::PlayerState::Roll)
	{
		// ダメージ計算
		int damage;
		if (_damage <= m_status.lock()->GetValue("DEF"))damage = 1;
		else damage = _damage - m_status.lock()->GetValue("DEF");
		m_status.lock()->Damage(damage);

		m_invWait = 120;
		m_color = { 10,10,10,1 };
		m_damageWait = 10;

		KdAudioManager::Instance().Play("Asset/Sounds/playerHit.wav", false, 0.2f);

		std::shared_ptr<Hurt> hurt = std::make_shared<Hurt>();
		hurt->SetPos(m_pos);
		SceneManager::Instance().AddObject(hurt);
		MapManager::Instance().AddObject(hurt);
	}
}

void Player::Init()
{
	m_invWait = 0;

	m_polygon = AssetManager::Instance().GetMaterial("playerIdle");

	// 状態
	m_state = Animation::PlayerState::Idle;

	// ステータス
	m_status = std::make_shared<PlayerStatus>();
	
	m_color = { 1,1,1,1 };
	m_damageWait = 0;

	m_movePow = 0.2f;
	m_dir = Animation::PlayerDir::Right;

	m_comboTime = 0;
	m_combo = Combo::None;

	m_bUse = false;

	m_walkSoundWait = 0;

	// デバッグ表示
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("PlayerCollision", { 0.0f,3.0f,0.0f }, 2.0f, KdCollider::TypePlayer);
}

void Player::Action()
{
	// アクション可能か？
	if (Animation::Instance().GetAction())
	{
		// 硬直状態じゃなければ
		if (!Animation::Instance().GetStiff())
		{
			// 方向ベクトル初期化
			m_vec = Math::Vector3::Zero;

			// アイテム使用
			if (GetAsyncKeyState('U') & 0x8000)
			{
				if (!m_bUse)
				{
					m_bUse = true;
					ItemManager::Instance().Use();
				}
			}
			else m_bUse = false;

			// 移動
			Move();

			// 攻撃
			Attack();
		}
	}

	m_vec.Normalize();	// 正規化
	m_vec *= m_movePow;
	if (!Animation::Instance().GetStiff())m_pos += m_vec;		// 移動量を加算
}

void Player::Move()
{
	if (GetAsyncKeyState('W') & 0x8000)m_vec.z = 1.0f;
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_vec.x = -1.0f;
		if (m_dir == Animation::PlayerDir::Right)
		{
			m_dir = Animation::PlayerDir::Left;
			m_polygon.TurnScale();
		}
	}
	if (GetAsyncKeyState('S') & 0x8000)m_vec.z = -1.0f;
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_vec.x = 1.0f;
		if (m_dir == Animation::PlayerDir::Left)
		{
			m_dir = Animation::PlayerDir::Right;
			m_polygon.TurnScale();
		}
	}

	if (m_vec != Math::Vector3::Zero)
	{
		if (m_walkSoundWait <= 0)
		{
			KdAudioManager::Instance().Play("Asset/Sounds/walk.wav",false, 0.1f);
			m_walkSoundWait = 30;
		}

		m_state = Animation::PlayerState::Run;
	}

	if (m_walkSoundWait > 0)m_walkSoundWait--;

	// 回避
	if (m_state == Animation::PlayerState::Run)
	{
		if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		{
			m_movePow = 0.6f;
			m_state = Animation::PlayerState::Roll;
			KdAudioManager::Instance().Play("Asset/Sounds/roll.wav", false, 0.1f);
		}
	}
}

void Player::Attack()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		m_movePow = 0.0f;

		bool right = true;
		if (m_dir == Animation::PlayerDir::Left)right = false;

		if (m_combo == Combo::None)
		{
			m_combo = Combo::One;
			m_state = Animation::PlayerState::Attack1;
			std::shared_ptr<PlayerSwordEffect1> effect = std::make_shared<PlayerSwordEffect1>();
			effect->SetPos(m_pos, right, m_status.lock()->GetValue("ATK"));
			SceneManager::Instance().AddObject(effect);
			KdAudioManager::Instance().Play("Asset/Sounds/attack1.wav", false, 0.2f);
			m_comboTime = 30;
		}
		else if (m_combo == Combo::One)
		{
			m_combo = Combo::Two;
			m_state = Animation::PlayerState::Attack2;
			std::shared_ptr<PlayerSwordEffect2> effect = std::make_shared<PlayerSwordEffect2>();
			effect->SetPos(m_pos, right, m_status.lock()->GetValue("ATK"));
			SceneManager::Instance().AddObject(effect);
			KdAudioManager::Instance().Play("Asset/Sounds/attack1.wav", false, 0.2f);
			m_comboTime = 30;
		}
		else if (m_combo == Combo::Two)
		{
			m_combo = Combo::None;
			m_state = Animation::PlayerState::Attack3;
			std::shared_ptr<PlayerSwordEffect3> effect = std::make_shared<PlayerSwordEffect3>();
			effect->SetPos(m_pos, right,m_status.lock()->GetValue("ATK"));
			SceneManager::Instance().AddObject(effect);
			KdAudioManager::Instance().Play("Asset/Sounds/attack2.wav", false, 0.2f);
			m_comboTime = 30;
		}
	}

	if (m_comboTime > 0)
	{
		m_comboTime--;
		if (m_comboTime <= 0)m_combo = Combo::None;
	}
}