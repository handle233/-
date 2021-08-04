#pragma once
/**
* project : �������Ⱦģ��
* file    : Modules.h
* Copyright 2021 handle All rights reserved.
* �廳Ԭ¡ƽԺʿ
**/
#include "CommonHead.h"
#include "Manager.h"
#include "Physics.h"
#include "Window.h"
#include "ReferenceFrame.h"

extern WindowProcess Processor;
extern Screen* Mem;
extern Manager* Master;

class Ball {
public:
	Bitmap Picture;
	Object Obj;
	Point Pt;
	Ball(const TCHAR* PhotoStr, Vector& BSize, double Mass);
	void Draw(ReferenceConvertor& Frme);
};

class MainScreen :public Module {
private:
	bool Track;
	Bitmap BG;

	Physics PhyKernel;
	List<Ball *> BallList;
	ReferenceConvertor Frame;
	Vector BallSize;
	double BallMass = 0.5;
	int nTick;
	::Timer Updater;
	::Timer Reactor;

	Ball* ControlBall;
	Ball* TrackBall;
	Ball* LineBall;

	FPSCounter FPS;
	FPSCounter TPS;
	FPSCounter ThS;
public:
	MainScreen();
	~MainScreen();
	void Main();
	void Timer();
};
