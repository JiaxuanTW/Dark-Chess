#pragma once

#include <QWidget>

class LoadingScreen : public QWidget
{
	Q_OBJECT

public:
	explicit LoadingScreen(QWidget* parent = Q_NULLPTR);
	QTimer* timer;

public slots:
	void updateProgress();

private:
	void paintEvent(QPaintEvent*);
	int progressBar1Pos;
};
