/******************************************************************
* ���� �̸� : FlowCahrtTemplate.h
* ��� : ������ �ۼ��� ��Ʈ��
* �ۼ��� : ����â
* �ۼ����� : 2015�� 4�� 10��
*******************************************************************/

#ifndef _FLOWCHARTTEMPLATE_H
#define _FLOWCHARTTEMPLATE_H

class Shape;
class Painter;
class FlowChartFont;
//class FlowChart;

#include <afxwin.h>
typedef signed long int Long;

class FlowChartTemplate : public CWnd {
public:
	enum { DRAWON, DRAWOFF };
public:
	FlowChartTemplate();
	~FlowChartTemplate();
public:
	Shape* shapeSelected;
	Painter *painter;
	LONG mode;
	Shape* flowChartTemplate;
	FlowChartFont *font;
	Shape *oldShapeSelected;
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point); // ���콺 ���� ��ư �ٿ�
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()          //��32���� ON_COMMAND ON_NOTIFY �������� ����
};

#endif // _FLOWCHARTTEMPLATE_H
