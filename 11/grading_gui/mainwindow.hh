#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include "gradecalculator.hh"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void on_spinBoxN_valueChanged(int value);
    void on_spinBoxG_valueChanged(int value);
    void on_spinBoxP_valueChanged(int value);
    void on_spinBoxE_valueChanged(int value);
    void on_calculatePushButton_clicked();
};
#endif // MAINWINDOW_HH
