// DrawVisitor.h
#include "FlowChartVisitor.h"
#include "Painter.h"

#ifndef _DRAWVISITOR_H
#define _DRAWVISITOR_H

class ScrollController;

class DrawVisitor : public FlowChartVisitor {
public:
	DrawVisitor(Painter *painter = 0, ScrollController *scrollController = 0);
	virtual ~DrawVisitor();
protected:
	virtual void Visit(Terminal *element);
	virtual void Visit(Preparation *element);
	virtual void Visit(PunchedCard *element);
	virtual void Visit(InputOutput *element);
	virtual void Visit(Process *element);
	virtual void Visit(Decision *element);
	virtual void Visit(Document *element);
	virtual void Visit(Arrow *element);
	virtual void Visit(LeftDown *element);
	virtual void Visit(RightDown *element);
	virtual void Visit(Join *element);
	virtual void Visit(RightDownJoin *element);
	virtual void Visit(RepeatTrue *element);
	virtual void Visit(RepeatFalse *element);
	virtual void Visit(FlowChart *element);
	virtual void Visit(Template *element);

	virtual void Visit(NumberBox *numberBox);
	virtual void Visit(A4Paper *a4Paper);
	virtual void Visit(TutorialMark *tutorialMark);
private:
	Painter *painter;
	ScrollController *scrollController;
};

#endif _DRAWVISITOR_H