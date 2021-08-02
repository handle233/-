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
int TickNum = 24;
Physics Phy(1000/TickNum);
Bitmap* Ball;
Object *A;
Object* B;

void PreLoad(const HWND &Win)
try {
	Exception::InitLog("Log.txt");
	Root = new Screen(Win);
	Mem = new Screen(*Root);
	Master = new Manager;

	Ball = new Bitmap(TEXT("B.bmp"));
	Ball->Transrgb = RGB(255, 255, 255);

	Point *PosA = new Point(300, -256);
	Vector Size(128, 128);
	A = new Object(*PosA, Size, 1.0);

	Point *PosB = new Point(500, -256);
	B = new Object(*PosB, Size, 10.0);

	Phy.AddObject(B);
	Phy.AddObject(A);

	Phy.SetDebugScreen(Mem);

}ROOT_EXCEPTION_FILTER

Timer Tmr(1000 / TickNum);
Timer KeyTmr(1000 / 24);
void MainFunction()
try {

	Master->Run();
	Mem->Clear(RGB(230, 230, 230));
	Ball->x = A->pt.x - A->Size.x / 2;
	Ball->y = (-A->pt.y) - A->Size.y / 2;
	*Mem + *Ball;
	Ball->x = B->pt.x - B->Size.x / 2;
	Ball->y = (-B->pt.y) - B->Size.y / 2;
	*Mem + *Ball;

	GraphObject Obj(*Mem);
	SetPixel(Obj.dc, A->pt.x, -A->pt.y, RGB(255, 0, 0));
	SetPixel(Obj.dc, B->pt.x, -B->pt.y, RGB(255, 0, 0));

	if (Tmr) {
		Phy.PhysicsSpin();
	}

	*Root << *Mem;

	if(KeyTmr){
		const double Delta = 20.0;
		if (Processor.IsKeyDown('W')) {
			A->Speed.y += Delta;
		}
		if (Processor.IsKeyDown('S')) {
			A->Speed.y -= Delta;
		}
		if (Processor.IsKeyDown('A')) {
			A->Speed.x -= Delta;
		}
		if (Processor.IsKeyDown('D')) {
			A->Speed.x += Delta;
		}
		if (Processor.IsKeyDown(VK_UP)) {
			B->Speed.y += Delta;
		}
		if (Processor.IsKeyDown(VK_DOWN)) {
			B->Speed.y -= Delta;
		}
		if (Processor.IsKeyDown(VK_LEFT)) {
			B->Speed.x -= Delta;
		}
		if (Processor.IsKeyDown(VK_RIGHT)) {
			B->Speed.x += Delta;
		}
		if (Processor.IsKeyDown(VK_F1)) {
			A->Speed.x = 0;
			A->Speed.y = 0;
			B->Speed.x = 0;
			B->Speed.y = 0;
		}
		if (Processor.IsKeyDown(VK_F2)) {
			A->Speed.x = 0;
			A->Speed.y = 0;
			B->Speed.x = 0;
			B->Speed.y = 0;
			A->pt.x = 300;
			A->pt.y = -256;
			B->pt.x = 500;
			B->pt.y = -256;
		}

		int a = Processor.IsRoll();
		if (a != 0) {
			TickNum += a;
			Phy.SetTickSpeed(TickNum);
			Tmr = Timer(1000 / TickNum);
			cout << "FPS:" << TickNum << endl;
		}

		if (Processor.IsKeyDown(VK_ESCAPE)) {
			PostQuitMessage(1);
		}
	}
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
