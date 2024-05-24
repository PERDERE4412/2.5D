#pragma once

class Skill
{
public:

	int GetBonus(std::string _name) { return m_bonusList[_name]; }

private:

	void Init();			// 初期化
	
	struct SkillData
	{
		int no;				// スキル番号
		int value;			// 値
		int point;			// 必要ポイント
		std::string type;	// スキルタイプ
		bool open;			// 解放しているか
		void Set(std::string _no, std::string _value, std::string _point, std::string _type, std::string _open);
	};

	// スキルリスト
	std::vector<SkillData> m_skillList;

	// ボーナス値リスト
	std::unordered_map<std::string,int> m_bonusList;

	void CreateBonus();

private:

	Skill() { Init(); }		// コンストラクタ
	~Skill() {}				// デストラクタ

public:

	// シングルトンパターン
	static Skill& Instance()
	{
		static Skill instance;
		return instance;
	}
};