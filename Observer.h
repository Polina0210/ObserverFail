#ifndef OBSERVER_H
#define OBSERVER_H

#include <iostream>
#include <list>
#include <string>

#include <QObject>
#include <QVector>
#include <QString>
#include <map>

using namespace std;


class Observer: public QObject
{
    Q_OBJECT
 public:

   Observer(QString a = " ", bool b = false, qint32 c = 0)
      {
          name = a; //имя
          exist = b; //существует
          size = c; //размер
          emit requestInformation(name,exist,size);
      }

  virtual ~Observer(){};

  void SetName(QString newname){
      name = newname;
      emit requestInformation(name,exist,size);

  };

  QString NameInfo(){
      return name;
  }

  bool ExistInfo(){
      return exist;
  }

  qint32 SizeInfo(){
      return size;
  }



signals:

  void requestInformation(QString,bool,qint32);
  void NewInfo(Observer*);

public slots:
   void Update(QString,bool,qint32);

private:
   QString name; //имя
   bool exist;  //существует
   qint32 size;  //размер

};

#endif // OBSERVER_H
