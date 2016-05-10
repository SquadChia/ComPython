#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "keyenterreceiver.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    ui->textEdit->setPlainText("Python 3.5.1 (v3.5.1:37a07cee5969, Dec  6 2015, 01:38:48) [MSC v.1900 32 bit (Intel)] on win32\nType \"copyright\", \"credits\" or \"license()\" for more information. \n>>> ");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getLine()
{
    n_line = ui->textEdit->toPlainText().toStdString();
    size_t index1 = n_line.find_last_of(">>>");
    size_t index2 = n_line.size()- index1;
    n_line = n_line.substr(index1+1, index2);
}

void MainWindow::addLine(std::string n_string)
{
    QString qstr = QString::fromStdString(n_string);
    ui->textEdit->append(qstr);

}

bool MainWindow::event(QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent *ke = (QKeyEvent *) event;
            if (ke->key() == Qt::Key_Return || ke->key() == Qt::Key_Enter)
            {
                qDebug() << "enter pressed";

            }
        }
        return QWidget::event(event);
}


void MainWindow::on_actionNew_triggered()
{
    mFilename = "";
    ui->textEdit->setPlainText("Python 3.5.1 (v3.5.1:37a07cee5969, Dec  6 2015, 01:38:48) [MSC v.1900 32 bit (Intel)] on win32\nType \"copyright\", \"credits\" or \"license()\" for more information. \n >>> ");
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, "Open a file");

    if (!file.isEmpty())
    {
        QFile sFile(file);
        if (sFile.open(QFile::ReadOnly | QFile::Text))
        {
            mFilename = file;
            QTextStream in(&sFile);
            QString text = in.readAll();
            sFile.close();

            ui->textEdit->setPlainText(text);
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    QFile sFile(mFilename);
    if (sFile.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream out(&sFile);

        out << ui->textEdit->toPlainText();

        sFile.flush();
        sFile.close();
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    QString file = QFileDialog::getSaveFileName(this, "Open a file");

    if (!file.isEmpty())
    {
        mFilename = file;
        on_actionSave_triggered();
    }
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}
