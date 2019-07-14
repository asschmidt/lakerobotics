/*
 * AbstractUIModelItem.h
 *
 *  Created on: 13.07.2019
 *      Author: Andreas
 */

#ifndef _ABSTRACT_UI_MODEL_ITEM_H_
#define _ABSTRACT_UI_MODEL_ITEM_H_

// Qt includes
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QVector>
#include <QtWidgets/QMenu>

// Project includes

/**
 * Abstract class used as base class for UI-related Models. Such a UI model is used to connect
 * a real data model to a UI component like a List, Table or TreeView. Due to this UI model, the data
 * model and the UI model are separated. Typically the UI model just includes a reference to the
 * real data model
 */
class AbstractUIModelItem
{
    public:
        AbstractUIModelItem(AbstractUIModelItem* pParent);
        virtual ~AbstractUIModelItem();

        virtual AbstractUIModelItem* getParent();
        virtual AbstractUIModelItem* getChild(int row);

        virtual int getChildCount() const;
        virtual int getColumnCount() const;

        virtual int getRow() const;

        virtual AbstractUIModelItem* appendChild(AbstractUIModelItem* pChild);

        virtual QVariant getData(const QModelIndex& index) = 0;

        virtual QMenu* createItemContextMenu(QMenu* pParentMenu);

    protected:
        AbstractUIModelItem* m_pParentItem;
        QVector<AbstractUIModelItem*> m_Childs;
};


#endif /* _ABSTRACT_UI_MODEL_ITEM_H_ */
