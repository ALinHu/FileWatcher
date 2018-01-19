/*
#-------------------------------------------------
#
#Project created by DeepGlint 2018-01-05T11:32:25
#@CopyRight:A-Lin Hu
#-------------------------------------------------*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QTime>
#include <QTimer>
#include <QSound>
#include <QMessageBox>
#include <QFileDialog>
#include<QFileSystemWatcher>
#include <QTextStream>

QString path = "/home/deepglint/ftp_svr_dir/1262842983";
QString dspath = "/home/deepglint/ftp_svr_dir/1262842983/q";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sound = new QSound("/home/deepglint/Music/189.wav",this);

    QTimer *timer1 = new QTimer(this);
    connect(timer1,&QTimer::timeout,this,&MainWindow::timerUpdate1);
    timer1->start(1000);

    QTimer *timer2 = new QTimer(this);
    connect(timer2,&QTimer::timeout,this,&MainWindow::timerUpdate2);
    timer2->start(60000);

    connect(&myWatcher, SIGNAL(directoryChanged(QString)),
            this, SLOT(showMessage(QString)));
    //add path to watching
    QDir myDir(path);
    myWatcher.addPath(path);
    QFileInfo file(path);
    if(file.isDir())
    {
        currentContent[path] =myDir.entryList(QDir::NoDotAndDotDot |
                                            QDir::AllDirs | QDir::Files, QDir::DirsFirst);
    }
}




MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::showMessage(const QString &path)
{
    QDir dir(path);
    //find the changes of file
    QStringList currEntryList = currentContent[path];
    QStringList newEntryList = dir.entryList(QDir::NoDotAndDotDot  |
                                              QDir::AllDirs | QDir::Files, QDir::DirsFirst);
    QSet<QString> curDirSet = QSet<QString>::fromList(currEntryList);
    QSet<QString> newDirSet = QSet<QString>::fromList(newEntryList);
    QSet<QString> newFiles = newDirSet - curDirSet;
    QStringList newFile = newFiles.toList();

    currentContent[path] = newEntryList;
    if(!newFile.isEmpty())
    {
         sound->play();
         int cnn = newFile.count();
         for(int i =0;i < cnn;i++)
         {
             QFileInfo infofile = newFile.at(i);
             QString newfilename =path + "/" + infofile.fileName();
             QFileInfo info(newfilename);
             QString imageTime;
             imageTime += tr("访问时间: %1 \n").arg(info.created().toString("yyyy-MM-dd hh:mm:ss"));
             ui->listWidget->addItem(imageTime);

             QFile TEXT("/home/deepglint/ftp_svr_dir/myfile.TEXT");
             if(TEXT.open(QFile::WriteOnly | QFile::Append))
             {
                 QTextStream out(&TEXT);
                 out<<center<<imageTime<<endl;
             }
             TEXT.close();
         }
    }
}

void MainWindow::timerUpdate1()
{
    //------display one picture------//
    {
        QLabel *a[6];
        a[0] = ui->label_1;
        a[1] = ui->label_2;
        a[2] = ui->label_3;
        a[3] = ui->label_4;
        a[4] = ui->label_5;
        a[5] = ui->label_6;

        QDir Dir(path);
        QStringList excludeFiles;
        Dir.setFilter(QDir::Files);
        QFileInfoList List = Dir.entryInfoList();
        int sum = List.count();
        for(int k = 0;k < sum && k < 6;k++)
        {
            QFileInfo fileInfo = List.at(k);
            QString fileName = fileInfo.fileName();
            if(excludeFiles.indexOf(fileName)!= -1)
                continue;
            QString newSrcFileName = path + "/" + fileInfo.fileName();
                QImage* img = new QImage;
                if(!(img->load(newSrcFileName)))
                {
                    QMessageBox::information(this,tr("can't open image"),tr("can't open image!"));
                    delete img;
                    return;
                }
                a[k]->setPixmap(QPixmap::fromImage(*img));
        }
    }
}

void MainWindow::timerUpdate2()
{
    //------copy and delete dir------//
    QDir dir(path);
    QStringList excludeFiles;
    dir.setFilter(QDir::Files);
    QFileInfoList list = dir.entryInfoList();
    int count = list.count();
    for (int i = 0;i < count;i++)
    {
        QFileInfo fileInfo = list.at(i);
        QString fileName = fileInfo.fileName();
        if(excludeFiles.indexOf(fileName)!= -1)
            continue;
        if(!dir.exists(dspath))
            dir.mkpath(dspath);
        QString newSrcFileName = path + "/" + fileInfo.fileName();
        QString newDstFileName = dspath+ "/" + fileInfo.fileName();
       QFile(newSrcFileName).copy(newDstFileName);
    }
    for (int j = 0;j< count;j++)
        dir.remove(dir[j]);
}

        /*
        //------sleep(6)------//
        QDateTime n2=QDateTime::currentDateTime();
          QDateTime now;
          do{
          now=QDateTime::currentDateTime();
          } while(n2.secsTo(now)<=6);//6为需要延时的秒数

        //------delect dir------//
        {
        int i,j=dir.count()-1;
            for(i=0;i<=j;i++)
                dir.remove(dir[i]);
        }
        //------paly music------//
        QDir temDir("/home/deepglint/Music/9374.wav");
        //QDir temDir("/home/deepglint/Music/9375.wav");
        QString absDir = temDir.absolutePath();
        QSound bell(absDir);
        bell.play();
         */
