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
    ModelRepository::getInstance()->getCANModel()->registerCANModelConnector(&m_CANModel);

    connect(&m_CANModel, &CANUIModel::rowsInserted, this, &CANTraceWindow::canModelChanged);

    ui->setupUi(this);
    this->createLayout();

    /*connect(&m_CANModel,
                SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this,
                SLOT(canModelChanged(QModelIndex,QModelIndex,QVector<int>)));*/
}

/**
 *
 */
CANTraceWindow::~CANTraceWindow()
{
    delete ui;
}

void CANTraceWindow::canModelChanged(const QModelIndex &parent, int first, int last)
{
    m_pTreeView->scrollToBottom();
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

    m_pTreeView->setModel(&m_CANModel);
}
