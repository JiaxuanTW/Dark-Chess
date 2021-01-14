#pragma once

/* 單機模式類別 */

#include "Board.h"
#include "NextMoveInfo.h"
#include "PiecePosition.h"

class SinglePlayer : public Board
{
public:
	//走棋運算
	int evaluate();
	void computerMove();
	int miniMax(int depth, int aTurn, int alpha, int beta);
	PiecePosition saveCurrentBoard();
	void undoFakeMove(PiecePosition piecePosition);
	QVector<NextMoveInfo> generateMoves();
	inline int negaTurn(int aTurn) { return aTurn == RED ? BLACK : RED; };
private:
	void mouseReleaseEvent(QMouseEvent* ev);
};