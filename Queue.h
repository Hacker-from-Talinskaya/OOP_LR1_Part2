#pragma once
#include <string>
#include "Ingridient.h"

using namespace std;

class Queue
{
public:
    Queue();
    Queue(const Queue& Q);

    int add(Ingridient i);
    int remove(int index);
    int clean();

    int getSize();

    Ingridient get(Ingridient *iterator);

    int toFile();
    int intoFile();

    void setIteratorIndex(int index);
    void setIteratorValue(Ingridient i);

    int getIteratorIndex();
    Ingridient getIteratorValue();

    bool equal(Ingridient one, Ingridient two);
private:
    pair<int,Ingridient> iterator;
    Ingridient *queue_;
    int size;
};

