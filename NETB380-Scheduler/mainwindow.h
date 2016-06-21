#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QString>
#include <schedule.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Schedule result,QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_doubleClicked(const QModelIndex &index);
    void swap(QModelIndex field1, QModelIndex field2);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QModelIndex field1;
    QModelIndex field2;
    QString tmp;
};

#endif // MAINWINDOW_H
