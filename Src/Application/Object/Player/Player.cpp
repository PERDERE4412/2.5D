#include "Player.h"

#include "../../Lib/Utility/Utility.h"
#include "../../Lib/AssetManager/AssetManager.h"
#include "../../Data/Status/Status.h"

void Player::Update()
{
	Action();

	// 壁との当たり判定
	if (m_pos.x > Screen::MapMaxX)m_pos.x = Screen::MapMaxX;
	if (m_pos.x < Screen::MapMinX)m_pos.x = Screen::MapMinX;
	if (m_pos.z > Screen::MapMaxZ)m_pos.z = Screen::MapMaxZ;
	if (m_pos.z < Screen::MapMinZ)m_pos.z = Screen::MapMinZ;

	// 行列作成
	Math::Matrix rotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(45));
	Math::Matrix rotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	m_world = rotX * rotY * Math::Matrix::CreateTranslation(m_pos);
	
	// アニメーション作成
	Animation::Instance().CreateAnime(m_dir,m_state, &m_polygon);
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

	// ステータス
	m_pStatus = std::make_shared<Status>();
	m_pStatus->Init();

	// 状態
	m_state = Animation::PlayerState::Idol;

	m_movePow = 0.2f;
	m_dir = Animation::PlayerDir::Right;

	m_comboTime = 0;
	m_combo = Combo::None;

	// 本体
	//m_polygon = AssetManager::Instance().GetMaterial("playerIdol");
	//m_polygon.SetUVRect(1);
}

void Player::Action()
{
	// アクション可能か？
	if (Animation::Instance().GetAction())
	{
		// 移動量初期化
		if (Animation::Instance().GetState() != Animation::PlayerState::Roll)m_movePow = 0.2f;

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
			m_movePow = 0.4f;
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
