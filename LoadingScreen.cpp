#include <QPainter>
#include <QTimer>

#include "LoadingScreen.h"

LoadingScreen::LoadingScreen(QWidget* parent) : QWidget(parent) {
	progressBar1Pos = 50;
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateProgress()));
	timer->start(10);
}

void LoadingScreen::updateProgress() {
	//更新進度條位置

	progressBar1Pos += 10;

	if (progressBar1Pos >= 1150)
		progressBar1Pos = 50;

	repaint();
}

void LoadingScreen::paintEvent(QPaintEvent*) {
	QPainter painter(this);
	QPixmap image;

	image.load("./images/progress_bar_bg");
	painter.drawPixmap(450, 515, image);

	image.load("./images/progress_bar.png");
	painter.drawPixmap(progressBar1Pos, 515, image);

	image.load("./images/loading.png");
	painter.drawPixmap(0, 0, image);
}
