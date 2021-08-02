#pragma once
/**
* project : 物理和渲染模型
* file    : Modules.h
* Copyright 2021 handle All rights reserved.
* 缅怀袁隆平院士
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
	Bitmap BG;

	Physics PhyKernel;
	List<Ball *> BallList;
	ReferenceConvertor Frame;
	Vector BallSize;
	double BallMass = 1.0;
	int nTick;
	::Timer Updater;
	::Timer Reactor;

	Ball* ControlBall;
public:
	MainScreen();
	~MainScreen();
	void Main();
	void Timer();
};
