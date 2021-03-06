#include "mainwindow.h"


using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new QFileSystemModel(this)),
    saveDir(""),
    emplMotif(""),
    tmpDir(QDir::tempPath())

{
    initUi();
    initControleur();
    connectAction();
    this->ctlPlan.desactiveSelectPlan(plans,true);
    this->setWindowTitle("Cubicle");
    this->setWindowIcon(QIcon(":/icone/cubicle.png"));

    deletePlanLed(0);
    ctlCube.desactivePlan(plans,ui);
    connexion();
    dirOpen=0;
}


void MainWindow::initUi(){
    ui->setupUi(this);
    ui->actionCopy->setDisabled(true);
    ui->actionDelete_pattern->setDisabled(true);
    ui->actionNew_Group->setDisabled(true);
    ui->actionNew_Pattern->setDisabled(true);
    ui->actionPaste_pattern->setDisabled(true);
    ui->actionSave->setDisabled(true);
    ui->actionCut_pattern->setDisabled(true);
    ui->actionSave_as->setDisabled(true);
    ui->actionRaise->setDisabled(true);
    ui->actionLower->setDisabled(true);
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);

    //créer les plans à selectionnées comme QPushButtonPers pour pouvoir effectuer des clics droits dessus
    for(int i=0;i<9;i++){
        plans[i]=new QPushButtonPers(this);
        QString nplan=QString::number(9-i);
        plans[i]->setText("plane"+nplan);
        ui->gridLayout->addWidget(plans[i],2*i,2);
        plans[i]->setUi(ui);
    }
}


void MainWindow::initControleur() {
    this->ctlPlan=ControlPlan2D();
    this->ctlCube=ControlCube3D();
    this->dupPlan=DuppliquerPlan();
    this->ctlArbr=ControlArborescence();
}


void MainWindow::connectAction(){
    connect(ui->actionNew_project,SIGNAL(triggered(bool)),this,SLOT(new_project()));
    connect(ui->actionOpen_directory,SIGNAL(triggered(bool)),this,SLOT(ouvrir_explorer()));
    connect(ui->actionCopy,SIGNAL(triggered(bool)),this,SLOT(copier()));
    connect(ui->actionPaste_pattern,SIGNAL(triggered(bool)),this,SLOT(coller()));
    connect(ui->actionNew_Pattern,SIGNAL(triggered(bool)),this,SLOT(ajouter_motif()));
    connect(ui->actionNew_Group,SIGNAL(triggered(bool)),this,SLOT(ajouter_groupe()));
    connect(ui->actionQuit_2,SIGNAL(triggered(bool)),this,SLOT(controlQuit()));
    connect(ui->actionDelete_pattern,SIGNAL(triggered(bool)),this,SLOT(controlDelete()));
    connect(ui->actionSave,SIGNAL(triggered(bool)),this,SLOT(controlSave()));
    connect(ui->treeView,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(doubleClick()));
    connect(ui->actionCut_pattern,SIGNAL(triggered(bool)),this,SLOT(couper()));
    connect(ui->actionRaise,SIGNAL(triggered(bool)),this,SLOT(monter()));
    connect(ui->actionLower,SIGNAL(triggered(bool)),this,SLOT(descendre()));
    connect(ui->actionSave_as,SIGNAL(triggered(bool)),this,SLOT(controlSaveAs()));
    connect(ui->actionHelp,SIGNAL(triggered(bool)),this,SLOT(helpwindow()));
    connect(ui->actionAbout_CUBICLE,SIGNAL(triggered(bool)),this,SLOT(About()));
    connect(ui->actionRename,SIGNAL(triggered(bool)),this,SLOT(rename()));
    connect(model,SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,SLOT(reordonneRenommage()));
    connect(ui->treeView,SIGNAL(pressed(QModelIndex)),this,SLOT(save()));
    connect(ui->actionCopy_Plane1,SIGNAL(triggered(bool)),this,SLOT(copyPlane()));
    connect(ui->actionPaste_Plane1,SIGNAL(triggered(bool)),this,SLOT(pastePlane()));
    connect(ui->actionCopy_Plane2,SIGNAL(triggered(bool)),this,SLOT(copyPlane()));
    connect(ui->actionPaste_Plane2,SIGNAL(triggered(bool)),this,SLOT(pastePlane()));
    connect(ui->actionCopy_Plane3,SIGNAL(triggered(bool)),this,SLOT(copyPlane()));
    connect(ui->actionPaste_Plane3,SIGNAL(triggered(bool)),this,SLOT(pastePlane()));
    connect(ui->actionCopy_Plane4,SIGNAL(triggered(bool)),this,SLOT(copyPlane()));
    connect(ui->actionPaste_Plane4,SIGNAL(triggered(bool)),this,SLOT(pastePlane()));
    connect(ui->actionCopy_Plane5,SIGNAL(triggered(bool)),this,SLOT(copyPlane()));
    connect(ui->actionPaste_Plane5,SIGNAL(triggered(bool)),this,SLOT(pastePlane()));
    connect(ui->actionCopy_Plane6,SIGNAL(triggered(bool)),this,SLOT(copyPlane()));
    connect(ui->actionPaste_Plane6,SIGNAL(triggered(bool)),this,SLOT(pastePlane()));
    connect(ui->actionCopy_Plane7,SIGNAL(triggered(bool)),this,SLOT(copyPlane()));
    connect(ui->actionPaste_Plane7,SIGNAL(triggered(bool)),this,SLOT(pastePlane()));
    connect(ui->actionCopy_Plane8,SIGNAL(triggered(bool)),this,SLOT(copyPlane()));
    connect(ui->actionPaste_Plane8,SIGNAL(triggered(bool)),this,SLOT(pastePlane()));
    connect(ui->actionCopy_Plane9,SIGNAL(triggered(bool)),this,SLOT(copyPlane()));
    connect(ui->actionPaste_Plane9,SIGNAL(triggered(bool)),this,SLOT(pastePlane()));

    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeView, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(ShowContextMenu(const QPoint&)));

}

