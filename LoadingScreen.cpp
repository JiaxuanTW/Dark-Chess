#include <QPainter>

#include "LoadingScreen.h"

void LoadingScreen::paintEvent(QPaintEvent*) {
	QPainter painter(this);
	QPixmap image;
	image.load("./images/opening.jpg");
	painter.drawPixmap(0, 0, image);
}
