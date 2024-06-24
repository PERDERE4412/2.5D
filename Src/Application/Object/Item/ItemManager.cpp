#include "ItemManager.h"

#include "Potion/Potion.h"

void ItemManager::Use()
{
	if (m_currentItem)
	{
		m_currentItem->Use();
	}
}

void ItemManager::GetItem(std::string _name)
{
	m_itemList[_name].num++;
	ChangeItem(_name);
}

void ItemManager::ReduceItem(std::string _name)
{
	m_itemList[_name].num--;
	if (m_itemList[_name].num <= 0)
	{
		m_currentItem->Expired();
	}
}

void ItemManager::ChangeItem(std::string _name)
{
	if (m_currentItem)m_currentItem->Expired();

	if (_name == "Potion")
	{
		std::shared_ptr<Potion> item = std::make_shared<Potion>();
		item->SetPlayer(m_player.lock());
		SceneManager::Instance().AddObject(item);
		m_currentItem = item;
	}
}

void ItemManager::Init()
{
	std::ifstream ifs("Asset/Data/Item/Item.csv"); //ファイル操作用の変数

	std::string lineString; //ファイルから1文字列読み取る変数

	std::getline(ifs, lineString);	// 1行目を飛ばす

	//①ファイルが終わるまでファイルから1文字列ずつ読み取る
	while (std::getline(ifs, lineString))
	{
		std::istringstream iss(lineString); // 文字列を操作する変数にファイルから読み取った文字列を格納
		std::string name;					// 名前
		std::string value;					// 値
		std::string num;					// 個数
		
		std::getline(iss, name, ',');
		std::getline(iss, value, ',');
		std::getline(iss, num, ',');

		m_itemList[name].value = stoi(value);
		m_itemList[name].num = stoi(num);
	}

	ifs.close();
}
