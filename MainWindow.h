#pragma once

#include <QtWidgets/QMainWindow>
#include <QStackedWidget>
#include <QMediaPlayer>
#include <QTimer>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    QStackedWidget* stack;
    QMediaPlayer* player;

public slots:
    void switchToMenu();
    void switchToSinglePlayer();
    void switchToMultiPlayer();
    void switchToResult(int displayMode);
    void redirectToScreen(int redirectIndex);

private:
    void config();
};
