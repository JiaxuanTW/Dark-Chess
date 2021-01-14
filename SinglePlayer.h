#pragma once

/* 單機模式類別 */

#include "Board.h"
#include "NextMoveInfo.h"
#include "PiecePosition.h"

class SinglePlayer : public Board
{
public:
	PiecePosition saveCurrentBoard();
	QVector<NextMoveInfo> generateMoves();
	void computerMove();
	int evaluate();
	int miniMax(int depth, int aTurn, int alpha, int beta);
	void undoFakeMove(PiecePosition piecePosition);
	inline int negaTurn(int aTurn) { return aTurn == RED ? BLACK : RED; };
private:
	void mouseReleaseEvent(QMouseEvent* ev);
};