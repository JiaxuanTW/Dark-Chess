#pragma once

/* 暗棋種類類別 */

class ChessType
{
public:
	unsigned int pos; //同棋種所有位置
	inline static unsigned int getLSB(unsigned int x) {
		//取得 Bitboard 最小位元
		//x: 傳入 Bitboard 值
		//return: 最小位元 Bitboard 值

		return x & (-x);
	}
	inline static unsigned int getMSB(unsigned int x ) {
		x |= x >> 32;
		x |= x >> 16;
		x |= x >> 8;
		x |= x >> 4;
		x |= x >> 2;
		x |= x >> 1;
		return (x >> 1) + 1;
	}
};