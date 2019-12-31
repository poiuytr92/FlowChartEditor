/******************************************************************
 * ���� �̸� :  Label.cpp
 * ��     �� : Text Class boundary
 * ��  �� �� : ����â
 * �ۼ� ���� : 2015�� 4�� 20��
*******************************************************************/
#include "Label.h"
#include "String.h"
#include "Shape.h"

#include "FlowChart.h"
#include "FlowChartEditor.h"
#include "DrawingPaper.h"
#include <Imm.h>

#include "../Notepad/GlyphFactory.h"
#include "../Notepad/Glyph.h"
#include "../Notepad/Row.h"
#include "../Notepad/CharacterMetrics.h"
#include "Process.h"
#include "Creator.h"
#include "SizeController.h"
#include "VariableList.h"
#include "Preparation.h"
#include "../Notepad/GlyphFactory.h"
#include "../Notepad/Font.h"
#include "TutorialForm.h"

#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "imm32")
// �޼��� ��
BEGIN_MESSAGE_MAP(Label, CWnd)
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_CREATE()
	ON_WM_CHAR()
	ON_MESSAGE(WM_IME_CHAR, OnImeChar)
	ON_MESSAGE(WM_IME_COMPOSITION, OnImeComposition)
	ON_MESSAGE(WM_IME_STARTCOMPOSITION, OnImeStartComposition)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

Label* Label::instance = 0;

Label* Label::Instance(String *text, COLORREF color)
{
	if (instance == 0)
	{
		instance = new Label(text, color);
	}
	return instance;
}

Label* Label::Instance()
{
	if (instance == 0)
	{
		instance = new Label;
	}
	return instance;
}


Label::Label() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
	this->sizeController = NULL;
}

Label::Label(String *text, COLORREF color)
	: NotepadForm(text) {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
	this->color = color;
	this->sizeController = NULL;
}

Label::~Label() {
	if (this->sizeController != NULL) {
		delete this->sizeController;
	}
}

void Label::Destroy() {
	if (instance != 0)
	{
		delete instance;
	}
	instance = 0;
}

void Label::Open(Long x, Long y, Long width, Long height, String* text) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void Label::OnKillFocus(CWnd* pNewWnd) {
	NotepadForm::OnKillFocus(pNewWnd);

	this->DestroyWindow();
}

void Label::OnSetFocus(CWnd* pOldWnd) {
	NotepadForm::OnSetFocus(pOldWnd);
}

int Label::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	NotepadForm::OnCreate(lpCreateStruct);
	this->sizeController = new SizeController(this);

	if (this->font != NULL) {
		delete this->font;
	}
	LOGFONT logFont;
	CDC *dc = this->GetDC();
	CFont *dcFont = dc->GetCurrentFont();
	dcFont->GetLogFont(&logFont);

	this->font = new Font(logFont, RGB(0, 0, 0), this);

	return 0;
}

void Label::OnPaint() {
	NotepadForm::OnPaint();
}


