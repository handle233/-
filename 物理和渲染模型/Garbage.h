#pragma once
WindowProcess TestA;
GDIRender* Render = nullptr;
PhotoMap* Bg, * Ball;
Text* AText;
ExceptionHandler Handler;
void TempLoad(HWND hwnd)
try {
	Exception::InitLog("Log.txt");
	Exception::SelHandler(&Handler);
	Render = new GDIRender(hwnd);
	
}ROOT_EXCEPTION_FILTER
void TempProc() {
	Bg->Draw(0, 0);
	Ball->Draw(100, 100);
	if (TestA.IsButtonDown()) {
		AText->Draw(100, 200);
	}
	if (TestA.IsButtonHit()) {
		Ball->ReSize(rand() % 100 + 50, rand() % 100 + 50);
	}
	Render->Present(true);
}
/*
* 这也是个毫无意义的空函数
*/
LRESULT CALLBACK TestWinProc(HWND hwnd, UINT msg, WPARAM wpm, LPARAM lpm) {
	if (TestA.WindowMessageFilter(hwnd, msg, wpm, lpm)) {
		return 0;
	}
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wpm, lpm);
	}
	return 0;
}