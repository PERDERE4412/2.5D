#pragma once

class StageClear :public KdGameObject
{
public:

	StageClear() { Init(); }
	~StageClear()override {}

	void Update()override;
	void DrawSprite()override;

private:

	void Init()override;

	KdTexture* m_pTex;

	Math::Color m_color;
	float m_alpha;
	float m_addAlpha;

	bool m_bAlpha;
	int m_wait;
};