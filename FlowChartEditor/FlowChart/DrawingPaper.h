/******************************************************************
* ���� �̸� : DrawingPaper.h
* ��� : CFrameWnd ���
* �ۼ��� : ����â
* �ۼ����� : 2015�� 4�� 06�� 
*******************************************************************/

#ifndef _DRAWINGPAPER_H
#define _DRAWINGPAPER_H

#include <afxwin.h>
#include "Array.h"
#include "Shape.h"

// �˾�â
#define IDM_AE_SEQUENCE 10001
#define IDM_AE_SELECION 10002
#define IDM_AE_ITERATION 10003
#define IDM_AE_MOVEMAKE 10004
#define IDM_AE_SIZEMAKE 10005
#define IDM_AE_INTERVALMAKE 1006

typedef unsigned long int DWORD;
typedef signed long int Long;

class Tool;
class Painter;
//class FlowChart;
//class Shape;
class Label;
class Clipboard;

class ScrollController;

class MemoryController;

class VariableList;

class Zoom;
//class VertexAttribute;
class DrawingPaper : public CWnd {

public:
	enum { IDLE, SELECT, DRAWING, MOVING, SIZING};

public:
	DrawingPaper();
	~DrawingPaper();

	void DrawTemporaryObject(Shape *entity);

	void DrawTemporaryObjects(Long (*indexes), Long count);	
	void DrawObjects(Long (*indexes), Long count);	
	void GetObjectsRgn(Long (*indexes), Long count, CRgn *region);

	void DrawSelectingArea();
	void DrawActiveShape(Shape *entity); // ������ ����� �� �ٸ���.
	void DrawActiveShape2(Shape *entity); // ������ ����� �� �ٸ���.

	void DrawSelectionMark(POINT (*points), Long count);
	void DrawSelectionMark2(POINT (*points), Long count);
	void FillSelectionMark(POINT point);

	void New();
	void Move(Long xDistance, Long yDistance);
	Long Save(const char (*fileName));
	Long Load(const char (*fileName));
	HCURSOR GetCursor();	

public:
	Shape* templateSelected;
	Painter *painter;
	
	//19.09.16 private���� public : ��ũ�� ó�� ����
	Shape *flowChart; // ����ڵ��� ���ٽ��� ����ϱ� ���ؼ� ������ �����
	ScrollController *scrollController;

	/////////////////////////////////////////////////////
	// ���콺 ����
	Long startX;
	Long startY;

	// ��� ������ ��
	Long currentX;
	Long currentY;
	/////////////////////////////////////////////////////
	Long indexOfSelected;

	LONG mode; //2019.09.20 MemoryController���� Undo ������ ���� �ű�. ���� �Ӽ��� ������ Ȥ�� private������ �Ƿ���?

	Label *label;
	Tool *tool;	

	MemoryController *memoryController;

	VariableList *variableList;
	Clipboard *clipboard;
	Zoom *zoom;
	Shape *a4Paper;

	HMENU hPopup;
private:
	friend class Label;
	friend class FlowChartTemplate;

	friend class ResizingTool;
	friend class MovingTool;
	friend class DrawingTool;
	friend class SelectingTool;
	friend class ToolFactory;	

	friend class SequenceMake;
	friend class IterationMake;
	friend class SelectionMake;

	friend class SizeMake;
	friend class IntervalMake;
	friend class MoveMake;

	friend class ErasingTool;

	friend class File;
	//friend class Configuration;

	friend class KeyFactory;
	friend class DeleteKey;
	friend class UpKey;
	friend class DownKey;
	friend class LeftKey;
	friend class RightKey;
	friend class EscapeKey;

	friend class Clipboard;

private:
	//FlowChart *flowChart;	
	// Label *label;

	LONG hitCode;


protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint(); 
	afx_msg void OnLButtonDown( UINT nFlags, CPoint point); // ���콺 ���� ��ư �ٿ�
	afx_msg void OnMouseMove( UINT nFlags, CPoint point );
	afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
	afx_msg void OnLButtonDblClk( UINT nFlags, CPoint point );
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void OnKillFocus( CWnd* pNewWnd );
	afx_msg void OnSetFocus( CWnd* pOldWnd );
	afx_msg void OnSize( UINT nType, int cx, int cy );	
	afx_msg BOOL OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message );	

	afx_msg void OnContextMenu( CWnd* pWnd, CPoint pos );
	afx_msg void OnSequnceMenuClick();
	afx_msg void OnIterationMenuClick();
	afx_msg void OnSelectionMenuClick();

	afx_msg void OnSizeMakeMenuClick();
	afx_msg void OnIntervalMakeMenuClick();
	afx_msg void OnMoveMakeMenuClick();

	//19.9.16 ��ũ��
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	DECLARE_MESSAGE_MAP() //��32���� ON_COMMAND ON_NOTIFY �������� ����
};
#endif  // _DRWAINGPAPER_H