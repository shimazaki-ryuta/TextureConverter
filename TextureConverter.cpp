#include "TextureConverter.h"
#include "ConvertString.h"
//#include <cstdio>
//#include <cstdlib>
#include <cassert>
#include <windows.h>
void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath) {
	//ファイル読み込み
	LoadWICTextureFromFile(filePath);

	SaveDDSTextureToFile();
}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath) {
	//ワイド文字列に変換
	std::wstring wfilePath = ConvertString(filePath);

	HRESULT hr;
	//テクスチャを読み込む
	hr = DirectX::LoadFromWICFile(wfilePath.c_str(),DirectX::WIC_FLAGS_NONE,&metadata_, scratchImage_);
	assert(SUCCEEDED(hr));

	//パスとファイル名を分割
	SeparateFilePath(wfilePath);

}

void TextureConverter::SaveDDSTextureToFile() {
	metadata_.format = DirectX::MakeSRGB(metadata_.format);
	HRESULT hr;
	std::wstring filePath = directoryPath_ + fileName_ + L".dds";

	hr = DirectX::SaveToDDSFile(scratchImage_.GetImages(),scratchImage_.GetImageCount(),metadata_, DirectX::DDS_FLAGS_NONE,filePath.c_str());
	assert(SUCCEEDED(hr));

}

void TextureConverter::SeparateFilePath(const std::wstring& filePath) {
	size_t pos1;
	std::wstring exceptExt;
	pos1 = filePath.rfind('.');
	//見つかったら
	if (pos1 != std::wstring::npos) {
		fileExt_ = filePath.substr(pos1 + 1,filePath.size() - pos1 - 1);
		exceptExt = filePath.substr(0,pos1);
	}
	else {
		fileExt_ = L"";
		exceptExt = filePath;
	}
	pos1 = exceptExt.rfind('\\');
	if (pos1 != std::wstring::npos) {
		directoryPath_ = exceptExt.substr(0,pos1+1);
		fileName_ = exceptExt.substr(pos1+1,exceptExt.size()-pos1-1);
		return;
	}
	pos1 = exceptExt.rfind('/');
	if (pos1 != std::wstring::npos) {
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}
	directoryPath_ = L"";
	fileName_ = exceptExt;
}