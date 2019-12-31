/******************************************************************
* ���� �̸� : Shape.h
* ��� : ����(��ȣ,��)�� �߻�ȭ Ŭ����
* �ۼ��� : ����â
* �ۼ����� : 2015�� 3�� 30�� 
*******************************************************************/

#ifndef _SHAPE_H
#define _SHAPE_H

#include "String.h" //path ����
#include <afxwin.h>

class ScrollController;

// ��ȣ ���� ��ũ�ε�

#define ID_TERMINAL				40001
#define ID_PREPARATION			40002
#define ID_PUNCHEDCARD		40003
#define ID_PROCESS				40004
#define ID_DECISION				40005
#define ID_DOCUMENT			40006
#define ID_ARROW					40007
#define ID_LEFTDOWN				40008
#define ID_RIGHTDOWN			40009
#define ID_JOIN						40010
#define ID_REPEATTRUE			40011
#define ID_REPEATFALSE			40012
#define ID_RIGHTDOWNJOIN	40013
#define ID_INPUTOUTPUT     	40014

enum SHAPE { ALL=0, SYMBOL=1, LINE=2, TERMINAL=4, PREPARATION=8, PUNCHEDCARD=16, PROCESS=32, DECISION=64,	
					DOCUMENT=128, INPUTOUTPUT=256, ARROW=512, LEFTDOWN=1024, RIGHTDOWN=2048, 
					JOIN=4096, REPEATTRUE=8196, REPEATFALSE=16384, RIGHTDOWNJOIN=32768 };

enum ATTRIBUTE{ POINT_IN , POINT_OUT, POINT_TRUE, POINT_FALSE };

enum DECISION_ { NONE = 0, SELECTION = 1,  ITERATION = 2};

// ���� ���� ��ũ�ε�
#define HIT_NONE				   0
#define HIT_BODY					   1
#define HIT_TOPLEFT			       2
#define HIT_TOPMIDDLE		       3
#define HIT_TOPRIGHT			   4
#define HIT_BOTTOMLEFT		   5
#define HIT_BOTTOMMIDDLE	   6
#define HIT_BOTTOMRIGHT	   7
#define HIT_LEFTMIDDLE		   8
#define HIT_RIGHTMIDDLE		   9
#define HIT_IN                       10
#define HIT_OUT                    11
#define HIT_HANDLE               12
#define HIT_TRUE                   13
#define HIT_FALSE                  14

enum Direction { RIGHT = 0, LEFT = 1};
enum PenStyle {SOLID, DASH, DOT, DASHDOT, DASHDOTDOT, INSIEDFRAME };

// �Ӽ� ����Ʈ ��
#define BACKGROUNDCOLOR 10
#define BORDERLINE 0
#define BORDERCOLOR 10
#define FONT_HEIGHT 12

// ��ȣ ����Ʈ ��
#define REPEATFALSE_WIDTH 30
#define REPEATFALSE_HEIGHT 40

#define REPEATTRUE_WIDTH 30
#define REPEATTRUE_HEIGHT 30

#define RIGHTDOWNJOIN_WIDTH 30
#define RIGHTDOWNJOIN_HEIGHT 30

#define ANNOTATION_WIDHT 30
#define DIRECTION RIGHT

// ȭ��ǥ
#define ARROW_SIZE 5

// ���εβ�
#define LINETHICKNESS 3

// ���� �ڽ�
#define BOXLENGTH 6 // �ڽ��� �׵θ� ����
#define MARKLENGTH 5 // ��ĥ�� ���� �ڽ� ����
#define BOXSCOPE 7 // ������ �ڽ� ���� ���� CRgn ���� �׵θ� ������ ��ã�� ����

// ���ùڽ� �ִ� ����
#define SELECTIONMARK 8

// �� �ʺ� ����
#define FORMWIDTH 100
#define FORMHEIGHT 30

#define BOXVERTECIES 4 // Attribute ���� ���

class Painter;
class FlowChartVisitor;

class Attribute{
public:
	Attribute();
	~Attribute();

	Attribute(const Attribute& source);
	Attribute& operator = (const Attribute& source);

	bool IsEqual(const Attribute& other);
	bool IsNotEqual(const Attribute& other);

	bool operator == (const Attribute& other);
	bool operator != (const Attribute& other);

	char GetVertexIn() const;
	char GetVertexOut() const;
	char GetVertexTrue() const;
	char GetVertexFalse() const;
	POINT GetPointIn() const;
	POINT GetPointOut() const;
	POINT GetPointTrue() const;
	POINT GetPointFalse() const;

public:	
	char vertexIn;
	char vertexOut;
	char vertexTrue;
	char vertexFalse;
	POINT pointIn;
	POINT pointOut;
	POINT pointTrue;
	POINT pointFalse;
};

inline char Attribute::GetVertexIn() const{
	return this->vertexIn;
}

inline char Attribute::GetVertexOut() const{
	return this->vertexOut;
}

inline char Attribute::GetVertexTrue() const{
	return this->vertexTrue;
}

inline char Attribute::GetVertexFalse() const{
	return this->vertexFalse;
}

inline POINT Attribute::GetPointIn() const{
	return this->pointIn;
}

inline POINT Attribute::GetPointOut() const{
	return this->pointOut;
}

inline POINT Attribute::GetPointTrue() const{
	return this->pointTrue;
}

inline POINT Attribute::GetPointFalse() const{
	return this->pointFalse;
}

class Shape {
public:
	Shape();
	Shape(Long x, Long y, Long width, Long height, COLORREF backGroundColor,
			PenStyle borderLine = static_cast<PenStyle>(BORDERLINE), DWORD borderColor = BORDERCOLOR,
		String contents = static_cast<String>(""));

