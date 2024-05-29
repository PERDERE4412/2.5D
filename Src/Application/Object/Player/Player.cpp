#include "Player.h"

#include "../../Lib/Utility/Utility.h"
#include "../../Lib/AssetManager/AssetManager.h"
#include "../../Data/Status/PlayerStatus.h"
#include "../../Scene/SceneManager.h"

void Player::Update()
{
	Action();

	// 壁との当たり判定
	/*if (m_pos.x > Screen::MapMaxX)m_pos.x = Screen::MapMaxX;
	if (m_pos.x < Screen::MapMinX)m_pos.x = Screen::MapMinX;
	if (m_pos.z > Screen::MapMaxZ)m_pos.z = Screen::MapMaxZ;
	if (m_pos.z < Screen::MapMinZ)m_pos.z = Screen::MapMinZ;*/

	// 行列作成
	Math::Matrix rotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(45));
	Math::Matrix rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	m_world = rotX * rotY * Math::Matrix::CreateTranslation(m_pos);
	
	// アニメーション作成
	Animation::Instance().CreateAnime(m_dir,m_state, &m_polygon);
}

void Player::PostUpdate()
{
	// =====================
	// 球判定
	// =====================

	// 球判定用の変数を作成
	KdCollider::SphereInfo sphere;
	// 球の中心点を設定
	sphere.m_sphere.Center = m_pos;
	sphere.m_sphere.Center.y += 2.0f;
	// 球の半径を設定
	sphere.m_sphere.Radius = 2.0f;
	// 当たり判定をしたいタイプを設定
	sphere.m_type = KdCollider::TypeGround;

	//デバッグ表示
	Math::Color gyro = {1,1,0,1};
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius,gyro);

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
		// 正規化(長さを１にする)
		// 方向は絶対長さ１
		hitDir.Normalize();

		// 地面に当たっている
		m_pos += hitDir * maxOverLap;
	}
}

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world);
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_world);
}

void Player::Init()
{
	// オブジェクトタイプ
	m_objType = ObjType::Player;

	// 状態
	m_state = Animation::PlayerState::Idol;

	m_movePow = 0.2f;
	m_dir = Animation::PlayerDir::Right;

	m_comboTime = 0;
	m_combo = Combo::None;

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Player::Action()
{
	// アクション可能か？
	if (Animation::Instance().GetAction())
	{
		// 移動量初期化
		if (Animation::Instance().GetState() != Animation::PlayerState::Roll)m_movePow = 0.3f;

		// 状態を初期化
		m_state = Animation::PlayerState::Idol;

		// 硬直状態じゃなければ
		if (!Animation::Instance().GetStiff())
		{
			// 方向ベクトル初期化
			m_vec = Math::Vector3::Zero;
			
			// 移動
			Move();

			// 攻撃
			Attack();
		}
	}

	m_vec.Normalize();	// 正規化
	m_vec *= m_movePow;
	if(!Animation::Instance().GetStiff())m_pos += m_vec;		// 移動量を加算
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
	if (m_vec != Math::Vector3::Zero)m_state = Animation::PlayerState::Run;

	// 回避
	if (m_state == Animation::PlayerState::Run)
	{
		if (GetAsyncKeyState('R') & 0x8000)
		{
			m_movePow = 0.6f;
			m_state = Animation::PlayerState::Roll;
		}
	}
}

void Player::Attack()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		m_movePow = 0.0f;
		if (m_combo == Combo::None)
		{
			m_combo = Combo::One;
			m_state = Animation::PlayerState::Attack1;
			m_comboTime = 30;
		}
		else if (m_combo == Combo::One)
		{
			m_combo = Combo::Two;
			m_state = Animation::PlayerState::Attack2;
			m_comboTime = 30;
		}
		else if (m_combo == Combo::Two)
		{
			m_combo = Combo::None;
			m_state = Animation::PlayerState::Attack3;
			m_comboTime = 30;
		}
	}

	if (m_comboTime > 0)
	{
		m_comboTime--;
		if (m_comboTime <= 0)m_combo = Combo::None;
	}
}
