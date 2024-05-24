#pragma once

class Item
{
public:

	void ChangeGold(int _gold) { m_gold += _gold; }

	// ゲッター
	int GetGold() { return m_gold; }

private:

	void Init();			// 初期化

	int m_gold;				// お金

private:

	Item() { Init(); }		// コンストラクタ
	~Item() {}				// デストラクタ

public:

	// シングルトンパターン
	static Item& Instance()
	{
		static Item instance;
		return instance;
	}
};