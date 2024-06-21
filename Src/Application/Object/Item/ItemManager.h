#pragma once

#include "BaseItem.h"

class ItemManager
{
public:

	void Use();

	void GetItem(std::string _name);

	void ReduceItem(std::string _name);
	
	void ChangeItem(std::string _name);

	BaseItem::ItemData GetData(std::string _name) { return m_itemList[_name]; }

	void SetPlayer(std::shared_ptr<Player> _player) { m_player = _player; }

private:

	void Init();

	std::weak_ptr<Player> m_player;

	// アイテムリスト
	std::unordered_map<std::string,BaseItem::ItemData> m_itemList;

	// 現在のアイテムのインスタンスを保持しているポインタ
	std::shared_ptr<BaseItem> m_currentItem = nullptr;

private:

	ItemManager() { Init(); }
	~ItemManager() {}

public:

	// シングルトンパターン
	static ItemManager& Instance()
	{
		static ItemManager instance;
		return instance;
	}
};