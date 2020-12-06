#include "menuWindow.h"

#include <Windows.h>

using namespace CLRTetris;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew menuWindow);
    return 0;
}