//le menu des clics droits sur l'arborescence
void MainWindow::ShowContextMenu(const QPoint& p){

    QPoint globalPos = ui->treeView->mapToGlobal(p);
    QMenu myMenu;
    QModelIndex index=ui->treeView->currentIndex();
    QString dir=model->fileInfo(index).absolutePath();
    QString nameGroup=model->fileInfo(index).baseName();
    if(nameGroup=="Cubicle"){
        return;
    }

    if(index.isValid()){
        if (model->fileInfo(index).isDir()) {
            if((dir+'/'+nameGroup)!=saveDir){

                myMenu.addAction(ui->actionNew_Pattern);
                myMenu.addAction(ui->actionPaste_pattern);
                myMenu.addAction(ui->actionRaise);
                myMenu.addAction(ui->actionLower);
            }
        }
        else {
            myMenu.addAction(ui->actionSave);
            myMenu.addAction(ui->actionCopy);
            myMenu.addAction(ui->actionCut_pattern);
            myMenu.addAction(ui->actionDelete_pattern);
            myMenu.addAction(ui->actionRename);
        }
    }

    myMenu.exec(globalPos);
}


void MainWindow::save(){

    this->ctlArbr.ctlSave(cubeMotif,emplMotif);
}


//ouvre le répertoire de travail
void MainWindow::ouvrir_explorer(){

    if (!saved) {
        int enregistrer=QMessageBox::question(this, "Quit", " Do you want to save the current project ?");
        if (enregistrer==QMessageBox::Yes){
            controlSave();
        }
    }

    this->ctlPlan.desactiveSelectPlan(plans,true);
    QString  tempdir=QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home");

    if (tempdir=="") {
        qDebug()<<tempdir;
        return;
    }
    else {
        QFileInfo f=QFileInfo(tempdir);
        saveDir = f.absolutePath();
        QString nomDossier=f.baseName();
        qDebug()<<" le nom du dossier est "+nomDossier;
        if (nomDossier!="Cubicle") {
            QMessageBox::information(this,tr("warning"),"cannot open this directory, please choose the folder Cubicle");
            ouvrir_explorer();
        }
        qDebug()<<" le chemin du namedir est "+saveDir;
    }

    QDir dir(saveDir+"/Cubicle");
    QStringList nameFilter;
    //nameFilter<<"*.txt";
    QFileInfoList list=dir.entryInfoList(QDir::Files);
    QFileInfoList list2=dir.entryInfoList(QDir::Dirs);

    //on ne doit pas charger le dossier d'un groupe de motif mais plutot le repertoire des groupes de motif
    if ((!list.isEmpty()) and (!list2.isEmpty())) {
        QMessageBox::information(this,tr("warning"),"cannot open this directory, please choose the source directory");
        return;
    }

    this->setWindowTitle("Cubicle["+saveDir+"/Cubicle"+"]");
    // je copie le dossier Cubicle dans le workspace"
    QDir dir0(tmpDir+"/workspace");

    if (!dir0.exists()){
        dir0.mkpath(".");
    }

    QDir dir2(tmpDir+"/workspace/Cubicle");

    if (dir2.exists()){
        removeDir(tmpDir+"/workspace/Cubicle");
    }

    copy(saveDir,tmpDir+"/workspace","Cubicle");
    tree();
    dirOpen=1;
    saved=false;
    emplMotif="";
    ui->actionSave_as->setDisabled(false);
    this->cubeMotif=Cube();
    deletePlanLed(1);
    ctlCube.desactivePlan(plans,ui);
    this->liste_vecteur3D.clear();
    this->ui->widget->setListPoints(liste_vecteur3D);
    ui->widget->setListPlan(liste_vecteur3D);
    ui->actionNew_Group->setDisabled(false);
}


