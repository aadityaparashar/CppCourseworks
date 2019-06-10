#include "generator.h"


Generator::Generator(QObject *parent) : QObject(parent)
{

}

int Generator::getRandomNumber(int x0, int xn)
{
    if (x0 != lower || xn != upper)
    {
        lower = x0;
        upper = xn;
        uniform_int_distribution<int> random_number(lower, upper);
        return random_number(gen);
    }
    else
    {
        uniform_int_distribution<int> random_number(lower, upper);
        return random_number(gen);
    }
}
