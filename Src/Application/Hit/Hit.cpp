#include "Hit.h"

#include "../Scene/SceneManager.h"

void Hit::Update()
{
	m_objList = SceneManager::Instance().GetObjList();
}

void Hit::Init()
{
}