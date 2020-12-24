#include "include/modelitem.h"
#include "includes/iattributable.h"

ModelItem::ModelItem(IAttributable *data, ModelItem *parent)
    : m_data(data)
    , m_parentItem(parent)
{}

ModelItem::~ModelItem()
{
    delete m_data;
    qDeleteAll(m_childItems);
}

void ModelItem::appendChild(ModelItem *item)
{
    m_childItems.append(item);
}

ModelItem *ModelItem::child(int row)
{
    if (row < 0 || row >= m_childItems.size())
    {
        return nullptr;
    }
    return m_childItems.at(row);
}

int ModelItem::childCount() const
{
    return m_childItems.count();
}

int ModelItem::columnCount() const
{
    return m_data->numberOfAttributes();
}

QVariant ModelItem::attribute(int column) const
{
    return m_data->attribute(column);
}

ModelItem *ModelItem::parentItem()
{
    return m_parentItem;
}

IAttributable *ModelItem::data() const
{
    return m_data;
}

int ModelItem::row() const
{
    if (m_parentItem)
    {
        return m_parentItem->m_childItems.indexOf(const_cast<ModelItem*>(this));
    }

    return 0;
}
