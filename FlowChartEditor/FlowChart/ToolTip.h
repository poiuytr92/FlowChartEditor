#ifndef _TOOLTIP_H
#define _TOOLTIP_H

#include "../Notepad/NotepadForm.h"

class SizeController;

class ToolTip : public NotepadForm {
public:
	static ToolTip* Instance();
	static ToolTip* Instance(char *text, COLORREF color);
	static void Destroy();
	void Open(Long x, Long y, Long width, Long height, char* text);

	Long GetX() const;
	Long GetY() const;
	Long GetWidth() const;
	Long GetHeight() const;

protected:
	ToolTip();
	ToolTip(char *text, COLORREF color);
	~ToolTip();
	
private:
	// ��ġ�� ũ��
	Long x;
	Long y;
	Long width;
	Long height;

	COLORREF color;
private:
	static ToolTip *instance;

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	DECLARE_MESSAGE_MAP()          //��32���� ON_COMMAND ON_NOTIFY �������� ����
};

inline Long ToolTip::GetX() const {
	return this->x;
}
inline Long ToolTip::GetY() const {
	return this->y;
}
inline Long ToolTip::GetWidth() const {
	return this->width;
}
inline Long ToolTip::GetHeight() const {
	return this->height;
}

#endif //_TOOLTIP_H