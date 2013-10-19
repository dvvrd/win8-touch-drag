#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWidgets/QVBoxLayout>

#include "touchdragwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(new TouchDragWidget);
    ui->centralWidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
