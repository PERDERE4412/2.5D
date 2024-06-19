#pragma once

class Player;
class Lich;

class Movie
{
public:

	void Update();

	void BootMovie() { m_bMovie = true; }
	void StartMovie() { m_bStart = true; }

	bool GetMovie() { return m_bMovie; }
	bool GetStart() { return m_bStart; }

	void SetCamera(std::shared_ptr<KdCamera> _camera) { m_camera = _camera; }
	void SetPlayer(std::shared_ptr<Player> _player) { m_player = _player; }
	void SetLich(std::shared_ptr<Lich> _lich) { m_lich = _lich; }

private:

	void Init();		// 初期化

	void MoveCamera();	// カメラの移動
	void BossSpawn();	// ボスの出現アニメーション

	bool m_bMovie;		// ムービーをするか？
	bool m_bStart;		// ムービー起動

	bool m_bMove;		// カメラ移動(true:スポーン座標 false:プレイヤー座標)する
	bool m_bSpawn;		// スポーン中か

	std::weak_ptr<KdCamera> m_camera;
	std::weak_ptr<Player> m_player;
	std::weak_ptr<Lich> m_lich;

	Math::Vector3 m_cameraPos;		// カメラ座標
	Math::Vector3 m_cameraDistPos;	// どれだけ遠ざけるか
	Math::Vector3 m_playerPos;		// プレイヤー座標
	Math::Vector3 m_lichSpawnPos;	// スポーン座標

private:

	Movie() { Init(); }
	~Movie() {}

public:

	// シングルトンパターン
	static Movie& Instance()
	{
		static Movie instance;
		return instance;
	}
};