#include "mainwindow.h"
#include "./ui_mainwindow.h"

std::once_flag flag1;

//std::vector<std::chrono::steady_clock::time_point> t;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMovie* movie = new QMovie(":/images/berserk.jpg");
    if(!movie->isValid()) {
        return;
    }
    ui->label->setMovie(movie);
    movie->start();

    ui->viewText->setText("Hello Hello is it me you are looking for");
}

void MainWindow::on_textEdit_textChanged()
{
    QTextDocument *doc = ui->viewText->document();

    QTextCursor hc(doc);
    QTextCursor cur(doc);

//    cur.atStart();
    QTextCharFormat plainFormat(hc.charFormat());
    QTextCharFormat colorFormat = plainFormat;
    colorFormat.setForeground(Qt::red);
//    bool found = false;

    QRegularExpression rx(QString("^%1").arg(ui->textEdit->toPlainText()));
    QStringList a = ui->viewText->toPlainText().split(" ");


//        while (!hc.isNull() && !hc.atEnd()) {
        QRegularExpressionMatch match = rx.match(ui->viewText->toPlainText());
        if (match.hasMatch()) {
            std::thread st1([this](){std::call_once(flag1, [this](){start_time = std::chrono::steady_clock::now();});});
            st1.join();
        }

        hc = doc->find(rx, hc, {QTextDocument::FindCaseSensitively, QTextDocument::FindWholeWords});
//        qDebug() << hc.position() << "cursor position";
//        qDebug() << hc.anchor() << "anchor";
//        qDebug() << hc.selectedText();
        if (hc.position() == ui->viewText->toPlainText().length() ) {
            qDebug() << "here";
            auto duration = std::chrono::duration_cast<std::chrono::minutes>(std::chrono::steady_clock::now() - start_time);
            qDebug() << duration.count();
            wpm(duration.count());
        }
//        qDebug() << hc.anchor() << "anchor position";
        hc.select(QTextCursor::WordUnderCursor);
        hc.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
        hc.mergeCharFormat(colorFormat);
}

void MainWindow::wpm(int sec) {
    auto size = ui->viewText->toPlainText().length();
//    sec = std::chrono::duration_cast<std::chrono::minutes>(sec);
    qDebug() << int(size/sec);
    ui->lcdNumber->display(int(size/sec));
}

MainWindow::~MainWindow()
{
    delete ui;
}



//tries
//    QString thetext = ui->viewText->toPlainText();
//    MyHighlighter *m = new MyHighlighter(ui->viewText->document());
/*
QRegularExpression rx(QString("^%1").arg(ui->textEdit->toPlainText()));

QRegularExpressionMatch match = rx.match("Hello is it me you are looking for");

QPalette qp = ui->viewText->palette();
QPalette  noMatch = ui->viewText->palette();
qp.setColor(QPalette::Base, Qt::red);
noMatch.setColor(QPalette::Base, Qt::blue);
if (match.hasMatch()) {
    ui->viewText->setPalette(qp);
} else {
    ui->viewText->setPalette(noMatch);
}
*/


//    m->highlightBlock(ui->textEdit->toPlainText());
//    delete m;

/*
 * void MyHighlighter::highlightBlock(const QString &text){
    QTextCharFormat myClassFormat;
    myClassFormat.setFontWeight(QFont::Bold);
    myClassFormat.setForeground(Qt::darkMagenta);

//    text is the text entered
    QRegularExpression rx(QString("^%1").arg(text));
    QRegularExpressionMatch match = rx.match("Hello is it me you are looking for");
    if (match.hasMatch()) {
        qDebug() << match.capturedLength();
        setFormat(0, match.capturedLength(), myClassFormat);
    } else {
        qDebug() << "text not matched";
    }
}
*/
