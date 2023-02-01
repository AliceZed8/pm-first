#include "Graphics.h"

bool Graphics::Init(HWND hwnd, int width, int height) 
{
	windowHeight = height;
	windowWidth = width;
	this->fpsTimer.Start();
	if (!InitDX(hwnd)) 
		return false;

	if (!InitShaders())
		return false;

	if (!InitScene())
		return false;

	//Настройка IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(this->device.Get(), this->deviceContext.Get());
	ImGui::StyleColorsDark();

	return true;
}
void Graphics::RenderFrame() {
	//рендер кадра

	//Очистка
	float bgcolor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	this->deviceContext->ClearRenderTargetView(this->renderTargetView.Get(), bgcolor);
	//Очистка глубины
	this->deviceContext->ClearDepthStencilView(this->depthstencilview.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	this->deviceContext->IASetInputLayout(this->vertexshader.GetInputLayout());

	//тип топологии/рисования
	this->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//состояние растеризатора
	this->deviceContext->RSSetState(this->rasterizer_state.Get());

	//установка состояния трафарета глубины
	this->deviceContext->OMSetDepthStencilState(this->depthstencilstate.Get(), 0);
	this->deviceContext->OMSetBlendState(NULL, NULL, 0xFFFFFFFF);

	//Установка самплера
	this->deviceContext->PSSetSamplers(0, 1, this->samplerState.GetAddressOf());

	//установка шейдеров
	this->deviceContext->VSSetShader(vertexshader.GetShader(), NULL, 0);
	this->deviceContext->PSSetShader(pixelshader.GetShader(), NULL, 0);

	{ //Тротуар
		this->model.Draw(camera.GetViewMatrix() * camera.GetProjectionMatrix());
	}

	//Вывод текста
	static int fpsCounter = 0;
	static std::string fps = "FPS: ";
	fpsCounter += 1;
	if (fpsTimer.GetMilisecondsElapsed() > 1000.0f) {
		fps = "FPS: " + std::to_string(fpsCounter);
		fpsCounter = 0;
		fpsTimer.Restart();
	}



	spriteBatch->Begin();
	spriteFont->DrawString(spriteBatch.get(), StringConverter::StringToWide(fps).c_str(), DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::Colors::White, 0.0f, DirectX::XMFLOAT2(1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
	spriteBatch->End();


	//IMGUI
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Test");

	ImGui::End();

	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	this->swapchain->Present(0, NULL);
}

//Инициализация DirectX
bool Graphics::InitDX(HWND hwnd) {

	try {

		//Получение графических адартеров
		std::vector<AdapterData> adapters = AdapterReader::GetAdapters();
		if (adapters.size() < 1) {
			ErrorLogger::Log("No DXGI Adapter found.");
			return false;
		}
		//Описание буфера
		DXGI_SWAP_CHAIN_DESC scd = { 0 };

		//Задание параметров
		scd.BufferDesc.Width = this->windowWidth;
		scd.BufferDesc.Height = this->windowHeight;
		scd.BufferDesc.RefreshRate.Numerator = 60;
		scd.BufferDesc.RefreshRate.Denominator = 1;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		scd.SampleDesc.Count = 1;
		scd.SampleDesc.Quality = 0;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.BufferCount = 1;
		scd.OutputWindow = hwnd;
		scd.Windowed = TRUE;
		scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;


		HRESULT hr;
		//Создание девайса и SwapChain
		hr = D3D11CreateDeviceAndSwapChain(
			adapters[0].pAdapter, // адаптер
			D3D_DRIVER_TYPE_UNKNOWN,
			NULL,
			NULL,
			NULL,
			0,
			D3D11_SDK_VERSION, //пакет sdk
			&scd, //описание
			this->swapchain.GetAddressOf(), //свап чейн
			this->device.GetAddressOf(), //устройство
			NULL,
			this->deviceContext.GetAddressOf() //контекст устройства
		);
		COM_ERROR_IF_FAILED(hr, "Ошибка при создании устройства и swap chain");

		//задний буффер
		Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
		hr = this->swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
		COM_ERROR_IF_FAILED(hr, "GetBuffer Ошибка");

		//цель рендеринга
		hr = this->device->CreateRenderTargetView(backBuffer.Get(), NULL, this->renderTargetView.GetAddressOf());
		COM_ERROR_IF_FAILED(hr, "CreateRenderTargetView Ошибка");

		//описание трафарета глубины
		CD3D11_TEXTURE2D_DESC depthStencilDesc(DXGI_FORMAT_D24_UNORM_S8_UINT, this->windowWidth, this->windowHeight);
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		//создание описания
		hr = this->device->CreateTexture2D(&depthStencilDesc, NULL, this->depthstencilbuffer.GetAddressOf());
		COM_ERROR_IF_FAILED(hr, "Failed to create depth stencil buffer ");

		//создание трафарета
		hr = this->device->CreateDepthStencilView(this->depthstencilbuffer.Get(), NULL, this->depthstencilview.GetAddressOf());
		COM_ERROR_IF_FAILED(hr, "Failed to create depth stencil view ");

		//Установка целей рендеринга
		this->deviceContext->OMSetRenderTargets(1, this->renderTargetView.GetAddressOf(), this->depthstencilview.Get());

		//состояние трафарета глубины
		CD3D11_DEPTH_STENCIL_DESC depthstencil_desc(D3D11_DEFAULT);
		depthstencil_desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;

		hr = this->device->CreateDepthStencilState(&depthstencil_desc, this->depthstencilstate.GetAddressOf());
		COM_ERROR_IF_FAILED(hr, "Failed to create depth stencil state");
		
		//viewport
		CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(this->windowWidth), static_cast<float>(this->windowHeight));
		this->deviceContext->RSSetViewports(1, &viewport);

		//состояние растеризатора 1
		CD3D11_RASTERIZER_DESC rasterizerDesc(D3D11_DEFAULT);
		hr = this->device->CreateRasterizerState(&rasterizerDesc, this->rasterizer_state.GetAddressOf());
		COM_ERROR_IF_FAILED(hr, "Failed to create Rasterizer State ");


		//состояние растеризатора 2
		CD3D11_RASTERIZER_DESC rasterizerDesc_cull_front(D3D11_DEFAULT);
		rasterizerDesc_cull_front.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
		hr = this->device->CreateRasterizerState(&rasterizerDesc_cull_front, this->rasterizer_state_cull_front.GetAddressOf());
		COM_ERROR_IF_FAILED(hr, "Failed to create Rasterizer State 2 ");


		//Создание состояния смешивания
		D3D11_BLEND_DESC blend_desc = { 0 };
		D3D11_RENDER_TARGET_BLEND_DESC rtbd = { 0 };

		rtbd.BlendEnable = true;
		rtbd.SrcBlend = D3D11_BLEND_SRC_ALPHA;
		rtbd.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		rtbd.BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		rtbd.SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		rtbd.DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
		rtbd.BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		rtbd.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		blend_desc.RenderTarget[0] = rtbd;

		hr = this->device->CreateBlendState(&blend_desc, this->blendState.GetAddressOf());
		COM_ERROR_IF_FAILED(hr, "Failed to create BlendState ");

		//подключение шрифта
		spriteBatch = std::make_unique<DirectX::SpriteBatch>(this->deviceContext.Get());
		spriteFont = std::make_unique<DirectX::SpriteFont>(this->device.Get(), L"Data\\Fonts\\comic_sans_16.spritefont");

		//Создание описания для самплера
		CD3D11_SAMPLER_DESC sampDesc(D3D11_DEFAULT);
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		hr = this->device->CreateSamplerState(&sampDesc, this->samplerState.GetAddressOf());
		COM_ERROR_IF_FAILED(hr, "Failed to create Sampler ");

	}
	catch (COMException& exception) {
		ErrorLogger::Log(exception);
		return false;
	}
	return true;

}

//Инициализация шейдеров
bool Graphics::InitShaders()
{
	//инициализация шейдеров
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	UINT numElements = ARRAYSIZE(layout);

	if (!vertexshader.Initialize(this->device, L"..//x64//Debug//vertexshader.cso", layout, numElements))
		return false;
	
	if (!pixelshader.Initialize(this->device, L"..//x64//Debug//pixelshader.cso")) 
		return false;

	return true;
}

//Сцена
bool Graphics::InitScene() {

	try {
		
		HRESULT hr;

		//Загрузка текстуры
		hr = DirectX::CreateWICTextureFromFile(this->device.Get(), L"Data\\Textures\\texture1.png", nullptr, this->grassTexture.GetAddressOf());
		COM_ERROR_IF_FAILED(hr, "Failed to create wic texture from file");

		hr = DirectX::CreateWICTextureFromFile(this->device.Get(), L"Data\\Textures\\texture4.png", nullptr, this->blockTexture.GetAddressOf());
		COM_ERROR_IF_FAILED(hr, "Failed to create wic texture from file");

		//Инициализация константного буфера
		hr = this->cb_vs_vertexshader.Init(this->device.Get(), this->deviceContext.Get());
		COM_ERROR_IF_FAILED(hr, "Failed to INIT Constant Buffer");

		//Инициализация константного буфера
		hr = this->cb_ps_pixelshader.Init(this->device.Get(), this->deviceContext.Get());
		COM_ERROR_IF_FAILED(hr, "Failed to INIT Constant Buffer");


		if (!model.Init(this->device.Get(), this->deviceContext.Get(), grassTexture.Get(), cb_vs_vertexshader)) {
			
			return false;
		}

		camera.SetPosition(0.0f, 0.0f, -2.0f);
		camera.SetProjectionValues(90.0f, static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1f, 1000.0f);
	
	
	
	}
	catch (COMException& exception) {
		ErrorLogger::Log(exception);
		return false;
	}

	return true;

}

