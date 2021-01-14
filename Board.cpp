#include <QVector>
#include <QImage>
#include <QPixmap>
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
#include <QTIme>

#include "Board.h"

Board::Board(QWidget* parent)
	: QWidget(parent) {

	//初始化成員變數
	turn = NULL;
	selectedId = -1;
	init();
	shuffle(); //生成隨機盤面
}

inline int Board::bitsHash(unsigned int x) {
	return (x * 0x08ED2BE6) >> 27;
}

int Board::getRowId(int squareId) {
	return squareId % 4;
}

int Board::getColumnId(int squareId) {
	return squareId / 4;
}

int Board::getSquareId(int row, int col) {
	return 4 * col + row;
}

int Board::getSquareId(unsigned int mask) {
	int index[32] = {
		31,  0,  1,  5,  2, 16, 27,  6,
		 3, 14, 17, 19, 28, 11,  7, 21,
		30,  4, 15, 26, 13, 18, 10, 20,
		29, 25, 12,  9, 24,  8, 23, 22,
	};
	return index[bitsHash(mask)];
}

int Board::getChessTypeId(int squareId) {
	for (size_t i = 0; i <= 15; i++) {
		if (chessType[i].pos & (rowMask[getRowId(squareId)] &
			colMask[getColumnId(squareId)]))
			return i;
	}
	return -1;
}

void Board::init() {
	chessType[0].pos = 0x00000000;
	chessType[1].pos = 0x00000002;
	chessType[2].pos = 0x00000011;
	chessType[3].pos = 0x00001100;
	chessType[4].pos = 0x11000000;
	chessType[5].pos = 0x00110000;
	chessType[6].pos = 0x22000000;
	chessType[7].pos = 0x00222220;
	chessType[8].pos = 0x00000008;
	chessType[9].pos = 0x00000044;
	chessType[10].pos = 0x0004400;
	chessType[11].pos = 0x44000000;
	chessType[12].pos = 0x00440000;
	chessType[13].pos = 0x88000000;
	chessType[14].pos = 0x00888880;
	chessType[15].pos = 0xFFFFFFFF;
	red = 0x33333333;
	black = 0xCCCCCCCC;
	occupied = 0xFFFFFFFF;
}

void Board::shuffle() {
	// 亂數洗牌

	// 初始化 各種棋位、紅棋位、黑棋位、占用棋位
	for (size_t i = 1; i <= 14; i++)
		chessType[i].pos = 0x00000000;
	red = 0x00000000;
	black = 0x00000000;
	occupied = 0xFFFFFFFF;

	int order[32] = { 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 7, 7, 7,
					   8, 9, 9,10,10,11,11,12,12,13,13,14,14,14,14,14 };

	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime())); // 初始化 qsrand 種子
	int x, y;

	for (size_t i = 0; i < 100; i++) {
		x = qrand() % 32;
		y = qrand() % 32;
		std::swap(order[x], order[y]);
	}

	for (size_t i = 0; i < 32; i++)
		chessType[order[i]].pos += pow(2, i);

	for (size_t i = 0; i < 15; i++)
		printf("%08x\n", chessType[i].pos);

	// 產生 red、black 資訊
	for (size_t i = 1; i <= 7; i++)
		red |= chessType[i].pos;

	for (size_t i = 8; i <= 14; i++)
		black |= chessType[i].pos;
}

void Board::movePiece(int srcSquareId, int destSquareId) {
	// 移動棋子
	// srcSquareId: 來源格子代號
	// destSquareId: 目的格子代號

	unsigned int srcMask = rowMask[getRowId(srcSquareId)] & colMask[getColumnId(srcSquareId)];
	unsigned int destMask = rowMask[getRowId(destSquareId)] & colMask[getColumnId(destSquareId)];
	int srcTypeId = getChessTypeId(srcSquareId);
	int destTypeId = getChessTypeId(destSquareId);
	chessType[0].pos |= srcMask;
	chessType[srcTypeId].pos ^= srcMask;
	chessType[srcTypeId].pos |= destMask;
	chessType[destTypeId].pos ^= destMask;

	// 調整 red、black、occupied 位置
	(srcTypeId <= 7 ? red : black) ^= srcMask;
	(srcTypeId <= 7 ? red : black) |= destMask;
	if (destTypeId != 0)
		(srcTypeId <= 7 ? black : red) ^= destMask;
	occupied = black|red;

	// 走完棋 -> 換邊
	nextTurn();
}

