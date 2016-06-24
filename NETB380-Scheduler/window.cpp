#include "window.h"
#include <QDialog>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>

#include <QDebug>

window::window(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowTitle("Scheduler");

    tabs = new QTabWidget(this);
    this->setCentralWidget(tabs);

}

window::~window()
{
    delete this;
    delete tabs;
}

void window::set_max(int x)
{
    this->max = x;
}

int window::get_max()
{
    return this->max;
}

void window::set_gen(int x)
{
    this->gen = x;
}

int window::get_gen()
{
    return this->gen;
}

void window::set_num(int x)
{
    this->num = x;
}

int window::get_num()
{
    return this->num;
}

QStringList window::login_window()
{
    QDialog *inputPanel = new QDialog(this);
    QFormLayout *form = new QFormLayout(inputPanel);
    QLabel *ip = new QLabel("IP Address :",inputPanel);
    QLineEdit *ipInput = new QLineEdit("LOCALHOST",inputPanel);
    form->addRow(ip,ipInput);

    QLabel *dbname = new QLabel("DataBase Name :",inputPanel);
    QLineEdit *dbInput = new QLineEdit("scheduler",inputPanel);
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
void window::display_settings_window()
{
    QDialog *settingsPanel = new QDialog(this);
    QFormLayout *form = new QFormLayout(settingsPanel);
    QLabel *maxgen_label = new QLabel("Number of Schedules the best would be choosen",settingsPanel);
    QLineEdit *maxgen_Input = new QLineEdit("2550",settingsPanel);
    form->addRow(maxgen_label,maxgen_Input);

    QLabel *gen_label = new QLabel("Number of defications done per Schedule",settingsPanel);
    QLineEdit *gen_Input = new QLineEdit("250",settingsPanel);
    form->addRow(gen_label,gen_Input);

    QLabel *displayed_label = new QLabel("Number of Schedules you would like displayed :",settingsPanel);
    QLineEdit *displayed_Input = new QLineEdit("1",settingsPanel);
    form->addRow(displayed_label,displayed_Input);

    QPushButton *start_btn = new QPushButton(settingsPanel);
    start_btn->setText("Start");
    start_btn->connect(start_btn,SIGNAL(clicked()),settingsPanel,SLOT(close()));
    form->addRow(start_btn);

    settingsPanel->exec();
    this->set_max(maxgen_Input->text().toInt());
    this->set_gen(gen_Input->text().toInt());
    this->set_num(displayed_Input->text().toInt());
}

void window::display_Table(Chromosome result, int i)
{
    QTableWidget* tableW= new QTableWidget(6,7,tabs);

    tableW->setHorizontalHeaderLabels(QStringList() << "Monday" << "Tuesday" << "Wensday" << "Thursday" << "Friday" << "Saturday" << "Sunday");
    tableW->setVerticalHeaderLabels(QStringList() << "8:00-9:30" << "9:40-11:10" << "11:20-12:50" << "13:00-14:30" << "14:40-16:10" << "16:20-17:50");

    result.get_best_chromosome().print_schedule(tableW);
    tableW->resizeRowsToContents();

    tableW->setAlternatingRowColors(true);
    tableW->setDragEnabled(true);
    tableW->setAcceptDrops(true);
    tableW->setDropIndicatorShown(true);
    tableW->setDragDropOverwriteMode(false);
    tableW->setDragDropMode(QAbstractItemView::InternalMove);
    tableW->setWordWrap(true);

    tabs->addTab(tableW,QString("Schedule %1").arg(i));
    this->resize(tableW->columnWidth(0)*8,tableW->rowHeight(0)*7);
}
