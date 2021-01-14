#pragma once

/* 生成走棋資訊類別 */

class NextMoveInfo
{
public:
	int src, dest;
	NextMoveInfo(int src, int dest) {
		this->src = src;
		this->dest = dest;
	}
};