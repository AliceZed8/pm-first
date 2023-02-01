#include "Model.h"

bool Model::Init(ID3D11Device* device, ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView* texture, ConstantBuffer<CB_VS_vertexshader>& cb_vs_vertexshader) {
	this->device = device;
	this->deviceContext = deviceContext;
	this->texture = texture;
	this->cb_vs_vertexshader = &cb_vs_vertexshader;

	
	Vertex v[] = {
			Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 1.0f), //0 FRONT
			Vertex(-0.5f,  0.5f, -0.5f, 0.0f, 0.0f), //1
			Vertex(0.5f,  0.5f, -0.5f, 1.0f, 0.0f), //2
			Vertex(0.5f,  -0.5f, -0.5f, 1.0f, 1.0f), //3

			Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 1.0f), //4 BACK
			Vertex(-0.5f,  0.5f, 0.5f, 0.0f, 0.0f), //5
			Vertex(0.5f,  0.5f, 0.5f, 1.0f, 0.0f), //6
			Vertex(0.5f,  -0.5f, 0.5f, 1.0f, 1.0f), //7
	};

	//�������
	DWORD indices[]{
		0, 1, 2, //FRONT
		0, 2, 3, //FRONT
		4, 7, 6, //BACK 
		4, 6, 5, //BACK
		3, 2, 6, //RIGHT SIDE
		3, 6, 7, //RIGHT SIDE
		4, 5, 1, //LEFT SIDE
		4, 1, 0, //LEFT SIDE
		1, 5, 6, //TOP
		1, 6, 2, //TOP
		0, 3, 7, //BOTTOM
		0, 7, 4, //BOTTOM

	};

	HRESULT hr;
	try {
		//����� ������
		hr = this->vertexBuffer.Init(this->device, v, ARRAYSIZE(v));
		COM_ERROR_IF_FAILED(hr, "Failed to create Vertex Buffer");

		//����� ��������
		hr = this->indexBuffer.Init(this->device, indices, ARRAYSIZE(indices));
		COM_ERROR_IF_FAILED(hr, "Failed to create Index Buffer");
	}
	catch (COMException& exception) {
		ErrorLogger::Log(exception);
		return false;
	}

	this->UpdateWorldMatrix();
	return true;
}

void Model::SetTexure(ID3D11ShaderResourceView* texture) {
	this->texture = texture;
}

void Model::Draw(const XMMATRIX& viewProjectionMatrix) {
	this->cb_vs_vertexshader->data.mat = this->worldMatrix * viewProjectionMatrix;
	this->cb_vs_vertexshader->data.mat = XMMatrixTranspose(cb_vs_vertexshader->data.mat);
	this->cb_vs_vertexshader->ApplyChanges();

	this->deviceContext->VSSetConstantBuffers(0, 1, cb_vs_vertexshader->GetAddressOf());

	this->deviceContext->PSSetShaderResources(0, 1, &this->texture);
	this->deviceContext->IASetIndexBuffer(this->indexBuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);

	UINT offset = 0;
	this->deviceContext->IASetVertexBuffers(0, 1, this->vertexBuffer.GetAddressOf(), this->vertexBuffer.StridePtr(),&offset);
	this->deviceContext->DrawIndexed(this->indexBuffer.BufferSize(), 0, 0);
}

void Model::UpdateWorldMatrix() {
	this->worldMatrix = XMMatrixIdentity();
}