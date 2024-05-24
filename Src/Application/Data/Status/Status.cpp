#include "Status.h"

void Status::Init()
{
	std::ifstream ifs("Asset/Data/Player/PlayerStatus.csv"); //ファイル操作用の変数

	std::string lineString; //ファイルから1文字列読み取る変数

	//①ファイルが終わるまでファイルから1文字列ずつ読み取る
	while (std::getline(ifs, lineString))
	{
		std::istringstream iss(lineString); // 文字列を操作する変数にファイルから読み取った文字列を格納
		std::string commaString;			// ファイルから読み取った文字列をコンマ区切りにする
		std::string value;					// 数値を格納

		std::getline(iss, commaString, ',');
		std::getline(iss, value, ',');

		m_statusList[commaString] = stoi(value);
	}

	ifs.close();
}
