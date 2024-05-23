#pragma once

class Status
{
public:

	Status() {}		// コンストラクタ	
	~Status() {}	// デストラクタ

	void Init(int hp, int mp, int atk, int def);	// 初期化

	// ゲッター
	int GetHp() { return m_hp; }
	int GetMaxHp() { return m_maxHp; }
	int GetMp() { return m_mp; }
	int GetMaxMp() { return m_maxMp; }
	int GetAtk() { return m_atk; }
	int GetDef() { return m_def; }

private:

	int m_hp;		// HP
	int m_maxHp;	// 最大HP
	int m_mp;		// MP
	int m_maxMp;	// 最大MP
	int m_atk;		// 攻撃力
	int m_def;		// 防御力
};