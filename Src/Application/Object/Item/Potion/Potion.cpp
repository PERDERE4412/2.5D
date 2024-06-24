#include "Potion.h"

#include "../ItemManager.h"
#include "../../../Data/Status/Player/PlayerStatus.h"
#include "../../Effect/Heal/Heal.h"
#include "../../Chara/Player/Player.h"

void Potion::Use()
{
	if (m_data.num <= 0)return;

	m_data.num--;	// 個数を減らす
	ItemManager::Instance().ReduceItem("Potion");
	KdAudioManager::Instance().Play("Asset/Sounds/heal.wav", false, 0.05f);

	// 回復処理
	m_player.lock()->GetStatus()->Heal(m_data.value);
	
	// エフェクト
	std::shared_ptr<Heal> heal = std::make_shared<Heal>();
	heal->SetPos(m_player.lock()->GetPos());
	SceneManager::Instance().AddObject(heal);
}

void Potion::Init()
{
	BaseItem::Init();

	m_pItemTex = AssetManager::Instance().GetTex("potion");

	m_data = ItemManager::Instance().GetData("Potion");
}
