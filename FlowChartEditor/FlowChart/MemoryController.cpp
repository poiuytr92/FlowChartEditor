#include "MemoryController.h"
#include "Memory.h"
#include "Executions.h"
#include "FlowChart.h"
#include "DrawingPaper.h"
#include "SelectingTool.h"

MemoryController::MemoryController(DrawingPaper *drawingPaper) {
	this->drawingPaper = drawingPaper;
	this->undoMemory = new Memory;
	this->redoMemory = new Memory;
}

MemoryController::MemoryController(const MemoryController& source) {
	this->drawingPaper = source.drawingPaper;
	this->undoMemory = new Memory(*source.undoMemory);
	this->redoMemory = new Memory(*source.redoMemory);
}

MemoryController::~MemoryController() {
	if (this->undoMemory != NULL) {
		delete this->undoMemory;
	}
	if (this->redoMemory != NULL) {
		delete this->redoMemory;
	}
}

MemoryController& MemoryController::operator=(const MemoryController& source) {
	this->drawingPaper = source.drawingPaper;
	this->undoMemory = new Memory(*source.undoMemory);
	this->redoMemory = new Memory(*source.redoMemory);

	return *this;
}

void MemoryController::Undo() {
	//=========���� ����ϸ� ���������� �����ߴ� �͸� �ǵ�����.===================
	Execution *execution = this->undoMemory->GetAt(this->undoMemory->GetLength() - 1);

	//1. ó���ߴ� ��ȣ�� ������ŭ �ݺ��ϴ�.
	Long i = execution->GetLength() - 1;
	while (i >= 0) {
		//1.1. ���� ��ȣ�� ��ġ�� ���ϴ�.
		if (dynamic_cast<AddExecution*>(execution)) { //1.2. �����ߴ� ó���� '�߰�'������ �����.
			//���� �� ������ positions���� ������ positions ���� �� ���� shape�� ���� ����� �� ū positions�� ������.
			//Shape *shape = execution->GetShape(i);
			//Long index = dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->Find(shape);
			Long index = execution->GetPosition(i);
			dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->Erase(index);
		}
		else if (dynamic_cast<RemoveExecution*>(execution)) { //1.3. �����ߴ� ó���� '����'������ ���� ��ȣ�� �߰��Ѵ�.
		Long position = execution->GetPosition(execution->GetLength() - (i + 1)); //���ؾ��Ҷ��� �տ�����
			if (position > dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->GetLength()) {
				position = dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->GetLength();
			}
			Shape *shape = execution->GetShape(execution->GetLength() - (i + 1));
			dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->Insert(position, shape->Clone());
			/*
			//�߰��� �� ����ó��(DrawingTool LbuttonUp ����)
			if (this->drawingPaper->templateSelected != NULL) {
				delete this->drawingPaper->templateSelected;
				this->drawingPaper->templateSelected = NULL;
			}
			this->drawingPaper->mode = DrawingPaper::SELECT;
			this->drawingPaper->tool = SelectingTool::Instance();
			*/
		}
		else if (dynamic_cast<OtherExecution*>(execution)) { //1.4. �����ߴ� ó���� '����'�̾����� ���� ��ȣ�� ġȯ�Ѵ�.
			Long position = execution->GetPosition(i);
			Shape *cloneShape = execution->GetShape(i);
			Shape *shape = dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->GetAt(position);
			shape->Move(cloneShape->GetX(), cloneShape->GetY());
			shape->ReSize(cloneShape->GetWidth(), cloneShape->GetHeight());
			shape->Rewrite(cloneShape->GetContents());
			/*
			//������ �� ����ó��(MovingTool, ResizingTool LButtonUp ����)
			this->drawingPaper->mode = DrawingPaper::SELECT;
			this->drawingPaper->tool = SelectingTool::Instance();
			*/
		}
		this->undoMemory->Quadrate(this->drawingPaper->flowChart);
		i--;
	}
	//ó���� ������ �����ش�. (���⼭ execution�� �Ҹ��� ȣ��)
	this->undoMemory->Remove(this->undoMemory->GetLength() - 1);
}

void MemoryController::Redo() {
	//=========�ٽ� �����ϸ� ���������� ���� ����ߴ� �͸� �ٽ� �����Ѵ�.===================
	Execution *execution = this->redoMemory->GetAt(this->redoMemory->GetLength() - 1);
	//1. ó���ߴ� ��ȣ�� ������ŭ �ݺ��ϴ�.
	Long i = execution->GetLength() - 1;
	while (i >= 0) {
		//1.1. ���� ��ȣ�� ��ġ�� ���ϴ�.
		if (dynamic_cast<AddExecution*>(execution)) { //1.2. ���� ����ߴ� ó���� '�߰�'������ ���� ��ȣ�� �߰��Ѵ�.
			Long position = execution->GetPosition(execution->GetLength() - (i + 1)); //���ؾ��Ҷ��� �տ�����
			if (position > dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->GetLength()) {
				position = dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->GetLength();
			}
			Shape *shape = execution->GetShape(execution->GetLength() - (i + 1));
			dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->Insert(position, shape->Clone());
		}
		else if (dynamic_cast<RemoveExecution*>(execution)) { //1.3. �����ߴ� ó���� '����'������ �����Ѵ�.
			//Shape *shape = execution->GetShape(i);
			//Long index = dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->Find(shape);
			Long index = execution->GetPosition(i);
			dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->Erase(index);
		}
		else if (dynamic_cast<OtherExecution*>(execution)) { //1.4. �����ߴ� ó���� '����'�̾����� ���� ��ȣ�� ġȯ�Ѵ�.
			Long position = execution->GetPosition(i);
			Shape *cloneShape = execution->GetShape(i);
			Shape *shape = dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->GetAt(position);
			shape->Move(cloneShape->GetX(), cloneShape->GetY());
			shape->ReSize(cloneShape->GetWidth(), cloneShape->GetHeight());
			shape->Rewrite(cloneShape->GetContents());
		}
		this->redoMemory->Quadrate(this->drawingPaper->flowChart);
		i--;
	}
	//ó���� ������ �����ش�. (���⼭ execution�� �Ҹ��� ȣ��)
	this->redoMemory->Remove(this->redoMemory->GetLength() - 1);
}

