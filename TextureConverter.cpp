#include "TextureConverter.h"
#include "ConvertString.h"
void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath) {
	//ファイル読み込み
	LoadWICTextureFromFile(filePath);
}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath) {
	//ワイド文字列に変換
	std::wstring wfilePath = ConvertString(filePath);

	//テクスチャを読み込む

}
