#ifndef _PAINTER_H
#define _PAINTER_H

#include <afxwin.h>
typedef signed long int Long;
///////////////////////////////////////////////////////////////////////////////////////////////
// ���� �Ӽ�
class LineProperty {
	friend class Painter;

public:
	LineProperty(LONG style = PS_SOLID, LONG width = 1, 
		LONG capStyle = PS_ENDCAP_SQUARE, LONG joinType = PS_JOIN_MITER, COLORREF color = RGB(0, 0, 0));
	~LineProperty();

	void Change(LONG style, LONG width, LONG capStyle, LONG joinType, COLORREF color );

	LONG GetStyle() const;
	LONG GetWidth() const;
	COLORREF GetColor() const;
	LONG GetCapStyle() const;
	LONG GetJoinType() const;

private:
	LONG style; // ����
	LONG width; // ����
	LONG capStyle; // �����ڸ� ����
	LONG joinType; // �̿�� ����
	COLORREF color; // ����
};

inline LONG LineProperty::GetStyle() const {
	return this->style;
}

inline LONG LineProperty::GetWidth() const {
	return this->width;
}

inline LONG LineProperty::GetCapStyle() const {
	return this->capStyle;
}

inline LONG LineProperty::GetJoinType() const {
	return this->joinType;
}

inline COLORREF LineProperty::GetColor() const {
	return this->color;
}

///////////////////////////////////////////////////////////////////////////
// ���� �Ӽ�
class PlaneProperty {
	friend class Painter;

public:
	PlaneProperty(LONG style = BS_HOLLOW, COLORREF color = RGB(255, 255, 255));
	~PlaneProperty();

	void Change(LONG style, COLORREF color);

	LONG GetStyle() const;
	COLORREF GetColor() const;
	
	// �� ����
	// --------------------------------------
	// ���� ��Ÿ�� : ä��� ��Ÿ��
	// ���� 
	// �� ��Ÿ��

	// Gradient ����
	//--------------------------------------
private:
	LONG style;  // ä��� ���� NONE | SOLID | GRADIENT | BITMAP
	COLORREF color;  // ����	
	// LONG brushStyle; // BS_DIBPATTERN | BS_HATCHED | BS_HOLLOW | BS_NULL | BS_PATTERN | BS_SOLID
	// LONG hatchStyle; // HS_BDIAGONAL | HS_CROSS | HS_DIAGCROSS | HS_FDIAGONAL | HS_HORIZONTAL | HS_VERTICAL
};

inline LONG PlaneProperty::GetStyle() const {
	return this->style;
}

inline COLORREF PlaneProperty::GetColor() const {
	return this->color;
}

///////////////////////////////////////////////////////////////////////////
class Painter {
public:
	Painter(CWnd *owner, LONG width, LONG height, COLORREF color = RGB(255, 255, 255), int bkMode=OPAQUE );
	Painter(CDC *dc, LONG width, LONG height, COLORREF color = RGB(255, 255, 255), int bkMode=OPAQUE );
	~Painter();

	// BK MODE
	LONG GetBkMode() const;
	LONG SetBkMode(LONG bkMode);

	LONG GetROP2( );
	LONG SetROP2(LONG nDrawMode );

	// ũ�⸦ �����ϴ�
	void Resize(CWnd *owner, COLORREF color = RGB(255, 255, 255));
	void Resize(CWnd *owner, LONG x, LONG y, LONG width, LONG height, COLORREF color = RGB(255, 255, 255));

	// ����� �����
	void EraseBackground(float x1, float y1, float w1, float h1);
	
	void BeginPath();
	void CreateFromPath(CRgn *region);
	void EndPath();

	void FillRegion(CRgn &region,COLORREF nIndex);
	void FillPolygon(POINT (*points), Long count,COLORREF color);
	
	void FrameRegion(CRgn &region,LONG width, LONG heigth, COLORREF nIndex);
	// ����� ĥ�ϴ�.	
	void FillBackground(POINT (*points), LONG count, COLORREF nIndex);	

	// ȭ�鿡 ����ϴ�
	void Render(CDC *dc, LONG x, LONG y, LONG width, LONG height);
	void StretchRender(CDC *dc, LONG x, LONG y, LONG width, LONG height, LONG xSrc, LONG ySrc, LONG widthSrc, LONG heightSrc);

	// ���� ���� �Ӽ��� �ٲٴ�
	void ChangeLineProperty(LONG style, LONG width, LONG capStyle, LONG joinType, COLORREF color );
	void ChangePlaneProperty(LONG style, COLORREF color );

