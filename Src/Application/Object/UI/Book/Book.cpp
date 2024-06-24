#include "Book.h"

#include "../../Chara/Player/Player.h"
#include "../../../Data/Status/Player/PlayerStatus.h"

#include "../../../main.h"

void Book::Update()
{
	UpdateValue();	// 値表示変更

	UpdateButton();
}

void Book::DrawSprite()
{
	// 本
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pTex, 0, 0, m_pTex->GetWidth(), m_pTex->GetHeight());

	// 値
	for (int i = 0; i < STATUS_NUM; i++)
	{
		for (int j = 0; j < DIGIT; j++)
		{
			if (!m_statusList[m_name[i]].bDraw[j])continue;

			KdShaderManager::Instance().m_spriteShader.DrawTex(m_statusList[m_name[i]].pTex, m_statusList[m_name[i]].pos[j].x, m_statusList[m_name[i]].pos[j].y, m_statusList[m_name[i]].rect[j].width * 3.5, m_statusList[m_name[i]].rect[j].height * 3.5, &m_statusList[m_name[i]].rect[j]);
		}
	}

	// ボタン
	for (int i = 0; i < BUTTON_NUM; i++)
	{
		// プラス
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_button[i].pTex[Button::Plus], m_button[i].pos[Button::Plus].x, m_button[i].pos[Button::Plus].y);

		// マイナス
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_button[i].pTex[Button::Minus], m_button[i].pos[Button::Minus].x, m_button[i].pos[Button::Minus].y);
	}

	// セット
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pSet, m_setPos.x, m_setPos.y);
}

void Book::Init()
{
	m_pTex = AssetManager::Instance().GetTex("book");

	std::unordered_map<std::string, int> statusList = m_player.lock()->GetStatus()->GetStatus();

	for (int i = 0; i < STATUS_NUM; i++)
	{
		m_statusList[m_name[i]].pTex = AssetManager::Instance().GetTex("number");
		m_statusList[m_name[i]].value = statusList[m_name[i]];

		for (int j = 0; j < DIGIT; j++)
		{
			m_statusList[m_name[i]].pos[j] = { 290.0f + 32.0f * j, 165.0f - 45.0f * i };
			m_statusList[m_name[i]].rect[j] = { 0,0,8,8 };
		}
	}

	// ボタン
	for (int i = 0; i < BUTTON_NUM; i++)
	{
		// プラス
		m_button[i].pTex[Button::Plus] = AssetManager::Instance().GetTex("plus");
		m_button[i].pos[Button::Plus] = { 400,30.0f - 45.0f * i };

		// マイナス
		m_button[i].pTex[Button::Minus] = AssetManager::Instance().GetTex("minus");
		m_button[i].pos[Button::Minus] = { 250,30.0f - 45.0f * i };
	}

	m_bKey = false;

	// セット
	m_pSet = AssetManager::Instance().GetTex("set");
	m_setPos = { 325,-210 };

	// ポイント
	m_maxPoint = m_statusList["POINT"].value;
	m_nowPoint = m_maxPoint;
	for (int i = 0; i < BUTTON_NUM; i++)m_setPoint[i] = 0;
}

void Book::UpdateValue()
{
	for (int i = 0; i < STATUS_NUM; i++)
	{
		// 数値取得
		int value = m_statusList[m_name[i]].value;

		// 桁毎に変換
		int digit[DIGIT];

		digit[0] = value / 100;
		digit[1] = (value % 100) / 10;
		digit[2] = value % 10;

		//切り取り範囲設定
		for (int j = 0; j < DIGIT; j++)
		{
			m_statusList[m_name[i]].rect[j].x = digit[j] * 8;

			if (j == 0)
			{
				if (digit[j] == 0)m_statusList[m_name[i]].bDraw[j] = false;
				else m_statusList[m_name[i]].bDraw[j] = true;
			}
			else if (j == 1)
			{
				if (digit[j - 1] == 0 && digit[j] == 0)m_statusList[m_name[i]].bDraw[j] = false;
				else m_statusList[m_name[i]].bDraw[j] = true;
			}
			else if (j == 2)
			{
				m_statusList[m_name[i]].bDraw[j] = true;
			}
		}
	}
}

void Book::UpdateButton()
{
	// マウス座標取得
	POINT mousePos;
	mousePos = GetMousePos();

	Math::Vector2 pos;
	float up;
	float down;
	float left;
	float right;

	// ボタンの中に入っているか
	for (int i = 0; i < BUTTON_NUM; i++)
	{
		// プラス
		pos = m_button[i].pos[Button::Plus];

		// ボタンの上下左右を取得
		up = pos.y + 16;
		down = pos.y - 16;
		left = pos.x - 16;
		right = pos.x + 16;

		if ((mousePos.y<up && mousePos.y>down) && (mousePos.x > left && mousePos.x < right))
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				if (!m_bKey && m_nowPoint != 0)
				{
					// 押したら
					m_bKey = true;
					KdAudioManager::Instance().Play("Asset/Sounds/button.wav", false, 0.2f);

					m_nowPoint--;
					m_setPoint[i]++;
					m_statusList[m_buttonName[i]].value++;
				}
			}
			else m_bKey = false;
		}

		// マイナス
		pos = m_button[i].pos[Button::Minus];

		// ボタンの上下左右を取得
		up = pos.y + 16;
		down = pos.y - 16;
		left = pos.x - 16;
		right = pos.x + 16;

		if (mousePos.y<up && mousePos.y>down && mousePos.x > left && mousePos.x < right)
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				if (!m_bKey && m_nowPoint != m_maxPoint)
				{
					// 押したら
					m_bKey = true;
					KdAudioManager::Instance().Play("Asset/Sounds/button.wav", false, 0.2f);

					if (m_setPoint[i] != 0)
					{
						m_setPoint[i]--;
						m_nowPoint++;
						m_statusList[m_buttonName[i]].value--;
					}
				}
			}
			else m_bKey = false;
		}
	}

	m_statusList["POINT"].value = m_nowPoint;

	// セットボタン
	pos = m_setPos;

	up = pos.y + 24;
	down = pos.y - 24;
	left = pos.x - 80;
	right = pos.x + 80;

	if (mousePos.y<up && mousePos.y>down && mousePos.x > left && mousePos.x < right)
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if (!m_bKey)
			{
				// 押したら
				m_bKey = true;
				KdAudioManager::Instance().Play("Asset/Sounds/button.wav", false, 0.2f);

				for (int i = 0; i < STATUS_NUM; i++)
				{
					m_player.lock()->GetStatus()->SetValue(m_name[i],m_statusList[m_name[i]].value);
				}
			}
		}
		else m_bKey = false;
	}
}

POINT Book::GetMousePos()
{
	POINT mousePos;

	// ディスプレイ上のマウス座標を取得(ディスプレイの左上が(0,0))
	GetCursorPos(&mousePos); // 変数のアドレスを渡す

	// 指定のウィンドウ基準のマウス座標に変換(ウィンドウの左上が(0,0))
	ScreenToClient(Application::Instance().GetWindowHandle(), &mousePos);

	// マウスの座標系を実行ウィンドウの座標系に補正する
	mousePos.x = mousePos.x - 1280 / 2;
	mousePos.y = -mousePos.y + 720 / 2;

	return mousePos;
}
