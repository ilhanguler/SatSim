#ifndef TIMEDRIVER_H
#define TIMEDRIVER_H

#include <QDateTime>
#include <QObject>
#include <QElapsedTimer>

class TimeDriver : public QObject
{
    Q_OBJECT
public:
    TimeDriver(QObject *parent = nullptr);

    TimeDriver(QDateTime simTime, qint64 deltaMSecs);

    QDateTime systemTime = QDateTime::currentDateTime();
    QDateTime simTime = QDateTime::currentDateTime();
    qint64 deltaMSecs = 1000;
    QElapsedTimer timer;

    void passDeltaTime();

public slots:
    void waitSimulation();
    void updateSystemTime();

signals:
    void timePassed();

};

#endif // TIMEDRIVER_H
