#pragma once

class WarriorStatus
{
public:

	WarriorStatus() { Init(); }
	~WarriorStatus() {}

	void Damage(int _damage) { m_statusList["HP"] -= _damage; }
	int GetValue(std::string _name) { return m_statusList[_name]; }

private:

	void Init();

	std::unordered_map<std::string, int> m_statusList;
};