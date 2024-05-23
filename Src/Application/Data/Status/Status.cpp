#include "Status.h"

void Status::Init(int hp, int mp, int atk, int def)
{
	m_hp = hp;
	m_maxHp = hp;
	m_mp = mp;
	m_maxMp = mp;
	m_atk = atk;
	m_def = def;
}
