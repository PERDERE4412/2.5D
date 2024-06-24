#pragma once

class Title :public KdGameObject
{
public:

	Title() { Init(); }
	~Title()override {}

	void DrawSprite()override;

private:

	void Init()override;

	KdTexture* m_pTex;
};