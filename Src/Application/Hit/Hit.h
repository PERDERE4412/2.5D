#pragma once

class Hit
{
public:

	void Update();

private:

	void Init();		// 初期化

	std::list<std::shared_ptr<KdGameObject>> m_objList;	// オブジェクトリスト

private:

	Hit() {}			// コンストラクタ
	~Hit() { Init(); }	// デストラクタ

public:

	// シングルトンパターン
	static Hit& Instance()
	{
		static Hit Instance;
		return Instance;
	}
};