void MainWindow::couper(){
    copier();
    copierCouper=1;
}


void MainWindow::copier(){
    QModelIndex index=ui->treeView->currentIndex();
    if (model->fileInfo(index).isFile()) {
        dirOrFile=false;
        paste_element=model->fileInfo(index).absoluteFilePath();
        nom_copie=model->fileInfo(index).baseName();
        copierCouper=0;
    }
}


void MainWindow::coller(){

    QString nameGroup;

    if (!dirOrFile){
        QModelIndex index=ui->treeView->currentIndex();
        if (index.isValid()){
            if (model->fileInfo(index).isDir()) {
                QString dir=model->fileInfo(index).absolutePath();
                nameGroup=model->fileInfo(index).baseName();
                // on vérifie qu'on ne colle pas dans Cubicle(répertoire des groupes)
                if((dir+'/'+nameGroup)!=tmpDir+"/workspace/Cubicle"){
                    QFile file(paste_element);
                    if (copierCouper==1){
                        qDebug()<< "le nouveau fichier après cut paste est "+ dir+"/"+nameGroup+"/"+nom_copie;
                        if(file.fileName()!=dir+"/"+nameGroup+"/"+nom_copie){
                            qDebug() << "le nom du fichier à couper est"+file.fileName();
                            QFileInfo fi(file.fileName());
                            QString oldNameGroup =fi.absolutePath();
                            qDebug()<< "le groupe ou se trouve le fichier coupé est "+fi.absolutePath();
                            file.rename(dir+"/"+nameGroup+"/"+nom_copie);
                            this->setEmpMotif("");
                            reordonneGroup(oldNameGroup);
                            reordonneGroup(dir+"/"+nameGroup);
                        }
                    }
                    else {
                        int dernierRang=-1 ;
                        int i=0;
                        while(index.child(i,0).isValid()){
                            dernierRang=index.child(i,0).row();
                            i++;
                        }
                        QString nouveauRang=QString::number(dernierRang+1);
                        if((dernierRang+1)<10)
                            nouveauRang="0"+nouveauRang;

                        qDebug() << "le dernier rang est "+ nouveauRang;

                        nom_copie=nouveauRang+nom_copie.mid(2);
                        bool valid = file.copy(dir+"/"+nameGroup+"/"+nom_copie+"_copie");

                        new_index=model->index(dir+"/"+nameGroup+"/"+nom_copie+"_copie");
                        ui->treeView->setCurrentIndex(new_index);
                        ui->treeView->selectionModel()->select(new_index,
                                                               QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
                        ui->treeView->edit(new_index);

                        if (!valid){
                            qDebug()<<"copier coller impossible";
                        }
                    }


                }
            }
        }
    }
}


void MainWindow::tree(){

    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->setRootPath(tmpDir + "/workspace"));
    model->setReadOnly(false);
    QModelIndex index=model->index(tmpDir+"/workspace");

    if(index.isValid()){
        ui->treeView->setRootIndex(index);
    }

    //on ouvre toujours le dossier de travail présent sur le workspace
    index= model->index(tmpDir+"/workspace/Cubicle");

    if(index.isValid()){
        ui->treeView->setExpanded(index,true);
        ui->treeView->scrollTo(index);
    }

    for(int i=1;i<4;i++){
        ui->treeView->hideColumn(i);
    }

    ui->treeView->resizeColumnToContents(0);
    ui->actionNew_Pattern->setEnabled(true);
    ui->actionDelete_pattern->setEnabled(true);
    ui->actionCopy->setDisabled(false);
    ui->actionPaste_pattern->setDisabled(false);
    ui->actionCut_pattern->setDisabled(false);
    ui->actionSave->setDisabled(false);
    ui->actionRaise->setDisabled(false);
    ui->actionLower->setDisabled(false);
    ui->actionNew_Group->setDisabled(false);
    ui->pushButton->setDisabled(false);
    ui->pushButton_2->setDisabled(false);
    ui->pushButton_3->setDisabled(false);
    ui->pushButton_4->setDisabled(false);
}

