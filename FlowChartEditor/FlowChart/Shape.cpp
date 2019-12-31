/******************************************************************
* ���� �̸� : Shape.cpp
* ��� : ����(��ȣ,��)�� �߻�ȭ Ŭ����
* �ۼ��� : ����â
* �ۼ����� : 2015�� 3�� 30��
*******************************************************************/
#include <afxwin.h>

#include "Shape.h"
#include "Painter.h"

#include "Document.h"
#include "InputOutput.h"
#include "Preparation.h"
#include "Terminal.h"
#include "Process.h"
#include "PunchedCard.h"
#include "Decision.h"
#include "ScrollController.h"
#include "Scrolls.h"
#include "Arrow.h"
#include "LeftDown.h"
#include "RightDown.h"
#include "Join.h"
#include "RepeatTrue.h"
#include "RepeatFalse.h"
#include "RightDownJoin.h"

Attribute::Attribute() {
	this->vertexIn = ' ';
	this->vertexOut = ' ';
	this->vertexTrue = ' ';
	this->vertexFalse = ' ';

	POINT initPoint = { 0,0 };
	this->pointIn = initPoint;
	this->pointOut = initPoint;
	this->pointTrue = initPoint;
	this->pointFalse = initPoint;
}

Attribute::~Attribute() {
}

Attribute::Attribute(const Attribute& source) {
	this->vertexIn = source.vertexIn;
	this->vertexOut = source.vertexOut;
	this->vertexTrue = source.vertexTrue;
	this->vertexFalse = source.vertexFalse;
	this->pointIn = source.pointIn;
	this->pointOut = source.pointOut;
	this->pointTrue = source.pointTrue;
	this->pointFalse = source.pointFalse;
}

Attribute& Attribute::operator = (const Attribute& source) {
	this->vertexIn = source.vertexIn;
	this->vertexOut = source.vertexOut;
	this->vertexTrue = source.vertexTrue;
	this->vertexFalse = source.vertexFalse;
	this->pointIn = source.pointIn;
	this->pointOut = source.pointOut;
	this->pointTrue = source.pointTrue;
	this->pointFalse = source.pointFalse;
	return *this;
}

bool Attribute::IsEqual(const Attribute& other) {
	bool retVO = false;
	if (this->vertexIn == other.vertexIn &&
		this->vertexOut == other.vertexOut &&
		this->vertexTrue == other.vertexTrue &&
		this->vertexFalse == other.vertexFalse &&
		this->pointIn.x == other.pointIn.x &&
		this->pointIn.y == other.pointIn.y &&
		this->pointOut.x == other.pointOut.x &&
		this->pointOut.y == other.pointOut.y &&
		this->pointTrue.x == other.pointTrue.x &&
		this->pointTrue.y == other.pointTrue.y &&
		this->pointFalse.x == other.pointFalse.x &&
		this->pointFalse.y == other.pointFalse.y) {
		retVO = true;
	}
	return retVO;
}

bool Attribute::IsNotEqual(const Attribute& other) {
	bool retVO = false;
	if (this->vertexIn != other.vertexIn ||
		this->vertexOut != other.vertexOut ||
		this->vertexTrue != other.vertexTrue ||
		this->vertexFalse != other.vertexFalse ||
		this->pointIn.x != other.pointIn.x ||
		this->pointIn.y != other.pointIn.y ||
		this->pointOut.x != other.pointOut.x ||
		this->pointOut.y != other.pointOut.y ||
		this->pointTrue.x != other.pointTrue.x ||
		this->pointTrue.y != other.pointTrue.y ||
		this->pointFalse.x != other.pointFalse.x ||
		this->pointFalse.y != other.pointFalse.y) {
		retVO = true;
	}
	return retVO;
}

bool Attribute::operator == (const Attribute& other) {
	bool retVO = false;
	if (this->vertexIn == other.vertexIn &&
		this->vertexOut == other.vertexOut &&
		this->vertexTrue == other.vertexTrue &&
		this->vertexFalse == other.vertexFalse &&
		this->pointIn.x == other.pointIn.x &&
		this->pointIn.y == other.pointIn.y &&
		this->pointOut.x == other.pointOut.x &&
		this->pointOut.y == other.pointOut.y &&
		this->pointTrue.x == other.pointTrue.x &&
		this->pointTrue.y == other.pointTrue.y &&
		this->pointFalse.x == other.pointFalse.x &&
		this->pointFalse.y == other.pointFalse.y) {
		retVO = true;
	}
	return retVO;
}

