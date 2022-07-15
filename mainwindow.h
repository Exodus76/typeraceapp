#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <QLabel>
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <iostream>

#include <QDebug>

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
    void wpm(int sec);
    ~MainWindow();
    std::chrono::steady_clock::time_point start_time;

private slots:
    void on_textEdit_textChanged();

private:
    Ui::MainWindow *ui;
    int acount = 1;
};

class MyHighlighter : public QSyntaxHighlighter
{
public:
    using QSyntaxHighlighter::QSyntaxHighlighter;

    void highlightBlock(const QString &text);

public:
    int count = 0;
};

#endif // MAINWINDOW_H
