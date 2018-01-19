/*
#-------------------------------------------------
#
#Project created by DeepGlint 2018-01-05T11:32:25
#@CopyRight:A-Lin Hu
#-------------------------------------------------*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<QSound>
#include <QMap>
#include<QFileSystemWatcher>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //static void watchpath(QString path);



//Add private slots
private slots:



        void showMessage(const QString &path);
        void timerUpdate1();
        void timerUpdate2();

private:
    Ui::MainWindow *ui;
    QFileSystemWatcher myWatcher;
    QMap<QString,QStringList> currentContent;
    QSound *sound;
;

};

#endif // MAINWINDOW_H
