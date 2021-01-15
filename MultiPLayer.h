#pragma once

#include "Board.h"

class MultiPlayer : public Board
{
	Q_OBJECT

public:
	explicit MultiPlayer();
	void mouseReleaseEvent(QMouseEvent* ev);
};