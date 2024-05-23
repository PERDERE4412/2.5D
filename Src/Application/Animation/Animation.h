#pragma once

class Animation
{
public:

	// プレイヤーの状態
	enum class PlayerState
	{
		None,
		Idol,
		Walk,
	};

	PlayerState GetState() { return m_state; }

	// アニメーション作成
	void CreateAnime(PlayerState _state,KdSquarePolygon* _polygon);

private:

	void Init();				// 初期化

	PlayerState m_state;		// プレイヤーの状態
	float m_cnt;				// アニメのカウント
	float m_cntSpeed;			// アニメのスピード
	int m_maxAnime;				// 最大のアニメ数

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