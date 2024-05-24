#include "Player.h"

//#include "../../Debug/ImGuiManager.h"

#include "../../Data/Skill/Skill.h"
#include "../../Lib/Utility/Utility.h"
#include "../../Lib/AssetManager/AssetManager.h"
#include "../../Data/Status/Status.h"

void Player::Update()
{
	int a=Skill::Instance().GetBonus("HP");

	// 状態を初期化
	m_state = Animation::PlayerState::Idol;

	// 方向ベクトルの作成
	Math::Vector3 moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState('W') & 0x8000)moveVec.z = 1.0f;
	if (GetAsyncKeyState('A') & 0x8000)moveVec.x = -1.0f;
	if (GetAsyncKeyState('S') & 0x8000)moveVec.z = -1.0f;
	if (GetAsyncKeyState('D') & 0x8000)moveVec.x = 1.0f;
	if (moveVec != Math::Vector3::Zero)m_state = Animation::PlayerState::Walk;

	moveVec.Normalize();	// 正規化
	moveVec *= MOVE_POW;
	m_pos += moveVec;		// 移動量を加算

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
	Animation::Instance().CreateAnime(m_state, &m_polygon);

	// デバッグ
	//ImGuiManager::Instance().SetPlayerPos(m_pos);
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

	// 本体
	//m_polygon = AssetManager::Instance().GetMaterial("playerIdol");
	//m_polygon.SetUVRect(1);
}