/*
//add code to copy dir//
QStringList excludeFiles;
dir.setFilter(QDir::Files);
QFileInfoList list = dir.entryInfoList();
int count = list.count();
for (int i = 0;i < count;i++)
{
    QFileInfo fileInfo = list.at(i);
    QString fileName = fileInfo.fileName();
    if(excludeFiles.indexOf(fileName)!= -1)
        continue;
    if(!dir.exists(dspath))
        dir.mkpath(dspath);
    QString newSrcFileName = path + "/" + fileInfo.fileName();
    QString newDstFileName = dspath+ "/" + fileInfo.fileName();
   QFile(newSrcFileName).copy(newDstFileName);
}
for (int j = 0;j< count;j++)
    dir.remove(dir[j]);
*/
/*
QString filename("/home/deepglint/w/666.jpg");
    QImage* img=new QImage;
    if(! ( img->load(filename) ) ) //加载图像
    {
        QMessageBox::information(this,
                                 tr("打开图像失败"),
                                 tr("打开图像失败!"));
        delete img;
        return;
    }
    a[0]->setPixmap(QPixmap::fromImage(*img));
    //ui->label_5->setPixmap(QPixmap::fromImage(*img));
    */

/*
//------display one picture------//
{
    QLabel *a[6];
    a[0] = ui->label_1;
    a[1] = ui->label_2;
    a[2] = ui->label_3;
    a[3] = ui->label_4;
    a[4] = ui->label_5;
    a[5] = ui->label_6;
    QString Src = "/home/deepglint/Pictures/2";
    QDir Dir(Src);
    QStringList excludeFiles;
    Dir.setFilter(QDir::Files);
    QFileInfoList List = Dir.entryInfoList();
    int sum = List.count();
    for(int k = 0;k < sum && k < 6;k++)
    {
        QFileInfo fileInfo = List.at(k);
        QString fileName = fileInfo.fileName();
        if(excludeFiles.indexOf(fileName)!= -1)
            continue;
        QString newSrcFileName = Src + "/" + fileInfo.fileName();
            QImage* img = new QImage;
            if(!(img->load(newSrcFileName)))
            {
                QMessageBox::information(this,tr("打开图像失败"),tr("打开图像失败!"));
                delete img;
                return;
            }
            a[k]->setPixmap(QPixmap::fromImage(*img));
    }
}
*/

