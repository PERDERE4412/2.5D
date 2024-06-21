#pragma once

class GetPotion :public KdGameObject
{
public:

	GetPotion() { Init(); }
	~GetPotion()override {}

	void Update()override;
	void DrawSprite()override;

private:

	void Init()override;

	KdTexture* m_pTex;
	Math::Vector2 m_pos;

	Math::Color m_color;
	float m_alpha;
	float m_addAlpha;

	bool m_bMove;
};