	// 
	void DrawGradientFill(COLORREF color1, COLORREF color2, LONG x, LONG y, LONG width, LONG height, BOOL vertical = TRUE);

	// ��
	void DrawLine(float x1, float y1, float x2, float y2);
	
	// �
	void DrawBezier( POINT (*points), LONG count );
	void DrawBezierTo( POINT (*points), LONG count );

	// �ٰ���
	void DrawRectangle( float x1, float y1, float w1, float h1 ); // �׸���
	void FillRectangle( float x1, float y1, float w1, float h1 ); // ĥ�ϴ�
	void FrameRectangle( float x1, float y1, float w1, float h1 ); // �׵θ��� �׸���
	void InvertRectangle( float x1, float y1, float w1, float h1 ); // ������Ű��

	void DrawRoundRectangle( float x1, float y1, float w1, float h1, float a1, float a2 );
	void FillRoundRectangle( float x1, float y1, float w1, float h1, float a1, float a2 );

	void DrawPolyline( POINT (*points), LONG count );
	void DrawPolygon( POINT (*points), LONG count );
	
	// ��, ȣ, ��ä��
	void DrawArc( float x1, float y1, float w1, float h1, float xStart, float yStart, float xEnd, float yEnd );
	void DrawPie( float x1, float y1, float w1, float h1, float xStart, float yStart, float xEnd, float yEnd );
	void FillPie( float x1, float y1, float w1, float h1, float xStart, float yStart, float xEnd, float yEnd );
	void DrawChord(  float x1, float y1, float w1, float h1, float xStart, float yStart, float xEnd, float yEnd );
	void FillChord( float x1, float y1, float w1, float h1, float xStart, float yStart, float xEnd, float yEnd );
	void DrawEllipse( float x1, float y1, float w1, float h1 );
	void FillEllipse( float x1, float y1, float w1, float h1 );
	
	//��Ƽ���ϸ���� �õ�
	//void DrawArc(float x, float y, float width, float height, float startAngle, float sweepAngle);
	//void DrawPolyLine(POINT(*points), LONG count);
	
	// Rect�� �̿��Ͽ� ���� ���� �׸���
	void PaintOverRectangle(float x1, float y1, float w1, float h1 );
	
	// ��Ʈ�� ó��
	HBITMAP GetCurrentBitmap();
	
	// �ؽ�Ʈ ���
	void TextOut(LONG fontHeight, LONG x,LONG y, LPCTSTR lpString, int nCount );
	int DrawText(LONG fontHeight, LPCTSTR lpString, int nCount, LPRECT lpRect, UINT uFormat );
	void ChangeFont(HFONT font, COLORREF color);

	void Resize(CWnd *owner, CSize size, CPoint point);

	// ��ó��
	// Path ó��

	// LineProperty
	LONG GetLineStyle() const;
	LONG GetLineWidth() const;
	COLORREF GetLineColor() const;
	LONG GetLineCapStyle() const;
	LONG GetLineJoinType() const;

	// PlaneProperty
	LONG GetPlaneStyle() const;
	COLORREF GetPlanColor() const;

	LOGFONT& GetFont() const;

private:
	//Double Buffering ���� �޸� DC�� ��Ʈ��
	/////////////////////////////////////////////////////
	HDC m_hdc; // �޸� DC
	////////////////////////////////////////////////////
	HBITMAP m_hbmp;
	HBITMAP m_holdbmp;

	LONG bkMode;  // OPAQUE|TRANSPARENT

	// �� ����
	LineProperty lineProperty;
	// ��� ����
	PlaneProperty planeProperty;

	
	// �ؽ�Ʈ ����
	//--------------------------------------------
	// ��Ʈ
	LOGFONT font;
	// ����
	// ������
};

inline LONG Painter::GetLineStyle() const {
	return lineProperty.GetStyle();
}

inline LONG Painter::GetLineWidth() const{
	return lineProperty.GetWidth();
}

inline COLORREF Painter::GetLineColor() const{
	return lineProperty.GetColor();
}

inline LONG Painter::GetLineCapStyle() const{
	return lineProperty.GetCapStyle();
}

inline LONG Painter::GetLineJoinType() const{
	return lineProperty.GetJoinType();
}

inline LONG Painter::GetPlaneStyle() const{
	return planeProperty.GetStyle();
}

inline COLORREF Painter::GetPlanColor() const{
	return planeProperty.GetColor();
}

inline LONG Painter::GetBkMode() const{
	return this->bkMode;
}

inline LOGFONT& Painter::GetFont() const {
	return const_cast<LOGFONT&>(this->font);
}

#endif // _PAINTER_H
