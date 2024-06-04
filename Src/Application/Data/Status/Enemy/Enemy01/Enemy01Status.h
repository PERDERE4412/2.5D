#pragma once

class Enemy01Status
{
public:

	Enemy01Status() { Init(); }
	~Enemy01Status() {}

	void Damage(int _damage) { m_statusList["HP"] -= _damage; }
	int GetValue(std::string _name) { return m_statusList[_name]; }

private:

	void Init();

	std::unordered_map<std::string, int> m_statusList;
};