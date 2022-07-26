#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <QLabel>
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QElapsedTimer>

#include <QDebug>

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
    ~MainWindow();
    QElapsedTimer timer;
    QTime start_time;
    QTime end_time;
//    std::chrono::steady_clock::time_point start_time;
//    std::chrono::steady_clock::time_point end_time;

private slots:
    void on_textEdit_textChanged();

    void on_pushButton_clicked();

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