void Board::flipPiece(int destSquareId) {
	//翻子行為

	int destRowId = getRowId(destSquareId);
	int destColumnId = getColumnId(destSquareId);
	unsigned int mask = rowMask[destRowId] & colMask[destColumnId];
	chessType[15].pos ^= mask;
	nextTurn();
}

bool Board::validMove(int srcSquareId, int destSquareId) {
	int srcTypeId = getChessTypeId(srcSquareId);
	int destTypeId = getChessTypeId(destSquareId);

	//棋方檢查
	if (turn == RED && srcTypeId >= 8) {
		printf("THIS IS NOT YOUR PIECE.");
		return false;
	}
	if (turn == BLACK && srcTypeId <= 7) {
		return false;
	}

	// 確認走棋目的是不是對手且不是暗棋 以及 在範圍內 
	unsigned int redMoveCheck = ((black) & (~chessType[15].pos) | chessType[0].pos) &
		moveMask[srcSquareId] & rowMask[getRowId(destSquareId)] &
		colMask[getColumnId(destSquareId)];
	unsigned int blackMoveCheck = ((red) & (~chessType[15].pos) | chessType[0].pos) &
		moveMask[srcSquareId] & rowMask[getRowId(destSquareId)] &
		colMask[getColumnId(destSquareId)];

	//if (redMoveCheck)
	//	cout << "PASS redMoveCheck" << endl;
	//else 
	//	cout << "FAIL redMoveCheck" << endl;
	//cout << "destTypeId = " << destTypeId << endl;
	//printf("black bitBoard: %08x\n", black);
	//printf("black & none: %08x\n", black | chessType[0].pos);
	//printf("moveMask bitBoard: %08x\n", moveMask[srcSquareId]);
	//printf("position bitBoard: %08x\n", chessType[destTypeId].pos);

	//if (blackMoveCheck) 
	//	cout << "PASS blackMoveCheck" << endl;
	//else 
	//	cout << "FAIL blackMoveCheck" << endl;
	//cout << "destTypeId = " << destTypeId << endl;
	//printf("red bitBoard: %08x\n", red);
	//printf("red & none: %08x\n", red | chessType[0].pos);
	//printf("moveMask bitBoard: %08x\n", moveMask[srcSquareId]);
	//printf("position bitBoard: %08x\n", chessType[destTypeId].pos);
	//printf("result: %08x\n", blackMoveCheck);

	//走、吃子合法性判斷
	switch (srcTypeId) {
	case 1:
		return redMoveCheck && destTypeId != 14 ? true : false;
	case 2:
		return redMoveCheck && destTypeId != 8 ? true : false;
	case 3:
		return redMoveCheck && destTypeId != 8 && destTypeId != 9 ? true : false;
	case 4:
		return redMoveCheck && destTypeId != 8 && destTypeId != 9 && destTypeId != 10 ? true : false;
	case 5:
		return redMoveCheck && (destTypeId == 12 || destTypeId == 13 ||
			destTypeId == 14 || destTypeId == 0) ? true : false;
	case 6:
		return (chessType[0].pos & moveMask[srcSquareId] & rowMask[getRowId(destSquareId)] &
			colMask[getColumnId(destSquareId)]) | ((black & Cgen(srcSquareId)) & rowMask[getRowId(destSquareId)] &
				colMask[getColumnId(destSquareId)] & (~(chessType[15].pos))) ? true : false; //炮點紅棋子
	case 7:
		return redMoveCheck && (destTypeId == 8 || destTypeId == 14 || destTypeId == 0) ? true : false;
	case 8:
		return blackMoveCheck && destTypeId != 7 ? true : false;
	case 9:
		return blackMoveCheck && destTypeId != 1 ? true : false;
	case 10:
		return blackMoveCheck && destTypeId != 1 && destTypeId != 2 ? true : false;
	case 11:
		return blackMoveCheck && destTypeId != 1 && destTypeId != 2 && destTypeId != 3 ? true : false;
	case 12:
		return blackMoveCheck && (destTypeId == 5 || destTypeId == 6 ||
			destTypeId == 7 || destTypeId == 0) ? true : false;
	case 13:
		return (chessType[0].pos & moveMask[srcSquareId] & rowMask[getRowId(destSquareId)] &
			colMask[getColumnId(destSquareId)]) | (red & Cgen(srcSquareId) & rowMask[getRowId(destSquareId)] &
				colMask[getColumnId(destSquareId)] & (~chessType[15].pos)) ? true : false; //炮點紅棋子	
	case 14:
		return blackMoveCheck && (destTypeId == 1 || destTypeId == 7 || destTypeId == 0) ? true : false;
	}
	return false;
}

