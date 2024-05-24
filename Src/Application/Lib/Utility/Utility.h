#pragma once

namespace Screen
{
	// 画面
	const int Width = 1280;				// 横幅
	const int Height = 720;				// 縦幅
	const int HalfWidth = Width / 2;	// 横幅の半分
	const int HalfHeight = Height / 2;	// 縦幅の半分
	const int Left = -Width / 2;		// 画面の左端
	const int Right = Width / 2;		// 画面の右端
	const int Top = Height / 2;			// 画面の上端
	const int Bottom = -Height / 2;		// 画面の下端

	// マップ
	const float MapMaxX = 17.0f;		// マップの奥端(X軸)
	const float MapMinX = -17.0f;		// マップの手前端(X軸)
	const float MapMaxZ = 14.0f;		// マップの奥端(Z軸)
	const float MapMinZ = -20.5f;		// マップの手前端(Z軸)
}