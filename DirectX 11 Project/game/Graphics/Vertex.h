#pragma once
#include <DirectXMath.h>

struct Vertex {

	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 texcoord;

	Vertex() {};
	Vertex(float x, float y, float z, float u, float v): pos(x, y, z), texcoord(u, v) {}

	
};