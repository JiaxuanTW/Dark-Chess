#pragma once

#include <QWidget>
#include <Qvector>

#include "ChessType.h"
#include "NextMoveInfo.h"
#include "PiecePosition.h"

class Board : public QWidget
{
	Q_OBJECT
public:
	explicit Board(QWidget* parent = Q_NULLPTR);

	/* 棋位資訊 */
	inline int getRowId(int squareId);
	inline int getColumnId(int squareId);
	inline int getSquareId(int row, int col);
	inline int getSquareId(unsigned int mask);
	inline int getChessTypeId(int squareId);

	/* 棋盤功能 */
	void init();
	void shuffle();
	
	/* 走棋運算 */
	void movePiece(int srcSquareId, int destSquareId);
	void flipPiece(int destSquareId);
	bool validMove(int srcSquareId, int destSquareId);
	void nextTurn();

	/* 繪製與操作 */
	int click(QPoint point);
	void drawPieces(QPainter& painter);
	void paintEvent(QPaintEvent*);
	virtual void mouseReleaseEvent(QMouseEvent* ev) = 0;

	/* 炮吃子、走步運算 */
	unsigned int Cgen(unsigned int src);
	unsigned int CgenR(unsigned int x, unsigned int c);
	unsigned int CgenC(unsigned int y, unsigned int r);
	unsigned int CgenCL(unsigned int y);
	unsigned int CgenCR(unsigned int y);
	unsigned int CgenC0(unsigned int y);
	unsigned int CgenC1(unsigned int y);
	unsigned int CgenC2(unsigned int y);
	unsigned int CgenC3(unsigned int y);
	unsigned int CgenC4(unsigned int y);
	unsigned int CgenC5(unsigned int y);
	unsigned int CgenC6(unsigned int y);
	unsigned int CgenC7(unsigned int y);

protected:
	ChessType chessType[16];
	unsigned int red, black, occupied;
	int turn;
	int selectedId;
	inline int bitsHash(unsigned int x);
	enum Turn { RED = -1, BLACK = 1 };
	//棋盤列遮罩
	unsigned int rowMask[4] = {
		0x11111111,
		0x22222222,
		0x44444444,
		0x88888888,
	};
	//棋盤欄遮罩
	unsigned int colMask[8] = {
		0x0000000F,
		0x000000F0,
		0x00000F00,
		0x0000F000,
		0x000F0000,
		0x00F00000,
		0x0F000000,
		0xF0000000,
	};
	//棋子在棋盤格上可移動位置遮罩
	unsigned int moveMask[32] = {
		0x00000012,
		0x00000025,
		0x0000004A,
		0x00000084,
		0x00000121,
		0x00000252,
		0x000004A4,
		0x00000848,
		0x00001210,
		0x00002520,
		0x00004A40,
		0x00008480,
		0x00012100,
		0x00025200,
		0x0004A400,
		0x00084800,
		0x00121000,
		0x00252000,
		0x004A4000,
		0x00848000,
		0x01210000,
		0x02520000,
		0x04A40000,
		0x08480000,
		0x12100000,
		0x25200000,
		0x4A400000,
		0x84800000,
		0x21000000,
		0x52000000,
		0xA4000000,
		0x48000000,
	};
};