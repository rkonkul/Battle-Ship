/*
Ryan Konkul - rkonku2
Scott Prentice - sprent2
CS 340
Project 5: Mine Sweeper
12/1/2011
*/

#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
