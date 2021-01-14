#include <QMediaPlaylist>
#include <QToolBar>

#include "MainWindow.h"
#include "Menu.h"
#include "SinglePlayer.h"
#include "MultiPlayer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    stack = new QStackedWidget();
    player = new QMediaPlayer();

    setCentralWidget(stack);

    Menu* menu = new Menu;
    SinglePlayer* single = new SinglePlayer;
    MultiPlayer* multi = new MultiPlayer;

    stack->addWidget(menu);
    stack->addWidget(single);
    stack->addWidget(multi);
    stack->setCurrentIndex(0);

    player = new QMediaPlayer();
    QMediaPlaylist* playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl::fromLocalFile("./audios/main_theme.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    player->setPlaylist(playlist);
    player->play();

    config(); //設置視窗參數
}

void MainWindow::config() {
    setFixedSize(1600, 900);
    setWindowTitle("Dark Chess");

    //移除視窗狀態欄
    QList<QToolBar*> allToolBars = this->findChildren<QToolBar*>();
    foreach(QToolBar * tb, allToolBars) {
        this->removeToolBar(tb);
    }

    // 移除標題列
    //setWindowFlags(Qt::Window | Qt::FramelessWindowHint);


}
