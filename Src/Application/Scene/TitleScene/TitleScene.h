#pragma once

#include"../BaseScene/BaseScene.h"

class TitleScene : public BaseScene
{
public :

	TitleScene() { Init(); }
	~TitleScene() {}

private :

	void Event() override;
	void Init() override;

	Math::Vector3 m_pos = {};

	bool m_bCreate;
	bool m_bKey;
};
