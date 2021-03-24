#ifndef MARKER_H
#define MARKER_H

#include <QObject>

class Marker : public QObject
{
    Q_OBJECT
public:
    enum State {
        Default,
        Missed,
        Got
    };
    Q_ENUM(State)

signals:

public slots:
private:
    explicit Marker(QObject *parent = nullptr) : QObject(parent)
    {
    }
};

#endif // MARKER_H
