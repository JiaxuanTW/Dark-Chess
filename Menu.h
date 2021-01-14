#pragma once

#include <QWidget>

class Menu : public QWidget
{
private:
	void paintEvent(QPaintEvent*);
	void mouseReleaseEvent(QMouseEvent* ev);
};