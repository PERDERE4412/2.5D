#pragma once

class AssetManager
{
public:

	// ポリゴン
	KdSquarePolygon GetMaterial(std::string _name);

	// モデル
	KdModelData GetModel(std::string _name);

private:

	// ポリゴン
	std::unordered_map<std::string, KdSquarePolygon> m_materialList;
	void LoadMaterial(std::string _name, std::string _path) { m_materialList[_name].SetMaterial(_path); }
	void SetMaterial(std::string _name, float _scale, KdSquarePolygon::PivotType _pivot, int _splitX, int _splitY);

	// モデル
	std::unordered_map<std::string, KdModelData> m_modelList;
	void LoadModel(std::string _name, std::string _path) { m_modelList[_name].Load(_path); }

	void Init();				// 初期化

private:

	AssetManager() { Init(); }	// コンストラクタ
	~AssetManager() {}			// デストラクタ

public:

	// シングルトンパターン
	static AssetManager& Instance()
	{
		static AssetManager instance;
		return instance;
	}
};