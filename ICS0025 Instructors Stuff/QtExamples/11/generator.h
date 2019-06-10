#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QRandomGenerator>
using namespace std;

class Generator : public QObject
{
    Q_OBJECT
public:
    explicit Generator(QObject *parent = nullptr);
    Q_INVOKABLE int getRandomNumber(int, int);
private:
    default_random_engine gen;
    int lower = 0,
        upper = 1000;

signals:

public slots:
};

#endif // GENERATOR_H
