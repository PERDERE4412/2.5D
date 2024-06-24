#include "Inventory.h"

#include "../Object/UI/Book/Book.h"
#include "../Object/Chara/Player/Player.h"

void Inventory::Update()
{
	if (GetAsyncKeyState('M') & 0x8000)
	{
		if (!m_bKey)
		{
			m_bKey = true;
			if (!m_bOpen)Open();
			else Close();
		}
	}
	else m_bKey = false;

	if (m_bOpen)m_book->Update();
}

void Inventory::Open()
{
	m_bOpen = true;

	std::shared_ptr<Book> book=std::make_shared<Book>();
	book->SetPlayer(m_player.lock());
	book->Init();
	SceneManager::Instance().AddObject(book);
	m_book = book;
}

void Inventory::Close()
{
	m_bOpen = false;

	m_book->Expired();
}

void Inventory::Init()
{
	m_bOpen = false;
	m_bKey = false;
}
