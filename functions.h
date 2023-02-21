#pragma once

typedef struct SPoint
{
	float x, y;
} TPoint;

typedef struct SObject
{
	TPoint pos;
	TPoint size;
	COLORREF brush;
	TPoint speed;

} TObject;

typedef struct SPosInLifeTime
{
	TPoint pos;
	TPoint size;
	int lifeTime;
} TPosInLifeTime;

TPoint point(float x, float y);

void ObjectInit
(
	TObject* obj,
	TPoint Pos,
	TPoint Size,
	COLORREF ColorRGB
);

void ObjectShow(TObject obj, HDC hdc);
void PlayerControl(TObject* obj);
void ObjectMove(TObject* obj);
void ArrayShow(HDC hdc, TPosInLifeTime* posArray, int arrayLen);
int IfMove(TObject obj);
void WinShow(HDC hdc, RECT rc, TObject obj,TPosInLifeTime* posArray, int arrayLen);

TObject ShadowObj;