//créer un nouveau motif
void MainWindow::ajouter_motif(){

    QModelIndex index=ui->treeView->currentIndex();

    if (index.isValid()){
        if (model->fileInfo(index).isDir()) {
            QString dir=model->fileInfo(index).absolutePath();
            QString nameGroup=model->fileInfo(index).baseName();

            if((dir + "/" + nameGroup) !=tmpDir){
                qDebug()<<"l'emplacement du dossier est "+dir;
                qDebug()<<"le nom du dossier est "+nameGroup;

                if(nameGroup!="Cubicle"){
                    NouveauMotif m=NouveauMotif("New Pattern",dir+"/"+nameGroup);
                    new_index =model->index(m.getNameFile());
                    qDebug() << "le path du pattern ajouté est "+ m.getNameFile();
                    ui->treeView->setCurrentIndex(new_index);
                    ui->treeView->selectionModel()->select(new_index,
                                                           QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
                    ui->treeView->edit(new_index);
                }
                else {
                    QMessageBox::information(this,tr("warning"),"cannot add a pattern, please choose or add a group");
                }
            }
        }
    }
}


void MainWindow::new_project(){
    if (!saved) {
        int enregistrer=QMessageBox::question(this, "Quit", " Do you want to save the current project ?");
        if (enregistrer==QMessageBox::Yes){
            controlSave();

        }

    }
    this->ctlPlan.desactiveSelectPlan(plans,true);
    QModelIndex index=model->index(tmpDir);
    QDir dir0(tmpDir+"/workspace");
    if(!dir0.exists()){

        dir0.mkpath(".");

    }
    QDir dir(tmpDir+"/workspace/Cubicle");
    if (dir.exists()){

        removeDir(tmpDir+"/workspace/Cubicle");
        if(!dir0.exists()){
            dir0.mkpath(".");

        }
    }

    index=model->index(tmpDir+"/workspace");

    if(!dir.exists()){
        dir.mkpath(".");
    }

    saveDir="";
    saved=false;
    dirOpen=2;
    emplMotif="";
    this->setWindowTitle("Cubicle") ;
    tree();
    ui->actionSave_as->setDisabled(false);
    saved=false;
    this->cubeMotif=Cube();
    deletePlanLed(1);
    ctlCube.desactivePlan(plans,ui);
    this->liste_vecteur3D.clear();
    this->ui->widget->setListPoints(liste_vecteur3D);
    ui->widget->setListPlan(liste_vecteur3D);
    ui->actionNew_Group->setDisabled(false);
}


void MainWindow::ajouter_groupe()
{
    int m;
    QString indice;
    QModelIndex index =model->index(tmpDir+"/workspace/Cubicle",0);
    QString name ="NewGroup";
    QDir dir(tmpDir+"/workspace/Cubicle");
    QFileInfoList entries = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries);
    dir.setSorting( QDir::Name);
    m=entries.size();

    if (m<10){
        indice ="0"+QString::number(m)+"_";
    }else {
        indice=QString::number(m)+"_";
    }

    name = indice + name;
    model->mkdir(index,name);
    new_index =model->index(tmpDir+"/workspace/Cubicle");
    new_index =model->index(tmpDir+"/workspace/Cubicle/"+name);
    qDebug() << "le nouveau index pointe sur "+tmpDir+"/workspace/Cubicle/"+name;
    ui->treeView->setCurrentIndex(new_index);
    ui->treeView->selectionModel()->select(new_index,
                                           QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
    ui->treeView->edit(new_index);
    dirOpen=1;
}


void MainWindow::monter(){
    this->ctlArbr.ctlSave(cubeMotif,emplMotif);
    this->ctlArbr.monter(ui,model);
    this->setEmpMotif("");
}


void MainWindow::descendre(){
    this->ctlArbr.ctlSave(cubeMotif,emplMotif);
    this->ctlArbr.descendre(ui,model);
    this->setEmpMotif("");
}


void MainWindow::controlQuit(){
    if (!this->saved) {
        int enregistrer=QMessageBox::question(this, "Quit", " Do you want to save the project before you quit ?");
        if (enregistrer==QMessageBox::Yes){
            controlSave();
            this->close();
        }
        else
        {
            this->close();
        }
    }
    else {
        this->close();
    }
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    controlQuit();
}


void MainWindow::controlDelete(){
    QModelIndex index=ui->treeView->currentIndex();
    if (model->fileInfo(index).isFile()) {
        dirOrFile=false;

        QString name=model->fileInfo(index).absoluteFilePath();
        QString path=model->fileInfo(index).absolutePath();
        qDebug() << "le path du fichier à supprimer est "+path;
        QFile file(name);
        int reponse = QMessageBox::question(this, "Quit", " Are you sure you want to delete this pattern ?");
        if (reponse == QMessageBox::Yes) {
            file.remove();
            new_index=model->index(path);

            ui->treeView->setCurrentIndex(new_index);
            ui->treeView->selectionModel()->select(new_index,
                                                   QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);

            this->deletePlanLed(1);
            ctlCube.desactivePlan(plans,ui);
        }
        reordonneGroup(path);
    }
    else {
        dirOrFile=true;
    }

}


void MainWindow::controlSave(){
    //enregistrer les modifications du dernier motifs
    GestionFichier ges;
    ges.ouvrir(this->emplMotif,this->cubeMotif);
    //si on n'as pas fait saveAs on doit choisir un répertoir
    if (saveDir=="") {
        controlSaveAs();
    }
    else {

        removeDir(saveDir+"/Cubicle");
        copy(tmpDir+"/workspace",saveDir,"Cubicle");
        saved=true;
        QMessageBox msgBox;
        msgBox.setText("Your project Cubicle has been succesfully saved");
        msgBox.exec();
    }

}


void MainWindow::controlSaveAs(){
    QString destPath=QFileDialog::getExistingDirectory(this, tr("Save as"),"/home");

    if (destPath=="") {qDebug()<<destPath;
        return;
    }

    QDir dir0(destPath);
    if(dir0.dirName()=="Cubicle"){
        QMessageBox::information(this,tr("warning"),"This directory is already named Cubicle, please choose an other directory");
        controlSaveAs();
    }
    qDebug()<<"la destination est "+destPath;
    QDir dir(destPath+"/Cubicle");

    if (dir.exists()) {

        int remplacer=QMessageBox::question(this, "Exist", "Project Cubicle already exists in this directory, do you want to replace it ?");

        if (remplacer==QMessageBox::No){
            controlSaveAs();
        }

        else {
            saveDir=destPath;

            controlSave();
        }

    }
    else {
        saveDir= destPath;
        qDebug()<< "le nouveau path est" + saveDir;
        controlSave();
        this->setWindowTitle("Cubicle["+destPath+"/Cubicle"+"]") ;

    }
}


void MainWindow::copy(const QString &sourcePath, const QString &destPath, const QString &name)
{
    static const QStringList filters = QStringList () << "*";
    static const QDir::Filters flags = QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files | QDir::Hidden;
    QString sourceObjectPath = sourcePath+"/"+name;
    QString destObjectPath = destPath +"/"+name;
    QDir dir(destObjectPath);

    if (dir.exists()) {
        removeDir(destObjectPath) ;
        qDebug()<<"j'ai supprimé le dossier "+destObjectPath;
    }
    QFileInfo fi (sourceObjectPath);

    if (fi.isDir ()) {
        qDebug () << "Créer le répertoire " << destObjectPath;
        QDir destDir(destPath);
        destDir.mkdir(name);
        qDebug () << "Recopier dedans, récursivement, le contenu de" << sourceObjectPath;
        QDir currentSourceDir (sourceObjectPath);
        const QStringList fileList = currentSourceDir.entryList (filters, flags);
        foreach (const QString &content, fileList) {
            copy (sourceObjectPath, destObjectPath, content);
        }
    } else {
        qDebug () << "Copier le fichier " << name << "de" << sourcePath << "vers" << destPath;
        QFile::copy (sourceObjectPath, destObjectPath);
    }
}


bool MainWindow::removeDir(const QString& PathDir)
{
    bool result = true;
    QDir dir(PathDir);

    if (dir.exists(PathDir)) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeDir(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result) {
                return result;
            }
        }
        result = dir.rmdir(PathDir);
    }
    return result;
}
void MainWindow::reordonneGroup(QString nameGroup){
    QDir dir(nameGroup);
    if (dir.exists()) {
        int i=0;
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isFile()) {
                QString ii=QString::number(i);
                if (i<10)
                    ii="0"+QString::number(i);
                QString namefile =info.baseName();
                QString dirfile=info.absolutePath();
                QFile file(dirfile+"/"+namefile);
                qDebug()<<"l'ancien path est "+dirfile+"/"+namefile;
                namefile=ii+"_"+namefile.mid(3);
                qDebug()<<"le namefile est "+namefile;
                qDebug()<<"le dirfile est "+dirfile;
                qDebug()<< dirfile+"/"+namefile;

                file.rename(dirfile+"/"+namefile);
                this->setEmpMotif("");
                i++;
            }
        }
    }
}


