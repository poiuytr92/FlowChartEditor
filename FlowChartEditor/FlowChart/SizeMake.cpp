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

	// 1. ���õ� ��ȣ���� ã�´�.
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

	// 2. ���� ����� ��ȣ�� ã�´�.
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

	// 3. ����� ��ȣ�� ũ�⸦ ����Ѵ�.
	Long width;
	Long height;
	width = indexes[index]->GetWidth();
	height = indexes[index]->GetHeight();

	// 4. ���õ� ��ȣ���� ũ�⸦ ���ؿ� �°� �Ѵ�.
	i = 0;
	while (i < count) {
		indexes[i]->ReSize(width, height);
		i++;
	}

	// 5. �������� ��ȣ�� �����.
	i = it - 1;
	while (i >= 0) {
		shape = dynamic_cast<FlowChart *>(canvas->flowChart)->GetAt(i);
		if (shape->IsSelected()) {
			dynamic_cast<FlowChart *>(canvas->flowChart)->Erase(i);
		}
		i--;
	}

	// 6. ���õ� ������ �������� �����ִ´�.
	i = 0;
	while (i < count) {
		dynamic_cast<FlowChart *>(canvas->flowChart)->Attach(indexes[i]);
		i++;
	}

	// 7. Indexes ����
	if (indexes != 0) {
		delete[] indexes;
	}
}