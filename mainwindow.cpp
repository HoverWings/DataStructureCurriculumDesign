#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setcomBox();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setcomBox()
{

}



