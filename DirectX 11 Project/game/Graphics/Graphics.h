#pragma once
#include "AdapterReader.h"
#include "Shaders.h"
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <WICTextureLoader.h>
#include "ConstantBuffer.h"
#include "Camera.h"
#include "../Timer.h"
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_win32.h"
#include "IMGUI/imgui_impl_dx11.h"
#include "Model.h"

class Graphics {
public:
	bool Init(HWND hwnd, int width, int height);
	void RenderFrame();
	Camera camera;

private:
	bool InitDX(HWND hwnd);
	bool InitShaders();
	bool InitScene();
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;

	VertexShader vertexshader;
	PixelShader pixelshader;

	ConstantBuffer<CB_VS_vertexshader> cb_vs_vertexshader;
	ConstantBuffer<CB_PS_pixelshader> cb_ps_pixelshader;

	Model model;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthstencilview;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthstencilbuffer;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilstate;

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizer_state;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizer_state_cull_front;
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendState;

	std::unique_ptr<DirectX::SpriteBatch> spriteBatch;
	std::unique_ptr<DirectX::SpriteFont> spriteFont;

	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> grassTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> blockTexture;

	int windowHeight = 0;
	int windowWidth = 0;
	Timer fpsTimer;
};
	
