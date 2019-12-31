#include "ResizingTool.h"

#include "DrawingPaper.h"
#include "FlowChart.h"
#include "Shape.h"
#include "Symbol.h"

#include "Arrow.h"
#include "LeftDown.h"
#include "RightDown.h"
#include "RightDownJoin.h"
#include "Join.h"
#include "RepeatTrue.h"
#include "RepeatFalse.h"

#include "SelectingTool.h"
#include <stdio.h>

#include "ScrollController.h"
#include "Scrolls.h"
#include "MemoryController.h"

#include "TutorialForm.h"
#include "Tutorials.h"
#include "FlowChartEditor.h"
#include "TutorialController.h"
#pragma warning (disable : 4996)

ResizingTool* ResizingTool::instance = 0;

ResizingTool::ResizingTool() {
}

ResizingTool* ResizingTool::Instance() {
	if (instance == 0) {
		instance = new ResizingTool;
	}
	return instance;
}

void ResizingTool::Destroy() {
	if (instance != 0) {
		delete instance;
		instance = 0;
	}
}

void ResizingTool::OnLButtonDown(DrawingPaper *canvas, UINT nFlags, CPoint point) {
	canvas->currentX = point.x;
	canvas->currentY = point.y;

	Long count;
	Long(*indexes);
	dynamic_cast<FlowChart *>(canvas->flowChart)->GetSelecteds(&indexes, &count);
	canvas->memoryController->RememberOther(indexes, count);
	if (indexes != 0) {
		delete[] indexes;
	}
}

