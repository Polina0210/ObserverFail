#ifndef MENEGER_H
#define MENEGER_H

//#include "Observer.h"

#include <iostream>
#include <list>
#include <string>
#include <QObject>


class Meneger: public QObject
{
    Q_OBJECT

 public:

   QVector<QString> fileNames;
   QVector<bool> fileExist;
   QVector<qint32> fileSize;
  // private static field instance: Database
   static Meneger* singleton_;

   Meneger(){};
   ~Meneger(){};

   Meneger(Meneger &other) = delete;
   void operator=(const Meneger &other) = delete;
   static Meneger *getInstance();


  void anythingChanged();
  void Add(QString namefile);
  void Del(QString namefile);
  void setFileInfo(int i,bool newexist, qint32 newsize);


signals:
   void FileChanged(QString,bool,qint32);

public slots:
   void giveInformation(QString,bool,qint32);


private:

};

#endif // MENEGER_H
