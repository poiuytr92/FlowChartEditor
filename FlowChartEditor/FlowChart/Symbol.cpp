/******************************************************************
* ���� �̸� : Symbol.cpp
* ��� : ��ȣ�� �߻�ȭ Ŭ����
* �ۼ��� : ����â
* �ۼ����� : 2015�� 3�� 30��
*******************************************************************/

#include "Symbol.h"

Symbol::Symbol(Long x, Long y, Long width, Long height, DWORD backGroundColor, PenStyle borderLine, DWORD borderColor, String contents)
	:Shape(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {
}

Symbol::~Symbol() {
}

Symbol::Symbol(const Symbol& source)
	:Shape(source) {
}

Symbol& Symbol::operator =(const Symbol& source)
{
	Shape::operator=(source);
	return *this;
}