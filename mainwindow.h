#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QMovie>
#include <QLabel>
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QElapsedTimer>
#include <sstream>
#include <QFile>
#include <QRandomGenerator>
#include <QStringList>
#include <QDebug>
#include <QGraphicsScene>

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void wpm();
    QString typeraceString();

    ~MainWindow();

    QGraphicsScene *scene;
    QLabel *gif_anim;
    QMovie *movie;

//    QElapsedTimer timer;
//    QTime start_time;
//    QTime end_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

private slots:

    void on_textEdit_textChanged();
    void keyPressEvent(QKeyEvent *event);

    void on_actionRestart_triggered();

private:
    Ui::MainWindow *ui;

    QString a;
};

//fail try
//class MyHighlighter : public QSyntaxHighlighter
//{
//public:
//    using QSyntaxHighlighter::QSyntaxHighlighter;

//    void highlightBlock(const QString &text);

//public:
//    int count = 0;
//};

#endif // MAINWINDOW_H
