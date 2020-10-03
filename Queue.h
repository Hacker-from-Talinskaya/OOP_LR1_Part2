#ifndef QUEUE_H
#define QUEUE_H
#include "Ingridient.h"

class Queue
{
public:
    Queue();
    Queue(const Queue& Q);

    void add_f(Ingridient i);
    void delete_f(int index);
    void clean_f();

    int get_size();

    Ingridient get(Ingridient *iterator);

    Ingridient *iterator;

    void toFile();
    void intoFile();
private:
    Ingridient *queue_;
    int size;
};

#endif // QUEUE_H
