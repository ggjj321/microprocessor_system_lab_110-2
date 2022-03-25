#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_2->close();
    ui->label_3->close();
    ui->label_4->close();
    ui->label_5->close();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    if(ui->checkBox->isChecked()==true){
        ui->label_2->show();
    }else{
        ui->label_2->close();
    }

    if(ui->checkBox_2->isChecked()==true){
        ui->label_3->show();
    }else{
        ui->label_3->close();
    }

    if(ui->checkBox_3->isChecked()==true){
        ui->label_4->show();
    }else{
        ui->label_4->close();
    }

    if(ui->checkBox_4->isChecked()==true){
        ui->label_5->show();
    }else{
        ui->label_5->close();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    shiningTime = 0;
    QString content = ui->textEdit->toPlainText();
    timeLimit = content.toInt() * 2 - 1;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(led_shining()));
    timer->start(1000);
}

void MainWindow::led_shining(){
    if(shiningTime == timeLimit){
        timer->stop();
    }
    if(shiningTime % 2 == 0){
        ui->label_2->show();
        ui->label_3->show();
        ui->checkBox->setChecked(true);
        ui->checkBox_2->setChecked(true);

        ui->label_4->close();
        ui->label_5->close();
        ui->checkBox_3->setChecked(false);
        ui->checkBox_4->setChecked(false);
    }else if(shiningTime % 2 == 1){
        ui->label_2->close();
        ui->label_3->close();
        ui->checkBox->setChecked(false);
        ui->checkBox_2->setChecked(false);

        ui->label_4->show();
        ui->label_5->show();
        ui->checkBox_3->setChecked(true);
        ui->checkBox_4->setChecked(true);
    }
    shiningTime += 1;
}















