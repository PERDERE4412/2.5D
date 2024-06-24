#pragma once

class Player;

class Book :public KdGameObject
{
public:

	Book() {}
	~Book()override {}

	void Update()override;

	void DrawSprite()override;

	void Init()override;

	void SetPlayer(std::shared_ptr<Player> _player) { m_player = _player; }

private:

	void UpdateValue();
	void UpdateButton();

	POINT GetMousePos();

	std::weak_ptr<Player> m_player;

	KdTexture* m_pTex;	// 本

	static const int STATUS_NUM = 8;
	std::string m_name[STATUS_NUM] = { "LEVEL","POINT","HP","MAXHP","ATK","DEF","EXP","NEXTEXP" };

	// 値表示変更関連
	static const int DIGIT = 3;
	struct StatusData
	{
		KdTexture* pTex;
		Math::Rectangle rect[DIGIT];
		Math::Vector2 pos[DIGIT];
		bool bDraw[DIGIT];
		int value;
	};

	std::unordered_map <std::string, StatusData> m_statusList;

	// ボタン関連
	enum Button
	{
		Plus,
		Minus,
		Kind
	};

	static const int BUTTON_NUM=3;
	std::string m_buttonName[BUTTON_NUM] = { "MAXHP","ATK","DEF" };

	struct ButtonData
	{
		KdTexture* pTex[Button::Kind];
		Math::Vector2 pos[Button::Kind];
	};

	ButtonData m_button[BUTTON_NUM];

	bool m_bKey;

	int m_maxPoint;
	int m_nowPoint;
	int m_setPoint[BUTTON_NUM];

	KdTexture* m_pSet;
	Math::Vector2 m_setPos;
};