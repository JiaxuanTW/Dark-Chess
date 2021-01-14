#include <QPainter>

#include "OpeningScreen.h"

void OpeningScreen::paintEvent(QPaintEvent*) {
	QPainter painter(this);
	QPixmap image;
	image.load("./images/opening.jpg");
	painter.drawPixmap(0, 0, image);
}
