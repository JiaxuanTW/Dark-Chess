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
    void redirectToScreen(int redirectIndex);
    void switchToSettings();
    void switchToSinglePlayer();
    void switchToMultiPlayer();

private:
    void config();
};
