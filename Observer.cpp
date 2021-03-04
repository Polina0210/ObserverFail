#include "Observer.h"

#include <QString>
#include <QTextStream>
#include <fstream> //ввод-вывод для файлов

void Observer:: Update(QString a,bool b,qint32 c) {
    if (a==name){
                   exist=b;
                   size=c;
                   emit NewInfo(this);
    }
};
