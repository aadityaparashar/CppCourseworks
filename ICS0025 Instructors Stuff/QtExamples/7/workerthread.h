#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QObject>
#include <QThread>

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    WorkerThread();
protected:
    void run() override;
};

#endif // WORKERTHREAD_H
