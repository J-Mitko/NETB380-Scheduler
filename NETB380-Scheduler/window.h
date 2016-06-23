#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QString>
#include <chromosome.h>
#include <QTabWidget>

class window : public QMainWindow
{
    Q_OBJECT
public:
    explicit window(QWidget *parent = 0);

    ~window();

    QStringList login_window();

    void display_Table(Chromosome result);

private:
    QStandardItemModel *model;
    QTabWidget* tabs;

signals:

private slots:
};

#endif // WINDOW_H
