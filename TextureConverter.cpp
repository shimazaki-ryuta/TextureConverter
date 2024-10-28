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

	DirectX::ScratchImage mipChain;
	HRESULT hr;

	hr = DirectX::GenerateMipMaps(scratchImage_.GetImages(),scratchImage_.GetImageCount(),scratchImage_.GetMetadata(),DirectX::TEX_FILTER_DEFAULT,0,mipChain);
	if(SUCCEEDED(hr)) {
		scratchImage_ = std::move(mipChain);
		metadata_ = scratchImage_.GetMetadata();
	}
	
	DirectX::ScratchImage converted;
	hr = DirectX::Compress(scratchImage_.GetImages(),scratchImage_.GetImageCount(),metadata_,DXGI_FORMAT_BC7_UNORM_SRGB,DirectX::TEX_COMPRESS_BC7_QUICK | DirectX::TEX_COMPRESS_SRGB_OUT | DirectX::TEX_COMPRESS_PARALLEL,1.0f,converted);
	if (SUCCEEDED(hr)) {
		scratchImage_ = std::move(converted);
		metadata_ = scratchImage_.GetMetadata();
	}

	metadata_.format = DirectX::MakeSRGB(metadata_.format);
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