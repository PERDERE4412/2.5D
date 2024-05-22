#pragma once

class AssetManager
{
public:

	// 画像のポインタを取得
	KdSquarePolygon GetMaterial(std::string materialName);

private:

	std::unordered_map<std::string, KdSquarePolygon> m_materialList;
	void LoadMaterial(std::string _name, std::string _path) { m_materialList[_name].SetMaterial(_path); }
	void SetMaterial(std::string _name,float _scale,KdSquarePolygon::PivotType _pivot,int _splitX,int _splitY);

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