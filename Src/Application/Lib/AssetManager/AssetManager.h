#pragma once

class AssetManager
{
public:

	// 画像のポインタを取得
	KdSquarePolygon* GetMaterial(std::string TextureName);

private:

	std::unordered_map<std::string, KdSquarePolygon> m_materialList;
	void LoadMaterial(std::string TextureName, std::string file_name) { m_materialList[TextureName].SetMaterial(file_name); }

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