void Board::nextTurn() {
	turn = (turn == RED ? BLACK : RED);
}

int Board::click(QPoint point) {
	//點擊功能
	//point: 點擊位置，從滑鼠事件中傳入
	//回傳點擊格子的代號

	for (size_t row = 0; row < 4; row++) {
		for (size_t col = 0; col < 8; col++) {
			if ((point.y() >= row * 150 + 185 && point.y() < (row + 1) * 150 + 185) &&
				(point.x() >= col * 150 + 50 && point.x() < (col + 1) * 150 + 50)) {
				return getSquareId(row, col);
			}
		}
	}

	//若點擊視窗外面就回傳範圍錯誤
	return -1;
}

unsigned int Board::Cgen(unsigned int src) {
	/*printf("src = %d\n", src);*/
	unsigned int r = src / 4; //取得row
	unsigned int c = src % 4; //取得col
	unsigned int x = ((colMask[r] & occupied) ^ (1 << src)) >> (4 * r); //判斷行炮位-推到第一列-削掉炮本身的位置-c表示炮在第幾行
	/*OOO炮 OO炮o O炮oo 炮ooo*/
	unsigned int y = ((rowMask[c] & occupied) ^ (1 << src)) >> c;  //判斷列炮位-推到第一行-削掉炮本身的位置-r表示炮在第幾列
	/*printf("r = %d,c =  %d\n", r, c);
	printf("x = %08x, y = %08x\n", x, y);
	printf("%08x\n", (CgenR(x, c) << (4 * r)) | (CgenC(y, r) << c));*/
	return ((CgenR(x, c) << (4 * r)) | (CgenC(y, r) << c));
}

unsigned int Board::CgenR(unsigned int x, unsigned int c) {
	switch (c) {
	case 0: //炮在第一行 將二三四最右邊之棋子拔掉 若還有旗 則回傳此旗(最右邊拔掉後之最右邊)
		if (x) {
			unsigned int mask = ChessType::getLSB(x);
			return (x ^= mask) ? ChessType::getLSB(x) : 0;
		}
		else return 0;
	case 1:
		return ((x & 12) == 12) ? 8 : 0; // 12 = 1100, 炮在第二行,若三四行有棋,回傳第四行為炮位(8=1000)
	case 2:
		return ((x & 3) == 3) ? 1 : 0; // 3 = 0011, 炮在第三行,若一二行有棋,回傳第一位為炮位(1=0001)
	case 3:
		if (x) {
			unsigned int mask = ChessType::getMSB(x);
			return (x ^= mask) ? ChessType::getMSB(x) : 0;
		}// 炮在第四行 將一二三最左邊之棋子拔掉 若還有旗 則回傳此旗(最左邊拔掉後之最左邊)
	}
}