bool Attribute::operator != (const Attribute& other) {
	bool retVO = false;
	if (this->vertexIn != other.vertexIn ||
		this->vertexOut != other.vertexOut ||
		this->vertexTrue != other.vertexTrue ||
		this->vertexFalse != other.vertexFalse ||
		this->pointIn.x != other.pointIn.x ||
		this->pointIn.y != other.pointIn.y ||
		this->pointOut.x != other.pointOut.x ||
		this->pointOut.y != other.pointOut.y ||
		this->pointTrue.x != other.pointTrue.x ||
		this->pointTrue.y != other.pointTrue.y ||
		this->pointFalse.x != other.pointFalse.x ||
		this->pointFalse.y != other.pointFalse.y) {
		retVO = true;
	}
	return retVO;
}

Shape::Shape()
	:contents() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
	this->backGroundColor = RGB(255, 255, 255);
	this->borderLine = static_cast<PenStyle>(BORDERLINE);
	this->borderColor = BORDERCOLOR;
	this->isSelected = false;
}

Shape::Shape(Long x, Long y, Long width, Long height, COLORREF backGroundColor,
	PenStyle borderLine, DWORD borderColor, String contents)
	:contents(contents) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->backGroundColor = backGroundColor;
	this->borderLine = borderLine;
	this->borderColor = borderColor;

	this->isSelected = false;
}

Shape::~Shape() {}

Shape::Shape(const Shape& source)
	: contents(source.contents) {
	this->x = source.x;
	this->y = source.y;

	this->width = source.width;
	this->height = source.height;

	this->backGroundColor = source.backGroundColor;

	this->borderLine = source.borderLine;
	this->borderColor = source.borderColor;
	this->isSelected = source.isSelected;
}

Shape& Shape::operator=(const Shape& source)
{
	this->x = source.x;
	this->y = source.y;

	this->width = source.width;
	this->height = source.height;

	this->backGroundColor = source.backGroundColor;

	this->borderLine = source.borderLine;
	this->borderColor = source.borderColor;

	this->contents = source.contents;

	this->isSelected = source.isSelected;

	return *this;
}

bool Shape::IsEqual(const Shape& other) {
	bool retVo = false;

	if (this->x == other.x &&
		this->y == other.y &&
		this->width == other.width &&
		this->height == other.height &&
		this->backGroundColor == other.backGroundColor &&
		this->borderLine == other.borderLine &&
		this->borderColor == other.borderColor &&
		this->contents == other.contents) {
		retVo = true;
	}
	return retVo;
}

bool Shape::IsNotEqual(const Shape& other) {
	bool retVo = false;

	if (this->x != other.x ||
		this->y != other.y ||
		this->width != other.width ||
		this->height != other.height ||
		this->backGroundColor != other.backGroundColor ||
		this->borderLine != other.borderLine ||
		this->borderColor != other.borderColor ||
		this->contents != other.contents) {
		retVo = true;
	}
	return retVo;
}

Long Shape::IsUpperThan(const Shape& other) {
	Long retVo;

	if (this->y < other.y)
		retVo = 1;
	else if (this->y == other.y)
		retVo = 0;
	else
		retVo = -1;

	return retVo;
}

Long Shape::IsDownThan(const Shape& other) {
	Long retVo;

	if (this->y > other.y)
		retVo = 1;
	else if (this->y == other.y)
		retVo = 0;
	else
		retVo = -1;

	return retVo;
}

Long Shape::IsFrontThan(const Shape& other) {
	Long retVo;

	if (this->x < other.x)
		retVo = 1;
	else if (this->y == other.y)
		retVo = 0;
	else
		retVo = -1;

	return retVo;
}

Long Shape::IsRearThan(const Shape& other) {
	Long retVo;

	if (this->x > other.x)
		retVo = 1;
	else if (this->y == other.y)
		retVo = 0;
	else
		retVo = -1;

	return retVo;
}

bool Shape::operator ==(const Shape& other) {
	bool retVo = false;

	if (this->x == other.x &&
		this->y == other.y &&
		this->width == other.width &&
		this->height == other.height &&
		this->backGroundColor == other.backGroundColor &&
		this->borderLine == other.borderLine &&
		this->borderColor == other.borderColor &&
		this->contents == other.contents) {
		retVo = true;
	}
	return retVo;
}
bool Shape::operator !=(const Shape& other) {
	bool retVo = false;

	if (this->x != other.x ||
		this->y != other.y ||
		this->width != other.width ||
		this->height != other.height ||
		this->backGroundColor != other.backGroundColor ||
		this->borderLine != other.borderLine ||
		this->borderColor != other.borderColor ||
		this->contents != other.contents) {
		retVo = true;
	}
	return retVo;
}

