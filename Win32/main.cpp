#include <sdkddkver.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <windowsx.h>
#include <ObjIdl.h>
#include <gdiplus.h>
#include <tchar.h>


#include "resource.h"
using namespace Gdiplus;
#pragma comment (lib, "Gdiplus.lib")

/**
*  enum Figure
* Used to define which figure to draw
*/
enum Figure
{
	None,
	Cercle,
	Square,
	Cross,
	Triangle
};

/**
* Fonction OnPaint test
* Used for test purposes
*/
VOID OnPaint(HDC hdc)
{
	Graphics graphics(hdc);
	Color color(0, 0, 0);
	Pen pen(color);
	graphics.DrawLine(&pen, 0, 0, 200, 100);
	graphics.Clear(Color(240, 240, 240));
}

/**
* function drawRect
* Used to draw a rectangle
*@param hdc
*@param color define the color of the figure
*/
VOID drawRect(HDC hdc, Color color)
{
	Graphics graphics(hdc);
	Pen pen(color);
	graphics.Clear(Color(240, 240, 240));
	Rect rectangle(40, 80, 100, 100);
	graphics.DrawRectangle(&pen, rectangle);
}

/**
* function drawCercle
* Used to draw a circle
*@param hdc
*@param color define the color of the figure
*/
VOID drawCercle(HDC hdc, Color color)
{
	Graphics graphics(hdc);
	Pen pen(color);
	Rect rectangle(40, 80, 100, 100);
	graphics.Clear(Color(240, 240, 240));
	graphics.DrawArc(&pen, rectangle, 0, 360);
}

/**
* function drawTriangle
* Used to draw a triangle
*@param hdc
*@param color define the color of the figure
*/
VOID drawTriangle(HDC hdc, Color color)
{
	Graphics graphics(hdc);
	Pen pen(color);
	graphics.Clear(Color(240, 240, 240));
	graphics.DrawLine(&pen, 40, 180, 140, 180);
	graphics.DrawLine(&pen, 140, 180, 90, 80);
	graphics.DrawLine(&pen, 90, 80, 40, 180);
}

/**
* function drawCross
* Used to draw a cross
*@param hdc
*@param color define the color of the figure
*/
VOID drawCross(HDC hdc, Color color)
{
	Graphics graphics(hdc);
	Pen pen(color);
	graphics.Clear(Color(240, 240, 240));
	graphics.DrawLine(&pen, 40, 80, 140, 180);
	graphics.DrawLine(&pen, 40, 180, 140, 80);
}

/**
* function WndProc
* Handle the events of the application
*@param hwnm
*@param message
*@param wParam
*@param lParam
*/
BOOL CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT paintStruct;
	HDC hDC;
	static Color drawingColor(Color::Black);
	static Figure figureToDraw(Figure::None);
	switch (message)
	{
	case WM_PAINT:
		hDC = BeginPaint(hwnd, &paintStruct);
		switch (figureToDraw)
		{
		case Cercle:
			drawCercle(hDC, drawingColor);
			break;
		case Square:
			drawRect(hDC, drawingColor);
			break;
		case Cross:
			drawCross(hDC, drawingColor);
			break;
		case Triangle:
			drawTriangle(hDC, drawingColor);
			break;
		default:
			break;
		}
		EndPaint(hwnd, &paintStruct);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case radioCercle:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				figureToDraw = Figure::Cercle;
				InvalidateRect(hwnd, NULL, true);
				UpdateWindow(hwnd);
				break;
			default:
				break;
			}
		}
		break;
		case radioCross:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				figureToDraw = Figure::Cross;
				InvalidateRect(hwnd, NULL, true);
				UpdateWindow(hwnd);
				break;
			default:
				break;
			}
		}
		break;

		case radioSquare:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				figureToDraw = Figure::Square;
				InvalidateRect(hwnd, NULL, true);
				UpdateWindow(hwnd);
				break;
			default:
				break;
			}
		}
		break;
		case radioTriangle:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				figureToDraw = Figure::Triangle;
				InvalidateRect(hwnd, NULL, true);
				UpdateWindow(hwnd);
				break;
			default:
				break;
			}
		}
		break;
		case radioBlue:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				drawingColor = Color::Blue;
				InvalidateRect(hwnd, NULL, true);
				UpdateWindow(hwnd);
				break;
			default:
				break;
			}
		}
		break;
		case radioGreen:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				drawingColor = Color::Green;
				InvalidateRect(hwnd, NULL, true);
				UpdateWindow(hwnd);
				break;
			default:
				break;
			}
		}
		break;
		case radioRed:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				drawingColor = Color::Red;
				InvalidateRect(hwnd, NULL, true);
				UpdateWindow(hwnd);
				break;
			default:
				break;
			}
		}
		break;
		case radioYellow:
		{
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				drawingColor = Color::Yellow;
				InvalidateRect(hwnd, NULL, true);
				UpdateWindow(hwnd);
				break;
			default:
				break;
			}
		}
		break;
		default:
			break;
		}
	}
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
		break;
	}
	return 0;
}

/**
* function WndProc
* Handle the events of the application
*@param hInstance
*@param hPrevInstance
*@param lpCmdLine
*@param nCmdShow
*@return if no problem (int)msg.wParam else 1
*/
int WINAPI WinMain( HINSTANCE hInstance,  HINSTANCE hPrevInstance,  LPSTR lpCmdLine,  int nCmdShow)
{
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	HWND dialog{};
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	dialog = CreateDialog(hInstance, MAKEINTRESOURCE(mainWindow), NULL, WndProc);
	if (!dialog)
	{
		MessageBox(NULL, "Error Loading", "CreateDialog", MB_ICONERROR);
		return 1;
	}

	ShowWindow(dialog, nCmdShow);
	UpdateWindow(dialog);

	MSG msg;
	while (::GetMessage(&msg, 0, 0, 0) > 0)
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}