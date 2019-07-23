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

// Project includes
#include "Model/CAN/CANMessageObject.h"
#include "Model/CAN/CANModel.h"
#include "Model/CAN/CANUiModel.h"

#include "Model/ModelRepository.h"

namespace Ui {
class CANTraceWindow;
}

class CANTraceWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit CANTraceWindow(QWidget *parent = nullptr);
        ~CANTraceWindow();

    private:
        void createLayout();
        void canModelChanged(const QModelIndex &parent, int first, int last);

    private:
        Ui::CANTraceWindow *ui;

        QTreeView* m_pTreeView;
        CANUIModel m_CANModel;
};

#endif // CANTRACEWINDOW_H
