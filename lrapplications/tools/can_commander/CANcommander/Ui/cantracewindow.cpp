/*
 * cantracewindow.cpp
 *
 *  Created on: 10.07.2019
 *      Author: Andreas
 */

// Standard includes
#include <iostream>

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
    ModelRepository::getInstance()->getCANModel()->registerCANModelConnector(&m_SingleCANModel);

    connect(&m_CANModel, &CANUIBaseModel::rowsInserted, this, &CANTraceWindow::canModelChanged);

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
void CANTraceWindow::canModelChanged(const QModelIndex &parent, int first, int last)
{
    if (m_CANModel.isUsingAutoScroll() == true)
    {
        m_pTreeView->scrollToBottom();
    }
}

/**
 *
 */
void CANTraceWindow::createActions()
{
    m_pShowDeltaTAction = new QAction(this);
    QPixmap* pShowDeltaTIcon = new QPixmap(":/Images/view_delta_t.png");
    m_pShowDeltaTAction->setCheckable(true);
    m_pShowDeltaTAction->setIcon(*pShowDeltaTIcon);
    connect(m_pShowDeltaTAction, SIGNAL(triggered()), this, SLOT(actShowDeltaT()));

    m_pShowScrollModeAction = new QAction(this);
    QPixmap* pShowScrollModeIcon = new QPixmap(":/Images/view_scroll_mode.png");
    m_pShowScrollModeAction->setIcon(*pShowScrollModeIcon);
    m_pShowScrollModeAction->setCheckable(true);
    connect(m_pShowScrollModeAction, SIGNAL(triggered()), this, SLOT(actShowScrollMode()));

    m_pShowHexAction = new QAction(this);
    QPixmap* pShowHexIcon = new QPixmap(":/Images/view_dec_hex.png");
    m_pShowHexAction->setIcon(*pShowHexIcon);
    m_pShowHexAction->setCheckable(true);
    connect(m_pShowHexAction, SIGNAL(triggered()), this, SLOT(actShowHex()));

    m_pShowSingleMessagesAction = new QAction(this);
    QPixmap* m_pShowSingleMessagesIcon = new QPixmap(":/Images/view_scroll_mode.png");
    m_pShowSingleMessagesAction->setIcon(*pShowScrollModeIcon);
    m_pShowSingleMessagesAction->setCheckable(true);
    connect(m_pShowSingleMessagesAction, SIGNAL(triggered()), this, SLOT(actShowSingleMessages()));

}

/**
 *
 */
QToolBar* CANTraceWindow::createToolbar()
{
    QToolBar* pToolbar = new QToolBar();
    pToolbar->setIconSize(QSize(16, 16));

    pToolbar->addAction(m_pShowDeltaTAction);
    pToolbar->addAction(m_pShowScrollModeAction);
    pToolbar->addAction(m_pShowHexAction);
    pToolbar->addAction(m_pShowSingleMessagesAction);

    return pToolbar;
}

/**
 *
 */
void CANTraceWindow::createLayout()
{
    QVBoxLayout* pLayout = new QVBoxLayout(this);

    createActions();

    QToolBar* pToolbar = createToolbar();
    pLayout->addWidget(pToolbar);

    m_pTreeView = new QTreeView();
    m_pTreeView->setModel(&m_CANModel);

    CANTraceDelegate* pDelegate = new CANTraceDelegate();
    m_pTreeView->setItemDelegate(pDelegate);
    pLayout->addWidget(m_pTreeView);

    this->setLayout(pLayout);
}

/**
 *
 */
void CANTraceWindow::actShowHex()
{
    m_CANModel.setUsingHexDisplay(m_pShowHexAction->isChecked());
    m_CANModel.submit();
}

/**
 *
 */
void CANTraceWindow::actShowDeltaT()
{
    m_CANModel.setUsingDeltaTDisplay(m_pShowDeltaTAction->isChecked());
    m_CANModel.submit();
}

/**
 *
 */
void CANTraceWindow::actShowScrollMode()
{
    m_CANModel.setUsingAutoScroll(m_pShowScrollModeAction->isChecked());
    m_CANModel.submit();
}

/**
 *
 */
void CANTraceWindow::actShowSingleMessages()
{
    if (m_pShowSingleMessagesAction->isChecked())
    {
        m_pTreeView->setModel(&m_SingleCANModel);
    }
    else
    {
        m_pTreeView->setModel(&m_CANModel);
    }
}

/**
 *
 */
void CANTraceDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem optCopy = option;

    if (index.column() == 3)
    {
        optCopy.font.setFamily(QString("Courier New"));
    }

    QStyledItemDelegate::paint(painter, optCopy, index);
}
