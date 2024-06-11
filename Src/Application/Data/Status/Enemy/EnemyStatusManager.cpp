#include "EnemyStatusManager.h"

void EnemyStatusManager::Init()
{
	// Enemy01
	std::ifstream ifs("Asset/Data/Enemy/Warrior/status.csv"); //ファイル操作用の変数

	std::string lineString; //ファイルから1文字列読み取る変数

	//①ファイルが終わるまでファイルから1文字列ずつ読み取る
	while (std::getline(ifs, lineString))
	{
		std::istringstream iss(lineString); // 文字列を操作する変数にファイルから読み取った文字列を格納
		std::string name;					// 名前を格納
		std::string value;					// 数値を格納

		std::getline(iss, name, ',');
		std::getline(iss, value, ',');

		m_statusList["Warrior"][name] = stoi(value);
	}

	ifs.close();
}