void MainWindow::reordonneRenommage(){
    QModelIndex index = ui->treeView->currentIndex();
    int i= index.row();
    qDebug() << "le rang du groupe est"+ QString::number(i);
    QString nameGroup = model->fileName(index);
    qDebug() << "le nom du groupe à modifier est "+ nameGroup;
    QString path = model->fileInfo(index).absolutePath();
    qDebug() << "le path du groupe est "+ path;
    QDir dir(path);
    QString indice;
    if (i<10){
        indice = "0"+QString::number(i)+"_";
    }else {
        indice = QString::number(i)+"_";
    }
    bool ok;
    int value=nameGroup.left(2).toInt(&ok);
    QString newNameGroup;
    if((ok)&&(nameGroup[2]=='_')){
     newNameGroup=indice+nameGroup.mid(3);
    }
    else{
           newNameGroup=indice+nameGroup;
    }

    QString pathTotalOld = path+"/"+nameGroup;
    QString pathTotalNew = path+"/"+newNameGroup;
    if (model->fileInfo(index).isDir()){
        dir.rename(pathTotalOld,pathTotalNew);
    }
    else{
            QFile file(pathTotalOld);
            file.rename(pathTotalNew);
            this->setEmpMotif("");
    }
}

void MainWindow::rename(){
    QModelIndex index=ui->treeView->currentIndex();
    if(index.isValid()){
        ui->treeView->selectionModel()->select(index,
                                               QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
        ui->treeView->edit(index);

    }
}


// supprimer  le plan 2D Lors d'un double clic sur un nouveau motif
void MainWindow::doubleClick(){
    QModelIndex index=ui->treeView->currentIndex();
    if (model->fileInfo(index).isFile()) {
        dirOrFile=false;

        //réactiver la sélection des plans
        this->ctlPlan.desactiveSelectPlan(plans,false);

        QString name=model->fileInfo(index).absoluteFilePath();
        this->currentPattern=model->fileInfo(index).baseName();

        if(name.compare(this->getEmplMotif())!=0){
            this->setEmpMotif(name);
            this->cubeMotif=Cube();
            deletePlanLed(1);
            ctlCube.desactivePlan(plans,ui);
            this->liste_vecteur3D.clear();
            this->ui->widget->setListPoints(liste_vecteur3D);
            ui->widget->setListPlan(liste_vecteur3D);
            GestionFichier ges;
            //parser le fichier afin de remplir la liste des vecteurs 3D
            QList<QVector3D> l;
            l=ges.parser(name,l);

            if(!l.empty()){
                this->ui->widget->setListPoints(l);
                for (QVector3D u:l){
                    Led l=this->cubeMotif.getList1()->value(u.y()).getLed(fabs(8-u.z()),fabs(8-u.x()));
                    l.modifierEtat();
                    Plan p=this->cubeMotif.getList1()->value(u.y());
                    p.updatePlan(l,fabs(8-u.z()),fabs(8-u.x()));
                    this->cubeMotif.updateCube(p,u.y());
                    liste_vecteur3D.append(u);
                    this->ui->widget->setListPoints(liste_vecteur3D);
                }

            }
            //séléctionner le 1er plan par défaut et l'afficher pour guider l'utilisateur
            this->setNumeroPlan(ctlCube.affichePlanLed("00",this->ui,plans,this->buttons,this->cubeMotif));
        }
        else {
            dirOrFile=true;
        }
    }
}


void MainWindow::deletePlanLed(int nfois){
    for (int i = 0; i < 9; i++) {
        for (int j=0;j<9; j++){
            QString col=QString::number(i);
            QString lig=QString::number(j);
            QString text=lig+col;
            int num=text.toInt(0,10);
            if(nfois==0){
                buttons[num]=new QPushButton("",this);
                buttons[num]->setGeometry(30, 30, 30, 30);
                buttons[num]->move(30*i+350, 30*j+200);
            }
            buttons[num]->hide();
        }
    }
}
void MainWindow::allume_led(const QString & valeur){
    this->liste_vecteur3D=ctlPlan.controlLed(valeur,this->cubeMotif,this->NumeroPlan,this->liste_vecteur3D,this->ui,this->buttons);
}
void MainWindow::affiche_plan_Cube(const QString &valeur){
    this->setNumeroPlan(ctlCube.affichePlanLed(valeur,this->ui,plans,this->buttons,this->cubeMotif));
}


//copier un plan pour duplication
void MainWindow::copyPlane(){

    //récupérer le sender (action) du slot
    QAction* action = qobject_cast<QAction* >(sender());
    QString nom=action->objectName();

    QString n=(QString)nom[16];
    qDebug()<<"le bouton qui  émet le siganl copier est "+n;
    int numPlan=n.toInt(0,10);
    this->numeroPlanADuppliquer=numPlan-1;
}

//coller un plan
void MainWindow::pastePlane(){

    QAction* action = qobject_cast<QAction* >(sender());
    QString nom=action->objectName();

    QString n=(QString)nom[17];
    qDebug()<<"le bouton qui émet le siganl coller est "+n;
    int numeroPlanPaste=n.toInt(0,10)-1;

    QList<QVector3D> l=this->dupPlan.collerPlan( cubeMotif,this->numeroPlanADuppliquer, numeroPlanPaste,liste_vecteur3D,emplMotif);
    //mettre à jour les vecteurs 3D
    liste_vecteur3D=l;
    this->ui->widget->setListPoints(liste_vecteur3D);
    this->ui->widget->setListPlan(liste_vecteur3D);
}

//connecter tous les plans au signal affiche_plan_cube
void MainWindow::connectPlanToAffiche(){

    QSignalMapper *signalMapper = new QSignalMapper(this);

       for (int i=0;i<9;i++){

           connect(plans[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
           QString text=QString::number(8-i);
           signalMapper->setMapping(plans[i], "0"+text);
       }
       connect(signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(affiche_plan_Cube(const QString &)));

}

void MainWindow::connexion(){

    connectPlanToAffiche();
    QSignalMapper *signalMapper1 = new QSignalMapper(this);
    for (int i = 0; i < 9; i++) {
        for (int j=0;j<9; j++){
            QString col=QString::number(i);
            QString lig=QString::number(j);
            QString text=lig+col;
            int num=text.toInt(0,10);
            connect(buttons[num], SIGNAL(clicked()), signalMapper1, SLOT(map()));
            signalMapper1->setMapping(buttons[num], text);
        }
    }
    connect(signalMapper1, SIGNAL(mapped(const QString &)), this, SLOT(allume_led(const QString &)));
}


int MainWindow::getNumeroPlan()
{
    return NumeroPlan;
}

void MainWindow::setNumeroPlan(int i)
{
    NumeroPlan=i;
}

void MainWindow::setEmpMotif(QString nom){
    this->emplMotif=nom;
}

QString MainWindow::getEmplMotif(){
    return this->emplMotif;
}


MainWindow::~MainWindow()
{
    delete ui;
    delete model;
}

void MainWindow::on_pushButton_clicked()
{
    monter();
}

void MainWindow::on_pushButton_2_clicked()
{
    descendre();
}

void MainWindow::on_pushButton_3_clicked()
{
    ajouter_motif();
}

void MainWindow::on_pushButton_4_clicked()
{
   ajouter_groupe();
}

void MainWindow::helpwindow(){

    DialogHelp h;
    h.show();
    h.exec();
}

void MainWindow::About(){
    DialogHelp h;
    h.AboutUS();
}
