#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include"sub_window.h"


extern int num;
extern int ch;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->QLineEdit_Process_Num->setPlaceholderText("input number...");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Input_clicked()
{
    QString text=ui->QLineEdit_Process_Num->text();
    num=text.toInt();
    //QMessageBox::information(this,"my",text);
    if(num==0||num<4||num>10)
    {
        QMessageBox::warning(this,"Waring","You input a wrong number!");
    }
    else
    {
        sub_window sub_window;
        sub_window.setModal(true);
        sub_window.exec();
    }
}


