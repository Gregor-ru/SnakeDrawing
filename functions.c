#pragma once

#include "framework.h"
#include "functions.h"

TPoint point(float x, float y)
{
	TPoint pt;
	pt.x = x;
	pt.y = y;
	return pt;
}

void ObjectInit
(
	TObject* obj,
	TPoint Pos,
	TPoint Size,
	COLORREF ColorRGB
)
{
	obj->pos = Pos;
	obj->size = Size;
	obj->brush = ColorRGB;
	obj->speed = point(0, 0);
}

int IfMove(TObject obj)
{
	if (
		GetKeyState(VK_UP) < 0 ||
		GetKeyState(VK_DOWN) < 0 ||
		GetKeyState(VK_LEFT) < 0 ||
		GetKeyState(VK_RIGHT) < 0
		)
	{
		return 1;
	}

	if (
		GetAsyncKeyState(VK_UP) > 0 ||
		GetAsyncKeyState(VK_DOWN) > 0 ||
		GetAsyncKeyState(VK_LEFT) > 0 ||
		GetAsyncKeyState(VK_RIGHT) > 0
		)
	{
		return -1;
	}

	return 0;
}

void ObjectShow(TObject obj, HDC hdc)
{
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, obj.brush);

	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, obj.brush);
	Rectangle
	(
		hdc,
		(int)(obj.pos.x),
		(int)(obj.pos.y),
		(int)(obj.pos.x + obj.size.x),
		(int)(obj.pos.y + obj.size.y)
	);

}

void PlayerControl(TObject* obj)
{
	static int objSpeed = 3;
	obj->speed.x = 0;
	obj->speed.y = 0;

	if (GetKeyState(VK_UP) < 0) obj->speed.y = -objSpeed;
	if (GetKeyState(VK_DOWN) < 0) obj->speed.y = objSpeed;
	if (GetKeyState(VK_LEFT) < 0) obj->speed.x = -objSpeed;
	if (GetKeyState(VK_RIGHT) < 0) obj->speed.x = objSpeed;
	if ((obj->speed.x != 0) && (obj->speed.y != 0))
		obj->speed = point(obj->speed.x * 0.7, obj->speed.y * 0.7);

}

void ObjectMove(TObject* obj)
{
	obj->pos.x += obj->speed.x;
	obj->pos.y += obj->speed.y;
}

void ArrayShow(HDC hdc, TPosInLifeTime *posArray, int arrayLen)
{
	
	TObject shadow;

	for (int i = 0; i < arrayLen; i++)
	{
		int color = (int)ITER_SIZE * posArray[i].lifeTime;

		if (posArray[i].lifeTime > 100) { color = (int)ITER_SIZE * (posArray[i].lifeTime - 100); }

		ObjectInit(&shadow, posArray[i].pos, posArray[i].size, RGB(color,255,color));

		/*printf("pos: (%f,%f)	Time: %d	rgb: %i %i %i\n", shadow.pos.x, shadow.pos.y, posArray[i].lifeTime - 100,
			GetRValue(shadow.brush), GetRValue(shadow.brush), GetRValue(shadow.brush));*/

		SelectObject(hdc, GetStockObject(DC_PEN));
		SetDCPenColor(hdc, shadow.brush);

		SelectObject(hdc, GetStockObject(DC_BRUSH));
		SetDCBrushColor(hdc, shadow.brush);
		Rectangle
		(
			hdc,
			(int)(shadow.pos.x),
			(int)(shadow.pos.y),
			(int)(shadow.pos.x + shadow.size.x),
			(int)(shadow.pos.y + shadow.size.y)
		);

	}

	//printf("\n");

}

void WinShow(HDC hdc, RECT rc, TObject obj, TPosInLifeTime *posArray, int arrayLen)
{
	HDC sqDc = CreateCompatibleDC(hdc);
	HBITMAP sqBm = CreateCompatibleBitmap(hdc, rc.right - rc.left, rc.bottom - rc.top);

	SelectObject(sqDc, sqBm);

	SelectObject(sqDc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(sqDc, RGB(255, 255, 255));
	Rectangle(sqDc, 0, 0, 640, 840);

	ArrayShow(sqDc, posArray, arrayLen);
	ObjectShow(obj, sqDc);

	BitBlt(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, sqDc, 0, 0, SRCCOPY);
	DeleteDC(sqDc);
	DeleteObject(sqBm);

}