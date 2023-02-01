#include "WindowContainer.h"


//Конструктор
RenderWindow::RenderWindow(
	WindowContainer* pWindowContainer, //контейнер окна
	HINSTANCE hInstance, //экземпляр
	std::string window_title, //заголовок окна
	std::string window_class, //заголовок класса окна
	int width, int height):
	pWindowContainer(pWindowContainer), hInstance(hInstance), 
	window_title(window_title),			window_class(window_class), 
	width(width),						height(height) 

{
	this->window_title_wide = StringConverter::StringToWide(window_title);
	this->window_class_wide = StringConverter::StringToWide(window_class);
}

HWND RenderWindow::GetHWND() const {
	return handle;
}
int RenderWindow::GetWidth() {
	return this->width;
}
int RenderWindow::GetHeight() {
	return this->height;
}


bool RenderWindow::run() {
	//регистрируем класс
	RegisterWindowClass();

	RECT wr;
	wr.left = 50;
	wr.top = 50;
	wr.right = wr.left + this->width;
	wr.bottom = wr.top + this->height;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);



	this->handle = CreateWindowEx(
		0,
		this->window_class_wide.c_str(),
		this->window_title_wide.c_str(),
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		wr.left,
		wr.top,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL,
		NULL,
		this->hInstance,
		pWindowContainer);

	if (this->handle == NULL) {
		ErrorLogger::Log(GetLastError(), "Create Window Failed" + this->window_title);
		return false;
	}

	ShowWindow(this->handle, SW_SHOW);
	SetForegroundWindow(this->handle);
	SetFocus(this->handle);

	return true;
}

LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;

	default:
		WindowContainer* const pWindow = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
}



LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_NCCREATE:
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		WindowContainer* pWindow = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);

		if (pWindow == nullptr) {
			ErrorLogger::Log("Error pointer to window container");
			exit(-1);

		}
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

void RenderWindow::RegisterWindowClass() {
	WNDCLASSEX wc;
	//описание класса
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = HandleMessageSetup; //функция для обработки сообщений
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = window_class_wide.c_str();
	wc.cbSize = sizeof(WNDCLASSEX);
	//регистрация
	RegisterClassEx(&wc);

}

RenderWindow::~RenderWindow() {
	//деструктор
	if (this->handle != NULL) {
		UnregisterClass(this->window_class_wide.c_str(), this->hInstance);
		DestroyWindow(this->handle);
	}
}


bool RenderWindow::ProcessMessage() {

	//чтение сообщений
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (PeekMessage(&msg, this->handle, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//если окна нет
	if (msg.message == WM_NULL) {
		if (!IsWindow(this->handle)) {
			this->handle = NULL;
			UnregisterClass(this->window_class_wide.c_str(), this->hInstance);
			return false;
		}
	}

	return true;
}