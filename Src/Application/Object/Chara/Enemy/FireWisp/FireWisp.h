#pragma once

#include "../BaseEnemy.h"

class FireWisp :public BaseEnemy
{
public:

	FireWisp() { Init(); }
	~FireWisp()override {}

	void Update()override;
	void PostUpdate()override;


private:

	void Init()override;

	void Move();
	void Attack();

	bool m_bBullet;						// 弾生成したか
};