/******************************************************************
* ���� �̸� : Line.cpp
* ��� : ���� �߻�ȭ Ŭ����
* �ۼ��� : ����â
* �ۼ����� : 2015�� 3�� 30�� 
*******************************************************************/

#include "Line.h"

Line::Line(Long x, Long y, Long width, Long height, DWORD backGroundColor, PenStyle borderLine, DWORD borderColor, String contents)
:Shape(x,y,width,height,backGroundColor,borderLine,borderColor,contents){
}

Line::~Line(){
}

Line::Line(const Line& source):Shape(source){
}

Line& Line::operator =(const Line& source){
	Shape::operator=(source);
	return * this;
}
