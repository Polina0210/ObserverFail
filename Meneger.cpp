#include "Meneger.h"
#include <QFile> //для работы с файлами
#include <QFileInfo> //информация о свойствах файла



Meneger* Meneger:: singleton_= nullptr;  //нулевой указатель

Meneger *Meneger::GetInstance() //получение экземпляра файлового менеджера
{
    if(singleton_ == nullptr){
       singleton_ = new Meneger();
    }
    return singleton_;
}

void Meneger:: setFileInfo(qint32 i,bool newexist, qint32 newsize)
{
        int numberfile;
        fileExist[i] = newexist;
        fileSize[i]  = newsize;
        numberfile = i;

        emit FileChanged(fileNames[numberfile],fileExist[numberfile],fileSize[numberfile]);
}

void Meneger::anythingChanged()
{
    for (qint32 i = 0; i < fileNames.size(); i++) //проходит по вектору
     {
        if (QFileInfo(fileNames[i]).exists()) //если файл существует
        { if(QFileInfo(fileNames[i]).exists()!=(fileExist[i])) //если существование файла изменилось
            setFileInfo(i,QFileInfo(fileNames[i]).exists(),QFileInfo(fileNames[i]).size()); //устанавливаем новые поля сществования и размера
          else if (QFileInfo(fileNames[i]).size()!=(fileSize[i])) //если размер файла изменился
               setFileInfo(i,QFileInfo(fileNames[i]).exists(),QFileInfo(fileNames[i]).size()); //устанавливаем новые поля сществования и размера
        }
        else { //если файла не существует, то ставим поля cуществоаания и размера = 0
            setFileInfo(i,0,0);
      }
    }
}

void Meneger::Add(QString namefile){
    fileNames.push_back(namefile);
    if (QFileInfo(namefile).exists()) {
        fileExist.push_back(1);
        fileSize.push_back(QFileInfo(namefile).size());
    }
    else {fileExist.push_back(0);
          fileSize.push_back(0);
         }
    qint32 number = fileNames.size()-1;
    emit FileChanged(fileNames[number],fileExist[number],fileSize[number]);
}

void Meneger::Del(QString namefile){
    for (qint32 index = 0; index < fileNames.size(); index++){
        if(fileNames[index]==namefile){
              fileSize.remove(index);
              fileExist.remove(index);
              fileNames.remove(index);
              emit FileChanged(namefile,0,0);}
    }

}

void Meneger::giveInformation(QString name,bool exist,qint32 size){
     for (qint32 i = 0; i < fileNames.size(); i++){
         if(fileNames[i]==name)
         {emit FileChanged(fileNames[i],fileExist[i],fileSize[i]);}
     }
   }


