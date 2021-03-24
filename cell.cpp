#include "cell.h"

Cell::Cell(bool shipOwnership, QObject *parent) :
    QObject(parent),
    m_shipOwnership(shipOwnership)
{
}

Cell::Cell(QString symbol, QObject *parent) :
    QObject(parent),
    m_shipOwnership(false),
    m_symbol(symbol),
    m_clickable(false)
{
}

Marker::State Cell::state() const
{
    return m_state;
}

bool Cell::clickable() const
{
    return m_clickable;
}

void Cell::setState(Marker::State state)
{
    if (m_state == state)
        return;

    m_state = state;
    emit stateChanged(m_state);
}

void Cell::setShipOwnership(bool shipOwnership)
{
    if (m_shipOwnership == shipOwnership)
        return;

    m_shipOwnership = shipOwnership;
    emit shipOwnershipChanged(m_shipOwnership);
}

void Cell::setClickable(bool clickable)
{
    if (m_clickable == clickable)
        return;

    m_clickable = clickable;
    emit clickableChanged(m_clickable);
}

bool Cell::shipOwnership() const
{
    return m_shipOwnership;
}