	virtual ~Shape() = 0;

	Shape(const Shape& source);
	Shape& operator=(const Shape& source);

	virtual bool IsEqual(const Shape& other);
	virtual bool IsNotEqual(const Shape& other);

	Long IsUpperThan(const Shape& other);
	Long IsDownThan(const Shape& other);
	Long IsFrontThan(const Shape& other);
	Long IsRearThan(const Shape& other);

	virtual bool operator ==(const Shape& other);
	virtual bool operator !=(const Shape& other);

	void Move(Long x, Long y);
	virtual void ReSize(Long width, Long height);
	void Rewrite( char (*text) );

	void Paint(COLORREF backGroundColor,PenStyle borderLine, DWORD borderColor);
		
	//virtual void Draw(CDC *dc) = 0;
	//virtual void Draw(Painter *painter) = 0; 
	virtual void DrawActiveShape(CDC *dc); // ���� ���� ���ýô� �̵��� �ʿ������� ���ùڽ��� �׸��� �ʴ´�.
	virtual void DrawActiveShape(Painter *painter); // ���� ���� ���ýô� �̵��� �ʿ������� ���ùڽ��� �׸��� �ʴ´�.

	// Visitor ���� ����
	virtual void Accept(FlowChartVisitor *draw) = 0;

	//virtual void DrawSelectionMark(CDC *dc);

	virtual Shape* Clone() = 0;
	
	//virtual void GetFormattingArea(Long *left, Long *top, Long *right, Long *bottom);
	//virtual void GetFormattingArea(Long *left, Long *top, Long *width, Long *height);
				
	virtual void GetRegion(CDC *dc, CRgn *region)=0;  //���콺 �巡�׷� ���� ���� �ѹ��� ���ý� ���
	virtual void GetRegion(Painter *painter, CRgn *region)=0;
	virtual void GetRegion(CDC *dc, Long thickness, CRgn *region)=0;
	virtual void GetRegion(Painter *painter, Long thickness, CRgn *region)=0;

	virtual void GetSelectionMarkerAllRegion( CRgn *region );

	virtual void GetAttribute(Attribute *Attribute){};
		
	Long GetX() const;
	Long GetY() const;
	Long GetWidth() const;
	Long GetHeight() const;
	COLORREF GetBackGroundColor() const;
	PenStyle GetBorderLine() const;
	DWORD GetBorderColor() const;

	String& GetContents() const;

	Long GetLeft() const;
	Long GetTop() const;
	Long GetRight() const;
	Long GetBottom() const;

	// ���� ���� 
	// virtual bool IsIncluded( int x, int y );
	virtual BOOL IsIncluded(CDC *dc, POINT point){return false;};
	virtual BOOL IsIncluded(Painter *painter, POINT point){return false;};
	virtual BOOL IsIncluded(Painter *painter, const RECT& rect){return false;};

	virtual void Select( bool selected );
	virtual bool IsSelected() const;

	//virtual int GetHitCode( CPoint point ) const;
	//virtual int GetHitCode( const CPoint& point, const CRect& rect ) const;
	virtual int GetHitCode( Painter *painter, CPoint point );
	virtual int GetHitCode( Painter *painter, const CPoint& point, const CRgn& region );

	virtual HCURSOR GetCursor( int hit ) const;

	virtual void Copy(Shape *object);
	//virtual void Copy(Shape *object) {}/* = 0*/;

	virtual void GetLine(char (*line)){};

	virtual Long CenterOfGravityY() const;
	virtual Long CenterOfGravityX() const;

	//virtual SHAPE Identify() const { return ID_SHAPE; }; // �Է��� SHAPE ����� BOOL�� �ٲ���
	virtual bool Identify(SHAPE identify){ return false; };
	virtual bool IsStyle(Long style);

	int GetSymbolID(); //190903 DrawingPaper.LButtonDown���� Creator.Create ����ϱ� ����
	int GetLineID(); //191227 Interpreter pattern ���� ��
public:	
	static void MakeRectToPoint(POINT point, RECT *rect);

protected:
	virtual void DrawSelectionMarkers( CDC* dc , ScrollController *scrollController);
	virtual void DrawSelectionMarkers( Painter* painter, ScrollController *scrollController);
	virtual void GetSelectionMarkerRect( UINT marker, CRect *rect );		

protected:
	Long x;
	Long y;
	Long width;
	Long height;
	COLORREF backGroundColor;
	PenStyle borderLine;
	DWORD borderColor;
	String contents;

	bool isSelected;
};

inline Long Shape::GetX() const{
	return this->x;
}

inline Long Shape::GetY() const{
	return this->y;
}

inline Long Shape::GetWidth() const{
	return this->width;
}

inline Long Shape::GetHeight() const{
	return this->height;
}

inline COLORREF Shape::GetBackGroundColor() const{
	return this->backGroundColor;
}

inline PenStyle Shape::GetBorderLine() const{
	return this->borderLine;
}

inline DWORD Shape::GetBorderColor() const{
	return this->borderColor;
}

inline String& Shape::GetContents() const {
	return const_cast<String&>(this->contents);
}

inline Long Shape::GetLeft() const {
	return this->x;
}
inline Long Shape::GetTop() const {
	return this->y;
}

inline Long Shape::GetRight() const {
	return (this->x + this->width);
}

inline Long Shape::GetBottom() const {
	return (this->y + this->height);
}

inline bool Shape::IsSelected() const {
	return this->isSelected;
}

inline Long Shape::CenterOfGravityY() const{
	return this->y;
}

inline Long Shape::CenterOfGravityX() const{
	return this->x + this->width/2;
}

inline bool Shape::IsStyle(Long style){
	return (style==ALL)?(true):(false);
}

#endif // _SHAPE_H