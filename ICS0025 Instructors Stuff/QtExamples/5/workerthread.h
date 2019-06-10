#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QObject>
#include <QThread>
#include <QRandomGenerator>
#include <QVector>
#include <QDateTime>
#include <QDebug>
#include <QMutex>
#include <QWaitCondition>

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    WorkerThread();
    QVector<quint32> *m_pRandomData = new QVector<quint32>(5);

protected:
    void run() override;

private:
    QMutex m_mutex;
    QWaitCondition m_stopCheck;

signals:
    void ready(QString);

public slots:
    void stop();
};

#endif // WORKERTHREAD_H
