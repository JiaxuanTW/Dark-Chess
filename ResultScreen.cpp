#include <qpainter.h>

#include "ResultScreen.h"

void ResultScreen::setDisplayMode(DisplayMode mode) {
	displayMode = mode;
}

void ResultScreen::paintEvent(QPaintEvent*) {
	QPainter painter(this);
	QPixmap image;
	
	if (displayMode == ComputerWins) {
		image.load("./images/result_computer.jpg");
	}
	else if (displayMode == PlayerWins) {
		image.load("./images/result_player.jpg");
	}
	else if (displayMode == Player1Wins) {
		image.load("./images/result_player1.jpg");
	}
	else if (displayMode == Player2Wins) {
		image.load("./images/result_player2.jpg");
	}
	painter.drawPixmap(0, 0, image);
}
