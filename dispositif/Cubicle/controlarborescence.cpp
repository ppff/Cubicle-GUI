#include "controlarborescence.h"

ControlArborescence::ControlArborescence()
{

}

void ControlArborescence:: ctlSave(Cube cubeMotif, QString emplMotif){
    GestionFichier ges;
    if(emplMotif!=""){
         qDebug()<<"je suis dans save";
         ges.ouvrir(emplMotif,cubeMotif);
    }
}

void ControlArborescence::monter(Ui::MainWindow *ui,QFileSystemModel *model){
    QString nameGroup;
    QString newNameGroup;
    QString nameGroupDessus;
    QString nameMotif;
    QString newNameMotif;
    QString nameMotifDessus;
    QModelIndex index=ui->treeView->currentIndex();
    QModelIndex indexMoinsUn=ui->treeView->indexAbove(index);

    if (index.isValid()){
           if (model->fileInfo(index).isDir()) {
               nameGroup=model->fileInfo(index).baseName();
               if (nameGroup=="Cubicle"){
                   return;
               }

               QString numero = nameGroup.left(2);
               int num = numero.toInt();
               if(num==0){
                   return;
               }

               while(model->fileInfo(indexMoinsUn).isFile()){
                   indexMoinsUn=ui->treeView->indexAbove(indexMoinsUn);
               }

                QString dir=model->fileInfo(index).absolutePath();
                nameGroupDessus=model->fileInfo(indexMoinsUn).baseName();
                qDebug()<<"1111111111111111";
                qDebug()<<"nameGroupDessus: "+ nameGroupDessus;
                QString nameRest = nameGroup.mid(3);
                QString nameDessusRest = nameGroupDessus.mid(3);

                if (num<11){
                    newNameGroup = "0"+QString::number(num-1)+"_"+nameRest;
                }else {
                    newNameGroup = QString::number(num-1)+"_"+nameRest;
                }
                QString pathTotalOld = dir+"/"+nameGroup;
                qDebug()<<"2222222222222222";
                qDebug()<<"pathTotalOld: "+ pathTotalOld;

                QString pathTotalNew = dir+"/"+newNameGroup;
                qDebug()<<"3333333333333333";
                qDebug()<<"pathTotalNew: "+ pathTotalNew;

                if (num<10){
                        //QString nameGroupMoinsUn = "0"+QString::number(num-1)+"_"+nameDessusRest;
                        QString totalnameGroupMoinsUn = dir+"/"+nameGroupDessus;
                        qDebug()<<"444444444444444444";
                        qDebug()<<"totalnameGroupMoinsUn: "+ totalnameGroupMoinsUn;
                        QString nameGroupMoinsUnChange = nameDessusRest;
                        qDebug()<<"555555555555555555555";
                        qDebug()<<"nameGroupMoinsUnChange: "+ nameGroupMoinsUnChange;
                        QString totalnameGroupMoinsUnChange = dir+"/"+nameGroupMoinsUnChange;
                        qDebug()<<"6666666666666666666666";
                        qDebug()<<"totalnameGroupMoinsUnChange: "+ totalnameGroupMoinsUnChange;

                        QDir directory(totalnameGroupMoinsUn);
                        directory.rename(totalnameGroupMoinsUn,totalnameGroupMoinsUnChange);
                       // emit model->directoryLoaded(totalnameGroupMoinsUnChange);

                        QDir dir1(pathTotalOld);
                        dir1.rename(pathTotalOld, pathTotalNew);
                        //emit model->directoryLoaded(pathTotalNew);

                        QString nameGroupMoinsUnChangeCorrect = "0"+QString::number(num)+"_"+nameDessusRest;
                        qDebug()<<"777777777777777777777777";
                        qDebug()<<"nameGroupMoinsUnChangeCorrect: "+ nameGroupMoinsUnChangeCorrect;

                        QString totalnameGroupMoinsUnCorrect = dir+"/"+nameGroupMoinsUnChangeCorrect;
                        qDebug()<<"8888888888888888888888888";
                        qDebug()<<"totalnameGroupMoinsUnCorrect: "+ totalnameGroupMoinsUnCorrect;

                        QDir dir2(totalnameGroupMoinsUnChange);
                        dir2.rename(totalnameGroupMoinsUnChange, totalnameGroupMoinsUnCorrect);
                        //emit model->directoryLoaded(totalnameGroupMoinsUnCorrect);
                        dir2.setSorting(QDir::Name);
                }else if(num==10){
                        QString nameGroupMoinsUn = "0"+QString::number(num-1)+"_"+nameDessusRest;
                        QString totalnameGroupMoinsUn = dir+"/"+nameGroupMoinsUn;

                        QString nameGroupMoinsUnChange = nameDessusRest;
                        QString totalnameGroupMoinsUnChange = dir+"/"+nameGroupMoinsUnChange;

                        QDir directory(totalnameGroupMoinsUn);
                        directory.rename(totalnameGroupMoinsUn,totalnameGroupMoinsUnChange);

                        QDir dir1(pathTotalOld);
                        dir1.rename(pathTotalOld, pathTotalNew);

                        QString nameGroupMoinsUnChangeCorrect = QString::number(num)+"_"+nameDessusRest;
                        QString totalnameGroupMoinsUnCorrect = dir+"/"+nameGroupMoinsUnChangeCorrect;
                        QDir dir2(totalnameGroupMoinsUnCorrect);
                        dir2.rename(totalnameGroupMoinsUnChange, totalnameGroupMoinsUnCorrect);
                        dir2.setSorting(QDir::Name);
                }else if(num>10){
                        QString nameGroupMoinsUn = QString::number(num-1)+"_"+nameDessusRest;
                        QString totalnameGroupMoinsUn = dir+"/"+nameGroupMoinsUn;

                        QString nameGroupMoinsUnChange = nameDessusRest;
                        QString totalnameGroupMoinsUnChange = dir+"/"+nameGroupMoinsUnChange;

                        QDir directory(totalnameGroupMoinsUn);
                        directory.rename(totalnameGroupMoinsUn,totalnameGroupMoinsUnChange);

                        QDir dir1(pathTotalOld);
                        dir1.rename(pathTotalOld, pathTotalNew);

                        QString nameGroupMoinsUnChangeCorrect = QString::number(num)+"_"+nameDessusRest;
                        QString totalnameGroupMoinsUnCorrect = dir+"/"+nameGroupMoinsUnChangeCorrect;
                        QDir dir2(totalnameGroupMoinsUnCorrect);
                        dir2.rename(totalnameGroupMoinsUnChange, totalnameGroupMoinsUnCorrect);
                        dir2.setSorting(QDir::Name);
                }
         }else{
                QString dir=model->fileInfo(index).absolutePath();
                nameMotif=model->fileInfo(index).baseName();
                QString numero1=nameMotif.left(2);
                int num1=numero1.toInt();
                if(num1==0){
                    return;
                }

                nameMotifDessus=model->fileInfo(indexMoinsUn).baseName();

                QString numero = nameMotif.left(2);
                QString nameRest = nameMotif.mid(3);
                QString nameDessusRest = nameMotifDessus.mid(3);
                int num = numero.toInt();
                if(num==0){
                    return;
                }
                if (num<11){
                    newNameMotif = "0"+QString::number(num-1)+"_"+nameRest;
                }else {
                    newNameMotif = QString::number(num-1)+"_"+nameRest;
                }
                QString pathTotalOld = dir+"/"+nameMotif+".txt";
                QString pathTotalNew = dir+"/"+newNameMotif+".txt";

                if (num<10){
                    //////////////////////////////
                        QString nameMotifMoinsUn = "0"+QString::number(num-1)+"_"+nameDessusRest+".txt";
                        QString totalnameMotifMoinsUn = dir+"/"+nameMotifMoinsUn;

                        QString nameMotifMoinsUnChange = nameDessusRest;
                        QString totalnameMotifMoinsUnChange = dir+"/"+nameMotifMoinsUnChange+".txt";

                        QFile directory(totalnameMotifMoinsUn);
                        directory.rename(totalnameMotifMoinsUn,totalnameMotifMoinsUnChange);
                    ////////////////////////////////
                        QFile dir1(pathTotalOld);
                        dir1.rename(pathTotalOld, pathTotalNew);
                    ////////////////////////////////
                        QString nameMotifMoinsUnChangeCorrect = "0"+QString::number(num)+"_"+nameDessusRest+".txt";
                        QString totalnameMotifMoinsUnCorrect = dir+"/"+nameMotifMoinsUnChangeCorrect;

                        QFile dir2(totalnameMotifMoinsUnChange);
                        dir2.rename(totalnameMotifMoinsUnChange, totalnameMotifMoinsUnCorrect);
                   ///////////////////////////////
                }else if(num==10){
                        QString nameMotifMoinsUn = "0"+QString::number(num-1)+"_"+nameDessusRest+".txt";
                        QString totalnameMotifMoinsUn = dir+"/"+nameMotifMoinsUn;

                        QString nameMotifMoinsUnChange = nameDessusRest;
                        QString totalnameMotifMoinsUnChange = dir+"/"+nameMotifMoinsUnChange+".txt";

                        QFile directory(totalnameMotifMoinsUn);
                        directory.rename(totalnameMotifMoinsUn,totalnameMotifMoinsUnChange);

                        QFile dir1(pathTotalOld);
                        dir1.rename(pathTotalOld, pathTotalNew);

                        QString nameMotifMoinsUnChangeCorrect = QString::number(num)+"_"+nameDessusRest+".txt";
                        QString totalnameMotifMoinsUnCorrect = dir+"/"+nameMotifMoinsUnChangeCorrect;
                        QFile dir2(totalnameMotifMoinsUnCorrect);
                        dir2.rename(totalnameMotifMoinsUnChange, totalnameMotifMoinsUnCorrect);
                }else if(num>10){
                        QString nameMotifMoinsUn = QString::number(num-1)+"_"+nameDessusRest+".txt";
                        QString totalnameMotifMoinsUn = dir+"/"+nameMotifMoinsUn;

                        QString nameMotifMoinsUnChange = nameDessusRest;
                        QString totalnameMotifMoinsUnChange = dir+"/"+nameMotifMoinsUnChange+".txt";

                        QFile directory(totalnameMotifMoinsUn);
                        directory.rename(totalnameMotifMoinsUn,totalnameMotifMoinsUnChange);

                        QFile dir1(pathTotalOld);
                        dir1.rename(pathTotalOld, pathTotalNew);

                        QString nameMotifMoinsUnChangeCorrect = QString::number(num)+"_"+nameDessusRest+".txt";
                        QString totalnameMotifMoinsUnCorrect = dir+"/"+nameMotifMoinsUnChangeCorrect;
                        QFile dir2(totalnameMotifMoinsUnCorrect);
                        dir2.rename(totalnameMotifMoinsUnChange, totalnameMotifMoinsUnCorrect);
                }
         }
    model->dataChanged(index,index);
    }
}

