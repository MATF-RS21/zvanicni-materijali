#include "include/modelitem.h"
#include "include/model.h"

#include "includes/student.h"
#include "includes/courseitem.h"

TreeModel::TreeModel(const QVector<Student *> & students, QObject *parent)
    : QAbstractItemModel(parent)
{
    m_rootItem = new ModelItem(new Student());
    setupModelData(students);
}

TreeModel::~TreeModel()
{
    delete m_rootItem;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return static_cast<ModelItem *>(parent.internalPointer())->columnCount();
    }
    return m_rootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    auto studentItem = static_cast<ModelItem*>(index.internalPointer());
    return studentItem->attribute(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
    }

    return QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return m_rootItem->data()->attributeName(section);
    }

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    ModelItem *parentItem;

    if (!parent.isValid())
    {
        parentItem = m_rootItem;
    }
    else
    {
        parentItem = static_cast<ModelItem *>(parent.internalPointer());
    }

    auto childItem = parentItem->child(row);
    if (childItem)
    {
        return createIndex(row, column, childItem);
    }
    return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    auto childItem = static_cast<ModelItem *>(index.internalPointer());
    auto parentItem = childItem->parentItem();

    if (parentItem == m_rootItem)
    {
        return QModelIndex();
    }

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
    {
        return 0;
    }

    ModelItem *parentItem;

    if (!parent.isValid())
    {
        parentItem = m_rootItem;
    }
    else
    {
        parentItem = static_cast<ModelItem *>(parent.internalPointer());
    }

    return parentItem->childCount();
}

void TreeModel::setupModelData(const QVector<Student *> students)
{
    for (const auto student : students)
    {
        // Add the current student as the root item's new child item...
        auto studentItem = new ModelItem(student, m_rootItem);
        m_rootItem->appendChild(studentItem);

        // ...and then add student's course items as his children
        for (const auto &courseItem : student->getCourseItems())
        {
            studentItem->appendChild(new ModelItem(courseItem, studentItem));
        }
    }
}
