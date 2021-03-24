#ifndef OBJECTLISTWRAPPER_H
#define OBJECTLISTWRAPPER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "cell.h"

class ObjectListWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> cells READ cells CONSTANT)
    Q_PROPERTY(int cellsInRow READ cellsInRow CONSTANT)

    static constexpr size_t CELLSINROW = 11;

public:
    explicit ObjectListWrapper(QObject *parent = nullptr);
    bool initialize();

    Q_INVOKABLE void setCell(int index, Marker::State state);

signals:

public slots:
    QList<QObject*> cells() const;
    constexpr size_t cellsInRow() const
    {
        return CELLSINROW;
    }

private:
    void populateModelWithData();

    void resetModel();

    qint32 calculateCellsWithShips();

    QList<QObject*> m_cells;
    QQmlApplicationEngine m_engine;
    int m_cellsInRow;
};

#endif // OBJECTLISTWRAPPER_H
