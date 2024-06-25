#include "PlayerStatus.h"

#include "../../../Object/Effect/LevelUp/LevelUp.h"
#include "../../../Object/Chara/Player/Player.h"

void PlayerStatus::SetExp(int _point)
{
	m_statusList["EXP"] += _point;	// 経験値を加算

	// 次のレベルまでの経験値を超えたらレベルアップ
	if (m_statusList["EXP"] >= m_statusList["NEXTEXP"])
	{
		if (m_statusList["LEVEL"] > 99)return;

		m_statusList["LEVEL"]++;
		m_statusList["EXP"] = m_statusList["EXP"] - m_statusList["NEXTEXP"];
		m_statusList["NEXTEXP"] = (int)(m_statusList["NEXTEXP"] * 1.5f);
	
		m_statusList["POINT"] += 5;

		std::shared_ptr<LevelUp> levelUp = std::make_shared<LevelUp>();
		levelUp->SetPlayer(m_player.lock());
		levelUp->SetPos(m_player.lock()->GetPos());
		SceneManager::Instance().AddObject(levelUp);
	}
}

void PlayerStatus::Damage(int _damage)
{
	m_statusList["HP"] -= _damage;
	/*if (m_statusList["HP"] <= 0)
	{
		m_statusList["HP"] = 0;
	}*/

	if (m_statusList["HP"] <= 10)
	{
		m_statusList["HP"] = 10;
	}
}

void PlayerStatus::Heal(int _heal)
{
	m_statusList["HP"] += _heal;
	if (m_statusList["HP"] > m_statusList["MAXHP"])
	{
		m_statusList["HP"] = m_statusList["MAXHP"];
	}
}

void PlayerStatus::Init()
{
	std::ifstream ifs("Asset/Data/Status/PlayerStatus.csv"); //ファイル操作用の変数

	std::string lineString; //ファイルから1文字列読み取る変数

	//①ファイルが終わるまでファイルから1文字列ずつ読み取る
	while (std::getline(ifs, lineString))
	{
		std::istringstream iss(lineString); // 文字列を操作する変数にファイルから読み取った文字列を格納
		std::string name;					// 名前を格納
		std::string value;					// 数値を格納

		std::getline(iss, name, ',');
		std::getline(iss, value, ',');

		m_statusList[name] = stoi(value);
	}

	ifs.close();
}
