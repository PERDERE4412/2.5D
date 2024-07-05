#pragma once

class Animation
{
public:

	// プレイヤーの状態
	enum class PlayerState
	{
		None,
		Idle,
		Run,
		Roll,
		Attack1,
		Attack2,
		Attack3,
		Death
	};

	enum class PlayerDir
	{
		Right,
		Left
	};

	PlayerState GetState() { return m_state; }

	bool GetAction() { return m_bAction; }
	bool GetStiff() { return m_bStiff; }

	// アニメーション作成
	void CreateAnime(PlayerDir _dir,PlayerState _state, KdSquarePolygon* _polygon);

	void Init();				// 初期化

private:

	void AnimeCnt();

	PlayerState m_state;		// プレイヤーの状態
	float m_cnt;				// アニメのカウント
	float m_cntSpeed;			// アニメのスピード
	int m_maxAnime;				// 最大のアニメ数

	bool m_bAction;				// アクション可能か？(true:可能 false:不可能)
	bool m_bStiff;				// 硬直中か？(true:はい false:いいえ)
	int m_wait;					// 硬直時間

private:

	Animation() { Init(); }		// コンストラクタ
	~Animation() {}				// デストラクタ

public:

	// シングルトンパターン
	static Animation& Instance()
	{
		static Animation instance;
		return instance;
	}
};