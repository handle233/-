#pragma once
/**
* project : 物理和渲染模型
* file    : CommonHead.h
* Copyright 2021 handle All rights reserved.
* 缅怀袁隆平院士
**/
#include "CommonHead.h"
#include "Container.h"

void nullproc();
class Window {
private:
	HWND hwnd;
	typedef void (*CyclingFunc)();
public:
	/*
	* Window函数是用来创建窗口的
	*/
	Window(HINSTANCE hInst, const WCHAR* ClassName, const WCHAR* WindowName, int Width, int Height, WNDPROC WinProc, const WCHAR* Icon = nullptr);
	/*
	* 用于消息循环
	*/
	void MessageLoop(CyclingFunc CycFun = nullproc);
	/*
	* 构造拷贝函数
	*/
	Window(const Window& Win) {
		hwnd = Win.hwnd;
	}
	/*
	* HWND to Window
	*/
	Window(HWND win) {
		hwnd = win;
	}
	/*
	* Window to HWND
	*/
	operator HWND() {
		return hwnd;
	}



	/*
	* 用来打开调试窗口
	*/
	static void OpenConsole();
};

class WindowProcess {
private:
	struct sKeyState {
		bool Down;
		bool Hit;
	}Keys[255];
	sKeyState LeftButton, RightButton;
	short Wheel;
	void KeyDownProc(WPARAM wpm, LPARAM lpm);
	void KeyUpProc(WPARAM wpm, LPARAM lpm);
	void MouseDownProc(UINT MouseMessage);
	void MouseUpProc(UINT MouseMessage);
public:
	WindowProcess() {
		memset(Keys, 0, sizeof(sKeyState) * 255);
		memset(&LeftButton, 0, sizeof(sKeyState));
		memset(&RightButton, 0, sizeof(sKeyState));
	}
	/*用于筛选消息*/
	bool WindowMessageFilter(HWND hwnd, UINT msg, WPARAM wpm, LPARAM lpm);
	/*键盘按下侦测*/
	bool IsKeyDown(int code);
	/*键盘按下侦测*/
	bool IsKeyHit(int code);
	/*鼠标按下侦测*/
	bool IsButtonHit(bool IsRight = false);
	/*鼠标按下侦测*/
	bool IsButtonDown(bool IsRight = false);
	/*鼠标滚轮侦测*/
	int IsRoll();
};

class Text;
class Bitmap;
class Screen {
public:
	friend class GraphObject;
private:
	HWND Win;
	RECT& rect;
	RECT Client;
	HDC dc;
	HBITMAP Bitmap;
public:
	BYTE Alpha;
	Screen(HWND hwnd);
	Screen(Screen& Scr);
	Screen(Screen& Scr, ::Bitmap& Pict);
	~Screen();
	void Clear(unsigned Colorgb);
	void Resize();
	void operator << (Screen& Scr);
	void operator += (Screen& Scr);

	void ReFormatBitmap(::Bitmap& Picture,int NewWidth,int NewHeight);
	void operator + (::Bitmap& Picture);
};
class GraphObject {
protected:
public:
	HDC& dc;//debug
	GraphObject(Screen& Scr);
};

class Text :public GraphObject {
public:
	HFONT hFont;
	Text(Screen& Scr);
	~Text();
};
class Bitmap{
public:
	int x,y,Width, Height;
	int Transrgb;
	BYTE Alpha;
	HBITMAP Photo;
	Bitmap(const TCHAR* sFile);
	~Bitmap();
};

class Timer {
private:
	unsigned Space;
	unsigned LstTime;
public:
	Timer(int TimeSpace) {
		Space = TimeSpace;
		LstTime = timeGetTime();
	}
	operator bool() {
		if (timeGetTime() - LstTime > Space) {
			LstTime = timeGetTime();
			return true;
		}
		return false;
	}
};
class ThreadSync {
private:
	CRITICAL_SECTION Section;
public:
	ThreadSync() {
		InitializeCriticalSection(&Section);
	}
	void Lock() {
		EnterCriticalSection(&Section);
	}
	void Free() {
		LeaveCriticalSection(&Section);
	}
	~ThreadSync() {
		DeleteCriticalSection(&Section);
	}
};