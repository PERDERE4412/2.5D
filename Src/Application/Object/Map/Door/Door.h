﻿#pragma once

class Player;

class Door :public KdGameObject
{
public:

	Door() { Init(); }			// コンストラクタ
	~Door()override {}			// デストラクタ

	void Update()override;		// 更新
	void DrawLit()override;		// 描画
	void DrawSprite()override;	// 描画

	void SetPlayer(std::weak_ptr<Player> _player) { m_player = _player; }

	void Set(std::string _type);

private:

	void Init()override;	// 初期化

	KdModelData m_model;	// モデルデータ
	Math::Vector3 m_pos;	// 座標

	std::string m_type;		// ドアタイプ

	struct DoorData
	{
		Math::Vector3 pos;	// ドア座標
		float deg=0.0f;		// 角度
	};

	std::unordered_map<std::string, DoorData> m_doorList;	// ドアデータリスト

	// UI
	KdTexture* m_pTex;		// 画像データ
	bool m_bEnter;

	std::weak_ptr<Player> m_player;
	std::weak_ptr<KdCamera> m_camera;
};