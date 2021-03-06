// SizeMake.h
#include "SizeMake.h"
#include "DrawingPaper.h"
#include "FlowChart.h"
#include "Shape.h"
#include "Symbol.h"
#include "MemoryController.h"

SizeMake::SizeMake() {
}

SizeMake::~SizeMake() {
}

void SizeMake::Create(DrawingPaper *canvas) {
	Long i;
	Long j = 0;
	Shape *shape;
	Shape* (*indexes) = 0;
	Long count = 0;

	// 1. 선택된 기호들을 찾는다.
	Long it = dynamic_cast<FlowChart *>(canvas->flowChart)->GetLength();

	if (it > 0) {
		indexes = new Shape*[it];
	}
	Long(*positions) = new Long[it];

	i = 0;
	while (i < it) {
		shape = dynamic_cast<FlowChart *>(canvas->flowChart)->GetAt(i);
		if (shape->IsSelected()) {
			if (dynamic_cast<Symbol *>(shape)) {
				indexes[j] = shape->Clone();
				positions[j] = i;
				count++;
				j++;
			}
			else {
				shape->Select(false);
			}
		}
		i++;
	}

	canvas->memoryController->RememberOther(positions, count);

	// 2. 가장 상단의 기호를 찾는다.
	Long index;
	Long y = 0;
	i = 0;
	while (i < count) {
		if (indexes[i]->GetY() < y || y == 0) {
			y = indexes[i]->GetY();
			index = i;
		}
		i++;
	}

	// 3. 상단의 기호의 크기를 기억한다.
	Long width;
	Long height;
	width = indexes[index]->GetWidth();
	height = indexes[index]->GetHeight();

	// 4. 선택된 기호들의 크기를 기준에 맞게 한다.
	i = 0;
	while (i < count) {
		indexes[i]->ReSize(width, height);
		i++;
	}

	// 5. 순서도의 기호를 지우다.
	i = it - 1;
	while (i >= 0) {
		shape = dynamic_cast<FlowChart *>(canvas->flowChart)->GetAt(i);
		if (shape->IsSelected()) {
			dynamic_cast<FlowChart *>(canvas->flowChart)->Erase(i);
		}
		i--;
	}

	// 6. 선택된 도형을 순서도에 끼워넣는다.
	i = 0;
	while (i < count) {
		dynamic_cast<FlowChart *>(canvas->flowChart)->Attach(indexes[i]);
		i++;
	}

	// 7. Indexes 해제
	if (indexes != 0) {
		delete[] indexes;
	}
}