#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gradecalculator.hh"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBoxE->setMinimum(0);
    ui->spinBoxE->setMaximum(1000);

    ui->spinBoxG->setMinimum(0);
    ui->spinBoxG->setMaximum(120);

    ui->spinBoxN->setMinimum(0);
    ui->spinBoxN->setMaximum(1000);

    ui->spinBoxP->setMinimum(0);
    ui->spinBoxP->setMaximum(1000);

    // Connect signals to slots
    connect(ui->spinBoxN, SIGNAL(valueChanged(int)), this, SLOT(on_spinBoxN_valueChanged(int)));
    connect(ui->spinBoxG, SIGNAL(valueChanged(int)), this, SLOT(on_spinBoxG_valueChanged(int)));
    connect(ui->spinBoxP, SIGNAL(valueChanged(int)), this, SLOT(on_spinBoxP_valueChanged(int)));
    connect(ui->spinBoxE, SIGNAL(valueChanged(int)), this, SLOT(on_spinBoxE_valueChanged(int)));
    connect(ui->calculatePushButton, SIGNAL(clicked()), this, SLOT(on_calculatePushButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calculatePushButton_clicked()
{
    int nScore = ui->spinBoxN->value();
    int gScore = ui->spinBoxG->value();
    int pScore = ui->spinBoxP->value();
    int eScore = ui->spinBoxE->value();

    int totalGrade = calculate_total_grade(nScore, gScore, pScore, eScore);

    QString result = "W-Score: " + QString::number(score_from_weekly_exercises(nScore, gScore)) + "\n"
                     "P-Score: " + QString::number(score_from_projects(pScore)) + "\n"
                     "Total grade: " + QString::number(totalGrade);

    ui->textBrowser->setText(result);
}

void MainWindow::on_spinBoxN_valueChanged(int value)
{
    ui->spinBoxN->setValue(value);
}

void MainWindow::on_spinBoxG_valueChanged(int value)
{
    ui->spinBoxG->setValue(value);
}

void MainWindow::on_spinBoxP_valueChanged(int value)
{
    ui->spinBoxP->setValue(value);
}

void MainWindow::on_spinBoxE_valueChanged(int value)
{
    ui->spinBoxE->setValue(value);
}
