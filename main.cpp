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

void PrintFile(Meneger *meneger){
    for (int i=0; i< meneger->CountOfFiles(); i++){
    QTextStream(stdout)<<"Fail name"<<i<<":" << meneger->InfoName(i) << endl;
    QTextStream(stdout)<<"Fail exist"<<i<<":" << meneger->InfoExist(i) << endl;
    QTextStream(stdout)<<"Fail size"<<i<<":" << meneger->InfoSize(i) << endl;
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

void FileInfo(Observer* observer) {
      QTextStream cout(stdout), cin(stdin);
    if (observer->ExistInfo()) {
        QTextStream(stdout) << "File name  " << observer->NameInfo() << endl;
        std::cout << "File size  " << observer->SizeInfo() << std::endl;
    }
    else {
        QTextStream(stdout) << "File named " << observer->NameInfo() <<" does not exist" <<endl;
    }

};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QTextStream cout(stdout), cin(stdin); //для ввода-вывода

    Meneger *meneger = Meneger::GetInstance();


    AddFiles(meneger);

    std::cout<<"Enter file name for observer"<<endl;
    QString nameObs = cin.readLine().trimmed().toLower();

    Observer Observer1;
    QObject::connect(meneger, SIGNAL(FileChanged(QString,bool,qint32)), &Observer1, SLOT(Update(QString,bool,qint32)));
    QObject::connect(&Observer1, SIGNAL(requestInformation(QString,bool,qint32)), meneger, SLOT(giveInformation(QString,bool,qint32)));
    QObject::connect(&Observer1, &Observer::NewInfo, FileInfo);
    Observer1.SetName(nameObs);


    std::cout<<"to update enter any number"<<endl;
    int n;
    std::cin>>n;
    meneger->anythingChanged();

    //изменение наблюдаемого файла
    std::cout<<"changing the watched file"<<endl;

    std::cout<<"Enter new file name for observer"<<endl;
    QString NewnameObs = cin.readLine().trimmed().toLower();
    Observer1.SetName(NewnameObs);

    //добавление наблюдателя
    std::cout<<"adding observer"<<endl;

    std::cout<<"Enter file name for observer"<<endl;
    QString nameObs2 = cin.readLine().trimmed().toLower();

    Observer Observer2;
    QObject::connect(meneger, SIGNAL(FileChanged(QString,bool,qint32)), &Observer2, SLOT(Update(QString,bool,qint32)));
    QObject::connect(&Observer2, SIGNAL(requestInformation(QString,bool,qint32)), meneger, SLOT(giveInformation(QString,bool,qint32)));
    QObject::connect(&Observer2, &Observer::NewInfo, FileInfo);
    Observer2.SetName(nameObs2);

    return app.exec();
}
