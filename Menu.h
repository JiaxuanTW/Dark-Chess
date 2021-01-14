#pragma once

#include <QWidget>

class Menu : public QWidget
{
	Q_OBJECT

private:
	void paintEvent(QPaintEvent*);
	void mouseReleaseEvent(QMouseEvent* ev);
};