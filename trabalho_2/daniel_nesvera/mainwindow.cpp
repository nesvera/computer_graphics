/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
****************************************************************************/

//Baseado no demo C:\Qt\Qt5.5.1\Examples\Qt-5.5\opengl\qopenglwidget

#include "mainwindow.h"

#include <QApplication>
#include <QMenuBar>
#include <QStatusBar>
#include <QGroupBox>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>
#include <QSpinBox>
#include <QScrollArea>
#include <QMessageBox>
#include <QResizeEvent>
#include <QListWidget>
#include <QGridLayout>
#include <QFormLayout>
#include <QDebug>

#include "control.h"

Canvas2D *canvas;

MainWindow::MainWindow()
{


    //****************************************************
    //cria os Widgets
    //****************************************************

    // Barra de ferramentas lateral
    QPushButton *buttonSelect = new QPushButton("Selecionar");
    QPushButton *buttonLine = new QPushButton("Linha");
    QPushButton *buttonRect = new QPushButton("Retângulo");
    QPushButton *buttonFreeHand = new QPushButton("Mão livre");
    QPushButton *buttonTriangle = new QPushButton("Triângulo");
    QPushButton *buttonCircle = new QPushButton("Círculo");
    QPushButton *buttonPolygon = new QPushButton("Hexágono");
    QPushButton *buttonContorno = new QPushButton("Contorno");
    QPushButton *buttonPreenchimento = new QPushButton("Preenchimento");

    QFormLayout *toolsLayout = new QFormLayout;
    toolsLayout->addRow(new QLabel(tr("")));
    toolsLayout->addRow(buttonSelect);
    toolsLayout->addRow(new QLabel(tr("")));
    toolsLayout->addRow(new QLabel(tr("Formas:")));
    toolsLayout->addRow(buttonLine);
    toolsLayout->addRow(buttonRect);
    toolsLayout->addRow(buttonFreeHand);
    toolsLayout->addRow(buttonTriangle);
    toolsLayout->addRow(buttonCircle);
    toolsLayout->addRow(buttonPolygon);
    toolsLayout->addRow(new QLabel(tr("")));
    toolsLayout->addRow(new QLabel(tr("Propriedades:")));
    toolsLayout->addRow(buttonContorno);
    toolsLayout->addRow(buttonPreenchimento);

    QGroupBox *toolsGroupBox = new QGroupBox(this);
    toolsGroupBox->setLayout(toolsLayout);
    toolsGroupBox->setTitle("Ferramentas");
    toolsGroupBox->setAlignment(Qt::AlignHCenter);

    // Canvas2D
    canvas = new Canvas2D(this);

    //****************************************************
    //cria os Layouts
    //****************************************************
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(toolsGroupBox,  0, 0, 1, 1);  //row, column, rowSpan, colSpan
    gridLayout->addWidget(canvas,         0, 1, 1, 4);

    QGroupBox * groupBox = new QGroupBox(this);
    groupBox->setLayout(gridLayout);
    setCentralWidget(groupBox);



    //****************************************************
    //cria menu
    //****************************************************
    QMenu *fileMenu = menuBar()->addMenu("&File");
    QAction *actNew = new QAction("&New", fileMenu);
    QAction *actOpen = new QAction("&Open", fileMenu);
    QAction *actSave = new QAction("&Save", fileMenu);
    QAction *actExit = new QAction("E&xit", fileMenu);

    fileMenu->addAction(actNew);
    fileMenu->addAction(actOpen);
    fileMenu->addAction(actSave);
    fileMenu->addAction(actExit);

    QMenu *fileHelp = menuBar()->addMenu("&Help");
    QAction *actAbout = new QAction("&About", fileHelp);

    fileHelp->addAction(actAbout);

    //o timer eh usado para controlar o refresh de tela, via SLOT(update()) abaixo. Ele nao faz controle de FPS
    m_timer = new QTimer(this);
    m_timer->setInterval(10);
    m_timer->start();

    //****************************************************
    // Tratamento de eventos de menu, checkbox
    //****************************************************
    connect(m_timer,                SIGNAL(timeout()),         canvas, SLOT(update()));
    connect(actNew,                 SIGNAL(triggered(bool)),   canvas, SLOT(btnNewHandler())   );
    connect(actOpen,                SIGNAL(triggered(bool)),   canvas, SLOT(btnOpenHandler())   );
    connect(actSave,                SIGNAL(triggered(bool)),   canvas, SLOT(btnSaveHandler())   );
    connect(actExit,                SIGNAL(triggered(bool)),   this,   SLOT(close())   );
    connect(actAbout,               SIGNAL(triggered(bool)),   this,   SLOT(aboutHandler())   );
    connect(buttonSelect,           SIGNAL(released()) ,       canvas, SLOT(btnSelectHandler()) );
    connect(buttonLine,             SIGNAL(released()) ,       canvas, SLOT(btnLineHandler()) );
    connect(buttonRect,             SIGNAL(released()) ,       canvas, SLOT(btnRectHandler()) );
    connect(buttonFreeHand,         SIGNAL(released()) ,       canvas, SLOT(btnFreeHandHandler()) );
    connect(buttonTriangle,         SIGNAL(released()) ,       canvas, SLOT(btnTriangleHandler()) );
    connect(buttonCircle,           SIGNAL(released()) ,       canvas, SLOT(btnCircleHandler()) );
    connect(buttonPolygon,          SIGNAL(released()) ,       canvas, SLOT(btnPolygonHandler()) );
    connect(buttonContorno,         SIGNAL(released()) ,       canvas, SLOT(btnContornoHandler()) );
    connect(buttonPreenchimento,    SIGNAL(released()) ,       canvas, SLOT(btnPreenchimentoHandler()) );


}

void MainWindow::checkBoxChanged(bool enabled)
{
    qDebug("Checkbox: %d", enabled );
    if (enabled) {
        m_timer->start();
    } else {
        m_timer->stop();
    }
    refreshRate->setEnabled(enabled);
}

void MainWindow::sliderChanged(int i)
{
    qDebug("Slider: %d", i );
}


void MainWindow::showMsg()
{
    QMessageBox* msg = new QMessageBox(this);
    msg->setText("Msg MainWindow\n Metodo showMsg()");
    msg->show();
}

void MainWindow::aboutHandler(){
    QMessageBox* msg = new QMessageBox(this);
    msg->setText("about");
    msg->show();
}

void MainWindow::updateIntervalChanged(int value)
{
    m_timer->setInterval(value);
    if (m_timer->isActive())
        m_timer->start();
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    //qDebug("janela redimensionada %d", e-> );
    //qDebug() << e->size();
    canvas->setWindowSize(e->size().width(), e->size().height());
}