void Shape::Move(Long x, Long y) {
	this->x = x;
	this->y = y;
}

void Shape::ReSize(Long width, Long height) {
	this->width = width;
	this->height = height;
}

void Shape::Paint(COLORREF backGroundColor, PenStyle borderLine, DWORD borderColor) {
	this->backGroundColor = backGroundColor;
	this->borderLine = borderLine;
	this->borderColor = borderColor;
}

void Shape::DrawActiveShape(CDC *dc) {
	POINT point[4];
	point[0].x = x - LINETHICKNESS;
	point[0].y = y - LINETHICKNESS;
	point[1].x = x + width + LINETHICKNESS;
	point[1].y = y - LINETHICKNESS;
	point[2].x = x + width + LINETHICKNESS;
	point[2].y = y + height + LINETHICKNESS;
	point[3].x = x - LINETHICKNESS;
	point[3].y = y + height + LINETHICKNESS;

	dc->Polygon(point, BOXVERTECIES);
}

void Shape::DrawActiveShape(Painter *painter) {
	POINT point[4];
	point[0].x = x - LINETHICKNESS;
	point[0].y = y - LINETHICKNESS;
	point[1].x = x + width + LINETHICKNESS;
	point[1].y = y - LINETHICKNESS;
	point[2].x = x + width + LINETHICKNESS;
	point[2].y = y + height + LINETHICKNESS;
	point[3].x = x - LINETHICKNESS;
	point[3].y = y + height + LINETHICKNESS;

	painter->DrawPolygon(point, BOXVERTECIES);
}

//////////////////////////////////////////////////////////////////////////
// ���� ���� : 2015-11-23

void Shape::Select(bool selected) {
	this->isSelected = selected;
}

int Shape::GetHitCode(Painter *painter, CPoint point) {
	CRgn region;
	this->GetRegion(painter, &region);
	return GetHitCode(painter, point, region);
}

int Shape::GetHitCode(Painter *painter, const CPoint& point, const CRgn& region) {
	int result = HIT_NONE;
	if (region.PtInRegion(point)) {
		result = HIT_BODY;
	}

	CRect rectSelect;
	GetSelectionMarkerRect(HIT_TOPLEFT, &rectSelect);
	if (rectSelect.PtInRect(point)) {
		result = HIT_TOPLEFT;
	}
	GetSelectionMarkerRect(HIT_TOPMIDDLE, &rectSelect);
	if (rectSelect.PtInRect(point)) {
		result = HIT_TOPMIDDLE;
	}
	GetSelectionMarkerRect(HIT_TOPRIGHT, &rectSelect);
	if (rectSelect.PtInRect(point)) {
		result = HIT_TOPRIGHT;
	}
	GetSelectionMarkerRect(HIT_BOTTOMLEFT, &rectSelect);
	if (rectSelect.PtInRect(point)) {
		result = HIT_BOTTOMLEFT;
	}
	GetSelectionMarkerRect(HIT_BOTTOMMIDDLE, &rectSelect);
	if (rectSelect.PtInRect(point)) {
		result = HIT_BOTTOMMIDDLE;
	}
	GetSelectionMarkerRect(HIT_BOTTOMRIGHT, &rectSelect);
	if (rectSelect.PtInRect(point)) {
		result = HIT_BOTTOMRIGHT;
	}
	GetSelectionMarkerRect(HIT_LEFTMIDDLE, &rectSelect);
	if (rectSelect.PtInRect(point)) {
		result = HIT_LEFTMIDDLE;
	}
	GetSelectionMarkerRect(HIT_RIGHTMIDDLE, &rectSelect);
	if (rectSelect.PtInRect(point)) {
		result = HIT_RIGHTMIDDLE;
	}
	return result;
}

void Shape::GetSelectionMarkerRect(UINT marker, CRect *rect)
{
	int x_;
	int y_;
	switch (marker) {
	case HIT_TOPLEFT:
		x_ = x;
		y_ = y;
		break;
	case HIT_TOPMIDDLE:
		x_ = x + width / 2;
		y_ = y;
		break;
	case HIT_TOPRIGHT:
		x_ = x + width;
		y_ = y;
		break;
	case HIT_LEFTMIDDLE:
		x_ = x;
		y_ = y + height / 2;
		break;
	case HIT_RIGHTMIDDLE:
		x_ = x + width;
		y_ = y + height / 2;
		break;
	case HIT_BOTTOMLEFT:
		x_ = x;
		y_ = y + height;
		break;
	case HIT_BOTTOMMIDDLE:
		x_ = x + width / 2;
		y_ = y + height;
		break;
	case HIT_BOTTOMRIGHT:
		x_ = x + width;
		y_ = y + height;
		break;
	}

	rect->left = x_ - 4;
	rect->top = y_ - 4;
	rect->right = x_ + 5;
	rect->bottom = y_ + 5;
}

