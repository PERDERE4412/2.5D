#pragma once

class ActionManager
{
public:

	bool GetAction() { return m_bAction; }	// アクション中か？

	void OnAction() { m_bAction = true; }
	void OffAction() { m_bAction = false; }

	bool GetKey() { return m_bKey; }

	void OnKey() { m_bKey = true; }
	void OffKey() { m_bKey = false; }

private:

	void Init();		// 初期化

	bool m_bAction;		// アクション中か？

	bool m_bKey;		// キーを押しているか？s

private:

	ActionManager() { Init(); }		// コンストラクタ
	~ActionManager() {}				// デストラクタ

public:

	// シングルトンパターン
	static ActionManager& Instance()
	{
		static ActionManager instance;
		return instance;
	}
};