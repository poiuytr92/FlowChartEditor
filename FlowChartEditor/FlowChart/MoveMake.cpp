//MoveMake.cpp

#include "MoveMake.h"
#include "DrawingPaper.h"
#include "FlowChart.h"
#include "Shape.h"
#include "RightDown.h"
#include "LeftDown.h"
#include "RightDownJoin.h"
#include "Join.h"
#include "RepeatFalse.h"
#include "MemoryController.h"

MoveMake::MoveMake(){
}

MoveMake::~MoveMake(){
}

void MoveMake::Create(DrawingPaper *canvas){
	Long i;
	Long j = 0;
	Long count = 0;
	Long it;
	Shape *shape;
	Shape* (*indexes) = 0;

	// 1. ���õ� ��ȣ���� ã�´�.
	i = 0;
	it = dynamic_cast<FlowChart *>(canvas->flowChart)->GetLength();
	indexes = new Shape*[it];

	Long(*positions) = new Long[it];

	while ( i < it ){
		shape = dynamic_cast<FlowChart *>(canvas->flowChart)->GetAt(i);
		if( shape->IsSelected() ){
			indexes[j] = shape->Clone();
			positions[j] = i;
			count++;
			j++;
		}
		i++;
	}

	canvas->memoryController->RememberOther(positions, count);

	// 2. ���� ����� ��ȣ�� ã�´�.	
	Long y = 0;
	Long index;
	i = 0;
	while ( i < count ){
		if( indexes[i]->GetY() < y || y == 0 ){
			y = indexes[i]->GetY();
			index = i;
		}
		i++;
	}

	// 3. ����� ��ġ�� ����Ѵ�.
	Long x;	
	Attribute attribute;
	Attribute attribute2;
	Long distance;
	indexes[index]->GetAttribute(&attribute);	

	// 4. ���õ� ��ȣ���� ���ؿ� �°� �̵��Ѵ�.
	i = 0;
	while ( i < count ){
		y = indexes[i]->GetY();
		x = indexes[i]->GetX();
		indexes[i]->GetAttribute(&attribute2);
		distance = attribute2.pointIn.x -attribute.pointIn.x;
		indexes[i]->Move(x-distance,y);
		i++;
	}

	// 5. �������� ��ȣ�� �����.
	i = it -1;
	while ( i >= 0 ){
		shape = dynamic_cast<FlowChart *>(canvas->flowChart)->GetAt(i);
		if( shape->IsSelected()){
			dynamic_cast<FlowChart *>(canvas->flowChart)->Erase(i);
		}
		i--;
	}

	// 6. ���õ� ������ �������� �����ִ´�.
	i = 0;
	while( i < count ){
		dynamic_cast<FlowChart *>(canvas->flowChart)->Attach(indexes[i]);
		i++;
	}

	// 7. Indexes ����
	if (indexes != 0) {
		delete[] indexes;
	}

	if (positions != 0) {
		delete[] positions;
	}
}