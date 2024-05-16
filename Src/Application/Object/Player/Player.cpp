#include "Player.h"

#include "../../Status/Status.h"

void Player::Update()
{
}

void Player::DrawLit()
{
}

void Player::Init()
{
	m_pStatus = std::make_shared<Status>();
	m_pStatus->Init(100, 100, 10, 10);
}
