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
#include <QDoubleSpinBox>

Canvas2D *canvas;

MainWindow::MainWindow()
{

    //****************************************************
    //cria os Widgets
    //****************************************************

    // Barra de ferramentas lateral
    QCheckBox *virabrequimCheckBox = new QCheckBox("Virabrequim", this);
    QCheckBox *blocoCheckBox = new QCheckBox("Bloco", this);
    QCheckBox *camisaCheckBox = new QCheckBox("Camisa", this);
    QCheckBox *pistaoCheckBox = new QCheckBox("Pistão", this);
    QCheckBox *bielaCheckBox = new QCheckBox("Biela", this);

    QDoubleSpinBox *rpmSpinBox = new QDoubleSpinBox(this);
    rpmSpinBox->setSuffix(" rps");
    rpmSpinBox->setValue(0);
    rpmSpinBox->setSingleStep(0.1);
    rpmSpinBox->setMaximum(10);
    rpmSpinBox->setToolTip("Altera rotação do motor");

    QFormLayout *toolsLayout = new QFormLayout;
    toolsLayout->addRow(new QLabel(tr("Habilitar Visualização")));
    toolsLayout->addRow(virabrequimCheckBox);
    toolsLayout->addRow(blocoCheckBox);
    toolsLayout->addRow(camisaCheckBox);
    toolsLayout->addRow(pistaoCheckBox);
    toolsLayout->addRow(bielaCheckBox);
    toolsLayout->addRow(new QLabel(tr("")));
    toolsLayout->addRow(new QLabel(tr("Rotação por segundo")));
    toolsLayout->addRow(rpmSpinBox);
    toolsLayout->setAlignment(rpmSpinBox, Qt::AlignCenter);

    QGroupBox *toolsGroupBox = new QGroupBox(this);
    toolsGroupBox->setLayout(toolsLayout);
    //toolsGroupBox->setTitle("Ferramentas");
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
    QAction *actExit = new QAction("E&xit", fileMenu);

    fileMenu->addAction(actExit);

    QMenu *fileHelp = menuBar()->addMenu("&Help");
    QAction *actAbout = new QAction("&About", fileHelp);

    fileHelp->addAction(actAbout);

    //o timer eh usado para controlar o refresh de tela, via SLOT(update()) abaixo. Ele nao faz controle de FPS
    m_timer = new QTimer(this);
    m_timer->setInterval(20);
    m_timer->start();

    //****************************************************
    // Tratamento de eventos de menu, checkbox
    //****************************************************
    connect(m_timer,                SIGNAL(timeout()),         canvas, SLOT(update()));
    connect(actExit,                SIGNAL(triggered(bool)),   this,   SLOT(close())   );
    connect(actAbout,               SIGNAL(triggered(bool)),   this,   SLOT(aboutHandler())   );
    connect(virabrequimCheckBox,    SIGNAL(clicked(bool)),     canvas, SLOT(virabrequimCheckBoxChanged(bool)));
    connect(blocoCheckBox,          SIGNAL(clicked(bool)),     canvas, SLOT(blocoCheckBoxChanged(bool)));
    connect(camisaCheckBox,         SIGNAL(clicked(bool)),     canvas, SLOT(camisaCheckBoxChanged(bool)));
    connect(pistaoCheckBox,         SIGNAL(clicked(bool)),     canvas, SLOT(pistaoCheckBoxChanged(bool)));
    connect(bielaCheckBox,          SIGNAL(clicked(bool)),     canvas, SLOT(bielaCheckBoxChanged(bool)));
    connect(rpmSpinBox,             SIGNAL(valueChanged(double)), canvas, SLOT(rpmSpinBoxChanged(double)));

    //exemplo
    //connect(buttonPreenchimento,    SIGNAL(released()) ,       canvas, SLOT(btnPreenchimentoHandler()) );


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
