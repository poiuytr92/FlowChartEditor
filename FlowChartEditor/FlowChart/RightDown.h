/******************************************************************
* ���� �̸� : RightDown.h
* ��� : ���ἱ ��ũ��Ʈ Ŭ����
* �ۼ��� : ����â
* �ۼ����� : 2015�� 3�� 31�� 
*******************************************************************/

#ifndef _RIGHTDOWN_H
#define _RIGHTDOWN_H

#include "Line.h"

class RightDown : public Line{
public:
	RightDown(Long x, Long y, Long width, Long height, DWORD backGroundColor = BACKGROUNDCOLOR,
			PenStyle borderLine = static_cast<PenStyle>(BORDERLINE), DWORD borderColor = BORDERCOLOR, String contents = static_cast<String>(""));
	~RightDown();
	
	RightDown(const RightDown& source);
	RightDown& operator =(const RightDown& source);

	virtual bool IsEqual(const Shape& other);
	virtual bool IsNotEqual(const Shape& other);

	virtual bool operator ==(const Shape& other);
	virtual bool operator !=(const Shape& other);

	//virtual void Draw(CDC *dc);
	//virtual void Draw(Painter *painter);
	virtual void DrawActiveShape(CDC *dc);
	virtual void DrawActiveShape(Painter *painter);

	virtual void Accept( FlowChartVisitor *draw);

	virtual Shape* Clone();
		
	//virtual void GetFormattingArea(Long *left, Long *top, Long *right, Long *bottom);

	virtual void GetRegion(CDC *dc, CRgn *region);
	virtual void GetRegion(Painter *painter, CRgn *region);
	virtual void GetRegion(CDC *dc, Long thickness, CRgn *region);
	virtual void GetRegion(Painter *painter, Long thickness, CRgn *region);
	virtual void GetSelectionMarkerAllRegion( CRgn *region );
					
	virtual BOOL IsIncluded(CDC *dc, POINT point);
	virtual BOOL IsIncluded(Painter *painter, POINT point);
	virtual BOOL IsIncluded(Painter *painter, const RECT& rect);

	virtual void GetSelectionMarkerRect( UINT marker, CRect *rect );

	virtual int GetHitCode( Painter *painter, const CPoint& point, const CRgn& region );

	virtual void GetLine(char (*line));
	virtual bool Identify( SHAPE identify );
	virtual bool IsStyle(Long style);

	virtual Long CenterOfGravityX() const;

	virtual void DrawSelectionMarkers( CDC* dc, ScrollController *scrollController );
	virtual void DrawSelectionMarkers( Painter* painter, ScrollController *scrollController );
	void GetAttribute(Attribute *attribute);
};

inline bool RightDown::Identify( SHAPE identify ){
	return ( identify == LINE || identify == RIGHTDOWN )?( true ):( false );
}

inline Long RightDown::CenterOfGravityX() const{
	return x;
}
#endif //_RIGHTDOWN_H