void Shape::GetSelectionMarkerAllRegion(CRgn *region) {
	Long x_, y_;
	CRgn region1;
	x_ = x;
	y_ = y;
	region->CreateRectRgn(x_ - 6, y_ - 6, x_ + 7, y_ + 7);

	x_ = x + width / 2;
	y_ = y;
	region1.CreateRectRgn(x_ - 6, y_ - 6, x_ + 7, y_ + 7);
	region->CombineRgn(region, &region1, RGN_OR);
	region1.DeleteObject();

	x_ = x + width;
	y_ = y;
	region1.CreateRectRgn(x_ - 6, y_ - 6, x_ + 7, y_ + 7);
	region->CombineRgn(region, &region1, RGN_OR);
	region1.DeleteObject();

	x_ = x;
	y_ = y + height / 2;
	region1.CreateRectRgn(x_ - 6, y_ - 6, x_ + 7, y_ + 7);
	region->CombineRgn(region, &region1, RGN_OR);
	region1.DeleteObject();

	x_ = x + width;
	y_ = y + height / 2;
	region1.CreateRectRgn(x_ - 6, y_ - 6, x_ + 7, y_ + 7);
	region->CombineRgn(region, &region1, RGN_OR);
	region1.DeleteObject();

	x_ = x;
	y_ = y + height;
	region1.CreateRectRgn(x_ - 6, y_ - 6, x_ + 7, y_ + 7);
	region->CombineRgn(region, &region1, RGN_OR);
	region1.DeleteObject();

	x_ = x + width / 2;
	y_ = y + height;
	region1.CreateRectRgn(x_ - 6, y_ - 6, x_ + 7, y_ + 7);
	region->CombineRgn(region, &region1, RGN_OR);
	region1.DeleteObject();

	x_ = x + width;
	y_ = y + height;
	region1.CreateRectRgn(x_ - 6, y_ - 6, x_ + 7, y_ + 7);
	region->CombineRgn(region, &region1, RGN_OR);
	region1.DeleteObject();
}

HCURSOR Shape::GetCursor(int hit) const {
	HCURSOR cursor = NULL;
	switch (hit) {
	case HIT_BODY:
		cursor = LoadCursor(NULL, IDC_SIZEALL);
		break;
	case HIT_TOPLEFT:
		cursor = LoadCursor(NULL, IDC_SIZENWSE);
		break;
	case HIT_TOPMIDDLE:
		cursor = LoadCursor(NULL, IDC_SIZENS);
		break;
	case HIT_TOPRIGHT:
		cursor = LoadCursor(NULL, IDC_SIZENESW);
		break;
	case HIT_BOTTOMLEFT:
		cursor = LoadCursor(NULL, IDC_SIZENESW);
		break;
	case HIT_BOTTOMMIDDLE:
		cursor = LoadCursor(NULL, IDC_SIZENS);
		break;
	case HIT_BOTTOMRIGHT:
		cursor = LoadCursor(NULL, IDC_SIZENWSE);
		break;
	case HIT_LEFTMIDDLE:
		cursor = LoadCursor(NULL, IDC_SIZEWE);
		break;
	case HIT_RIGHTMIDDLE:
		cursor = LoadCursor(NULL, IDC_SIZEWE);
		break;
	}

	return cursor;
}

void Shape::Copy(Shape *object) {
	this->x = object->GetX();
	this->y = object->GetY();
	this->width = object->GetWidth();
	this->height = object->GetHeight();
	this->backGroundColor = object->GetBackGroundColor();
	this->borderLine = object->GetBorderLine();
	this->borderColor = object->GetBorderColor();
	this->contents = object->GetContents();

	this->isSelected = object->IsSelected();
}

