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
    QTimer* countdown;

public slots:
    void switchToMenu();
    void switchToLoadingScreen();
    void switchToSettings();
    void switchToSinglePlayer();
    void switchToMultiPlayer();

private:
    void config();
};
