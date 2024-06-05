#pragma once

class Player;

class DropGold :public KdGameObject
{
public:

	DropGold() { Init(); }
	~DropGold()override {}

	void Update()override;
	void PostUpdate()override;

	void GenerateDepthMapFromLight()override;
	void DrawLit()override;
	void DrawBright()override;
	void DrawSprite()override;

	void Set(std::weak_ptr<Player> _player, Math::Vector3 _pos, int _gold);

private:

	void Init()override;

	KdSquarePolygon m_polygon;		// 板ポリゴン

	KdTexture* m_pTex = nullptr;	// 画像ポインタ

	std::weak_ptr<KdCamera> m_camera;	// カメラのweakポインタ

	Math::Vector3 m_pos;			// 座標
	Math::Color m_color;			// 色
	float m_addAlpha;				// 加算するアルファ値

	std::weak_ptr<Player> m_player;	// プレイヤー情報

	int m_gold;						// 取得するゴールド
};