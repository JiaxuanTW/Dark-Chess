#include "Menu.h"
#include "MainWindow.h"
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>


void Menu::paintEvent(QPaintEvent*) {
	QPainter painter(this);
	QPixmap image;
	image.load("./images/main.jpg");
	painter.drawPixmap(0, 0, image);
}

void Menu::mouseReleaseEvent(QMouseEvent* ev) {

	printf("%d / %d \n", ev->x(), ev->y());
	//建立指向底層視窗的指標
	MainWindow* control = static_cast<MainWindow*>(this->parentWidget()->parentWidget());

	//控制按鈕按下功能
	if (ev->x() >= 1090 && ev->x() <= 1515 && ev->y() >= 570 && ev->y() <= 640) {
		control->stack->setCurrentIndex(1);
		control->player->stop();
	}
	else if (ev->x() >= 1130 && ev->x() <= 1520 && ev->y() >= 670 && ev->y() <= 730) {
		control->stack->setCurrentIndex(2);
		control->player->stop();
	}
	else if (ev->x() >= 1130 && ev->x() <= 1520 && ev->y() >= 760 && ev->y() <= 820) {
		printf("CLOSE\n");
		control->close();
	}
}
