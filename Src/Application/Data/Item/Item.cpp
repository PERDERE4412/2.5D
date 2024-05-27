#include "Item.h"

void Item::ChangeGold(int _gold)
{
	m_gold += _gold;

	if (m_gold > 999)m_gold = 999;
	if (m_gold < 0)m_gold = 0;
}

void Item::Init()
{
	m_gold = 0;
}
