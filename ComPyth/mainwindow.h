#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <QKeyEvent>
#include <QEvent>
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow *ui;

    void getLine();

    void addLine(std::string n_string);

    std::string n_line;

    void addLineBlue(std::string n_string);

private slots:
    void on_actionNew_triggered();

    void on_actionCopy_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionShow_Creators_triggered();

private:
    QString mFilename;

};

#endif // MAINWINDOW_H
