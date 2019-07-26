/*
 * cantracewindow.h
 *
 *  Created on: 10.07.2019
 *      Author: Andreas
 */

#ifndef CANTRACEWINDOW_H
#define CANTRACEWINDOW_H

// Qt includes
#include <QtWidgets/QWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QStyledItemDelegate>
#include <QtWidgets/QAction>
#include <QtWidgets/QToolbar>

// Project includes
#include "Model/CAN/CANMessageObject.h"
#include "Model/CAN/CANModel.h"
#include "Model/CAN/CANUiBaseModel.h"
#include "Model/ModelRepository.h"

namespace Ui {
class CANTraceWindow;
}

/**
 *
 */
class CANTraceWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit CANTraceWindow(QWidget *parent = nullptr);
        ~CANTraceWindow();

    private:
        void createActions();
        QToolBar* createToolbar();
        void createLayout();

        void canModelChanged(const QModelIndex &parent, int first, int last);

    private slots:
        void actShowHex();
        void actShowDeltaT();
        void actShowScrollMode();

    private:
        Ui::CANTraceWindow *ui;

        QAction* m_pShowDeltaTAction;
        QAction* m_pShowScrollModeAction;
        QAction* m_pShowHexAction;

        QTreeView* m_pTreeView;
        CANUIBaseModel m_CANModel;
};

/**
 *
 */
class CANTraceDelegate : public QStyledItemDelegate
{
    public:
        void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // CANTRACEWINDOW_H