void ResizingTool::OnMouseMove(DrawingPaper *canvas, UINT nFlags, CPoint point) {
	Long x, y, width, height, width2, height2;
	Shape *shape;
	shape = (dynamic_cast<FlowChart *>(canvas->flowChart))->GetAt(canvas->indexOfSelected);
	
	Long(*indexes)=new Long[dynamic_cast<FlowChart*>(canvas->flowChart)->GetLength()];
	indexes[0] = canvas->indexOfSelected;

	if (dynamic_cast<Symbol *>(shape)) {
		switch (canvas->hitCode) {
		case HIT_TOPLEFT:
			x = shape->GetLeft() + point.x - canvas->currentX;
			y = shape->GetTop() + point.y - canvas->currentY;
			width = shape->GetRight() - x;
			height = shape->GetBottom() - y;
			break;

		case HIT_TOPMIDDLE:
			x = shape->GetLeft();
			y = shape->GetTop() + point.y - canvas->currentY;
			width = shape->GetRight() - x;
			height = shape->GetBottom() - y;
			break;

		case HIT_TOPRIGHT:
			x = shape->GetLeft();
			y = shape->GetTop() + point.y - canvas->currentY;
			width = shape->GetRight() + point.x - canvas->currentX - x;
			height = shape->GetBottom() - y;
			break;

		case HIT_LEFTMIDDLE:
			x = shape->GetLeft() + point.x - canvas->currentX;
			y = shape->GetTop();
			width = shape->GetRight() - x;
			height = shape->GetBottom() - y;
			break;

		case HIT_RIGHTMIDDLE:
			x = shape->GetLeft();
			y = shape->GetTop();
			width = shape->GetRight() + point.x - canvas->currentX - x;
			height = shape->GetBottom() - y;
			break;

		case HIT_BOTTOMLEFT:
			x = shape->GetLeft() + point.x - canvas->currentX;
			y = shape->GetTop();
			width = shape->GetRight() - x;
			height = shape->GetBottom() + point.y - canvas->currentY - y;
			break;

		case HIT_BOTTOMMIDDLE:
			x = shape->GetLeft();
			y = shape->GetTop();
			width = shape->GetRight() - x;
			height = shape->GetBottom() + point.y - canvas->currentY - y;
			break;

		case HIT_BOTTOMRIGHT:
			x = shape->GetLeft();
			y = shape->GetTop();
			width = shape->GetRight() + point.x - canvas->currentX - x;
			height = shape->GetBottom() + point.y - canvas->currentY - y;
			break;
		}
		if (width >= 150 && height >= 50) {
			shape->Move(x, y);
			shape->ReSize(width, height);
		}
	}
	else if (dynamic_cast<Arrow *>(shape)) {
		switch (canvas->hitCode) {
		case HIT_IN:
			x = shape->GetX();
			y = shape->GetY() + point.y - canvas->currentY;
			width = shape->GetWidth();
			height = shape->GetBottom() - y;
			break;
		case HIT_OUT:
			x = shape->GetX();
			y = shape->GetY();
			width = shape->GetWidth();
			height = shape->GetHeight() + point.y - canvas->currentY;
			break;
		}
		shape->Move(x, y);
		shape->ReSize(width, height);
	}
	else if (dynamic_cast<LeftDown *>(shape)) {
		switch (canvas->hitCode) {
		case HIT_IN:
			x = shape->GetX() + point.x - canvas->currentX;
			y = shape->GetY() + point.y - canvas->currentY;
			width = shape->GetX() + shape->GetWidth() - x;
			height = shape->GetY() + shape->GetHeight() - y;
			break;
		case HIT_OUT:
			x = shape->GetX();
			y = shape->GetY();
			width = shape->GetWidth() + point.x - canvas->currentX;
			height = shape->GetHeight() + point.y - canvas->currentY;
			break;
		}
		shape->Move(x, y);
		shape->ReSize(width, height);
	}
	else if (dynamic_cast<RightDown *>(shape)) {
		switch (canvas->hitCode) {
		case HIT_IN:
			x = shape->GetX() + point.x - canvas->currentX;
			y = shape->GetY() + point.y - canvas->currentY;
			width = shape->GetX() + shape->GetWidth() - x;
			height = shape->GetY() + shape->GetHeight() - y;
			break;
		case HIT_OUT:
			x = shape->GetX();
			y = shape->GetY();
			width = shape->GetWidth() + point.x - canvas->currentX;
			height = shape->GetHeight() + point.y - canvas->currentY;
			break;
		}
		shape->Move(x, y);
		shape->ReSize(width, height);
	}
	else if (dynamic_cast<Join *>(shape)) {
		switch (canvas->hitCode) {
		case HIT_TRUE:
			x = shape->GetX() + point.x - canvas->currentX;
			y = shape->GetY() + point.y - canvas->currentY;
			width = shape->GetX() + shape->GetWidth() - x;
			height = shape->GetY() + shape->GetHeight() - y;
			height2 = dynamic_cast<Join *>(shape)->GetHeight2();
			break;
		case HIT_FALSE:
			x = shape->GetX();
			y = shape->GetY();
			width = shape->GetWidth() + point.x - canvas->currentX;
			height = shape->GetHeight() + point.y - canvas->currentY;
			height2 = dynamic_cast<Join *>(shape)->GetHeight2();
			break;
		case HIT_OUT:
			x = shape->GetX();
			y = shape->GetY();
			width = shape->GetWidth();
			height = shape->GetHeight();
			height2 = dynamic_cast<Join *>(shape)->GetHeight2() + point.y - canvas->currentY;
			break;
		}
		shape->Move(x, y);
		dynamic_cast<Join *>(shape)->ReSize(width, height, height2);
	}
	else if (dynamic_cast<RightDownJoin *>(shape)) {
		switch (canvas->hitCode) {
		case HIT_FALSE:
			x = shape->GetX() + point.x - canvas->currentX;
			y = shape->GetY() + point.y - canvas->currentY;
			width = shape->GetX() + shape->GetWidth() - x;
			height = shape->GetY() + shape->GetHeight() - y;
			width2 = dynamic_cast<RightDownJoin *>(shape)->GetWidth2();
			height2 = dynamic_cast<RightDownJoin *>(shape)->GetHeight2();
			break;
		case HIT_HANDLE:
			x = shape->GetX();
			y = shape->GetY();
			width = shape->GetWidth();
			height = shape->GetHeight();
			width2 = dynamic_cast<RightDownJoin *>(shape)->GetWidth2() + point.x - canvas->currentX;
			height2 = dynamic_cast<RightDownJoin *>(shape)->GetHeight2() + point.y - canvas->currentY;
			break;
		case HIT_TRUE:
			x = shape->GetX();
			y = shape->GetY();
			width = shape->GetWidth() + point.x - canvas->currentX;
			height = shape->GetHeight() + point.y - canvas->currentY;
			width2 = dynamic_cast<RightDownJoin *>(shape)->GetWidth2();
			height2 = dynamic_cast<RightDownJoin *>(shape)->GetHeight2();
			break;
		}
		shape->Move(x, y);
		dynamic_cast<RightDownJoin *>(shape)->ReSize(width, height, width2, height2);
	}
	else if (dynamic_cast<RepeatTrue *>(shape)) {
		switch (canvas->hitCode) {
		case HIT_IN:
			x = shape->GetX() + point.x - canvas->currentX;
			y = shape->GetY() + point.y - canvas->currentY;
			width = shape->GetX() + shape->GetWidth() - x;
			height = shape->GetY() + shape->GetHeight() - y;
			width2 = dynamic_cast<RepeatTrue *>(shape)->GetWidth2();
			height2 = dynamic_cast<RepeatTrue *>(shape)->GetHeight2();
			break;
		case HIT_OUT:
			x = shape->GetX();
			y = shape->GetY();
			width = shape->GetWidth() + point.x - canvas->currentX;
			height = shape->GetHeight() + point.y - canvas->currentY;
			width2 = dynamic_cast<RepeatTrue *>(shape)->GetWidth2();
			height2 = dynamic_cast<RepeatTrue *>(shape)->GetHeight2();
			break;
		case HIT_HANDLE:
			x = shape->GetX();
			y = shape->GetY();
			width = shape->GetWidth();
			height = shape->GetHeight();
			width2 = dynamic_cast<RepeatTrue *>(shape)->GetWidth2() + point.x - canvas->currentX;
			height2 = dynamic_cast<RepeatTrue *>(shape)->GetHeight2() + point.y - canvas->currentY;
			break;
		}
		shape->Move(x, y);
		dynamic_cast<RepeatTrue *>(shape)->ReSize(width, height, width2, height2);

	}
	else if (dynamic_cast<RepeatFalse *>(shape)) {
		switch (canvas->hitCode) {
		case HIT_IN:
			x = shape->GetX() + point.x - canvas->currentX;
			y = shape->GetY() + point.y - canvas->currentY;
			width = shape->GetX() + shape->GetWidth() - x;
			height = shape->GetY() + shape->GetHeight() - y;
			width2 = dynamic_cast<RepeatFalse *>(shape)->GetWidth2();
			height2 = dynamic_cast<RepeatFalse *>(shape)->GetHeight2();
			break;
		case HIT_OUT:
			x = shape->GetX();
			y = shape->GetY();
			width = shape->GetWidth() + point.x - canvas->currentX;
			height = shape->GetHeight() + point.y - canvas->currentY;
			width2 = dynamic_cast<RepeatFalse *>(shape)->GetWidth2();
			height2 = dynamic_cast<RepeatFalse *>(shape)->GetHeight2();
			break;
		case HIT_HANDLE:
			x = shape->GetX();
			y = shape->GetY();
			width = shape->GetWidth();
			height = shape->GetHeight();
			width2 = dynamic_cast<RepeatFalse *>(shape)->GetWidth2() + point.x - canvas->currentX;
			height2 = dynamic_cast<RepeatFalse *>(shape)->GetHeight2() + point.y - canvas->currentY;
			break;
		}
		shape->Move(x, y);
		dynamic_cast<RepeatFalse *>(shape)->ReSize(width, height, width2, height2);
	}
	canvas->currentX = point.x;
	canvas->currentY = point.y;
	canvas->Invalidate(true);

	if (indexes != 0) {
		delete[] indexes;
	}
}

void ResizingTool::OnLButtonUp(DrawingPaper *canvas, UINT nFlags, CPoint point) {
	// 20160720 ���� ũ�� ����� �����ϴ� ������� ����
	canvas->mode = DrawingPaper::SELECT;
	canvas->tool = SelectingTool::Instance();
	canvas->RedrawWindow();

	TutorialForm *tutorialForm = (TutorialForm*)dynamic_cast<FlowChartEditor*>(canvas->GetParent())->windows[2];
	if (tutorialForm != NULL) {
		tutorialForm->tutorialController->Update();
	}
}