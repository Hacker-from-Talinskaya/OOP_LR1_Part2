#include "mainwindow.h"
#include "Ingridient.h"
#include "Queue.h"
#include <QApplication>
#include <iostream>

int toScreen(Queue q){
    for (int i = 0; i < q.getSize(); i++){
        q.setIteratorIndex(i);
        cout << "name: " << q.getIteratorValue().getName() << " quanity: " << q.getIteratorValue().getQuanity() << "  system calculation: " << q.getIteratorValue().getSystemCalculation() << endl;
    }
    return 0; // для проверки через assert
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
