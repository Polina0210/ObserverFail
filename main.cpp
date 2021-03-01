#include <QCoreApplication>
#include<QTimer>
#include<iostream>
#include "Observer.h"
#include "Meneger.h"

#include <QFileInfo>
#include<QTimer>

#include <QString>
#include <QTextStream>

#include <QFile> //для работы с файлами

#include <QDateTime> //даты
#include <fstream> //ввод-вывод для файлов


using namespace std;

void PrintFile(Meneger meneger){
    for (int i=0; i< meneger.fileNames.size(); i++){
    QTextStream(stdout)<<"Fail name"<<i<<":" << meneger.fileNames[i] << endl;
    QTextStream(stdout)<<"Fail exist"<<i<<":" << meneger.fileExist[i] << endl;
    QTextStream(stdout)<<"Fail size"<<i<<":" << meneger.fileSize[i] << endl;
    }
}

void AddFiles(Meneger* meneger){
    QTextStream cout(stdout), cin(stdin);
    int n; //количество файлов в списке менеджера
    std::cout<<"Enter the number of new files"<<endl;
    std::cin>>n;
    for (int i=0; i<n; i++){
         std::cout<<"Enter the "<<i+1<<"-th file"<<endl;
         QString fail = cin.readLine().trimmed().toLower();
         meneger->Add(fail);
    }

}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QTextStream cout(stdout), cin(stdin); //для ввода-вывода

    Meneger *meneger = Meneger::getInstance();


   AddFiles(meneger);

    std::cout<<"Enter file name for observer"<<endl;
    QString nameObs = cin.readLine().trimmed().toLower();

    Observer Observer1;
    QObject::connect(meneger, SIGNAL(FileChanged(QString,bool,qint32)), &Observer1, SLOT(Update(QString,bool,qint32)));
    QObject::connect(&Observer1, SIGNAL(requestInformation(QString,bool,qint32)), meneger, SLOT(giveInformation(QString,bool,qint32)));
    Observer1.SetName(nameObs);


    std::cout<<"to update enter any number"<<endl;
    int n;
    std::cin>>n;
    meneger->anythingChanged();

    Observer1.FileInfo();

    //изменение наблюдаемого файла
    std::cout<<"changing the watched file"<<endl;

    std::cout<<"Enter new file name for observer"<<endl;
    QString NewnameObs = cin.readLine().trimmed().toLower();
    Observer1.SetName(NewnameObs);

    Observer1.FileInfo();

    //добавление наблюдателя
    std::cout<<"adding observer"<<endl;

    std::cout<<"Enter file name for observer"<<endl;
    QString nameObs2 = cin.readLine().trimmed().toLower();

    Observer Observer2;
    QObject::connect(meneger, SIGNAL(FileChanged(QString,bool,qint32)), &Observer2, SLOT(Update(QString,bool,qint32)));
    QObject::connect(&Observer2, SIGNAL(requestInformation(QString,bool,qint32)), meneger, SLOT(giveInformation(QString,bool,qint32)));
    Observer2.SetName(nameObs2);

    //состояние всех наблюдателей
    std::cout<<"condition of all observers"<<endl;
    Observer1.FileInfo();
    Observer2.FileInfo();


   //meneger.anythingChanged();


    std::cout<<"Ok"<<endl;


    QTimer::singleShot(0, &app, SLOT(quit()));
    return app.exec();
}
