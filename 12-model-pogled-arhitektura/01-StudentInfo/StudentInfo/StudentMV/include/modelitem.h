#ifndef STUDENTTREEITEM_H
#define STUDENTTREEITEM_H

#include <QVariant>
#include <QVector>

class IAttributable;

class ModelItem
{
public:
    explicit ModelItem(IAttributable *data, ModelItem *parentItem = nullptr);
    ~ModelItem();

    void appendChild(ModelItem *child);

    ModelItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant attribute(int column) const;
    int row() const;
    ModelItem *parentItem();
    IAttributable* data() const;

private:
    IAttributable *m_data;
    QVector<ModelItem *> m_childItems;
    ModelItem *m_parentItem;
};

#endif // STUDENTTREEITEM_H
