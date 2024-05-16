#pragma once

class Map :public KdGameObject
{
public:

	Map() { Init(); }
	~Map() {}

	void DrawLit();
	void Init();

private:

	std::shared_ptr<KdModelData> m_model=nullptr;

};