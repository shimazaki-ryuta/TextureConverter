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

	//�����̐�����Ȃ�������~�߂�
	assert(argc >= NumArgument);

	//COM�̏�����
	HRESULT hr = CoInitializeEx(nullptr,COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	TextureConverter converter;
	converter.ConvertTextureWICToDDS(argv[kFilePath]);

	//COM�I��
	CoUninitialize();

	system("pause");
	return 0;
}