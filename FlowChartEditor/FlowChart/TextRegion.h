#ifndef _TEXTREGION_H
#define _TEXTREGION_H

#include "Shape.h"

class TextRegion : public Shape {
public:
	TextRegion(Long x, Long y, Long width, Long height, DWORD backGroundColor = BACKGROUNDCOLOR,
		PenStyle borderLine = static_cast<PenStyle>(BORDERLINE), DWORD borderColor = BORDERCOLOR, String contents = static_cast<String>(""), Direction direction = DIRECTION);

	virtual ~TextRegion();

	TextRegion(const TextRegion& source);
	TextRegion& operator =(const TextRegion& source);

	void Draw(CDC *dc);
	void Draw(Painter *painter);

	virtual void Accept(FlowChartVisitor *draw) {};
	virtual Shape* Clone();

	virtual void GetRegion(CDC *dc, CRgn *region) {};  //���콺 �巡�׷� ���� ���� �ѹ��� ���ý� ���
	virtual void GetRegion(Painter *painter, CRgn *region) {};
	virtual void GetRegion(CDC *dc, Long thickness, CRgn *region) {};
	virtual void GetRegion(Painter *painter, Long thickness, CRgn *region) {};

	virtual BOOL IsIncluded(CDC *dc, POINT point);
};

#endif //_TEXTREGION_H