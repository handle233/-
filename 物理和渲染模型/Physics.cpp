/**
* project : �������Ⱦģ��
* file    : Main.cpp
* Copyright 2021 handle All rights reserved.
* �廳Ԭ¡ƽԺʿ
**/
#include "Physics.h"

Object::Object(Point& Pos, Vector& Size_, double Mass_) :pt(Pos), Mass(Mass_) {
	Size = Size_;
}

Physics::Physics(int TickNum) : Tick(TickNum)
{
	Obj = nullptr;
	Objs = new List<Object*>;
	printf("Call!\n");
}

bool Physics::ColliTendCheck(Object& a, Object& b)
{
	Point Pt = a.pt;
	Pt.x -= a.Size.x / 2;
	Pt.y -= a.Size.y / 2;
	Rect ColRecA(Pt, a.Size);

	Pt = b.pt;
	Pt.x -= b.Size.x / 2;
	Pt.y -= b.Size.y / 2;
	Rect ColRecB(Pt, b.Size);

	if (Obj != nullptr) {
		RECT Tmp = ColRecA;
		Tmp.top = -Tmp.top;
		Tmp.bottom = -Tmp.bottom;
		//FillRect(Obj->dc, &Tmp, (HBRUSH)GetStockObject(GRAY_BRUSH));
	}
	if (Obj != nullptr) {
		RECT Tmp = ColRecB;
		Tmp.top = -Tmp.top;
		Tmp.bottom = -Tmp.bottom;
		//FillRect(Obj->dc, &Tmp, (HBRUSH)GetStockObject(GRAY_BRUSH));
	}
	if (ColRecA && ColRecB) {
		return true;
	}

	return false;
}

void Physics::SetDebugScreen(Screen* Scr)
{
	Obj = new GraphObject(*Scr);
}

void Physics::Colli(Object& a, Object& b)
{
	if (!ColliTendCheck(a, b)) {
		return;
	}
	Point DeltaPt = (a.pt - b.pt);
	Vector DeltaVA(DeltaPt.x,DeltaPt.y);
	DeltaVA = DeltaVA / DeltaVA.abs();

	double BorderWidth = sqrt(Figure(abs(a.Size.x / 2 + b.Size.x / 2)).Square() +
		Figure(abs(a.Size.y / 2 + b.Size.y / 2)).Square());

	double Width = sqrt(Figure(abs(DeltaPt.x)).Square() + Figure(abs(DeltaPt.y)).Square());
	double Rate = (BorderWidth - Width) / BorderWidth;
	cout << BorderWidth - Width << "	" << Rate*100 << "%" << "	" << BorderWidth * Rate << endl;

	DeltaVA = DeltaVA * BorderWidth * Rate;
	//DeltaVA = DeltaVA * 5;
	a.Speed = a.Speed + DeltaVA / a.Mass;
	b.Speed = b.Speed - DeltaVA / b.Mass;
}
/*
* Vector V0 = a.Speed - b.Speed;
	V0 = V0 * a.Mass;

	Point DeltaPos = b.pt - a.pt;
	Vector pV1(DeltaPos.x, DeltaPos.y);
	pV1 = pV1 / pV1.abs();
	
	Vector V1;
	double Sita = V0.Angle() - pV1.Angle();
	double x1 = sin(Sita) + cos(Sita);
	V1 = pV1*(V0.length() / (x1));

	Vector V2 = V0-V1;
	Vector OriginB = b.Speed;
	b.Speed = V1 / a.Mass + OriginB;
	a.Speed = V2 / b.Mass + OriginB;
*/

bool Physics::AddObject(Object* pObj)
{
	Objs->Add(-1, pObj);
	return true;
}

void Physics::PhysicsSpin()
{
	for (int a = 0; a < Objs->length; a++) {
		for (int b = a + 1; b < Objs->length; b++) {
			Colli(*(*Objs)[a], *(*Objs)[b]);
		}
	}
	for (int a = 0; a < Objs->length; a++) {
		(*Objs)[a]->pt.x += (*Objs)[a]->Speed.x / Tick;
		(*Objs)[a]->pt.y += (*Objs)[a]->Speed.y / Tick;
	}
}
