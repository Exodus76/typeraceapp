#include "mainwindow.h"
#include "./ui_mainwindow.h"

//std::once_flag flag1;

//std::vector<std::chrono::steady_clock::time_point> t;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textEdit->setDisabled(true);
    ui->label->setDisabled(true);
    ui->viewText->setTextInteractionFlags(Qt::NoTextInteraction); //disable selection

    a = "about above add after again air all almost along also always america an and animal another answer any are around as ask at away back be because been before began begin being below between big book both boy but by call came can car carry change children city close come could country cut day did different do does down each earth eat end";
    //75 w 404 char

    ui->viewText->setText(a);
}

void MainWindow::on_pushButton_clicked()
{
//    qDebug() << start_time;
    timer.start();
    ui->pushButton->setDisabled(true);
    ui->textEdit->setDisabled(false);
}

void MainWindow::on_textEdit_textChanged()
{
    auto to_type = ui->textEdit->toPlainText();
    QTextDocument *doc = ui->viewText->document();

    QTextCursor hc(doc);

    QTextCharFormat plainFormat(hc.charFormat());
    QTextCharFormat colorFormat = plainFormat;
    colorFormat.setForeground(Qt::red);

    QRegularExpression rx(QString("^%1").arg(to_type));


    hc = doc->find(rx, hc, {QTextDocument::FindCaseSensitively, QTextDocument::FindWholeWords});

    if (hc.position() ==  a.count()) {
        wpm();
        qDebug() << "here";
    }

    hc.select(QTextCursor::WordUnderCursor);
    hc.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
    hc.mergeCharFormat(colorFormat);
}

void MainWindow::wpm() {
    auto duration = timer.elapsed();
    qDebug() << duration; // in milliseconds
    auto cps = a.count()/(duration/100);

    qDebug() << cps * (60/4.7) << "<-- wpm";
//    ui->lcdNumber->display(int(cps * 12));
    ui->label->setDisabled(false);
    ui->label->setNum(int(cps * (60/4.7)));
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

