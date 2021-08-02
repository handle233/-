#pragma once
/**
* project : 物理和渲染模型
* file    : GameMain.h
* Copyright 2021 handle All rights reserved.
* 缅怀袁隆平院士
**/
#include "CommonHead.h"
#include "Window.h"
#include "Manager.h"
#include "MathSupport.h"
//void TempProc();
//LRESULT CALLBACK TestWinProc(HWND hwnd, UINT msg, WPARAM wpm, LPARAM lpm);
//void TempLoad(HWND hwnd);

void PreLoad(const HWND& Win);
void MainFunction();
void Clear();
LRESULT CALLBACK MainWinProc(HWND hwnd, UINT msg, WPARAM wpm, LPARAM lpm);