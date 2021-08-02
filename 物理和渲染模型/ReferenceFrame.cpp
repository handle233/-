#include "ReferenceFrame.h"
/**
* project : 物理和渲染模型
* file    : ReferenceFrame.cpp
* Copyright 2021 handle All rights reserved.
* 缅怀袁隆平院士
**/

ReferenceConvertor::ReferenceConvertor()
{
	Magnif = 1.0;
	SourceDirX = Positive;
	SourceDirY = Positive;
	DestinDirX = Positive;
	DestinDirY = Positive;
	OriginOffset.x = 0;
	OriginOffset.y = 0;
}

Point ReferenceConvertor::Convert(Point Pt)
{
	Pt.x = (Pt.x + OriginOffset.x) * SourceDirX * DestinDirX * Magnif;
	Pt.y = (Pt.y + OriginOffset.y) * SourceDirY * DestinDirY * Magnif;
	return Pt;
}

Point ReferenceConvertor::Disconvert(Point Pt)
{
	if (Magnif <= 0) {
		throw Exception(EXPT_ERROR, "放大比率为0，不是该值的常规范围");
	}
	Pt.x = (Pt.x * SourceDirX * DestinDirX / Magnif) - OriginOffset.x;
	Pt.y = (Pt.y * SourceDirY * DestinDirY / Magnif) - OriginOffset.y;
	return Pt;
}

Vector ReferenceConvertor::Resize(Vector Vec)
{
	if (Magnif <= 0) {
		throw Exception(EXPT_ERROR, "放大比率为0，不是该值的常规范围");
	}
	return Vec * Magnif;
}
