#pragma once
#include <string>
#include "externals/DirectXTex/DirectXTex/DirectXTex.h"
class TextureConverter
{
public:
	
	//テクスチャをWICからDDSに変換する
	void ConvertTextureWICToDDS(const std::string& filePath);

	//パスとファイル名を分割する
	void SeparateFilePath(const std::wstring& filePath);

private:
	//テクスチャファイル読み込み
	void LoadWICTextureFromFile(const std::string& filePath);

	//DDSテクスチャファイル書き出し
	void SaveDDSTextureToFile();

	DirectX::TexMetadata metadata_;
	DirectX::ScratchImage scratchImage_;

	std::wstring directoryPath_;
	//ファイル名
	std::wstring fileName_;
	//拡張子
	std::wstring fileExt_;
};
