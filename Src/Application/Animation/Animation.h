#pragma once

class Animation
{
public:

	enum class PlayerState
	{
		Idol,
		Walk,
	};

	PlayerState GetState() { return m_state; }
	void SetState(PlayerState _state) { m_state = _state; }

	void CreateAnime(KdSquarePolygon* _polygon);

private:

	void Init();

	PlayerState m_state;

private:

	Animation() { Init(); }
	~Animation() {}

public:

	// シングルトンパターン
	static Animation& Instance()
	{
		static Animation instance;
		return instance;
	}
};