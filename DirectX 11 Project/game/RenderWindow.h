#pragma once
#include "ErrorLogger.h"

class WindowContainer;

class RenderWindow {
private:
	void RegisterWindowClass();
	HWND handle = NULL;
	HINSTANCE hInstance;
	WindowContainer *pWindowContainer;
	std::string window_title, window_class;
	std::wstring window_title_wide, window_class_wide;
	int width, height;

public:
	RenderWindow(WindowContainer* pWindowContainer, HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height);
	bool run();
	HWND GetHWND() const;
	int GetWidth();
	int GetHeight();
	bool ProcessMessage();
	~RenderWindow();
};