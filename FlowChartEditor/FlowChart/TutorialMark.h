#ifndef _TUTORIALMARK_H
#define _TUTORIALMARK_H

#include "Shape.h"

class TutorialMark : public Shape {
public:
	TutorialMark(Long x, Long y, Long width, Long height, DWORD backGroundColor = BACKGROUNDCOLOR,
		PenStyle borderLine = static_cast<PenStyle>(BORDERLINE), DWORD borderColor = BORDERCOLOR, String contents = static_cast<String>(""), Direction direction = DIRECTION);

	virtual ~TutorialMark();

	TutorialMark(const TutorialMark& source);
	TutorialMark& operator =(const TutorialMark& source);

	virtual void Accept(FlowChartVisitor *draw);

	virtual Shape* Clone();

	virtual void GetRegion(CDC *dc, CRgn *region) {};  //���콺 �巡�׷� ���� ���� �ѹ��� ���ý� ���
	virtual void GetRegion(Painter *painter, CRgn *region) {};
	virtual void GetRegion(CDC *dc, Long thickness, CRgn *region) {};
	virtual void GetRegion(Painter *painter, Long thickness, CRgn *region) {};
};

#endif //_TUTORIALMARK_H