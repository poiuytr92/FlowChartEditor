/******************************************************************
* ���� �̸� :  Label.h
* ��     �� : Text Class boundary
* ��  �� �� : ����â
* �ۼ� ���� : 2015�� 4�� 20�� 
*******************************************************************/
#ifndef _LABEL_H
#define _LABEL_H

#include "../Notepad/NotepadForm.h"

typedef signed long int Long;
typedef unsigned long int ULong;

class Text;
class String;
class Caret;
class Shape;
class SizeController;

class Label : public NotepadForm {
public:
	static Label* Instance();
	static Label* Instance(String *text, COLORREF color);
	static void Destroy();
	void Open(Long x, Long y, Long width, Long height, String* text);

	Long GetX() const;
	Long GetY() const;
	Long GetWidth() const;
	Long GetHeight() const;

protected:
	Label();
	Label(String *text, COLORREF color);
	~Label();
#if 0
	Label(const Label& source);
	Label& operator = (const Label& source);

	// ĳ���� �����Ѵ�
	void SetCaret();

	// ���� ��ġ�� ���� x, y ��ǥ�� ���Ѵ�
	void GetXYFromIndex(Long index, Long *x, Long *y);
	// x, y ��ǥ�� ���� ��ġ�� ���Ѵ�
	Long GetIndexFromXY(Long x, Long y);

	// �̵� ����
	void Move(UINT key);

	void Erase(UINT key);

	// ���� �ٲٱ� ���� �۾� ������ ��������� �˻��ϴ�
	Long FindEndOfLine();
#endif
public:
	SizeController *sizeController;
private:
	// ��ġ�� ũ��
	Long x;
	Long y;
	Long width;
	Long height;

	COLORREF color;

	// �ٰ���

	// �ѱ� �Է� ����
	//BOOL isHangulInputing;

private:
	static Label *instance;
protected:
	afx_msg void OnKillFocus( CWnd* pNewWnd );
	afx_msg void OnSetFocus( CWnd* pOldWnd );
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint(); 
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnImeStartComposition(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnImeChar(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnImeComposition(WPARAM wParam, LPARAM lParam);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);

#if 0
	afx_msg void OnDestroy();


	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown( UINT nFlags, CPoint point);

	


#endif
	DECLARE_MESSAGE_MAP()          //��32���� ON_COMMAND ON_NOTIFY �������� ����
};

inline Long Label::GetX() const {
	return this->x;
}
inline Long Label::GetY() const {
	return this->y;
}
inline Long Label::GetWidth() const {
	return this->width;
}
inline Long Label::GetHeight() const {
	return this->height;
}

#endif //_LABEL_H