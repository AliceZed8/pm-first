#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <iostream>

template <class T>
class VertexBuffer {
private:
	VertexBuffer(const VertexBuffer<T>& rhs);

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
	std::unique_ptr<UINT> stride;
	UINT buffersize = 0;

public:
	VertexBuffer(){}

	ID3D11Buffer* Get() const {
		return buffer.Get();
	}
	ID3D11Buffer* const* GetAddressOf() {
		return buffer.GetAddressOf();
	}

	UINT BufferSize() const {
		return this->buffersize;
	}

	const UINT Stride() const {
		return *this->stride.get();
	}
	const UINT * StridePtr() const {
		return this->stride.get();
	}

	HRESULT Init(ID3D11Device* device, T* data, UINT numVertices) {
		if (buffer.Get() != nullptr) buffer.Reset();
		
		this->buffersize = numVertices;
		if (this->stride.get() == nullptr)
			this->stride = std::make_unique<UINT>(sizeof(T));

		

		D3D11_BUFFER_DESC vertex_buffer_desc;
		ZeroMemory(&vertex_buffer_desc, sizeof(vertex_buffer_desc));

		vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
		vertex_buffer_desc.ByteWidth = sizeof(T) * numVertices;
		vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertex_buffer_desc.CPUAccessFlags = 0;
		vertex_buffer_desc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA vertex_buffer_data;
		ZeroMemory(&vertex_buffer_data, sizeof(vertex_buffer_data));
		vertex_buffer_data.pSysMem = data;

		return device->CreateBuffer(&vertex_buffer_desc, &vertex_buffer_data, this->buffer.GetAddressOf());
	}

};


