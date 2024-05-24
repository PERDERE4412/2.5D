#pragma once

class Status
{
public:

	Status() {}		// コンストラクタ	
	~Status() {}	// デストラクタ

	void Init();	// 初期化

	// ゲッター
	int GetValue(std::string _name) { return m_statusList[_name]; }

private:

	// ステータスリスト
	std::unordered_map<std::string, int> m_statusList;

};