void ControlArborescence::descendre(Ui::MainWindow *ui,QFileSystemModel *model){
    QString nameGroup;
    QString newNameGroup;
    QString nameGroupDessous;
    QString nameMotif;
    QString newNameMotif;
    QString nameMotifDessous;
    QModelIndex index=ui->treeView->currentIndex();
    QModelIndex indexPlusUn=ui->treeView->indexBelow(index);

       if (index.isValid()){
           if (model->fileInfo(index).isDir()) {
                nameGroup=model->fileInfo(index).baseName();
                if (nameGroup=="Cubicle"){
                    return;
                }
                QString dir=model->fileInfo(index).absolutePath();

                QDir temp(dir);
                QFileInfoList entries = temp.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries);
                int m=entries.size();
                QString numero = nameGroup.left(2);
                int num = numero.toInt();
                if(num==m-1){
                    return;
                }

                while(model->fileInfo(indexPlusUn).isFile()){
                    indexPlusUn=ui->treeView->indexBelow(indexPlusUn);
                }
                nameGroupDessous=model->fileInfo(indexPlusUn).baseName();
                QString nameRest = nameGroup.mid(3);
                QString numeroDessous = nameGroupDessous.left(2);
                QString nameDessousRest = nameGroupDessous.mid(3);

                int numDessous = numeroDessous.toInt();


                if (num<9){
                    newNameGroup = "0"+QString::number(num+1)+"_"+nameRest;
                }else {
                    newNameGroup = QString::number(num+1)+"_"+nameRest;
                }
                QString pathTotalOld = dir+"/"+nameGroup;
                QString pathTotalNew = dir+"/"+newNameGroup;

                if (num<9){
                    if (numDessous==num+1){
                        QString nameGroupPlusUn = "0"+QString::number(num+1)+"_"+nameDessousRest;
                        QString totalnameGroupPlusUn = dir+"/"+nameGroupPlusUn;

                        QString nameGroupPlusUnChange = nameDessousRest;
                        QString totalnameGroupPlusUnChange = dir+"/"+nameGroupPlusUnChange;

                        QDir directory(totalnameGroupPlusUn);
                        directory.rename(totalnameGroupPlusUn,totalnameGroupPlusUnChange);

                        QDir dir1(pathTotalOld);
                        dir1.rename(pathTotalOld, pathTotalNew);

                        QString nameGroupPlusUnChangeCorrect = "0"+QString::number(num)+"_"+nameDessousRest;
                        QString totalnameGroupPlusUnCorrect = dir+"/"+nameGroupPlusUnChangeCorrect;
                        QDir dir2(totalnameGroupPlusUnCorrect);
                        dir2.rename(totalnameGroupPlusUnChange, totalnameGroupPlusUnCorrect);
                        dir2.setSorting(QDir::Name);
                    }
                }else if(num==9){
                    if (numDessous==num+1){
                        QString nameGroupPlusUn = QString::number(num+1)+"_"+nameDessousRest;
                        QString totalnameGroupPlusUn = dir+"/"+nameGroupPlusUn;

                        QString nameGroupPlusUnChange = nameDessousRest;
                        QString totalnameGroupPlusUnChange = dir+"/"+nameGroupPlusUnChange;

                        QDir directory(totalnameGroupPlusUn);
                        directory.rename(totalnameGroupPlusUn,totalnameGroupPlusUnChange);

                        QDir dir1(pathTotalOld);
                        dir1.rename(pathTotalOld, pathTotalNew);

                        QString nameGroupPlusUnChangeCorrect = "0"+QString::number(num)+"_"+nameDessousRest;
                        QString totalnameGroupPlusUnCorrect = dir+"/"+nameGroupPlusUnChangeCorrect;
                        QDir dir2(totalnameGroupPlusUnCorrect);
                        dir2.rename(totalnameGroupPlusUnChange, totalnameGroupPlusUnCorrect);
                        dir2.setSorting(QDir::Name);
                    }
                }else if(num>9){
                    if (numDessous==num+1){
                        QString nameGroupPlusUn = QString::number(num+1)+"_"+nameDessousRest;
                        QString totalnameGroupPlusUn = dir+"/"+nameGroupPlusUn;

                        QString nameGroupPlusUnChange = nameDessousRest;
                        QString totalnameGroupPlusUnChange = dir+"/"+nameGroupPlusUnChange;

                        QDir directory(totalnameGroupPlusUn);
                        directory.rename(totalnameGroupPlusUn,totalnameGroupPlusUnChange);

                        QDir dir1(pathTotalOld);
                        dir1.rename(pathTotalOld, pathTotalNew);

                        QString nameGroupPlusUnChangeCorrect = QString::number(num)+"_"+nameDessousRest;
                        QString totalnameGroupPlusUnCorrect = dir+"/"+nameGroupPlusUnChangeCorrect;
                        QDir dir2(totalnameGroupPlusUnCorrect);
                        dir2.rename(totalnameGroupPlusUnChange, totalnameGroupPlusUnCorrect);
                        dir2.setSorting(QDir::Name);
                    }
                }

         }else{
               QString dir=model->fileInfo(index).absolutePath();
               nameMotif=model->fileInfo(index).baseName();
               QDir temp(dir);
               QFileInfoList entries = temp.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries);
               int m=entries.size();
               QString numero = nameMotif.left(2);
               int num = numero.toInt();
               if(num==m-1){
                   return;
               }

               nameMotifDessous=model->fileInfo(indexPlusUn).baseName();
               QString nameRest = nameMotif.mid(3);
               QString numeroDessous = nameMotifDessous.left(2);
               QString nameDessousRest = nameMotifDessous.mid(3);

               int numDessous = numeroDessous.toInt();

               if (num<9){
                   newNameMotif = "0"+QString::number(num+1)+"_"+nameRest;
               }else {
                   newNameMotif = QString::number(num+1)+"_"+nameRest;
               }
               QString pathTotalOld = dir+"/"+nameMotif+".txt";
               QString pathTotalNew = dir+"/"+newNameMotif+".txt";

               if (num<9){
                   if (numDessous==num+1){
                       QString nameMotifPlusUn = "0"+QString::number(num+1)+"_"+nameDessousRest+".txt";
                       QString totalnameMotifPlusUn = dir+"/"+nameMotifPlusUn;

                       QString nameMotifPlusUnChange = nameDessousRest;
                       QString totalnameMotifPlusUnChange = dir+"/"+nameMotifPlusUnChange+".txt";

                       QFile directory(totalnameMotifPlusUn);
                       directory.rename(totalnameMotifPlusUn,totalnameMotifPlusUnChange);

                       QFile dir1(pathTotalOld);
                       dir1.rename(pathTotalOld, pathTotalNew);

                       QString nameMotifPlusUnChangeCorrect = "0"+QString::number(num)+"_"+nameDessousRest+".txt";
                       QString totalnameMotifPlusUnCorrect = dir+"/"+nameMotifPlusUnChangeCorrect;
                       QFile dir2(totalnameMotifPlusUnCorrect);
                       dir2.rename(totalnameMotifPlusUnChange, totalnameMotifPlusUnCorrect);
                   }
               }else if(num==9){
                   if (numDessous==num+1){
                       QString nameMotifPlusUn = QString::number(num+1)+"_"+nameDessousRest+".txt";
                       QString totalnameMotifPlusUn = dir+"/"+nameMotifPlusUn;

                       QString nameMotifPlusUnChange = nameDessousRest;
                       QString totalnameMotifPlusUnChange = dir+"/"+nameMotifPlusUnChange+".txt";

                       QFile directory(totalnameMotifPlusUn);
                       directory.rename(totalnameMotifPlusUn,totalnameMotifPlusUnChange);

                       QFile dir1(pathTotalOld);
                       dir1.rename(pathTotalOld, pathTotalNew);

                       QString nameMotifPlusUnChangeCorrect = "0"+QString::number(num)+"_"+nameDessousRest+".txt";
                       QString totalnameMotifPlusUnCorrect = dir+"/"+nameMotifPlusUnChangeCorrect;
                       QFile dir2(totalnameMotifPlusUnCorrect);
                       dir2.rename(totalnameMotifPlusUnChange, totalnameMotifPlusUnCorrect);
                   }
               }else if(num>9){
                   if (numDessous==num+1){
                       QString nameMotifPlusUn = QString::number(num+1)+"_"+nameDessousRest+".txt";
                       QString totalnameMotifPlusUn = dir+"/"+nameMotifPlusUn;

                       QString nameMotifPlusUnChange = nameDessousRest;
                       QString totalnameMotifPlusUnChange = dir+"/"+nameMotifPlusUnChange+".txt";

                       QFile directory(totalnameMotifPlusUn);
                       directory.rename(totalnameMotifPlusUn,totalnameMotifPlusUnChange);

                       QFile dir1(pathTotalOld);
                       dir1.rename(pathTotalOld, pathTotalNew);

                       QString nameMotifPlusUnChangeCorrect = QString::number(num)+"_"+nameDessousRest+".txt";
                       QString totalnameMotifPlusUnCorrect = dir+"/"+nameMotifPlusUnChangeCorrect;
                       QFile dir2(totalnameMotifPlusUnCorrect);
                       dir2.rename(totalnameMotifPlusUnChange, totalnameMotifPlusUnCorrect);
                   }
               }
         }
          model->dataChanged(index,index);
   }
}
