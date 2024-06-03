#pragma once

class EnemyAnimation
{
public:

	// エネミーの状態
	enum class EnemyState
	{
		None,
		Idle,
		Run,
		Attack1,
		Attack2,
	};

	enum class EnemyDir
	{
		Right,
		Left
	};

	EnemyState GetState() { return m_state; }

	bool GetAction() { return m_bAction; }
	bool GetStiff() { return m_bStiff; }

	// アニメーション作成
	void CreateAnime(EnemyDir _dir, EnemyState _state, KdSquarePolygon* _polygon);

private:

	void Init();				// 初期化

	void AnimeCnt();

	EnemyState m_state;			// プレイヤーの状態
	float m_cnt;				// アニメのカウント
	float m_cntSpeed;			// アニメのスピード
	int m_maxAnime;				// 最大のアニメ数

	bool m_bAction;				// アクション可能か？(true:可能 false:不可能)
	bool m_bStiff;				// 硬直中か？(true:はい false:いいえ)
	int m_wait;					// 硬直時間

private:

	EnemyAnimation() { Init(); }		// コンストラクタ
	~EnemyAnimation() {}				// デストラクタ

public:

	// シングルトンパターン
	static EnemyAnimation& Instance()
	{
		static EnemyAnimation instance;
		return instance;
	}
};