#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

    ui->viewText->setText("Hello is it me you are looking for");
}

void MainWindow::on_textEdit_textChanged()
{
    QTextDocument *doc = ui->viewText->document();

    QTextCursor hc(doc);
    QTextCursor cur(doc);

    cur.atStart();
    QTextCharFormat plainFormat(hc.charFormat());
    QTextCharFormat colorFormat = plainFormat;
    colorFormat.setForeground(Qt::red);
//    bool found = false;

    QRegularExpression rx(QString("^%1").arg(ui->textEdit->toPlainText()));

//    while (!hc.isNull() && !hc.atEnd()) {
        hc = doc->find(rx, hc, {QTextDocument::FindCaseSensitively, QTextDocument::FindWholeWords});

        qDebug() << hc.position() << "cursor position";
        qDebug() << hc.anchor() << "anchor";
        qDebug() << hc.selectedText();
        if (hc.position() == 34) {
            this->close();
        }
//        qDebug() << hc.anchor() << "anchor position";
        hc.select(QTextCursor::WordUnderCursor);
        hc.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
        hc.mergeCharFormat(colorFormat);

//    }


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
