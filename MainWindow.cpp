#include <QMediaPlaylist>
#include <QToolBar>
#include <QThread>

#include "MainWindow.h"
#include "OpeningScreen.h"
#include "LoadingScreen.h"
#include "ResultScreen.h"
#include "Menu.h"
#include "SinglePlayer.h"
#include "MultiPlayer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    stack = new QStackedWidget();
    player = new QMediaPlayer();

    setCentralWidget(stack);

    OpeningScreen* opening = new OpeningScreen;
    Menu* menu = new Menu;
    SinglePlayer* single = new SinglePlayer;
    MultiPlayer* multi = new MultiPlayer;
    LoadingScreen* loading = new LoadingScreen;
    
    ResultScreen* result1 = new ResultScreen;
    result1->setDisplayMode(ResultScreen::ComputerWins);
    ResultScreen* result2 = new ResultScreen;
    result1->setDisplayMode(ResultScreen::PlayerWins);
    ResultScreen* result3 = new ResultScreen;
    result1->setDisplayMode(ResultScreen::Player1Wins);
    ResultScreen* result4 = new ResultScreen;
    result1->setDisplayMode(ResultScreen::Player2Wins);

    stack->addWidget(opening);  // 0
    stack->addWidget(menu);     // 1
    stack->addWidget(single);   // 2
    stack->addWidget(multi);    // 3
    stack->addWidget(loading);  // 4
    stack->addWidget(result1);  // 5
    stack->addWidget(result2);  // 6
    stack->addWidget(result3);  // 7
    stack->addWidget(result4);  // 8
    
    stack->setCurrentIndex(0);

    //載入主頁面前LOGO頁
    QTimer::singleShot(3 * 1000, this, SLOT(switchToMenu()));

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

    //移除標題列
    //setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

void MainWindow::switchToMenu() {
    stack->setCurrentIndex(1);

    player = new QMediaPlayer();
    QMediaPlaylist* playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl::fromLocalFile("./audios/main_theme.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    player->setPlaylist(playlist);

    player->play();
}

void MainWindow::switchToSinglePlayer() {
    player = new QMediaPlayer();
    QMediaPlaylist* playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl::fromLocalFile("./audios/bgm.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    player->setPlaylist(playlist);

    player->play();
    stack->setCurrentIndex(2);
}

void MainWindow::switchToMultiPlayer() {
    player = new QMediaPlayer();
    QMediaPlaylist* playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl::fromLocalFile("./audios/bgm.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    player->setPlaylist(playlist);

    player->play();
    stack->setCurrentIndex(3);
}

void MainWindow::redirectToScreen(int redirectIndex) {
    player->stop();
    stack->setCurrentIndex(4);

    int delay = 4500; // Loading 畫面等待時間
    switch (redirectIndex) {
    case 1:
        QTimer::singleShot(delay, this, SLOT(switchToMenu())); 
        break;
    case 2:
        QTimer::singleShot(delay, this, SLOT(switchToSinglePlayer()));
        break;
    case 3:
        QTimer::singleShot(delay, this, SLOT(switchToMultiPlayer()));
        break;
    }
}

void MainWindow::switchToResult(int displayMode) {
    switch (displayMode) {
    case ResultScreen::ComputerWins:
        stack->setCurrentIndex(5);
        break;
    case ResultScreen::PlayerWins:
        stack->setCurrentIndex(6);
        break;
    case ResultScreen::Player1Wins:
        stack->setCurrentIndex(7);
        break;
    case ResultScreen::Player2Wins:
        stack->setCurrentIndex(8);
        break;
    }
}