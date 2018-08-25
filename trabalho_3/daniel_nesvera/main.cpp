/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
****************************************************************************/

#include <QApplication>
#include <QMainWindow>
#include "mainwindow.h"

//Baseado no demo C:\Qt\Qt5.5.1\Examples\Qt-5.5\opengl\qopenglwidget

int main( int argc, char ** argv )
{
    QApplication a( argc, argv );

    MainWindow mw;
    mw.setMinimumSize(1280,720);
    mw.resize(1280,720);

    mw.show();

    return a.exec();
}
