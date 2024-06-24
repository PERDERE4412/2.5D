#pragma once

class ClickStart :public KdGameObject
{
public:

	ClickStart() { Init(); }
	~ClickStart()override {}

	void Update()override;
	void DrawSprite()override;

private:

	void Init()override;

	KdTexture* m_pTex;
	Math::Color m_color;

	float m_alpha;
	float m_addAlpha;
};