#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "chrono"
#include <sstream>
#include <QFile>
#include <QRandomGenerator>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textEdit->setDisabled(true);
    ui->label->setDisabled(true);
    ui->viewText->setTextInteractionFlags(Qt::NoTextInteraction); //disable selection

    a = typeraceString();
    //    qDebug << a.toLatin1();

    //    a = "about above add after again air all almost along also always america an and animal another answer";
    //75 w 404 char

    ui->viewText->setText(a);
}

void MainWindow::on_pushButton_clicked()
{
    startTime = std::chrono::high_resolution_clock::now(); //start the chrono time on start
    ui->pushButton->setDisabled(true);
    ui->textEdit->setDisabled(false);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Return)
    {
        qDebug() << "Ctr+Enter pressed";
        on_pushButton_clicked(); //start the typerace
        ui->textEdit->setFocus(); //set focus on the textedit to type
    }
}

void MainWindow::on_textEdit_textChanged()
{
    auto beingTyped = ui->textEdit->toPlainText();
    //    ui->textEdit->keyPressEvent()

    qDebug() << beingTyped;

    QTextStream splita(&a);


    QTextDocument *doc = ui->viewText->document();

    QTextCursor hc(doc);

    QTextCharFormat plainFormat(hc.charFormat());
    QTextCharFormat colorFormat = plainFormat;
    colorFormat.setForeground(Qt::red);

    QRegularExpression rx(QString("^%1").arg(beingTyped));

    //hc keeps track of where we are in the viewText.
    hc = doc->find(rx, hc, {QTextDocument::FindCaseSensitively, QTextDocument::FindWholeWords});

    if (hc.position() !=  a.size())
    {
        wpm();
        qDebug() << "here";
    } else if (hc.position() == a.size())
    {
        ui->textEdit->setDisabled(true);
    }

    hc.select(QTextCursor::WordUnderCursor);
    hc.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
    hc.mergeCharFormat(colorFormat);
}

void MainWindow::wpm() {
    endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    qDebug() << duration << "<-- Time elapsed";

    double cps = static_cast<double>(a.size())/(static_cast<double>(duration)/1000.0);
    qDebug() << cps;
    qDebug() << cps * (60/4.7) << "<-- wpm";
    ui->label->setDisabled(false);
    ui->label->setNum(int(cps * (60/4.7)));
}

QString MainWindow::typeraceString() {

    QFile File("words.txt");

    if (!File.open(QIODevice::ReadOnly | QIODevice::Text))
        return QString();

    QStringList words;
    QTextStream in(&File);
    while (!in.atEnd()) {
        //reads everything line by line
        //trimming to remove any unwanted whitespace
        QString line = in.readLine().trimmed();
        if (!line.isEmpty())
            words.append(line);
    }

    QString randomWords;

    int count = qMin(words.size(), 20);
    QRandomGenerator rand(QRandomGenerator::global()->generate());
    for (int i = 0; i < count; i++) {
        int index = rand.bounded(words.size());
        randomWords.append(words.takeAt(index));
        if (!(i+1 == count))randomWords.append(" ");
    }

    return randomWords;

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
