/**
* project : 物理和渲染模型
* file    : GameMain.cpp
* Copyright 2021 handle All rights reserved.
* 缅怀袁隆平院士
**/
#include "CommonHead.h"
#include "GameMain.h"
#include "Modules.h"

WindowProcess Processor;
Screen* Root, * Mem;
Manager *Master;

void PreLoad(const HWND &Win)
try {
	Exception::InitLog("Log.txt");
	Root = new Screen(Win);
	Mem = new Screen(*Root);
	Master = new Manager;

	MainScreen* pF = new MainScreen;
	Master->AddMod(pF);
	Master->AddRunMod(Master->SeekMod(1));
	Master->AddTimeMod(Master->SeekMod(1));
}ROOT_EXCEPTION_FILTER

void MainFunction()
try {

	Mem->Clear(RGB(255, 255, 255));
	Master->Run();
	*Root << *Mem;

}ROOT_EXCEPTION_FILTER
void Clear()
try {
	delete Master;
	delete Mem;
	delete Root;
	Exception::CloseLog();
}ROOT_EXCEPTION_FILTER

LRESULT CALLBACK MainWinProc(HWND hwnd, UINT msg, WPARAM wpm, LPARAM lpm)
{
	if (Processor.WindowMessageFilter(hwnd, msg, wpm, lpm)) {
		return 0;
	}
	switch (msg) {
	case WM_CREATE:
		break;
	case WM_PAINT:
		ValidateRect(hwnd, nullptr);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wpm, lpm);
	}
	return true;
}
