#include "Zoom.h"
#include "FlowChart.h"
#include "DrawingPaper.h"
#include "RightDownJoin.h"
#include "RepeatFalse.h"
#include "RepeatTrue.h"
#include "Join.h"
#include "LeftDown.h"
#include "RightDown.h"
#include "Memory.h"
#include "MemoryController.h"
#include "Executions.h"
#include <cmath>
#include "Painter.h"
#include "ScrollController.h"
#include "Scrolls.h"

Zoom::Zoom(Long rate) {
	this->rate = rate;
}

Zoom::Zoom(const Zoom& source) {
	this->rate = source.rate;
}

Zoom::~Zoom() {

}

Zoom& Zoom::operator=(const Zoom& source) {
	this->rate = source.rate;

	return *this;
}

void Zoom::Set(Long changeRate) {
	this->rate = changeRate;
}