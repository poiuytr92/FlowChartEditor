#ifndef _MEMORYCONTROLLER_H
#define _MEMORYCONTROLLER_H

typedef signed long int Long;
class DrawingPaper;
class Memory;

class MemoryController {
public:
	MemoryController(DrawingPaper *drawingPaper = 0);
	MemoryController(const MemoryController& source);
	~MemoryController();
	MemoryController& operator=(const MemoryController& source);

	void Undo();
	void Redo();

	Long RememberAdd(Long (*position), Long count); //For Undo
	Long RememberRemove(Long (*position), Long count); //For Undo
	Long RememberOther(Long (*position), Long count); //For Undo
	Long RememberRedo(); //For Undo
	Long RememberUndo(); //For Redo

	void Quadrate(); //memory���� execution���� ������ �ִ� shape�� index�� position�� sort�� ���� ���� index�� �޶����� ��ġ������� ��.

	Memory* GetUndoMemory() const;
	Memory* GetRedoMemory() const;
private:
	DrawingPaper *drawingPaper;
	Memory *undoMemory;
	Memory *redoMemory;
};

inline Memory* MemoryController::GetUndoMemory() const {
	return const_cast<Memory*>(this->undoMemory);
}

inline Memory* MemoryController::GetRedoMemory() const {
	return const_cast<Memory*>(this->redoMemory);
}

#endif //_MEMORYCONTROLLER_H