/******************************************************************
* ���� �̸� : Line.h
* ��� : ���� �߻�ȭ Ŭ����
* �ۼ��� : ����â
* �ۼ����� : 2015�� 3�� 30�� 
*******************************************************************/

#ifndef _LINE_H
#define _LINE_H

#include "Shape.h"

class Line : public Shape {
	public:		
		Line(Long x, Long y, Long width, Long height, DWORD backGroundColor = BACKGROUNDCOLOR,
			  PenStyle borderLine = static_cast<PenStyle>(BORDERLINE), DWORD borderColor = BORDERCOLOR, String contents = static_cast<String>(""));

		virtual ~Line() = 0;

		Line(const Line& source);
		Line& operator =(const Line& source);

		virtual bool IsStyle(Long style);
};

inline bool Line::IsStyle(Long style){
	return ((style>>1)%2)?(true):(false);
}
#endif// _LINE_H