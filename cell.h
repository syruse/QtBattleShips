#ifndef CELL_H
#define CELL_H

#include <QObject>
#include "marker.h"

class Cell : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Marker::State state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(bool shipOwnership READ shipOwnership WRITE setShipOwnership NOTIFY shipOwnershipChanged)
    Q_PROPERTY(bool clickable READ clickable WRITE setClickable NOTIFY clickableChanged)
    Q_PROPERTY(QString symbol READ symbol CONSTANT)

public:
    explicit Cell(bool shipOwnership, QObject *parent = nullptr);
    explicit Cell(QString symbol, QObject *parent = nullptr);

    Marker::State state() const;
    bool shipOwnership() const;
    bool clickable() const;

    QString symbol() const
    {
        return m_symbol;
    }

public slots:
    void setState(Marker::State state);
    void setShipOwnership(bool shipOwnership);
    void setClickable(bool clickable);

signals:
    void stateChanged(Marker::State state);
    void shipOwnershipChanged(bool shipOwnership);
    void clickableChanged(bool clickable);

private:
    bool m_shipOwnership;
    QString m_symbol = "";
    bool m_clickable = true;
    Marker::State m_state = Marker::Default;
};

#endif // CELL_H
