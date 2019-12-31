#include "RectangleRegion.h"
#include "Painter.h"
#include "FlowChartVisitor.h"

RectangleRegion::RectangleRegion(Long x, Long y, Long width, Long height, DWORD backGroundColor, PenStyle borderLine, DWORD borderColor, String contents, Direction direction)
	:Shape(x, y, width, height, backGroundColor, borderLine, borderColor, contents) {

}

RectangleRegion::~RectangleRegion() {
}

RectangleRegion::RectangleRegion(const RectangleRegion& source)
	:Shape(source) {

}

RectangleRegion& RectangleRegion::operator =(const RectangleRegion& source) {
	Shape::operator=(source);

	return *this;
}

void RectangleRegion::Draw(CDC *dc) {
	dc->FillSolidRect(this->x, this->y, this->width, this->height, this->backGroundColor);
}

void RectangleRegion::Draw(Painter *painter) {
	Long x2 = this->x + this->width;
	Long y2 = this->y + this->height;
	POINT points[5] = { {this->x,this->y},{x2,this->y},{x2,y2},{this->x,y2},{this->x,this->y} };
	painter->FillBackground(points, 5, this->backGroundColor);
}

Shape* RectangleRegion::Clone() {
	return new RectangleRegion(*this);
}

BOOL RectangleRegion::IsIncluded(CDC *dc, POINT point) {
	CRgn region;
	BOOL ret;
	region.CreateRectRgn(x, y, x + width, y + height);
	ret = region.PtInRegion(point);
	region.DeleteObject();
	return ret;
}