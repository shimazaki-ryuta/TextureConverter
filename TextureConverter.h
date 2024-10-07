#pragma once
#include <string>
class TextureConverter
{
public:
	
	//テクスチャをWICからDDSに変換する
	void ConvertTextureWICToDDS(const std::string& filePath);
private:
	//テクスチャファイル読み込み
	void LoadWICTextureFromFile(const std::string& filePath);
};
