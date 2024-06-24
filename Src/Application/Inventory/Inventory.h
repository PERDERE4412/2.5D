#pragma once

class Book;
class Player;

class Inventory
{
public:

	bool GetOpen() { return m_bOpen; }

	void Update();

	void SetPlayer(std::shared_ptr<Player> _player) { m_player = _player; }

private:

	void Init();

	std::weak_ptr<Player> m_player;

	void Open();
	void Close();

	bool m_bOpen;
	bool m_bKey;

	std::shared_ptr<Book> m_book;

private:

	Inventory() { Init(); }
	~Inventory() {}

public:

	static Inventory& Instance()
	{
		static Inventory instance;
		return instance;
	}
};