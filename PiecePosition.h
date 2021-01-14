#pragma once

/* 棋盤盤面資訊類別 */

#include "ChessType.h"

class PiecePosition
{
public:
	ChessType chessType[16];
	unsigned int red, black, occupied;
};