#include "Queue.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <fstream>


Queue::Queue()
{
    this->queue_ = new Ingridient[0];
    this->size = 0;
    this->iterator.first = 0;
    this->iterator.second = this->queue_[0];
}
Queue::Queue(const Queue& Q)
{
    this->queue_ = Q.queue_;
    this->size = Q.size;
    this->iterator = Q.iterator;
}
int Queue::add(Ingridient i){
    this->size++; // увеличиваем нашу переменную ответственную за размер списка
    Ingridient *new_array = new Ingridient[this->size]; // создаем массив нового размера


    for (int i = 0; i < this->size - 1; i++){
        new_array[i] = this->queue_[i]; // в новый массив записываем все элементы из старого
    }

    new_array[this->size - 1] = i; // добавляем новый элемент в конец

    delete [] this->queue_;
    this->queue_ = new Ingridient[this->size]; // создаем наш массив нового размера
    this->queue_= new_array; // присваиваем заполненный массив с новым элементом
    this->iterator.second = this->queue_[this->iterator.first];
    return 0;
}
int Queue::remove(int index){
    if (index < this->size){
        this->size--; // уменьшаем нашу переменную ответственную за размер списка
        Ingridient* new_array = new Ingridient[size]; // создаем массив нового размера
        for (int i = 0; i < index; i++)
            new_array[i] = this->queue_[i]; // в новый массив записываем все элементы из старого находящиеся до необходимого нам элемента для удаления
        for (int i = index; i < size; i++)
            new_array[i] = this->queue_[i + 1]; // в новый массив записываем все элементы из старого находящиеся до необходимого нам элемента для удаления
        delete [] this->queue_;
        this->queue_ = new Ingridient[size]; // создаем наш массив нового размера
        this->queue_ = new_array; // присваиваем заполненный массив без элемента для удаления
        if (this->iterator.first >= this->size)
            this->iterator.first = this->size - 1;
        this->iterator.second = this->queue_[this->iterator.first];
        return 0;
    }
    return 1;
}
int Queue::clean()
{
    delete [] this->queue_;
    this->queue_ = new Ingridient[0];
    this->size = 0;
    return 0;
}
int Queue::getSize()
{
    return this->size;
}
int Queue::toFile()
{
    QJsonArray array; // создаем массив Json обьектов

    for (int i = 0; i < this->size; i++)
    {
        QString name = QString::fromUtf8(this->queue_[i].getName().c_str()); // а вот тут моя проблема заключается в том, что я использовал string в полях класса , а Qt-шные библиотеки не знают о таком типе, а занкомы только с QString, поэтому все строки нам прийдется конвертить постоянно...((
        QString system_calculation = QString::fromUtf8(this->queue_[i].getSystemCalculation().c_str());
        QJsonObject obj { // создаем обьект который позже добавится в массив где будет храниться в удобном для нас виде
            {"quanity", this->queue_[i].getQuanity()}, // а вот сама магия, рассмотрим ее
            {"name", name}, // QJsonObject может состоять из нескольки полей, как уже было представленно выше, и каждое поле берется в фигурные скобки,в скобках указвается имя интересующего нас параметра и его значение
            {"system_calculation", system_calculation} // заметьте, в случае создания нескольких полей в одном QJsonObject между полями ставятся запятые
        };
        array.append(obj); // добавляем наш QJsonObject в массив
    }
    QJsonDocument stack_doc(array); // добавляем наш массив в документ, из которо , собственно, мы и преобразуем в строку наш контейнер , которую позже запишем в файл


    ofstream out("/home/vldmr_bs/oop_lab2/queue_.txt");
    if (out.is_open())
    {
        out << stack_doc.toJson().toStdString() << endl; // запись в файл , заметьте, функция .tоJson() - преобразует документ в QString , но так как для записи используем обычный плюсовый инструмент, то он не знает ни о каких QString, и нам надо ее преобразовать в string
    }
    out.close();
    return 0;
}

int Queue::intoFile()
{
    string line, stack = "";

    ifstream in("/home/vldmr_bs/oop_lab2/queue_.txt"); // окрываем файл для чтения
    if (in.is_open()) // сама
    {
        while (getline(in, line))
        {
            stack += line;
        }
    }
    in.close();

    QJsonDocument doc = QJsonDocument::fromJson(QString::fromUtf8(stack.c_str()).toLocal8Bit()); // преварщаем считаную строку в QJsonDocument

    QJsonArray array = doc.array(); // преварщаем QJsonDocument в массив
    Ingridient *new_array = new Ingridient[array.size()]; // создаем наш массив куда будем записывать все знаечния
    for (int i = 0; i < array.size(); i++)
    {
        // доступ к какой либо записи происходит через обращения к индексу массива через функцию .at(index), после чего в квадратных скобках указываем имя строки которую хотим получить, после чего мы получаем значение, но нам надо преобраховать его к нашему типу, так как Qt библиотеки знают только QString, то сначала получаем QString, а после просто string. Также важное замечание - при считывании числа float мы не можем завернуть его сразу в float, поэтому я заворачиваю его в в double (у них с float одинаковая маска), у меня это работет корректно, в случае если у вас это корректно не работает, то используем static_cast<float>(сюда double указываем)
        Ingridient in(array.at(i)["name"].toString().toStdString(),array.at(i)["system_calculation"].toString().toStdString(),array.at(i)["quanity"].toDouble()); // создаем класс
        new_array[i] = in; // добавляем экземпляр класса в наш список
    }

    this->queue_ = new_array;

    return 0;
}

void Queue::setIteratorIndex(int index){
    if (this->iterator.first != index && index < this->size && index >= 0){
        this->iterator.first = index;
        this->iterator.second = this->queue_[this->iterator.first];
    }
}

void Queue::setIteratorValue(Ingridient i){
    if (i.getQuanity() >= 0){
        this->iterator.second = i;
    }
}

int Queue::getIteratorIndex(){
    return this->iterator.first;
}
Ingridient Queue::getIteratorValue(){
    return this->iterator.second;
}

bool Queue::equal(Ingridient one, Ingridient two){
    if (one.getName() == two.getName() && one.getQuanity() == two.getQuanity() && one.getSystemCalculation() == two.getSystemCalculation())
        return true;
    else
        return false;
}
