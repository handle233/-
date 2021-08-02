/**
* project : 物理和渲染模型
* file    : Modules.cpp
* Copyright 2021 handle All rights reserved.
* 缅怀袁隆平院士
**/

#include "Manager.h"
#include "Window.h"
#include "Modules.h"

MainScreen::MainScreen():Module(1),nTick(24),BallSize(128,128),
PhyKernel(24),Updater(1000/nTick), Reactor(1000 / nTick),
BG(TEXT("BG.bmp"))
{
	BG.Alpha = 200;
	BG.Width = WINDOW_ORIGIN_WIDTH;
	BG.Height = WINDOW_ORIGIN_HEIGHT;
	//Mem->ReFormatBitmap(BG, WINDOW_ORIGIN_WIDTH, WINDOW_ORIGIN_HEIGHT);
	ControlBall = nullptr;
	Frame.DestinDirY = ReferenceConvertor::AxisDirection::Negative;
	PhyKernel.SetDebugScreen(Mem);
}
MainScreen::~MainScreen()
{

}

void MainScreen::Main()
{
	GraphObject GObj(*Mem);
	*Mem + BG;
	for (int a = 0; a < BallList.length; a++) {
		wchar_t str[16] = TEXT("");
		swprintf_s(str, 16, TEXT("%d"), a);
		BallList[a]->Draw(Frame);
		Point pt = Frame.Convert(BallList[a]->Pt);
		TextOut(GObj.dc, pt.x, pt.y, str, wcslen(str));
	}

	if (ControlBall != nullptr) {

		Point Conved = Frame.Convert(ControlBall->Pt);

		Rect SelRect = Rect(Conved.x - ControlBall->Picture.Width / 2,
			Conved.y - ControlBall->Picture.Height / 2,
			ControlBall->Picture.Width, ControlBall->Picture.Height);

		RECT rect = SelRect;

		FillRect(GObj.dc, &rect, (HBRUSH)GetStockObject(GRAY_BRUSH));
	}
}

void MainScreen::Timer()
{
	if (Updater) {
		PhyKernel.PhysicsSpin();

		if (Processor.IsKeyDown('Q')) {
			Frame.Magnif = Frame.Magnif - 0.05;
		}
		if (Processor.IsKeyDown('E')) {
			Frame.Magnif = Frame.Magnif + 0.05;
		}
		static const double Val = 8;
		if (Processor.IsKeyDown(VK_UP)) {
			Frame.OriginOffset.y += Val;
		}
		if (Processor.IsKeyDown(VK_DOWN)) {
			Frame.OriginOffset.y -= Val;
		}
		if (Processor.IsKeyDown(VK_LEFT)) {
			Frame.OriginOffset.x -= Val;
		}
		if (Processor.IsKeyDown(VK_RIGHT)) {
			Frame.OriginOffset.x += Val;
		}

		if (Processor.IsKeyDown('W')) {
			ControlBall->Obj.Speed.y += Val;
		}
		if (Processor.IsKeyDown('S')) {
			ControlBall->Obj.Speed.y -= Val;
		}
		if (Processor.IsKeyDown('A')) {
			ControlBall->Obj.Speed.x -= Val;
		}
		if (Processor.IsKeyDown('D')) {
			ControlBall->Obj.Speed.x += Val;
		}
	}

	int Temp = Processor.IsRoll();
	if (Temp != 0) {
		nTick += Temp;
		PhyKernel.SetTickSpeed(nTick);
		Updater = ::Timer(1000 / nTick);
		cout << "FPS:" << nTick << endl;
	}
	if (Processor.IsButtonHit(true)) {
		cout << "Create one!" << endl;
		Ball* New = new Ball(TEXT("B.bmp"), BallSize, BallMass);
		New->Picture.Alpha = 100;

		New->Pt = Frame.Disconvert(Processor.GetMousePos());
		cout << "At " << New->Pt.x << " " << New->Pt.y << endl;
		BallList.Add(-1, New);
		PhyKernel.AddObject(&New->Obj);
	}
	if (Processor.IsButtonHit()) {
		Point Mouse = Processor.GetMousePos();

		Mouse = Frame.Disconvert(Frame.Convert(Mouse));
		GraphObject GObj(*Mem);
		SetPixel(GObj.dc, Mouse.x, Mouse.y, RGB(255, 0, 0));

		Mouse = Frame.Disconvert(Mouse);
		int Index = -1;
		for (int a = 0; a < BallList.length; a++) {
			Point Pt = BallList[a]->Obj.pt;
			Pt.x = Pt.x - BallList[a]->Obj.Size.x / 2;
			Pt.y = Pt.y - BallList[a]->Obj.Size.y / 2;
			Rect Size(Pt, BallList[a]->Obj.Size);
			if (Size == Mouse) {
				Index = a;
			}
		}
		if (Index != -1) {
			cout << "Select:" << Index << endl;
			ControlBall = BallList[Index];
		}
		else {
			ControlBall = nullptr;
		}
	}

}

Ball::Ball(const TCHAR* PhotoStr, Vector& BSize, double Mass) :Picture(PhotoStr), Obj(Pt, BSize, Mass)
{
	Picture.Transrgb = RGB(255, 255, 255);
}
void Ball::Draw(ReferenceConvertor& Frme)
{
	Point Conved = Frme.Convert(Pt);
	Picture.x = Conved.x - Picture.Width / 2;
	Picture.y = Conved.y - Picture.Height / 2;
	Picture.Width = Picture.OriginWidth*Frme.Magnif;
	Picture.Height = Picture.OriginHeight * Frme.Magnif;
	*Mem + Picture;
}
