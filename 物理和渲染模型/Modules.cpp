/**
* project : 物理和渲染模型
* file    : Modules.cpp
* Copyright 2021 handle All rights reserved.
* 缅怀袁隆平院士
**/

#include "Manager.h"
#include "Window.h"
#include "Modules.h"

MainScreen::MainScreen():Module(1),nTick(200),BallSize(512,512),
PhyKernel(200),Updater(1000/nTick), Reactor(1000 / nTick),
BG(TEXT("BG.bmp"))
{
	Track = false;
	TrackBall = nullptr;
	LineBall = nullptr;
	Frame.OriginOffset.x = WINDOW_ORIGIN_WIDTH / 2;
	Frame.OriginOffset.y = -WINDOW_ORIGIN_HEIGHT / 2;

	BG.Alpha = 150;
	BG.Width = WINDOW_ORIGIN_WIDTH;
	BG.Height = WINDOW_ORIGIN_HEIGHT;
	Mem->ReFormatBitmap(BG, WINDOW_ORIGIN_WIDTH, WINDOW_ORIGIN_HEIGHT);
	ControlBall = nullptr;
	Frame.DestinDirY = ReferenceConvertor::AxisDirection::Negative;
	PhyKernel.SetDebugScreen(Mem);
	GraphObject GObj(*Mem);
	SetBkMode(GObj.dc, TRANSPARENT);

}
MainScreen::~MainScreen()
{

}

void MainScreen::Main()
{
	FPS.UpdateFps();
	GraphObject GObj(*Mem);
	*Mem + BG;

	Point Origin;
	Origin = Frame.Convert(Origin);
	MoveToEx(GObj.dc, 0, Origin.y, nullptr);
	LineTo(GObj.dc, WINDOW_ORIGIN_WIDTH, Origin.y);
	MoveToEx(GObj.dc, Origin.x, 0, nullptr);
	LineTo(GObj.dc, Origin.x, WINDOW_ORIGIN_HEIGHT);

	SetPixel(GObj.dc, Origin.x, Origin.y, RGB(255, 0, 0));

	wchar_t str[32] = TEXT("");
	for (int a = 0; a < BallList.length; a++) {
		swprintf_s(str, 16, TEXT("%d"), a);
		BallList[a]->Draw(Frame);
		Point pt = Frame.Convert(BallList[a]->Pt);
		TextOut(GObj.dc, pt.x, pt.y, str, wcslen(str));
	}

	if (LineBall != nullptr) {
		Point pt = Frame.Convert(LineBall->Obj.pt);
		MoveToEx(GObj.dc, WINDOW_ORIGIN_WIDTH / 2, WINDOW_ORIGIN_HEIGHT / 2, nullptr);
		LineTo(GObj.dc, pt.x, pt.y);
	}

	if (ControlBall != nullptr) {

		Point Conved = Frame.Convert(ControlBall->Pt);

		Rect SelRect = Rect(Conved.x - ControlBall->Picture.Width / 2,
			Conved.y - ControlBall->Picture.Height / 2,
			ControlBall->Picture.Width, ControlBall->Picture.Height);

		RECT rect = SelRect;

		FillRect(GObj.dc, &rect, (HBRUSH)GetStockObject(GRAY_BRUSH));
	}

	const int TextHeight = 12;
	swprintf_s(str, TEXT("FPS: %d"), FPS.LastFPS);
	TextOut(GObj.dc, 0, 0 + TextHeight * 0, str, wcslen(str));
	swprintf_s(str, TEXT("TPS: %d"), TPS.LastFPS);
	TextOut(GObj.dc, 0, 0 + TextHeight * 1, str, wcslen(str));
	swprintf_s(str, TEXT("THS: %d"), ThS.LastFPS);
	TextOut(GObj.dc, 0, 0 + TextHeight * 2, str, wcslen(str));
}