void Shape::DrawSelectionMarkers(CDC* dc, ScrollController *scrollController)
{
	CRect rectSelect;
	CBrush brush;
	CBrush *oldBrush;
	brush.CreateSolidBrush(RGB(0, 0, 255));
	oldBrush = dc->SelectObject(&brush);
	GetSelectionMarkerRect(HIT_TOPLEFT, &rectSelect);
	Long positionX = scrollController->GetScroll(1)->GetPosition();
	Long positionY = scrollController->GetScroll(0)->GetPosition();
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	dc->Rectangle(rectSelect);

	GetSelectionMarkerRect(HIT_TOPMIDDLE, &rectSelect);
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	dc->Rectangle(rectSelect);

	GetSelectionMarkerRect(HIT_TOPRIGHT, &rectSelect);
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	dc->Rectangle(rectSelect);

	GetSelectionMarkerRect(HIT_BOTTOMLEFT, &rectSelect);
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	dc->Rectangle(rectSelect);

	GetSelectionMarkerRect(HIT_BOTTOMMIDDLE, &rectSelect);
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	dc->Rectangle(rectSelect);

	GetSelectionMarkerRect(HIT_BOTTOMRIGHT, &rectSelect);
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	dc->Rectangle(rectSelect);

	GetSelectionMarkerRect(HIT_RIGHTMIDDLE, &rectSelect);
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	dc->Rectangle(rectSelect);

	GetSelectionMarkerRect(HIT_LEFTMIDDLE, &rectSelect);
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	dc->Rectangle(rectSelect);

	dc->SelectObject(oldBrush);
	brush.DeleteObject();
}

void Shape::DrawSelectionMarkers(Painter* painter, ScrollController *scrollController)
{
	CRect rectSelect;

	painter->ChangePlaneProperty(BS_SOLID, RGB(0, 0, 255));

	GetSelectionMarkerRect(HIT_TOPLEFT, &rectSelect);
	Long positionX = scrollController->GetScroll(1)->GetPosition();
	Long positionY = scrollController->GetScroll(0)->GetPosition();
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle(rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom);

	GetSelectionMarkerRect(HIT_TOPMIDDLE, &rectSelect);
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle(rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom);

	GetSelectionMarkerRect(HIT_TOPRIGHT, &rectSelect);
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle(rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom);

	GetSelectionMarkerRect(HIT_BOTTOMLEFT, &rectSelect);
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle(rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom);

	GetSelectionMarkerRect(HIT_BOTTOMMIDDLE, &rectSelect);
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle(rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom);

	GetSelectionMarkerRect(HIT_BOTTOMRIGHT, &rectSelect);
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle(rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom);

	GetSelectionMarkerRect(HIT_RIGHTMIDDLE, &rectSelect);
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle(rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom);

	GetSelectionMarkerRect(HIT_LEFTMIDDLE, &rectSelect);
	rectSelect.left -= positionX;
	rectSelect.top -= positionY;
	rectSelect.right -= positionX;
	rectSelect.bottom -= positionY;
	painter->DrawRectangle(rectSelect.left, rectSelect.top, rectSelect.right, rectSelect.bottom);
}

void Shape::MakeRectToPoint(POINT point, RECT *rect) {
	rect->top = point.y - BOXSCOPE;
	rect->bottom = point.y + BOXSCOPE;
	rect->left = point.x - BOXSCOPE;
	rect->right = point.x + BOXSCOPE;
}

void Shape::Rewrite(char(*text)) {
	this->contents = text;
}

int Shape::GetSymbolID() {
	int id=0;
	if (dynamic_cast<Document*>(this)) {
		id = ID_DOCUMENT;
	}
	else if (dynamic_cast<InputOutput*>(this)) {
		id = ID_INPUTOUTPUT;
	}
	else if (dynamic_cast<Preparation*>(this)) {
		id = ID_PREPARATION;
	}
	else if (dynamic_cast<Terminal*>(this)) {
		id = ID_TERMINAL;
	}
	else if (dynamic_cast<Process*>(this)) {
		id = ID_PROCESS;
	}
	else if (dynamic_cast<PunchedCard*>(this)) {
		id = ID_PUNCHEDCARD;
	}
	else if (dynamic_cast<Decision*>(this)) {
		id = ID_DECISION;
	}

	return id;
}

int Shape::GetLineID() {
	int id = 0;
	if (dynamic_cast<Arrow*>(this)) {
		id = ID_ARROW;
	}
	else if (dynamic_cast<LeftDown*>(this)) {
		id = ID_LEFTDOWN;
	}
	else if (dynamic_cast<RightDown*>(this)) {
		id = ID_RIGHTDOWN;
	}
	else if (dynamic_cast<Join*>(this)) {
		id = ID_JOIN;
	}
	else if (dynamic_cast<RepeatTrue*>(this)) {
		id = ID_REPEATTRUE;
	}
	else if (dynamic_cast<RepeatFalse*>(this)) {
		id = ID_REPEATFALSE;
	}
	else if (dynamic_cast<RightDownJoin*>(this)) {
		id = ID_RIGHTDOWNJOIN;
	}

	return id;
}