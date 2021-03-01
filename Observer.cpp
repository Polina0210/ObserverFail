#include "Observer.h"

#include <QString>
#include <QTextStream>
#include <fstream> //ввод-вывод для файлов

void Observer:: Update(QString a,bool b,qint32 c) {
    if (a==name){
                   exist=b;
                   size=c;
    std::cout << "New data for observer:"<< std::endl;
    FileInfo();}
};


void Observer:: FileInfo() {
      QTextStream cout(stdout), cin(stdin);
    if (exist) {
        QTextStream(stdout) << "File name  " << name << endl;
        std::cout << "File size  " << size << std::endl;
    }
    else {
        QTextStream(stdout) << "File named " << name <<" does not exist" <<endl;
    }

};
