#include "App.h"

int main()
{
	XeEngine::Application* sonic1 = new RESonic1App;
	sonic1->Run();
	delete sonic1;
}