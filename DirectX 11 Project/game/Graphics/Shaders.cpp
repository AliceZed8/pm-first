#include "Shaders.h"

bool VertexShader::Initialize(
	Microsoft::WRL::ComPtr<ID3D11Device>& device,
	std::wstring shaderpath,
	D3D11_INPUT_ELEMENT_DESC* desc,
	UINT numElements) 
	{

	//Чтение шейдера из файла
	HRESULT hr = D3DReadFileToBlob(shaderpath.c_str(), this->shader_buffer.GetAddressOf());
	
	if (FAILED(hr)) {
		std::wstring errorMsg = L"Failed to load shader: ";
		errorMsg += shaderpath;
		ErrorLogger::Log(hr, errorMsg);
		return false;
	}

	//Создание шейдера
	hr = device->CreateVertexShader(this->shader_buffer->GetBufferPointer(), this->shader_buffer->GetBufferSize() , NULL, this->shader.GetAddressOf());
	
	if (FAILED(hr)) {
		std::wstring errorMsg = L"Failed to create vertex shader: ";
		errorMsg += shaderpath;
		ErrorLogger::Log(hr, errorMsg);
		return false;
	}


	//Создание макета
	hr = device->CreateInputLayout(desc, numElements, this->shader_buffer->GetBufferPointer(), this->shader_buffer->GetBufferSize(), this->inputLayout.GetAddressOf());
	if (FAILED(hr)) {
		ErrorLogger::Log(hr, "Failed to create input layout");
		return false;
	}

	return true;
}


ID3D11VertexShader* VertexShader::GetShader() {
	return this->shader.Get();
}

ID3D10Blob* VertexShader::GetBuffer() {
	return this->shader_buffer.Get();
}


ID3D11InputLayout* VertexShader::GetInputLayout() {
	return this->inputLayout.Get();
}



bool PixelShader::Initialize(
	Microsoft::WRL::ComPtr<ID3D11Device>& device,
	std::wstring shaderpath)
{

	//Чтение шейдера из файла
	HRESULT hr = D3DReadFileToBlob(shaderpath.c_str(), this->shader_buffer.GetAddressOf());

	if (FAILED(hr)) {
		std::wstring errorMsg = L"Failed to load pixel shader: ";
		errorMsg += shaderpath;
		ErrorLogger::Log(hr, errorMsg);
		return false;
	}

	//Создание шейдера
	hr = device->CreatePixelShader(this->shader_buffer->GetBufferPointer(), this->shader_buffer->GetBufferSize(), NULL, this->shader.GetAddressOf());

	if (FAILED(hr)) {
		std::wstring errorMsg = L"Failed to create pixel shader: ";
		errorMsg += shaderpath;
		ErrorLogger::Log(hr, errorMsg);
		return false;
	}
	return true;
}


ID3D11PixelShader* PixelShader::GetShader() {
	return this->shader.Get();
}

ID3D10Blob* PixelShader::GetBuffer() {
	return this->shader_buffer.Get();
}
