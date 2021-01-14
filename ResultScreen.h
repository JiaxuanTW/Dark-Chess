#pragma once

#include <QWidget>

class ResultScreen: public QWidget
{
	Q_OBJECT

public:
	enum DisplayMode
	{
		NONE,
		ComputerWins,
		PlayerWins,
		Player1Wins,
		Player2Wins
	};
	void setDisplayMode(DisplayMode mode);
	

private:
	int displayMode;
	void paintEvent(QPaintEvent*);
};
