#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect signals and slots
    connect(ui->countButton, SIGNAL(clicked()), this, SLOT(on_countButton_clicked()));
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->weightLineEdit, SIGNAL(editingFinished()), this, SLOT(on_weightLineEdit_editingFinished()));
    connect(ui->heightLineEdit, SIGNAL(editingFinished()), this, SLOT(on_heightLineEdit_editingFinished()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_weightLineEdit_editingFinished()
{
    ui->weightLineEdit->text();

}


void MainWindow::on_heightLineEdit_editingFinished()
{
    ui->heightLineEdit->text();

}


void MainWindow::on_countButton_clicked()
{
    QString weightStr = ui->weightLineEdit->text();
    QString heightStr = ui->heightLineEdit->text();

    bool ok;
    float weight = weightStr.toFloat(&ok);
    float height = heightStr.toFloat(&ok);

    if (height == 0) {
        // Handle division by zero
        ui->resultLabel->setText("Cannot count");
        ui->infoTextBrowser->clear();
    } else {
        // Calculate BMI
        float bmi = weight / ((height/100) * (height/100));

        // Update resultLabel
        ui->resultLabel->setText(QString("%1").arg(bmi));

        // Update infoTextBrowser
        if (bmi < 18.5)
            ui->infoTextBrowser->setText("Underweight");
        else if (bmi >= 18.5 && bmi <= 25)
            ui->infoTextBrowser->setText("Normal range");
        else
            ui->infoTextBrowser->setText("Overweight");
    }
}



