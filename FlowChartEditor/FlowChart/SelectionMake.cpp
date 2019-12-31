// SelectionMake.cpp

#include "SelectionMake.h"
#include "DrawingPaper.h"
#include "FlowChart.h"
#include "Shape.h"
#include "Symbol.h"
#include "Decision.h"
#include "LeftDown.h"
#include "RightDown.h"
#include "RightDownJoin.h"
#include "RepeatFalse.h"
#include "Join.h"
#include "Arrow.h"
#include "ScrollController.h"
#include "Scrolls.h"
#include "MemoryController.h"

SelectionMake::SelectionMake() {
}

SelectionMake::~SelectionMake() {
}

void SelectionMake::Create(DrawingPaper *canvas) {
	// 1. �迭 ÷�ڰ� ���� ���� ������ ã�´�.
	Long(*indexes) = 0;
	Long length;
	Shape *shape, *top;
	Long x, y, width, height, width2, height2;
	Long index = -1, index_ = -1;
	Long i, j;
	Attribute attribute, decisionAttribute, initAttribute;
	RECT rect, rect2, bufferRange;

	FlowChart temp((dynamic_cast<FlowChart *>(canvas->flowChart))->GetCapacity());
	FlowChart lefts((dynamic_cast<FlowChart *>(canvas->flowChart))->GetCapacity());
	FlowChart rights((dynamic_cast<FlowChart *>(canvas->flowChart))->GetCapacity());
	FlowChart buffer((dynamic_cast<FlowChart *>(canvas->flowChart))->GetCapacity());

	dynamic_cast<FlowChart *>(canvas->flowChart)->GetSelecteds(&indexes, &length);
	for (i = 0; i < length; i++) {
		if (index == -1 || indexes[i] < index) { // ������ ��ġ�� ã�´�.
			index = indexes[i];
		}
		shape = (dynamic_cast<FlowChart *>(canvas->flowChart))->GetAt(indexes[i])->Clone();
		temp.Attach(shape); // ���õ� ��ȣ���� �ӽÿ� ���� �ű��.
	}

	dynamic_cast<FlowChart *>(canvas->flowChart)->EraseSelectedAll(); // �������� ���õ� ��� ��ȣ�� �����.

	if (indexes != 0) {
		delete[] indexes;
		indexes = 0;
	}

	// Decision�� ���Ѵ�.
	for (i = 0; i < length; i++) {
		if (dynamic_cast<Decision *>(temp.GetAt(i))) {
			if (index_ == -1 || temp.GetAt(i)->GetY() < temp.GetAt(index_)->GetY()) {
				index_ = i;
			}
		}
	}
	top = temp.GetAt(index_)->Clone();
	buffer.Attach(top); //buffer �迭�� 0��°�� ������ ����� Decision�̴�.
	temp.Erase(index_);

	// top�� LeftDown RightDown ��ȣ�� �ִٸ� �����.
	temp.Find(LEFTDOWN | RIGHTDOWN, &indexes, &length);
	for (i = length; i > 0; i--) {
		attribute = initAttribute;
		temp.GetAt(i - 1)->GetAttribute(&attribute);
		Shape::MakeRectToPoint(attribute.pointIn, &rect);
		if (top->IsIncluded(canvas->painter, rect)) {
			temp.Erase(i - 1);
		}
	}

	// lefts �� rights�� ���´�.
	for (i = 0; i < temp.GetLength(); i++) {
		if (temp.GetAt(i)->CenterOfGravityX() < top->CenterOfGravityX()) {
			lefts.Attach(temp.GetAt(i)->Clone());
		}
		else {
			rights.Attach(temp.GetAt(i)->Clone());
		}
	}

	//19.9.16 �Ǵܱ�ȣ �¿��� ù ��° ��ȣ�� �߾�x�� �Ǵܱ�ȣ �� ������ ���ʿ� ������ ������ ��ġ�� �����δ�.
	if (lefts.GetAt(0)->CenterOfGravityX() > top->GetX() - 40) {
		lefts.GetAt(0)->Move(top->GetX() - 40 - lefts.GetAt(0)->GetWidth() / 2, lefts.GetAt(0)->GetY());
	}
	if (rights.GetLength() > 0 && rights.GetAt(0)->CenterOfGravityX() < top->GetX() + top->GetWidth() + 40) {
		rights.GetAt(0)->Move(top->GetX() + top->GetWidth() + 40 - rights.GetAt(0)->GetWidth() / 2, rights.GetAt(0)->GetY());
	}

	// lefts �� rights�� �������� �����Ѵ�.
	// ���İ������� ������ ���δ�. tempLefts �� tempRights�� �̿��ؼ� ��������
	FlowChart tempLefts(lefts);
	FlowChart tempRights(rights);
	tempLefts.AscendingSort();
	tempRights.AscendingSort();

	// ������ ��ȣ�� Arrow�̸� �����Ѵ�.
	i = tempLefts.GetLength() - 1;
	if (i >= 0 && dynamic_cast<Arrow *>(tempLefts.GetAt(i))) {
		index_ = lefts.Find(tempLefts.GetAt(i));
		lefts.Erase(index_);
		tempLefts.Erase(i);
		i--;
	}

	j = tempRights.GetLength() - 1;
	if (j >= 0 && dynamic_cast<Arrow *>(tempRights.GetAt(j))) {
		index_ = rights.Find(tempRights.GetAt(j));
		rights.Erase(index_);
		tempRights.Erase(j);
		j--;
	}

	// RightDownJoin ��ȣ�� �׷��� �ִٸ� �����
	if (i >= 0 && dynamic_cast<RightDownJoin *>(tempLefts.GetAt(i))) {
		attribute = initAttribute;
		tempLefts.GetAt(i)->GetAttribute(&attribute);
		Shape::MakeRectToPoint(attribute.pointFalse, &rect);
		if (top->IsIncluded(canvas->painter, rect)) {
			index_ = lefts.Find(tempLefts.GetAt(i));
			lefts.Erase(index_);
			tempLefts.Erase(i);
		}
	}
	else if (i >= 0 && dynamic_cast<Join *>(tempLefts.GetAt(i))) // Join ��ȣ�� �׷��� �ִٸ� �����.
	{
		attribute = initAttribute;
		tempLefts.GetAt(i)->GetAttribute(&attribute);
		Shape::MakeRectToPoint(attribute.pointTrue, &rect);
		Shape::MakeRectToPoint(attribute.pointFalse, &rect2);
		if (tempRights.GetAt(j)->IsIncluded(canvas->painter, rect) || tempRights.GetAt(j)->IsIncluded(canvas->painter, rect2)) {
			index_ = lefts.Find(tempLefts.GetAt(i));
			lefts.Erase(index_);
			tempLefts.Erase(i);
		}
	}

	if (j >= 0 && dynamic_cast<RightDownJoin *>(tempRights.GetAt(j))) {
		attribute = initAttribute;
		tempRights.GetAt(j)->GetAttribute(&attribute);
		Shape::MakeRectToPoint(attribute.pointFalse, &rect);
		if (top->IsIncluded(canvas->painter, rect)) {
			index_ = rights.Find(tempRights.GetAt(j));
			rights.Erase(index_);
			tempRights.Erase(j);
		}
	}
	else if (j >= 0 && dynamic_cast<Join *>(tempRights.GetAt(j))) {
		attribute = initAttribute;
		tempRights.GetAt(j)->GetAttribute(&attribute);
		Shape::MakeRectToPoint(attribute.pointTrue, &rect);
		Shape::MakeRectToPoint(attribute.pointFalse, &rect2);
		if (tempLefts.GetAt(i)->IsIncluded(canvas->painter, rect) || tempLefts.GetAt(i)->IsIncluded(canvas->painter, rect2)) {
			index_ = rights.Find(tempRights.GetAt(j));
			rights.Erase(index_);
			tempRights.Erase(j);
		}
	}

	// LeftDown�� �׸���.	
	top->GetAttribute(&decisionAttribute);
	x = decisionAttribute.pointTrue.x;
	y = decisionAttribute.pointTrue.y;

	attribute = initAttribute;
	tempLefts.GetAt(0)->GetAttribute(&attribute);
	width = attribute.pointIn.x - decisionAttribute.pointTrue.x;
	height = attribute.pointIn.y - decisionAttribute.pointTrue.y;
	shape = new LeftDown(x, y, width, height, 20, DASH, 20, String("TRUE"));
	shape->Select(true);
	buffer.Attach(shape);

	//lefts ���� buffer �� �ű��. 
	for (i = 0; i < lefts.GetLength(); i++) {
		buffer.Attach(lefts.GetAt(i)->Clone());
	}

	if (rights.GetLength() > 0) { // Join�� �����Ѵ�.
		// rightDown�� �׸���.
		buffer.GetRange(&bufferRange);

		x = decisionAttribute.pointFalse.x;
		y = decisionAttribute.pointFalse.y;

		attribute = initAttribute;
		tempRights.GetAt(0)->GetAttribute(&attribute);
		width = attribute.pointIn.x - decisionAttribute.pointFalse.x;
		height = attribute.pointIn.y - decisionAttribute.pointFalse.y;

		shape = new RightDown(x, y, width, height, 20, DASH, 20, String("FALSE"));
		shape->Select(true);
		buffer.Attach(shape);

		// rights ���� buffer �� �ű��
		for (i = 0; i < rights.GetLength(); i++) {
			buffer.Attach(rights.GetAt(i)->Clone());
		}

		// join�� �׸���.
		attribute = initAttribute;
		i = tempLefts.GetLength() - 1;
		tempLefts.GetAt(i)->GetAttribute(&attribute);
		x = attribute.pointOut.x;
		y = attribute.pointOut.y;

		attribute = initAttribute;
		i = tempRights.GetLength() - 1;
		tempRights.GetAt(i)->GetAttribute(&attribute);
		width = attribute.pointOut.x - x;
		height = attribute.pointOut.y - y;

		(height >= 0) ? (height2 = height + 30) : (height2 = 30);
		shape = new Join(x, y, width, height, height2, 20, DASH, 20, String(" "));
		shape->Select(true);
		buffer.Attach(shape);
	}
	else {
		//RightDownJoin�� �����Ѵ�.
		buffer.GetRange(&bufferRange);

		x = decisionAttribute.pointFalse.x;
		y = decisionAttribute.pointFalse.y;

		width2 = bufferRange.right - x + 30;

		attribute = initAttribute;
		i = tempLefts.GetLength() - 1;
		//buffer.GetAt(i)->GetAttribute(&attribute);
		width = attribute.pointOut.x - x;
		height = attribute.pointOut.y - y;
		height2 = 30;

		shape = new RightDownJoin(x, y, width, height, width2, height2, 20, DASH, 20, String("FALSE"));
		shape->Select(true);
		buffer.Attach(shape);
	}

	// Arrow�� �׸���.	
	attribute = initAttribute;
	i = buffer.GetLength() - 1;
	buffer.GetAt(i)->GetAttribute(&attribute);
	x = attribute.pointOut.x;
	y = attribute.pointOut.y;

	width = 0;
	height = 30;
	shape = new Arrow(x, y, width, height, 20, DASH, 20, String(" "));
	shape->Select(true);
	buffer.Attach(shape);

	Long(*positions) = new Long[buffer.GetLength()];
	j = 0;
	Long count = 0;

	buffer.AscendingSort();

	for (i = 0; i < buffer.GetLength(); i++) {
		Long position = dynamic_cast<FlowChart *>(canvas->flowChart)->Insert(index + i, buffer.GetAt(i)->Clone());
		if (dynamic_cast<Line*>(buffer.GetAt(i))) {
			positions[j++] = position;
			count++;
		}
	}
	canvas->memoryController->RememberAdd(positions, count);

	if (positions != 0) {
		delete[] positions;
	}

	canvas->RedrawWindow();
}