Long MemoryController::RememberAdd(Long(*position), Long count) {
	//FlowChart�� Attach �� ��ȣ�� �߰��� ó�� ���Ŀ� ȣ���ϱ�
	Execution *execution = new AddExecution;
	Long i = 0;
	while (i < count) {
		Shape *shape = dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->GetAt(position[i]);
		execution->Add(shape->Clone(), position[i]);
		i++;
	}
	Long index = this->undoMemory->Add(execution);

	//undoMemory�� Redo�� �ƴ� �ٸ� ó���� ���� �߰��� ��� redoMemory�� ��������.
	if (this->redoMemory != 0) {
		this->redoMemory->RemoveAll();
	}

	return index;
}

Long MemoryController::RememberRemove(Long(*position), Long count) {
	//FlowChart�� Erase �� ��ȣ�� ���� ó�� ������ ȣ���ϱ�
	Execution *execution = new RemoveExecution;
	Long i = 0;
	while (i < count) {
		Shape *shape = dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->GetAt(position[i]);
		execution->Add(shape->Clone(), position[i]);
		i++;
	}
	Long index = this->undoMemory->Add(execution);

	//undoMemory�� Redo�� �ƴ� �ٸ� ó���� ���� �߰��� ��� redoMemory�� ��������.
	if (this->redoMemory != 0) {
		this->redoMemory->RemoveAll();
	}

	return index;
}

Long MemoryController::RememberOther(Long(*position), Long count) {
	//FlowChart�� Move, ReSize, ReWirte �� ��ȣ�� ������ ó�� ������ ȣ���ϱ�
	Execution *execution = new OtherExecution;
	Long i = 0;
	while (i < count) {
		Shape *shape = dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->GetAt(position[i]);
		execution->Add(shape->Clone(), position[i]);
		i++;
	}
	Long index = this->undoMemory->Add(execution);

	//undoMemory�� Redo�� �ƴ� �ٸ� ó���� ���� �߰��� ��� redoMemory�� ��������.
	if (this->redoMemory != 0) {
		this->redoMemory->RemoveAll();
	}

	return index;
}

Long MemoryController::RememberRedo() {
	Long index;
	Execution *execution = this->redoMemory->GetAt(this->redoMemory->GetLength() - 1);
	if (dynamic_cast<OtherExecution*>(execution)) { //redoMemory�� ������ execution�� other�̸�
		//�ش� execution�� ������ �ִ� flowChart������ ��ġ�� �ش��ϴ� ��ȣ���� ����(redo ��) ������ ���� execution�� �����. 
		Execution *otherExecution = new OtherExecution;
		Long i = 0;
		while (i < execution->GetLength()) {
			Long position = execution->GetPosition(i);
			Shape *shape = dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->GetAt(position);
			otherExecution->Add(shape->Clone(), position);
			i++;
		}
		index = this->undoMemory->Add(otherExecution);
	}
	else { //add or remove : clone ����
		index = this->undoMemory->Add(execution->Clone());
	}
	return index;
}

Long MemoryController::RememberUndo() {
	Long index;
	Execution *execution = this->undoMemory->GetAt(this->undoMemory->GetLength() - 1);
	if (dynamic_cast<OtherExecution*>(execution)) { //undoMemory�� ������ execution�� other�̸�
		//�ش� execution�� ������ �ִ� flowChart������ ��ġ�� �ش��ϴ� ��ȣ���� ����(undo ��) ������ ���� execution�� �����. 
		Execution *otherExecution = new OtherExecution;
		Long i = 0;
		while (i < execution->GetLength()) {
			Long position = execution->GetPosition(i);
			Shape *shape = dynamic_cast<FlowChart*>(this->drawingPaper->flowChart)->GetAt(position);
			otherExecution->Add(shape->Clone(), position);
			i++;
		}
		index = this->redoMemory->Add(otherExecution);
	}
	else { //add or remove : clone ����
		index = this->redoMemory->Add(execution->Clone());
	}
	return index;
}

void MemoryController::Quadrate() {
	//1. undoMemory�� ��ġ��Ų��.
	this->undoMemory->Quadrate(this->drawingPaper->flowChart);
	//2. redoMemory�� ��ġ��Ų��.
	this->redoMemory->Quadrate(this->drawingPaper->flowChart);
}