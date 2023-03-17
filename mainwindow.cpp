#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "chrono"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textEdit->setDisabled(true);
    ui->label->setDisabled(true);
    ui->viewText->setTextInteractionFlags(Qt::NoTextInteraction); //disable selection

    a = typeraceString();

    scene = new QGraphicsScene(this);
    gif_anim = new QLabel();
    changeMovie(":images//stable_resize.gif", gif_anim, false);

//    gif_anim->setMovie(movie);
//    movie->start();

    // Set the size of the QLabel to match the size of the animation
//     gif_anim->setFixedSize(movie->frameRect().size());

    QGraphicsProxyWidget *proxy = scene->addWidget(gif_anim);
    ui->graphicsView->setScene(scene);

    ui->viewText->setText(a);
}

//function to start the typerace using ctrl+Enter and initialize some variables
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //TODO: only run the control + return event once
    if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Return)
    {
        //change the gif, start the animation, pause it
//        qDebug() << movie->frameCount();
        changeMovie(":images//move_resize.gif", gif_anim, true);

        //start the chrono time on start
        startTime = std::chrono::high_resolution_clock::now();

        //enable and set focus on the textedit to type
        ui->textEdit->setDisabled(false);
        ui->textEdit->setFocus();
    } else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_R) {

        //reset the time
        startTime = std::chrono::high_resolution_clock::now();

        a = typeraceString();
        ui->viewText->setText(a);

        //move the cursor to the beginning
        //change textedit and reset it too
        hc.setPosition(0);
        ui->textEdit->setDisabled(true);
        ui->textEdit->clear();
//        ui->textEdit->setFocus();

        //reset label
        ui->label->clear();
    }
}

//handles the text changes on textEdit
void MainWindow::on_textEdit_textChanged()
{
    // get the text being typed
    auto beingTyped = ui->textEdit->toPlainText();

    QTextStream splita(&a);

    QTextDocument *doc = ui->viewText->document();

//    QTextCursor hc(doc);

    QTextCharFormat plainFormat(hc.charFormat());
    QTextCharFormat colorFormat = plainFormat;
    colorFormat.setForeground(Qt::red);

    QRegularExpression rx(QString("^%1").arg(beingTyped));

    //hc keeps track of where we are in the viewText.
    hc = doc->find(rx, hc, {QTextDocument::FindCaseSensitively, QTextDocument::FindWholeWords});

    //when the text is changed in the textEdit jump to the next frame of the movie and update
    //the words per minute

    movie->jumpToNextFrame();
    wpm();

    if (hc.position() == a.size())
    {
        changeMovie(":images//stable_resize.gif", gif_anim, false);
        ui->textEdit->setDisabled(true);
    }

    hc.select(QTextCursor::WordUnderCursor);
    hc.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
    hc.mergeCharFormat(colorFormat);
}

void MainWindow::wpm() {

    endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    double cps = static_cast<double>(a.size())/(static_cast<double>(duration)/1000.0);

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

void MainWindow::changeMovie(QString file, QLabel *gif,bool paused)
{
    movie = new QMovie(file);
    if (!movie->isValid()) {
        qDebug() << "Error loading GIF: " << movie->lastErrorString();
    }
    gif->setMovie(movie);
    movie->start();
    movie->setPaused(paused);
}


void MainWindow::on_actionRestart_triggered()
{
    //set the new word list
    a = typeraceString();
    ui->viewText->setText(a);

    //move the cursor to the beginning
    //change textedit and reset it too
    hc.setPosition(0);
    ui->textEdit->setDisabled(false);
    ui->textEdit->clear();
    ui->textEdit->setFocus();

    //reset label
    ui->label->clear();

//    qApp->quit();
//    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
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
