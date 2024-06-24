#include "EnemyStatusManager.h"

void EnemyStatusManager::Init()
{
	std::ifstream ifs("Asset/Data/Status/EnemyStatus.csv"); // ファイル操作用の変数

	std::string lineString;			// ファイルから1文字列読み取る変数

	std::getline(ifs, lineString);	// 1行目を飛ばす

	// ①ファイルが終わるまでファイルから1文字列ずつ読み取る
	while (std::getline(ifs, lineString))
	{
		std::istringstream iss(lineString); // 文字列を操作する変数にファイルから読み取った文字列を格納
		std::string name;					// 名前
		std::string hp;						// HP
		std::string maxHp;					// 最大HP
		std::string atk;					// 攻撃力
		std::string def;					// 防御力
		std::string exp;					// 経験値

		std::getline(iss, name, ',');
		std::getline(iss, hp, ',');
		std::getline(iss, maxHp, ',');
		std::getline(iss, atk, ',');
		std::getline(iss, def, ',');
		std::getline(iss, exp, ',');

		m_statusList[name].name = name;
		m_statusList[name].hp = stoi(hp);
		m_statusList[name].maxHp = stoi(maxHp);
		m_statusList[name].atk = stoi(atk);
		m_statusList[name].def = stoi(def);
		m_statusList[name].exp = stoi(exp);
	}

	ifs.close();
}
