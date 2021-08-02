#pragma once
/**
* project : �������Ⱦģ��
* file    : Main.cpp
* Copyright 2021 handle All rights reserved.
* �廳Ԭ¡ƽԺʿ
**/
#include "CommonHead.h"
#include "MathSupport.h"
#include "Container.h"
#include "Window.h"

class Object;
class Physics {
private:
	GraphObject *Obj;
	int Tick;
	List<Object*> *Objs;
	bool ColliTendCheck(Object& a, Object& b);
public:
	void SetDebugScreen(Screen* Scr);
	void Colli(Object& a, Object& b);
	const int& TickSpeed = Tick;
	Physics(int TickNum);
	void SetTickSpeed(int TickS) { Tick = TickS; }
	bool AddObject(Object* pObj);
	void PhysicsSpin();
};

class Object {
	friend class Physics;
public:
	Point& pt;
	Vector Speed;
	Vector Size;
	double Mass;
	Object(Point& Pos, Vector& Size_, double Mass_);
};