void Label::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	SHORT isCtrl = GetKeyState(VK_CONTROL) & 0X8000;

	if (!isCtrl) { //ctrl + a ���� �� �� �޽��� ȣ���. + spacebar

		NotepadForm::OnChar(nChar, nRepCnt, nFlags);

		//Ư�����ڸ� ��ĭ ���µ� ���ܵ� : ' " > <  . ! 
		if (((nChar >= 33 && nChar <= 47) || (nChar >= 58 && nChar <= 64)
			|| (nChar >= 91 && nChar <= 96) || (nChar >= 123 && nChar <= 126))
			&& (nChar != 34 && nChar != 39 && nChar != 60 && nChar != 62 && nChar != 33 /*&& nChar != 46*/)) { //���Ⱑ ������ Ư����ȣ��
			GlyphFactory glyphFactory;
			Glyph *glyph = glyphFactory.Make(" ");
			Long index = this->current->GetCurrent();

			if (index >= this->current->GetLength()) {
				this->current->Add(glyph);
			}
			else {
				this->current->Add(index, glyph);
			}
	}

		DrawingPaper *drawingPaper = (DrawingPaper*)this->GetParent();
		Shape *shape = dynamic_cast<FlowChart*>(drawingPaper->flowChart)->GetAt(drawingPaper->indexOfSelected);
		//�غ��ȣ�� �ƴ� �� ó���Ѵ�.
		if (!(dynamic_cast<Preparation*>(shape))) {
			bool isMustCheck = false;
			//������ �ԷµǸ� ������ ó���Ѵ�.
			if ((nChar >= 65 && nChar <= 90) || (nChar >= 97 && nChar <= 122)) {
				isMustCheck = true;
			}
			//���ڰ� �ԷµǸ� ���� �� ���� �̻��� �ԷµǾ� �־���� �ϰ� �� ���� ���ڰ� �����̸� ó���Ѵ�.
			else if ((nChar >= 48 && nChar <= 57) && this->current->GetCurrent() > 1) {
				char previous = *(this->current->GetAt(this->current->GetCurrent() - 2)->GetContent().c_str());
				if ((previous >= 65 && previous <= 90) || (previous >= 97 && previous <= 122)) {
					isMustCheck = true;
				}
			}
			if (isMustCheck == true) {
				//���� ��ġ�� �ش��ϴ� �ܾ �����ϱ�
				String variable;

				Glyph *line = this->current->Clone();
				Long startIndex = line->MovePreviousWord();
				Long endIndex = line->MoveNextWord();
				Long i = startIndex;
				char character = *(line->GetAt(i++)->GetContent().c_str());
				variable += character;
				while (i < endIndex && ((character >= 65 && character <= 90) || (character >= 97 && character <= 122) ||
					(variable.GetLength() > 0 && (character >= 48 && character <= 57)))) {
					character = *(line->GetAt(i)->GetContent().c_str());
					variable += character;
					i++;
				}
				Long ret = drawingPaper->variableList->Find(variable);
				character = *(line->GetAt(startIndex)->GetContent().c_str());
				if (ret == -1 && (character != 34 && character != 39)) { //����ǥ �ڿ� �� ���ڸ� ����
					this->current->Remove(this->current->GetCurrent() - 1);
					bool result = PlaySound("sound_button_wrong0.2.wav", NULL, SND_FILENAME);
				}
			}
		}
}
}

void Label::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {


	NotepadForm::OnKeyDown(nChar, nRepCnt, nFlags);


}

void Label::OnLButtonDown(UINT nFlags, CPoint point) {
	if (this->sizeController != NULL) {
		delete this->sizeController;
		this->sizeController = NULL;
	}

	NotepadForm::OnLButtonDown(nFlags, point);

	if (this->sizeController == NULL) {
		this->sizeController = new SizeController(this);
	}
}

void Label::OnMouseMove(UINT nFlags, CPoint point) {
	NotepadForm::OnMouseMove(nFlags, point);
}

LRESULT Label::OnImeChar(WPARAM wParam, LPARAM lParam) {
	NotepadForm::OnImeChar(wParam, lParam);

	return 0;
}

LRESULT Label::OnImeComposition(WPARAM wParam, LPARAM lParam) {
	NotepadForm::OnImeComposition(wParam, lParam);

	return ::DefWindowProc(this->m_hWnd, WM_IME_COMPOSITION, wParam, lParam);
}
LRESULT Label::OnImeStartComposition(WPARAM wParam, LPARAM lParam) {
	return 0;
}

BOOL Label::OnEraseBkgnd(CDC* pDC) {
	RECT rect;
	this->GetClientRect(&rect);
	pDC->FillSolidRect(&rect, this->color);
	return CWnd::OnEraseBkgnd(pDC);
}

void Label::OnSize(UINT nType, int cx, int cy) {
	NotepadForm::OnSize(nType, cx, cy);
}