// IntervalMake.cpp

#include "IntervalMake.h"
#include "DrawingPaper.h"
#include "FlowChart.h"
#include "Shape.h"
#include "Symbol.h"
#include "MemoryController.h"

IntervalMake::IntervalMake(){
}

IntervalMake::~IntervalMake(){
}

void IntervalMake::Create(DrawingPaper *canvas){
	// 1. ���õ� �������� ã�´�.
	Shape *shape;
	Long count = 0;

	Long it = dynamic_cast<FlowChart *>(canvas->flowChart)->GetLength();
	Shape* (*indexes) = new Shape* [it];
	Long(*positions) = new Long[it];

	Long i = 0;	
	while ( i < it ){
		shape = dynamic_cast<FlowChart *>(canvas->flowChart)->GetAt(i);
		if( shape->IsSelected()){
			//  ���õ� ��ȣ�� �� ���� ���� �����Ѵ�.
			if( dynamic_cast<Symbol *>(shape) ){
				indexes[count] = shape->Clone();
				positions[count] = i;
				count++;
			}
			else{
				shape->Select(false);
			}
		}
		i++;
	}

	// 2. �������� y ��ǥ�� �������� ������������ ���� �Ѵ�. (��������)
	Shape *temp;	
	Long y;
	Long y_;
	Long j;
	Long k;
	for( i = 1 ; i < count; i++){		
		y = indexes[i]->GetY();		
		j = 0;		
		y_ = indexes[j]->GetY();
		while( j < i &&  y_ < y ){
			j++;
			y_ = indexes[j]->GetY();
		}

		temp = indexes[i];

		for(k = i ; k >= j+1; k--){
			indexes[k] = indexes[k-1];
		}
		indexes[k] = temp;
	}

	// 3. ������ ������ ���Ѵ�. ��ü���̿��� �������� ���̸� ���� ������ ���� - 1 ���� ������.
	Long height = indexes[count-1]->GetY() - indexes[0]->GetY() - indexes[0]->GetHeight();

	i = 1;
	while ( i < count-1 ){
		height = height - indexes[i]->GetHeight();
		i++;
	}
	Long interval = height/(count-1);

	// 4. ������ �� ��ġ �Ѵ�.
	canvas->memoryController->RememberOther(positions, count);

	Long previousHeight; // ���������� ����
	previousHeight = indexes[0]->GetY() + indexes[0]->GetHeight();
	i = 1; // ù�� ° ������ ��ġ ����
	while ( i < count ){
		indexes[i]->Move(indexes[i]->GetX(), previousHeight + interval);
		previousHeight = previousHeight + interval + indexes[i]->GetHeight();
		i++;
	}

	// 5. �������� ���õ� ������ �����.
	i = it -1;
	while ( i >= 0 ){
		shape = dynamic_cast<FlowChart *>(canvas->flowChart)->GetAt(i);
		if( shape->IsSelected()){
			dynamic_cast<FlowChart *>(canvas->flowChart)->Erase(i);
		}
		i--;
	}

	// 6. �������� ���õ� ������ ���� �ִ´�.
	i = 0;
	while ( i < count ){
		dynamic_cast<FlowChart *>(canvas->flowChart)->Attach(indexes[i]);
		i++;
	}

	if ( indexes != 0 ){
		delete[] indexes;
	}

	if (positions != 0) {
		delete[] positions;
	}
}