#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>
#include <QDebug>

class MainWindow;
class Counter : public QObject
{
    Q_OBJECT // Do not forget

private:
    int m_Value = 0;
    MainWindow *m_pMainWindow = nullptr;
public:
    Counter();
public slots:
    void Increment() { m_Value++; emit valueChanged(m_Value); }
signals:
    void valueChanged(int);
};

#endif // COUNTER_H
