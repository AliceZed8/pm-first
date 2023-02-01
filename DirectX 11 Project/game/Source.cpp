#include "Engine.h"


//¬ход в приложение
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{

	// ласс движка
	Engine engine(
		hInstance, "Test", "class", 800, 600
	);
	if (engine.run()) {
		while (engine.ProcessMessage()) {
			engine.Update();
			engine.RenderFrame();
		}
	}
	

	return 0;
}