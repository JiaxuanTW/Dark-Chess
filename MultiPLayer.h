#pragma once

#include "Board.h"

class MultiPlayer : public Board
{
	Q_OBJECT

public:
	void mouseReleaseEvent(QMouseEvent* ev);
};