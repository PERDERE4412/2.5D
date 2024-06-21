#include "Potion.h"

#include "../ItemManager.h"
#include "../../../Data/Status/Player/PlayerStatus.h"
#include "../../Effect/Heal/Heal.h"
#include "../../../Scene/SceneManager.h"
#include "../../Chara/Player/Player.h"

void Potion::Use()
{
	if (m_data.num <= 0)return;

	m_data.num--;	// 個数を減らす
	ItemManager::Instance().ReduceItem("Potion");

	// 回復処理
	PlayerStatus::Instance().Heal(m_data.value);

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
