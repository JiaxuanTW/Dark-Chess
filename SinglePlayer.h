#pragma once

/* 單機模式類別 */

#include "Board.h"
#include "NextMoveInfo.h"
#include "PiecePosition.h"

class SinglePlayer : public Board
{
private:
	QVector<NextMoveInfo> generateMoves();
	PiecePosition saveCurrentBoard();
	void computerMove();
	int evaluate();
	int miniMax(int depth, int aTurn);
	void undoFakeMove(PiecePosition piecePosition);
	void mouseReleaseEvent(QMouseEvent* ev);
	inline int negaTurn(int aTurn) { return aTurn == RED ? BLACK : RED; };
};