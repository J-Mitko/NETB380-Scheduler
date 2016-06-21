#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QGridLayout>

MainWindow::MainWindow(Schedule result, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Scheduler");

    QGridLayout *layout =   new QGridLayout;

    model = new QStandardItemModel(6,6,this);
    model->setHorizontalHeaderLabels(QStringList() << "Monday" << "Tuesday" << "Wensday" << "Thursday" << "Friday" << "Saturday");
    model->setVerticalHeaderLabels(QStringList() << "8:00-9:30" << "9:40-11:10" << "11:20-12:50" << "13:00-14:30" << "14:40-16:10" << "16:20-17:50");


           result.print_schedule(model);

    ui->tableView->setLayout(layout);
    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    field1 = index;
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    field2 = index;
    swap(field1,field2);
}

void MainWindow::swap(QModelIndex field1, QModelIndex field2)
{
    qDebug() << "swapped";
    tmp=field1.data().toString();
    model->setData(field1,field2.data().toString());
    model->setData(field2,tmp);
}
