#pragma once

class EnemyAnimation
{
public:

	EnemyAnimation() { Init(); }		// コンストラクタ
	~EnemyAnimation() {}				// デストラクタ

	// エネミーの状態
	enum class State
	{
		None,
		Idle,
		Run,
		Attack,
		Death,
	};

	State GetState() { return m_state; }

	int GetUVRect() { return (int)m_cnt; }

	bool GetAction() { return m_bAction; }
	bool GetStiff() { return m_bStiff; }

	bool GetKill() { return m_bKill; }

	// アニメーション作成
	void CreateAnime(std::string _name,Utility::CharaDir _dir, State _state, KdSquarePolygon* _polygon);

private:

	void Init();				// 初期化

	void AnimeCnt();

	State m_state;				// プレイヤーの状態
	float m_cnt;				// アニメのカウント
	float m_cntSpeed;			// アニメのスピード
	int m_maxAnime;				// 最大のアニメ数

	bool m_bAction;				// アクション可能か？(true:可能 false:不可能)
	bool m_bStiff;				// 硬直中か？(true:はい false:いいえ)
	int m_wait;					// 硬直時間

	bool m_bKill;				// 殺す
};