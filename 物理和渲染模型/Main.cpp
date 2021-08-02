/**
* project : �������Ⱦģ��
* file    : Main.cpp
* Copyright 2021 handle All rights reserved.
* �廳Ԭ¡ƽԺʿ
**/
#include "CommonHead.h"
#include "Window.h"
#include "GameMain.h"



int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
) {
	//Window::OpenConsole();
	Window MainWin(hInstance, WINDOW_CLASS, WINDOW_NAME, WINDOW_ORIGIN_WIDTH, WINDOW_ORIGIN_HEIGHT,MainWinProc);
	//ShowWindow(MainWin, SW_HIDE);

	PreLoad(MainWin);
	MainWin.MessageLoop(MainFunction);
	Clear();

	return 1;
}
