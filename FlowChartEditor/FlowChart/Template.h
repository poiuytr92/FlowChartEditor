/******************************************************************
* ���� �̸� : Template.h
* ��� : ������ �ۼ��� ��Ʈ�� Ŭ����
* �ۼ��� : ����â
* �ۼ����� : 2015�� 4�� 13�� 
*******************************************************************/

#ifndef _TEMPLATE_H
#define _TEMPLATE_H

#include "Shape.h"
#include "Array.h"

typedef signed long int Long;

class Template : public Shape{
public:
	Template(Long capacity = 30);
	~Template();

	Template(const Template& source);
	Template& operator =(const Template& source);

	Long Register(Shape* shape);
	Long UnRegister(Long index);
	void Clear();


	Shape* GetAt(Long index);
	Long GetCapacity() const;
	Long GetLength() const;

	//virtual void Draw(CDC *dc);
	//virtual void Draw(Painter *painter);

	virtual Long Find(CDC *dc, CPoint point);

	virtual void Accept(FlowChartVisitor *draw);

	virtual Shape* Clone();		

	virtual void GetRegion(CDC *dc, CRgn *region){};  //���콺 �巡�׷� ���� ���� �ѹ��� ���ý� ���
	virtual void GetRegion(Painter *painter, CRgn *region){};
	virtual void GetRegion(CDC *dc, Long thickness, CRgn *region){};
	virtual void GetRegion(Painter *painter, Long thickness, CRgn *region){};

private:
	Long capacity;
	Long length;
	Array<Shape *> templates;
};
Long CompareCoordinateForTemplate(void *one, void *other);

inline Long Template::GetCapacity() const{
	return this->capacity;
}

inline Long Template::GetLength() const{
	return this->length;
}

#endif //_TEMPLATE_H
