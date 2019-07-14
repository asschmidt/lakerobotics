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

    private:
        Ui::CANTraceWindow *ui;

        QTreeView* m_pTreeView;
};

#endif // CANTRACEWINDOW_H
