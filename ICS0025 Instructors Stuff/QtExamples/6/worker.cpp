#include <QObject>
#include <QThread>
#include "worker.h"

Worker::Worker(QObject *parent) : QObject(parent)
{
}

void Worker::createRandomVector()
{
    forever
    {
        m_mutex.lock();
        QRandomGenerator generator(static_cast<quint32>(QDateTime::currentMSecsSinceEpoch()));
        generator.fillRange(m_pRandomData->data(), m_pRandomData->size());
        QString outputText;
        std::for_each(m_pRandomData->begin(), m_pRandomData->end(),
                      [&](quint32 i) { outputText += QString::number(i); outputText += ' '; });
        emit ready(outputText);
        if (m_stopCheck.wait(&m_mutex, 5000))
        {
            emit ready("");
            return;
        }
        m_mutex.unlock();
    }
}

void Worker::stop()
{
  m_stopCheck.wakeOne();
}
