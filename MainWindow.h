#pragma once

#include <QtWidgets/QMainWindow>
#include <QStackedWidget>
#include <QMediaPlayer>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    QStackedWidget* stack;
    QMediaPlayer* player;

private:
    void config();
};
