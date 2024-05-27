#pragma once

class LevelBar :public KdGameObject
{
public:

	LevelBar() { Init(); }
	~LevelBar()override {}

	void Update()override;
	void DrawSprite()override;

private:

	void Init()override;

	struct  TexData
	{
		KdTexture* pTex;
		Math::Vector3 pos;
		Math::Vector3 size;
		Math::Matrix mat;
		Math::Rectangle rect;
		int width;
		int height;
		void Set();
	};

	TexData m_frame;
	TexData m_bar;
};