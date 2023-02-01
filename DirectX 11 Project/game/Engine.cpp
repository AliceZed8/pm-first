#include "Engine.h"

Engine::Engine(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height) {
	this->render_window = new RenderWindow(this , hInstance, window_title, window_class, width, height);
}


bool Engine::run() {
	timer.Start();
	if (!this->render_window->run())
		return false;
	if (!gfx.Init(this->render_window->GetHWND(), this->render_window->GetWidth(), this->render_window->GetHeight())) {
		return false;
	}
	return true;
}

bool Engine::ProcessMessage() {
	return this->render_window->ProcessMessage();
}

void Engine::Update() {
	float dt = timer.GetMilisecondsElapsed();
	timer.Restart();

	while (!keyboard.CharBufferIsEmpty()) {
		unsigned char ch = keyboard.ReadChar();
	}

	while (!keyboard.KeyBufferIsEmpty()) {
		KeyboardEvent kbe = keyboard.ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
	}

	while (!mouse.EventBufferIsEmpty()) {
		MouseEvent me = mouse.ReadEvent();
		if (mouse.IsRightDown()) {
		if (me.GetType() == MouseEvent::EventType::RAW_MOVE) {
			gfx.camera.AdjustRotation((float)me.GetPosY() * 0.01f, (float)me.GetPosX() * 0.01f, 0);
		}}
	}

	const float cameraSpeed = 0.005f * dt;
	if (keyboard.KeyIsPressed('W')) {
		this->gfx.camera.AdjustPosition(gfx.camera.GetForwardVector() * cameraSpeed);
	}
	if (keyboard.KeyIsPressed('A')) {
		this->gfx.camera.AdjustPosition(gfx.camera.GetLeftVector() * cameraSpeed);
	}
	if (keyboard.KeyIsPressed('S')) {
		this->gfx.camera.AdjustPosition(gfx.camera.GetBackwardVector() * cameraSpeed);
	}
	if (keyboard.KeyIsPressed('D')) {
		this->gfx.camera.AdjustPosition(gfx.camera.GetRightVector() * cameraSpeed);
	}
	if (keyboard.KeyIsPressed(VK_SPACE)) {
		this->gfx.camera.AdjustPosition(0.0f, cameraSpeed, 0.0f);
	}
	if (keyboard.KeyIsPressed('Z')) {
		this->gfx.camera.AdjustPosition(0.0f, -cameraSpeed, 0.0f);
	}










}

void Engine::RenderFrame()
{
	gfx.RenderFrame();
}

