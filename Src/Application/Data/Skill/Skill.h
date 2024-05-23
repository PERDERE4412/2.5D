#pragma once

class Skill
{
public:

private:

	void Init();			// 初期化

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