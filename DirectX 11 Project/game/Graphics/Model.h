#pragma once
#include "Vertex.h"
#include "ShaderBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

using namespace DirectX;
class Model {
public:
	bool Init(ID3D11Device* device, ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView * texture, ConstantBuffer<CB_VS_vertexshader> & cb_vs_vertexshader);
	void SetTexure(ID3D11ShaderResourceView* texture);
	void Draw(const XMMATRIX& viewProjectionMaxtrix);
private:
	void UpdateWorldMatrix();
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* deviceContext = nullptr;
	ConstantBuffer<CB_VS_vertexshader>* cb_vs_vertexshader = nullptr;
	ID3D11ShaderResourceView* texture = nullptr;

	VertexBuffer<Vertex> vertexBuffer;
	IndexBuffer indexBuffer;
	XMMATRIX worldMatrix = XMMatrixIdentity();
};