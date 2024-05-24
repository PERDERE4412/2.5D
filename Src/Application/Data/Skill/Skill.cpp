#include "Skill.h"

void Skill::Init()
{
	std::ifstream ifs("Asset/Data/Player/PlayerSkill.csv"); //ファイル操作用の変数

	std::string lineString; //ファイルから1文字列読み取る変数
	std::getline(ifs, lineString);

	//①ファイルが終わるまでファイルから1文字列ずつ読み取る
	while (std::getline(ifs, lineString))
	{
		std::istringstream iss(lineString); // 文字列を操作する変数にファイルから読み取った文字列を格納
		std::string no;						// 番号を格納
		std::string value;					// 数値を格納
		std::string point;					// 必要ポイント
		std::string type;					// スキルタイプ
		std::string open;					// 解放フラグ

		std::getline(iss, no, ',');
		std::getline(iss, value, ',');
		std::getline(iss, point, ',');
		std::getline(iss, type, ',');
		std::getline(iss, open, ',');

		SkillData data;
		data.Set(no, value, point, type, open);

		m_skillList.push_back(data);
	}

	ifs.close();

	// ボーナス値作成
	CreateBonus();
}

void Skill::CreateBonus()
{
	// ボーナス値初期化
	m_bonusList["HP"] = 0;
	m_bonusList["MP"] = 0;
	m_bonusList["ATK"] = 0;
	m_bonusList["DEF"] = 0;

	// ボーナス値加算
	for (SkillData& data : m_skillList)
	{
		if (!data.open)continue;

		if (data.type == "HP")m_bonusList["HP"]+=data.value;
		if (data.type == "MP")m_bonusList["MP"] += data.value;;
		if (data.type == "ATK")m_bonusList["ATK"] += data.value;;
		if (data.type == "DEF")m_bonusList["DEF"] += data.value;;
	}
}

void Skill::SkillData::Set(std::string _no, std::string _value, std::string _point, std::string _type, std::string _open)
{
	no = stoi(_no);
	value = stoi(_value);
	point = stoi(_point);
	type = _type;
	if (_open == "FALSE")open = false;
	if (_open == "TRUE")open = true;
}
