#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <vector>

class IndexBuffer {
private:
	IndexBuffer(const IndexBuffer& rhs);
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
	UINT buffersize = 0;
public:
	IndexBuffer(){}
	ID3D11Buffer* Get() const {
		return buffer.Get();
	}

	ID3D11Buffer* const* GetAdressOf() const {
		return buffer.GetAddressOf();
	}
	UINT BufferSize() const {
		return buffersize;
	}

	HRESULT Init(ID3D11Device* device, DWORD* data, UINT numIndices) {
		if (buffer.Get() != nullptr)
			buffer.Reset();

		this->buffersize = numIndices;
		//Буфер индексов
		D3D11_BUFFER_DESC indices_buffer_desc;
		ZeroMemory(&indices_buffer_desc, sizeof(indices_buffer_desc));

		indices_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
		indices_buffer_desc.ByteWidth = sizeof(DWORD) * numIndices;
		indices_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indices_buffer_desc.CPUAccessFlags = 0;
		indices_buffer_desc.MiscFlags = 0;


		//данные буфера индексов
		D3D11_SUBRESOURCE_DATA indexbufferdata;
		ZeroMemory(&indexbufferdata, sizeof(indexbufferdata));
		indexbufferdata.pSysMem = data;

		return device->CreateBuffer(&indices_buffer_desc, &indexbufferdata, this->buffer.GetAddressOf());
	}
};

