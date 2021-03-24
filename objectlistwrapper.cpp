#include <QDebug>
#include "objectlistwrapper.h"
#include <QRandomGenerator>
#include <iostream>
#include <string>

ObjectListWrapper::ObjectListWrapper(QObject *parent) : QObject(parent)
{
    populateModelWithData();
}

bool ObjectListWrapper::initialize()
{
    resetModel();
    m_engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (m_engine.rootObjects().isEmpty())
        return false;

    return true;
}

void ObjectListWrapper::setCell(int index, Marker::State state)
{
    qDebug() << "Changing cell with index: " << index << " to state: " << state;
    if(index >= m_cells.size())
        return;

    Cell* pcell = qobject_cast<Cell*> (m_cells.at(index));
    if( state!= pcell->state())
    {
        pcell->setState(state);
        pcell->setClickable(false);
    }

    qint32 shipsAmount = calculateCellsWithShips();
    if(shipsAmount <= 0)
        qDebug() << "you won";
}

QList<QObject *> ObjectListWrapper::cells() const
{
    return m_cells;
}

void ObjectListWrapper::populateModelWithData()
{
    std::cout << "battle field filled with next ships location:\n";
    QRandomGenerator generator;

    m_cells.append(new Cell(QChar(), this));
    for(size_t i = 1; i < CELLSINROW; ++i)
    {
        char ascii = 'A' + i - 1;
        QChar symbol(ascii);
        m_cells.append(new Cell(symbol, this));
    }

    for(size_t i = 0; i < CELLSINROW * (CELLSINROW - 1); ++i)
    {
        if((i+CELLSINROW) % CELLSINROW == 0)
        {
            int column = i / CELLSINROW + 1;
            m_cells.append(new Cell(QString::number(column), this));
        }
        else
        {
            bool shipOwnership = generator.generate() % 2;
            std::cout << shipOwnership;
            m_cells.append(new Cell(shipOwnership, this));
        }

        if((i+1) % CELLSINROW == 0)
            std::cout << std::endl;
    }
}

void ObjectListWrapper::resetModel()
{
    m_engine.rootContext()->setContextProperty("Wrapper",this);
}

qint32 ObjectListWrapper::calculateCellsWithShips()
{
    std::cout << "calculateCellsWithShips:\n";
    const QObjectList& children = this->children();
    Q_ASSERT(children.size());
    qint32 amount = 0;

    for(qsizetype i = 0; i < children.size(); ++i)
    {
        Cell* pcell = qobject_cast<Cell*>(children.at(i));
        if(pcell->symbol().isEmpty())
        {
           bool shipOwnership = pcell->shipOwnership();
           amount += shipOwnership ? 1 : 0;
           std::cout << shipOwnership;
        }

        if((i+1) % CELLSINROW == 0)
            std::cout << std::endl;
    }

    return amount;
}
