#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QRandomGenerator>
#include <QVector>
#include <QDateTime>
#include <QDebug>
#include <QMutex>
#include <QWaitCondition>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);

private:
    QVector<quint32> *m_pRandomData = new QVector<quint32>(5);
    QMutex m_mutex;
    QWaitCondition m_stopCheck;

signals:
    void ready(QString);
    void finished();

public slots:
    void createRandomVector();
    void stop();
};

#endif // WORKER_H
