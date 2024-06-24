#pragma once

class Fade
{
public:

	void Update();		// 更新
	void DrawSprite();	// 描画

	void BootChangeMap(std::string _type);		// マップ切り替え起動
	void BootChangeTitle();
	void BootChangeGame();

	bool GetMapFade();
	bool GetGameFade();

private:

	void Init();								// 初期化

	void UpdateMapChange(std::string _type);	// マップ切り替え
	void UpdateTitleChange();
	void UpdateGameChange();

	KdTexture* m_pTex;		// 画像
	Math::Color m_color;	// 色
	float m_alpha;			// 透明度
	float m_addAlpha;		// 加算透明度

	std::string m_type;		// ドアタイプ

	bool m_bGameFade;		// ゲームにフェード中か
	bool m_bTitleFade;		// タイトルにフェード中か
	bool m_bMapFade;		// マップにフェード中か
	bool m_bInOut;			// フェードイン・アウト (true:イン false:アウト)

private:

	Fade() { Init(); }
	~Fade() {}

public:

	// シングルトンパターン
	static Fade& Instance()
	{
		static Fade instance;
		return instance;
	}
};