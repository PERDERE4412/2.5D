#pragma once

class Player;

class BaseItem:public KdGameObject
{
public:

	BaseItem() { Init(); }
	~BaseItem()override {}

	void Update()override;
	void DrawSprite()override;

	virtual void Use() {}

	void SetPlayer(std::shared_ptr<Player> _player) { m_player = _player; }

	struct ItemData
	{
		int value;
		int num;
	};

protected:

	void Init()override;

	std::weak_ptr<Player> m_player;

	KdTexture* m_pItemTex;
	KdTexture* m_pNumTex;
	Math::Rectangle m_numRect;

	ItemData m_data;
};