unsigned int Board::CgenC(unsigned int y, unsigned int r) {
	switch (r) {//炮在第0~7之位置(
	case 0:
		return CgenC0(y);
	case 1:
		return CgenC1(y);
	case 2:
		return CgenC2(y);
	case 3:
		return CgenC3(y);
	case 4:
		return CgenC4(y);
	case 5:
		return CgenC5(y);
	case 6:
		return CgenC6(y);
	case 7:
		return CgenC7(y);
	}
}

unsigned int Board::CgenCL(unsigned int y) { //找下面
	unsigned int mask = ChessType::getLSB(y);
	return (y ^= mask) ? ChessType::getLSB(y) : 0;
}

unsigned int Board::CgenCR(unsigned int y) { //找上面
	unsigned int mask = ChessType::getMSB(y);
	return (y ^= mask) ? ChessType::getMSB(y) : 0;
}

unsigned int Board::CgenC0(unsigned int y) { //炮在最上面 只找下面
	return CgenCL(y);
}

unsigned int Board::CgenC1(unsigned int y) {//炮在第二位 找下面六位
	return CgenCL(y & 0x11111100); // 下六
}

unsigned int Board::CgenC2(unsigned int y) {//炮在第三位 找第一位或刪掉前三位找下面五位
	unsigned int part = 0;
	if ((y & 0x00000011) == 0x00000011)//上二
		part |= 1;
	return part | CgenCL(y & 0x11111000); //下五
}

unsigned int Board::CgenC3(unsigned int y) {//炮在第四位 找前三位或刪掉前四位找下面四位
	unsigned int part = 0;
	part = CgenCR(y & 0x00000111); //上三
	return part | CgenCL(y & 0x11110000); // 下四
}

unsigned int Board::CgenC4(unsigned int y) {//炮在第五位 找前四位或刪掉前五位找下面三位
	unsigned int part = 0;
	part = CgenCR(y & 0x00001111); //上四
	return part | CgenCL(y & 0x11100000);//下三
}

unsigned int Board::CgenC5(unsigned int y) {//炮在第六位 找前五位或刪掉前六位找下兩位
	unsigned int part = 0;
	part = CgenCR(y & 0x00011111); //上五
	return part | CgenCL(y & 0x11000000); //下二
}

unsigned int Board::CgenC6(unsigned int y) {//炮在第七位 找前六位
	return CgenCR(y & 0x00111111); //上六
}

unsigned int Board::CgenC7(unsigned int y) {//炮在最下面 只找上面
	return CgenCR(y); //上七
}

void Board::drawPieces(QPainter& painter) {
	//繪製棋子

	QPixmap image;
	for (int i = 1; i <= 14; i++) {
		QString src = "./images/";
		src.append(QString::fromStdString(std::to_string(i)));
		src.append(".png");
		image.load(src);
		unsigned int bitBoard = chessType[i].pos;
		while (bitBoard) {
			unsigned int mask = ChessType::getLSB(bitBoard);
			bitBoard ^= mask;
			painter.drawPixmap(getColumnId(getSquareId(mask)) * 150 + 50,
				getRowId(getSquareId(mask)) * 150 + 185, image);
		}
	}

	//繪製未翻棋
	image.load("./images/15.png");
	unsigned int bitBoard = chessType[15].pos;
	while (bitBoard) {
		unsigned int mask = ChessType::getLSB(bitBoard);
		bitBoard ^= mask;
		painter.drawPixmap(getColumnId(getSquareId(mask)) * 150 + 50,
			getRowId(getSquareId(mask)) * 150 + 185, image);
	}
}

void Board::paintEvent(QPaintEvent*) {
	// 繪製視窗（Qt內建函數）
	QPainter painter(this);
	QPixmap image;
	// 繪製棋盤
	image.load("./images/board.jpg");
	painter.drawPixmap(0, 0, image);
	// 繪製棋子
	drawPieces(painter);
	// 繪製選取框
	if (selectedId != -1) {
		image.load("./images/select.png");
		painter.drawPixmap(getColumnId(selectedId) * 150 + 50,
			getRowId(selectedId) * 150 + 185, image);
	}
}