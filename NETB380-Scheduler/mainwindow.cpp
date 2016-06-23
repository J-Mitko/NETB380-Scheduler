#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>


MainWindow::MainWindow( QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Scheduler");
}

MainWindow::~MainWindow()
{
    delete ui;
}

QStringList MainWindow::login_window()
{
    QDialog *inputPanel = new QDialog(this);
    QFormLayout *form = new QFormLayout(inputPanel);
    QLabel *ip = new QLabel("IP Address :",inputPanel);
    QLineEdit *ipInput = new QLineEdit("LOCALHOST",inputPanel);
    form->addRow(ip,ipInput);

    QLabel *dbname = new QLabel("DataBase Name :",inputPanel);
    QLineEdit *dbInput = new QLineEdit("courseinfo",inputPanel);
    form->addRow(dbname,dbInput);

    QLabel *userName = new QLabel("Username :",inputPanel);
    QLineEdit *userNameInput = new QLineEdit("postgres",inputPanel);
    form->addRow(userName,userNameInput);

    QLabel *password = new QLabel("Password :",inputPanel);
    QLineEdit *passInput = new QLineEdit("admin",inputPanel);
    passInput->setEchoMode(QLineEdit::Password);
    form->addRow(password,passInput);

    QPushButton *connect_btn = new QPushButton(inputPanel);
    connect_btn->setText("Connect to Database");
    connect_btn->connect(connect_btn,SIGNAL(clicked()),inputPanel,SLOT(close()));
    form->addRow(connect_btn);

    inputPanel->exec();

    return QStringList() << ipInput->text() << dbInput->text() << userNameInput->text() << passInput->text();
}

void MainWindow::display_Table(Chromosome result)
{
    model = new QStandardItemModel(6,6,this);
    model->setHorizontalHeaderLabels(QStringList() << "Monday" << "Tuesday" << "Wensday" << "Thursday" << "Friday" << "Saturday");
    model->setVerticalHeaderLabels(QStringList() << "8:00-9:30" << "9:40-11:10" << "11:20-12:50" << "13:00-14:30" << "14:40-16:10" << "16:20-17:50");

    result.get_best_chromosome().print_schedule(model);

    ui->tableView->setModel(model);
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
