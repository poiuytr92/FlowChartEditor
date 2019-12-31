/******************************************************************
* ���� �̸� : Decision.h
* ��� : �Ǵܱ�ȣ�� ��ũ��Ʈ Ŭ����
* �ۼ��� : ����â
* �ۼ����� : 2015�� 3�� 30�� 
*******************************************************************/

#ifndef _DECISION_H
#define _DECISION_H

#include "Symbol.h"

class Decision : public Symbol{
public:
	Decision(Long x, Long y, Long width, Long height, DWORD backGroundColor = BACKGROUNDCOLOR,
			PenStyle borderLine = static_cast<PenStyle>(BORDERLINE), DWORD borderColor = BORDERCOLOR, String contents = static_cast<String>(""));
	~Decision();
	Decision(const Decision& source);
	Decision& operator =(const Decision& source);

	virtual bool IsEqual(const Shape& other);
	virtual bool IsNotEqual(const Shape& other);

	virtual bool operator ==(const Shape& other);
	virtual bool operator !=(const Shape& other);

	//virtual void Draw(CDC *dc);
	//virtual void Draw(Painter *painter);

	virtual void Accept( FlowChartVisitor *draw);

	virtual Shape* Clone();

	//virtual void GetFormattingArea(Long *left, Long *top, Long *right, Long *bottom);
	//virtual void GetFormattingArea(Long *left, Long *top, Long *right, Long *bottom);
	//virtual void GetFormattingArea(Long *left, Long *right);

	virtual void GetRegion(CDC *dc, CRgn *region);
	virtual void GetRegion(Painter *painter, CRgn *region);
	virtual void GetRegion(CDC *dc, Long thickness, CRgn *region);
	virtual void GetRegion(Painter *painter, Long thickness, CRgn *region);
		
	virtual BOOL IsIncluded(CDC *dc, POINT point);
	virtual BOOL IsIncluded(Painter *painter, POINT point);
	virtual BOOL IsIncluded(Painter *painter, const RECT& rect);

	void GetAttribute(Attribute *attribute);

	virtual void GetLine(char (*line));
	
	virtual bool Identify(SHAPE identify);
	virtual bool IsStyle(Long style);

	virtual void DrawSelectionMarkers( CDC* dc, ScrollController *scrollController);
	virtual void DrawSelectionMarkers( Painter* painter, ScrollController *scrollController);
};

inline bool Decision::Identify(SHAPE identify){
	return ( identify == DECISION || identify == SYMBOL )?( true ):( false );
}

class DecisionForSelection : public Decision{
public:
	DecisionForSelection(Long x, Long y, Long width, Long height, DWORD backGroundColor = BACKGROUNDCOLOR, PenStyle borderLine = static_cast<PenStyle>(BORDERLINE), DWORD borderColor = BORDERCOLOR, String contents = static_cast<String>(""));
	
	DecisionForSelection(const Decision& other);

	~DecisionForSelection();
};

class DecisionForIteration : public Decision{
public:
	DecisionForIteration(Long x, Long y, Long width, Long height, DWORD backGroundColor = BACKGROUNDCOLOR, 
		PenStyle borderLine = static_cast<PenStyle>(BORDERLINE), DWORD borderColor = BORDERCOLOR, String contents = static_cast<String>(""));

	DecisionForIteration(const Decision& other);

	~DecisionForIteration();
};


#endif// _DECISION_H