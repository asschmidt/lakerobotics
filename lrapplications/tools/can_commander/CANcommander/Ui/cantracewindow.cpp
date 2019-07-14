/*
 * cantracewindow.cpp
 *
 *  Created on: 10.07.2019
 *      Author: Andreas
 */

// Qt includes
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QToolbar>
#include <QtWidgets/QAction>

// Project includes
#include "cantracewindow.h"
#include "ui_cantracewindow.h"

/**
 *
 */
CANTraceWindow::CANTraceWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CANTraceWindow)
{
    ui->setupUi(this);
    this->createLayout();
}

/**
 *
 */
CANTraceWindow::~CANTraceWindow()
{
    delete ui;
}

/**
 *
 */
void CANTraceWindow::createLayout()
{
    QVBoxLayout* pLayout = new QVBoxLayout(this);

    QToolBar* pToolbar = new QToolBar();

    m_pTreeView = new QTreeView();

    pLayout->addWidget(pToolbar);
    pLayout->addWidget(m_pTreeView);

    this->setLayout(pLayout);
}
