/******************************************************************
* ���� �̸� : Symbol.h
* ��� : ��ȣ�� �߻�ȭ Ŭ����
* �ۼ��� : ����â
* �ۼ����� : 2015�� 3�� 30�� 
*******************************************************************/

#ifndef _SYMBOL_H
#define _SYMBOL_H

#include "Shape.h"

class Symbol : public Shape {
	public:		
		Symbol(Long x, Long y, Long width, Long height, DWORD backGroundColor = BACKGROUNDCOLOR,
			  PenStyle borderLine = static_cast<PenStyle>(BORDERLINE), DWORD borderColor = BORDERCOLOR, String contents = static_cast<String>(""));

		virtual ~Symbol() = 0;

		Symbol(const Symbol& source);
		Symbol& operator =(const Symbol& source);

		virtual bool IsStyle(Long style);
};

inline bool Symbol::IsStyle(Long style) {
	return (style % 2) ? (true) : (false);
}


#endif// _SYMBOL_H