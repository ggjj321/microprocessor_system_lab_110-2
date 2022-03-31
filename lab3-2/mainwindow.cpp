#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include "export.h"
#include "direction.h"
#include "value.h"
#include "unexport.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_2->close();
    ui->label_3->close();
    ui->label_4->close();
    ui->label_5->close();

//    gpio_export(396); // led1
//    gpio_set_dir(396, "out");
//    gpio_set_value(396, 0);

//    gpio_export(397); // led2
//    gpio_set_dir(397, "out");
//    gpio_set_value(397, 0);

//    gpio_export(429); // led3
//    gpio_set_dir(429, "out");
//    gpio_set_value(429, 0);

//    gpio_export(427); // led4
//    gpio_set_dir(427, "out");
//    gpio_set_value(427, 0);
}

MainWindow::~MainWindow()
{
//    gpio_unexport(396); // led1
//    gpio_unexport(397); // led2
//    gpio_unexport(429); // led3
//    gpio_unexport(427); // led4
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    if(ui->checkBox->isChecked()==true){ // Led1
        ui->label_2->show();
        gpio_set_value(396, 1);
    }else{
        ui->label_2->close();
        gpio_set_value(396, 0);
    }

    if(ui->checkBox_2->isChecked()==true){ // Led2
        ui->label_3->show();
        gpio_set_value(396, 1);
    }else{
        ui->label_3->close();
        gpio_set_value(396, 0);
    }

    if(ui->checkBox_3->isChecked()==true){ // Led3
        ui->label_4->show();
        gpio_set_value(396, 1);
    }else{
        ui->label_4->close();
        gpio_set_value(396, 0);
    }

    if(ui->checkBox_4->isChecked()==true){ // Led4
        ui->label_5->show();
        gpio_set_value(396, 1);
    }else{
        ui->label_5->close();
        gpio_set_value(396, 0);
    }
}


void MainWindow::on_switchOnButton_clicked()
{
    shiningTime = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(led_shining()));
    timer->start(5 * (100 - ui->spinBox->value()));
}

void MainWindow::led_shining(){
    timer->setInterval(5 * (100 - ui->spinBox->value()));
    if(shiningTime % 2 == 0){
        ui->label_2->show();
        ui->label_3->show();
        ui->checkBox->setChecked(true);
        ui->checkBox_2->setChecked(true);

        ui->label_4->close();
        ui->label_5->close();
        ui->checkBox_3->setChecked(false);
        ui->checkBox_4->setChecked(false);

        gpio_set_value(396, 1); // Led1
        gpio_set_value(396, 1); // Led2
        gpio_set_value(396, 0); // Led3
        gpio_set_value(396, 0); // Led4
    }else if(shiningTime % 2 == 1){
        ui->label_2->close();
        ui->label_3->close();
        ui->checkBox->setChecked(false);
        ui->checkBox_2->setChecked(false);

        ui->label_4->show();
        ui->label_5->show();
        ui->checkBox_3->setChecked(true);
        ui->checkBox_4->setChecked(true);

        gpio_set_value(396, 1); // Led1
        gpio_set_value(396, 1); // Led2
        gpio_set_value(396, 0); // Led3
        gpio_set_value(396, 0); // Led4
    }
    shiningTime += 1;
}

void MainWindow::on_switchOffButton_clicked()
{
    timer->stop();
    shiningTime = 0;
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Right){
        ui->horizontalSlider->valueChanged(ui->horizontalSlider->value()+1);
    }else if(event->key() == Qt::Key_Left){
        ui->horizontalSlider->valueChanged(ui->horizontalSlider->value()-11);
    }
}
