#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QString>
#include <chromosome.h>
#include <QTabWidget>
#include <QProgressBar>
#include <QMessageBox>

class window : public QMainWindow
{
    Q_OBJECT
public:
    explicit window(QWidget *parent = 0);

    ~window();

    QStringList login_window();

    void display_Table(Chromosome result, int i);

    void display_settings_window();

    void set_max(int x);

    int get_max();

    void set_gen(int x);

    int get_gen();

    void set_num(int x);

    int get_num();

private:
    QStandardItemModel *model;
    QTabWidget* tabs;
    QProgressBar* progressBar;
    int max,gen,num;


protected:
signals:

private slots:
};

#endif // WINDOW_H