void MainScreen::Timer()
{
	if (Updater) {
		PhyKernel.PhysicsSpin();
		if (Track && TrackBall != nullptr) {
			Point Default(WINDOW_ORIGIN_WIDTH / 2, -WINDOW_ORIGIN_HEIGHT / 2);
			Point The = TrackBall->Pt;
			The = The * Frame.Magnif;
			Frame.OriginOffset = Default - (The);
		}
		TPS.UpdateFps();

		if (Processor.IsKeyDown('Q')) {
			Frame.Magnif = Frame.Magnif * 0.95;
		}
		if (Processor.IsKeyDown('E')) {
			Frame.Magnif = Frame.Magnif / 0.95;
		}
		static const double Val = 8;
		if (Processor.IsKeyDown(VK_UP)) {
			Frame.OriginOffset.y -= Val;
		}
		if (Processor.IsKeyDown(VK_DOWN)) {
			Frame.OriginOffset.y += Val;
		}
		if (Processor.IsKeyDown(VK_LEFT)) {
			Frame.OriginOffset.x += Val;
		}
		if (Processor.IsKeyDown(VK_RIGHT)) {
			Frame.OriginOffset.x -= Val;
		}

		if (Processor.IsKeyDown('W')&&ControlBall) {
			ControlBall->Obj.Speed.y += Val;
		}
		if (Processor.IsKeyDown('S') && ControlBall) {
			ControlBall->Obj.Speed.y -= Val;
		}
		if (Processor.IsKeyDown('A') && ControlBall) {
			ControlBall->Obj.Speed.x -= Val;
		}
		if (Processor.IsKeyDown('D') && ControlBall) {
			ControlBall->Obj.Speed.x += Val;
		}
	}

	int Temp = Processor.IsRoll();
	if (Temp != 0) {
		if (ControlBall == nullptr) {
			nTick += Temp;
			PhyKernel.SetTickSpeed(nTick);
			Updater = ::Timer(1000 / nTick);
			cout << "FPS:" << nTick << endl;
		}
		else {
			ControlBall->Obj.Mass += 0.5 * Temp;
			cout << "Mass:" << ControlBall->Obj.Mass << endl;
		}
	}
	if (Processor.IsButtonHit(true)) {
		cout << "Create one!" << endl;
		Ball* New = new Ball(TEXT("B.bmp"), BallSize, BallMass);
		Mem->ReFormatBitmap(New->Picture, BallSize.x, BallSize.y);
		//New->Picture.Alpha = 100;

		New->Pt = Frame.Disconvert(Processor.GetMousePos());
		cout << "At " << New->Pt.x << " " << New->Pt.y << endl;
		BallList.Add(-1, New);
		PhyKernel.AddObject(&New->Obj);
		ControlBall = New;
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
	if (Processor.IsKeyHit(VK_DELETE)) {
		int Index = -1;
		for (int a = 0; a < BallList.length; a++) {
			if (BallList[a] == ControlBall) {
				Index = a;
			}
		}
		if (Index != -1) {
			cout << "Delete:" << Index << endl;
			if (ControlBall == BallList[Index]) {
				ControlBall = nullptr;
			}
			if (LineBall == BallList[Index]) {
				LineBall = nullptr;
			}
			if (TrackBall == BallList[Index]) {
				TrackBall = nullptr;
			}
			PhyKernel.DelObject(&BallList[Index]->Obj);
			BallList.Del(Index);
			delete ControlBall;
			ControlBall = nullptr;
		}
		else {
			cout << "Unselect" << endl;
		}
	}
	if (Processor.IsKeyHit(VK_F1)) {
		PhyKernel.MultiThreadSupport(2);
		cout << "Multi Thread is open" << endl;
	}
	if (Processor.IsKeyHit(VK_F2)) {
		LineBall = ControlBall;
	}
	if (Processor.IsKeyHit(VK_F3)) {
		if (ControlBall) {
			Track = true;
		}
		else {
			Track = false;
		}
		TrackBall = ControlBall;
		cout << "Track:" << Track << endl;
	}
	ThS.UpdateFps();
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
