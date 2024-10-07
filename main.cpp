#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "TextureConverter.h"
#include <Windows.h>
enum Argument
{
	kApplicationPath,
	kFilePath,
	
	NumArgument
};

int main(int argc,char* argv[]) {

	//ˆø”‚Ì”‘«‚è‚È‚©‚Á‚½‚ç~‚ß‚é
	assert(argc >= NumArgument);

	//COM‚Ì‰Šú‰»
	HRESULT hr = CoInitializeEx(nullptr,COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	TextureConverter converter;
	converter.ConvertTextureWICToDDS(argv[kFilePath]);

	//COMI—¹
	CoUninitialize();

	system("pause");
	return 0;
}