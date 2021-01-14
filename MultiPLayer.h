#pragma once

#include "Board.h"

class MultiPlayer : public Board
{
public:
	void mouseReleaseEvent(QMouseEvent* ev);
};