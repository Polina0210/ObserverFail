#ifndef MENEGER_H
#define MENEGER_H

//#include "Observer.h"

#include <iostream>
#include <list>
#include <string>
#include <QObject>
#include <QTimer>


class Meneger: public QObject
{
    Q_OBJECT

protected:
    Meneger(){
        QTimer* tmr = new QTimer(this);
        QObject::connect(tmr, SIGNAL (timeout()), this, SLOT(anythingChanged()));
        tmr->start(1000);
    };

    ~Meneger(){

    };
    static Meneger* singleton_;

    std::string value_;

public:

    Meneger(Meneger &other)=delete;
    void operator=(const Meneger &) = delete;
    static Meneger *GetInstance();




    void setFileInfo(int i,bool newexist, qint32 newsize);

    void Add(QString namefile);
    void Del(QString namefile);

    QString InfoName(int i){
        return fileNames[i];
    }

    bool InfoExist(int i){
        return fileExist[i];
    }

    qint32 InfoSize(int i){
        return fileSize[i];
    }

    int CountOfFiles(){
        return fileNames.size();
    }


 private:

   QVector<QString> fileNames;
   QVector<bool> fileExist;
   QVector<qint32> fileSize;


  // private static field instance: Database



signals:
   void FileChanged(QString,bool,qint32);

public slots:
   void giveInformation(QString,bool,qint32);
   void anythingChanged();



};

#endif // MENEGER_H
