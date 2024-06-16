#pragma once

class MiniMap :public KdGameObject
{
public:

	MiniMap() { Init(); }
	~MiniMap()override {}

	void DrawSprite()override;

	void Set(int _mapId);

private:

	void Init()override;

	KdTexture* m_frameTex;
	KdTexture* m_mapTex;

	KdTexture* m_playerTex;
	Math::Vector2 m_nowPlayerPos;
	std::unordered_map<int, Math::Vector2> m_playerPosList;

	bool m_bKey;
};