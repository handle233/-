#pragma once
/**
* project : �������Ⱦģ��
* file    : GameMain.h
* Copyright 2021 handle All rights reserved.
* �廳Ԭ¡ƽԺʿ
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