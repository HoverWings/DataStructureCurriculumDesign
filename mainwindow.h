#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QAxObject>
#include <QVariant>
#include "readexcel.h"
#include <QDebug>
#include "excelengine.h"


namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_chooseStudentButton_clicked();

    void on_loadStudentButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
