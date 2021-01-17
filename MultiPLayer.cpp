#include <QMouseEvent>

#include "MultiPLayer.h"
#include "MainWindow.h"

MultiPlayer::MultiPlayer() {
	setPlayerInfo("PLAYER 1", "PLAYER 2");
}

void MultiPlayer::mouseReleaseEvent(QMouseEvent* ev) {
	int clickedId = click(ev->pos());

	if (ev->x() >= 1530 && ev->x() <= 1600 &&
		ev->y() >= 0 && ev->y() <= 50) {
		MainWindow* control = static_cast<MainWindow*>(this->parentWidget()->parentWidget());
		control->redirectToScreen(1);
		init();
		setPlayerInfo("PLAYER 1", "PLAYER 2");
		shuffle();
	}

	//若點擊非法範圍 -> 無效
	if (clickedId == -1)
		return;

	//若第一手 -> 翻棋並決定玩家棋方
	if (turn == NULL) {
		flipPiece(clickedId);
		getChessTypeId(clickedId) <= 7 ? turn = BLACK : turn = RED;
		getChessTypeId(clickedId) <= 7 ? turnConstant = BLACK : turnConstant = RED;
		repaint();
		return;
	}

	//選子行為，第一次選子
	if (selectedId == -1) {
		if (rowMask[getRowId(clickedId)] & colMask[getColumnId(clickedId)]
			& chessType[15].pos) {
			// 翻子
			flipPiece(clickedId);
			repaint();
		}
		else {
			selectedId = clickedId;
		}
	}
	else {
		if (validMove(selectedId, clickedId)) {
			movePiece(selectedId, clickedId);
			selectedId = -1;
			repaint();
		}
		else {
			printf("Capture Failed!\n");
		}
		selectedId = -1;
	}
	repaint();
}
