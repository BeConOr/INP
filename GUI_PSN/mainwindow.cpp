#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "data.h"
#include "units.h"
#include "currtask.h"
#include "Struck.h"
#include <QtWidgets>
#include "geometry.h"
#include "line.h"
#include "circle.h"
#include "ellipse.h"
#include "arc.h"
#include "bound.h"
#include "mesh.h"
#include "iostream"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();

    setCurrentFile(QString());
    setUnifiedTitleAndToolBarOnMac(true);

    inData.typeT = {"Laplace", "Poisson", "Trace", "Beams"};
    inData.geomT = {"Plane", "Plane Ext", "Axial", "Harmonics"};
    inData.meshArr = {"No Listing", "Parameters", "Arrays", "Matrices"};

    stData = {0, 2, 0, 0, 0, true, true, true, 0, 0.5, 0, 0.0, 0.0};

    for(int i = 0; i < 7; i++){
        order[i] = 0;
    }

    coef = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};

    task = new CurrTask(stData, coef, order);
    graphicsView = new View();
    ui->centralLay->addWidget(graphicsView);
    scene = new QGraphicsScene();
    graphicsView->setScene(scene);
    graphicsView->setRenderHint(QPainter::Antialiasing);                // Устанавливаем сглаживание
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключаем скроллбар по вертикали
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    scene->setSceneRect(QRectF(QPointF(0, 0), QSizeF(scene->width(), scene->height())));// Отключаем скроллбар по горизонтали
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::launchData(){
    Data *DataDialog = new Data(inData, stData);

    if (DataDialog->exec() == QDialog::Accepted) {
        StartData par = DataDialog->getPar();
        par.copy(&stData);
        task->setParam(stData);
    }
            delete DataDialog;
}

void MainWindow::launchUnits(){
    Units *UnitsDialog = new Units(inUnits, order);

    if (UnitsDialog->exec() == QDialog::Accepted) {
        UnitsDialog->passUnits(&coef, order);
    }
            delete UnitsDialog;
}

void MainWindow::launchGeom(){
    Geometry *GeomDialog = new Geometry(figureList);
    connect(GeomDialog, &Geometry::sendList, this, &MainWindow::getFigureList);
    connect(GeomDialog, &Geometry::Exit, this, &MainWindow::slotExit);
    GeomDialog->showFullScreen();
//    if(GeomDialog->){
//        disconnect(GeomDialog, &Geometry::sendList, this, &MainWindow::getFigureList);
//        disconnect(GeomDialog, &Geometry::Exit, this, &MainWindow::slotExit);
//        delete GeomDialog;
//    }
}

void MainWindow::launchBound(){
    Bound *BoundDialog = new Bound(figureList);
    BoundDialog->show();
}

void MainWindow::launchMesh(){
    Mesh *MeshDialog = new Mesh(mesh_size);
    MeshDialog->show();
    if (MeshDialog->exec() == QDialog::Accepted) {
        mesh_size = MeshDialog->sizeVal();
    }
            delete MeshDialog;
    qDebug() << mesh_size;
}
//! [4]

//! [5]
void MainWindow::newFile()
//! [5] //! [6]
{
    if (maybeSave()) {
        stData = {0, 2, 0, 0, 0, true, true, true, 0, 0.5, 0, 0.0, 0.0};

        for(int i = 0; i < 7; i++){
            order[i] = 0;
        }

        coef = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
        task->setParam(stData);
        task->setUnits(coef, order);
        setCurrentFile(QString());
        foreach(Figure *item, figureList){
            item->deleteLater();
        }
        figureList.clear();
    }
}
//! [6]

//! [7]
void MainWindow::open()
//! [7] //! [8]
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/", tr("Work file (*.p2n)"));
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}
//! [8]

//! [9]
bool MainWindow::save()
//! [9] //! [10]
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}
//! [10]

//! [11]
bool MainWindow::saveAs()
//! [11] //! [12]
{
    QFileDialog dialog(this, tr("Open File"), "/poisson", tr("Work file (*.p2n)"));
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() != QDialog::Accepted)
        return false;
    return saveFile(dialog.selectedFiles().first());
}

void MainWindow::createActions()
//! [17] //! [18]
{

    //QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QMenu *fileMenu = ui->menubar->addMenu(tr("&File"));
    //QToolBar *fileToolBar = new QToolBar(this);
    QToolBar *fileToolBar = addToolBar(tr("File"));
    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
    QAction *newAct = new QAction(newIcon, tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
    fileMenu->addAction(newAct);
    fileToolBar->addAction(newAct);

//! [19]
    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
    QAction *openAct = new QAction(openIcon, tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAct);
    fileToolBar->addAction(openAct);
//! [18] //! [19]

    const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
    QAction *saveAct = new QAction(saveIcon, tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);
    fileMenu->addAction(saveAct);
    fileToolBar->addAction(saveAct);

    const QIcon saveAsIcon = QIcon::fromTheme("document-save-as");
    QAction *saveAsAct = fileMenu->addAction(saveAsIcon, tr("Save &As..."), this, &MainWindow::saveAs);
    //QAction *saveAsAct = fileMenu->addAction(saveAsIcon, tr("Save &As..."));
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));

//! [20]

    fileMenu->addSeparator();

    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    QAction *exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);
//! [20]
    exitAct->setStatusTip(tr("Exit the application"));

//! [21]
    QMenu *dataMenu = ui->menubar->addMenu(tr("&Data"));
    QToolBar *editToolBar = addToolBar(tr("Data"));
    const QIcon paramIcon = QIcon::fromTheme("application-exit");
    QAction *paramAct = dataMenu->addAction(paramIcon, tr("P&arameters"), this, &MainWindow::launchData);
    paramAct->setStatusTip(tr("Set parameters of the task"));

    const QIcon unitsIcon = QIcon::fromTheme("application-exit");
    QAction *unitsAct = dataMenu->addAction(unitsIcon, tr("U&nits"), this, &MainWindow::launchUnits);
    unitsAct->setStatusTip(tr("Set units of the task"));
//!
#ifndef QT_NO_CLIPBOARD
//    const QIcon cutIcon = QIcon::fromTheme("edit-cut", QIcon(":/images/cut.png"));
//    QAction *cutAct = new QAction(cutIcon, tr("Cu&t"), this);
////! [21]
//    cutAct->setShortcuts(QKeySequence::Cut);
//    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
//                            "clipboard"));
    //connect(cutAct, &QAction::triggered, textEdit, &QPlainTextEdit::cut);
    //dataMenu->addAction(cutAct);
    //editToolBar->addAction(cutAct);
    //editToolBar->addAction(pasteAct);

    menuBar()->addSeparator();

    QMenu *geomMenu = ui->menubar->addMenu(tr("&Geometry"));
    const QIcon geomIcon = QIcon::fromTheme("application-exit");
    QAction *geomAct = geomMenu->addAction(geomIcon, tr("Set& geometry"), this, &MainWindow::launchGeom);
    geomAct->setStatusTip(tr("Set geometry of the task"));

    const QIcon boundIcon = QIcon::fromTheme("application-exit");
    QAction *boundAct = geomMenu->addAction(boundIcon, tr("Boundary& condition"), this, &MainWindow::launchBound);
    boundAct->setStatusTip(tr("Define boundary condition"));
    const QIcon meshIcon = QIcon::fromTheme("application-exit");
    QAction *meshAct = geomMenu->addAction(boundIcon, tr("&Mesh"), this, &MainWindow::launchMesh);
    meshAct->setStatusTip(tr("Set mesh"));
    //QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
    QMenu *viewMenu = ui->menubar->addMenu(tr("&View"));


    QMenu *traceMenu = ui->menubar->addMenu(tr("&Trace"));
    QMenu *procMenu = ui->menubar->addMenu(tr("&Process"));
    QMenu *runMenu = ui->menubar->addMenu(tr("&Run"));

    const QIcon fieldIcon = QIcon::fromTheme("application-exit");
    QAction *fieldAct = runMenu->addAction(fieldIcon, tr("Field& files"), this, &MainWindow::fieldFileWrite);
    fieldAct->setStatusTip(tr("Create field files"));

    QMenu *resMenu = ui->menubar->addMenu(tr("&Results"));
    QMenu *winMenu = ui->menubar->addMenu(tr("&Window"));

#endif // !QT_NO_CLIPBOARD

    QMenu *helpMenu = ui->menubar->addMenu(tr("&Help"));
    //QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
    QAction *aboutAct = helpMenu->addAction(tr("&About"));
    aboutAct->setStatusTip(tr("Show the application's About box"));

#ifndef QT_NO_CLIPBOARD
    //cutAct->setEnabled(false);
//! [23] //! [24]
    //copyAct->setEnabled(false);
    //connect(textEdit, &QPlainTextEdit::copyAvailable, cutAct, &QAction::setEnabled);
    //connect(textEdit, &QPlainTextEdit::copyAvailable, copyAct, &QAction::setEnabled);
#endif // !QT_NO_CLIPBOARD
}

void MainWindow::setCurrentFile(const QString &fileName)
//! [46] //! [47]
{
    curFile = fileName;
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.p2n";
    setWindowFilePath(shownName);
}

bool MainWindow::maybeSave()
//! [40] //! [41]
{
//    if (!textEdit->document()->isModified())
//        return true;
//    const QMessageBox::StandardButton ret
//        = QMessageBox::warning(this, tr("Application"),
//                               tr("The document has been modified.\n"
//                                  "Do you want to save your changes?"),
//                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
//    switch (ret) {
//    case QMessageBox::Save:
//        return save();
//    case QMessageBox::Cancel:
//        return false;
//    default:
//        break;
//    }
//    return true;
    return true;
}

bool MainWindow::saveFile(const QString &fileName)
//! [44] //! [45]
{
    QString errorMessage;
    fileN = fileName.mid(0, (fileName.count()-4));

    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QSaveFile file(fileN + ".p2n");
    QFile fileGeom(fileN + ".geom");
    fileGeom.open(QFile::WriteOnly | QFile::Text);
    QTextStream outGeo(&fileGeom);   // we will serialize the data into the file
    outGeo << figureList.count() << "\n";
    foreach(Figure *item, figureList){
        double* angles = item->getAngles();
        outGeo << item->startPoint().x() << "|" << item->startPoint().y() << "|" << item->endPoint().x() << "|" << item->endPoint().y() << "|" << angles[0] << "|" << angles[1] << "|"<< item->getType() << "|" << item->getGroupId() << "|" << item->getGroupName() << "|" << item->getBound().type << "|" << item->getBound().method << "|" << item->getBound().value[0] << "|" << item->getBound().value[1] << "|" << item->itemName << "\n";
    }
    fileGeom.close();
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        out << stData.typeT << "\n";
        out << stData.geomT << "\n";
        out << stData.stream << "\n";
        out << stData.Q << "\n";
        out << stData.E << "\n";
        out << stData.H << "\n";
        out << stData.matrix << "\n";
        out << stData.field << "\n";
        out << stData.trace << "\n";
        out << stData.step << "\n";
        out << stData.numb << "\n";
        out << stData.umin << "\n";
        out << stData.umax << "\n";
        out << mesh_size << "\n";
        for(int i = 0; i < 7; i++){
            out << order[i] << "\n";
        }
        if (!file.commit()) {
            errorMessage = tr("Cannot write file %1:\n%2.")
                           .arg(QDir::toNativeSeparators(fileName), file.errorString());
        }
    } else {
        errorMessage = tr("Cannot open file %1 for writing:\n%2.")
                       .arg(QDir::toNativeSeparators(fileName), file.errorString());
    }
    QGuiApplication::restoreOverrideCursor();

    if (!errorMessage.isEmpty()) {
        QMessageBox::warning(this, tr("Application"), errorMessage);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::loadFile(const QString &fileName)
//! [42] //! [43]
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    if(!figureList.isEmpty()){
        foreach(Figure *figure, figureList){
            figure->deleteLater();
        }
        figureList.clear();
    }

    QString geomName = fileName.mid(0, fileName.indexOf(".", 0));
    fileN = geomName;
    qDebug() << fileN;

    QFile fileGeom(geomName + ".geom");
    fileGeom.open(QIODevice::ReadOnly);
    QTextStream inGeo(&fileGeom);
    QString line;
    while (inGeo.readLineInto(&line)) {
        qDebug() << line;
        int start = -1;
        int end = 0;
        int counter = 1;
        QString type;
        QString group;
        int typeB = 0;
        QString itemName;
        bool method = false;
        double value[2] = {0.0, 0.0};
        int ID = 0;
        QList<qreal> coor;
        bool flag = true;
        while(flag){
            end = line.indexOf("|", start+1);
            qDebug() << "start = "<<start;
            qDebug() << "end = "<<end;
//            if(end == -1){
//                type = line.mid(start+1);
//            }else{
//                coor.append(line.mid((start+1), (end - start - 1)).toDouble());
//            }
            switch(counter){
            case 7:
                type = line.mid((start+1), (end - start - 1));
                break;
            case 8:
                ID = line.mid((start+1), (end - start - 1)).toInt();
                break;
            case 9:
                group = line.mid((start+1), (end - start - 1));
                break;
            case 10:
                typeB = line.mid((start+1), (end - start - 1)).toInt();
                break;
            case 11:
                method = line.mid((start+1), (end - start - 1)).toInt();
                break;
            case 12:
                value[0] = line.mid((start+1), (end - start - 1)).toDouble();
                break;
            case 13:
                value[1] = line.mid((start+1), (end - start - 1)).toDouble();
                break;
            case 14:
                itemName = line.mid(start+1);
                break;
            default:
                coor.append(line.mid((start+1), (end - start - 1)).toDouble());
                break;
            }

            start = end;
            counter++;
            if(start == -1){flag = false;}
        }
        qDebug() << coor << ", type: " <<type;
        qDebug() << ID << ", group: " <<group;
        Figure *tempFig;
        bool notEmpty = false;
        if(type.contains("Line", Qt::CaseInsensitive)){
            Line *line = new Line(QPointF(coor[0], coor[1]));
            line->setEndPoint(QPointF(coor[2], coor[3]));
            tempFig = line;
            notEmpty = true;
//            line->changeGroup(ID, group);
//            line->setBound(typeB, method, value);
//            figureList.append(line);
        }
        if(type.contains("Circle", Qt::CaseInsensitive)){
            Circle *circle = new Circle(QPointF(coor[0], coor[1]));
            circle->setEndPoint(QPointF(coor[2], coor[3]));
            tempFig = circle;
            notEmpty = true;
//            circle->changeGroup(ID, group);
//            figureList.append(circle);
        }
        if(type.contains("Ellipse", Qt::CaseInsensitive)){
            Ellips *ellipse = new Ellips(QPointF(coor[0], coor[1]));
            ellipse->setEndPoint(QPointF(coor[2], coor[3]));
            tempFig = ellipse;
            notEmpty = true;
//            ellipse->changeGroup(ID, group);
//            figureList.append(ellipse);
        }
        if(type.contains("Arc", Qt::CaseInsensitive)){
            class Arc *arc = new class Arc(QPointF(coor[0], coor[1]));
            arc->byButton(QPointF(coor[0], coor[1]), coor[2], QPointF(180.0 * coor[4] / M_PI, 180.0 * coor[5]  / M_PI));
            tempFig = arc;
            notEmpty = true;
//            circle->changeGroup(ID, group);
//            figureList.append(circle);
        }
        if(notEmpty){
            tempFig->changeGroup(ID, group);
            tempFig->setBound(typeB, method, value);
            tempFig->itemName = itemName;
            figureList.append(tempFig);
        }
    }// read the data serialized from the file
    fileGeom.close();
    if(!figureList.isEmpty()){
        foreach(Figure *figure, figureList){
            scene->addItem(figure);
        }
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    stData.typeT = in.readLine().toInt();
    stData.geomT = in.readLine().toInt();
    stData.stream = in.readLine().toInt();
    stData.Q = in.readLine().toInt();
    stData.E = in.readLine().toInt();
    stData.H = in.readLine().toInt();
    stData.matrix = in.readLine().toInt();
    stData.field = in.readLine().toInt();
    stData.trace = in.readLine().toInt();
    stData.step = in.readLine().toDouble();
    stData.numb = in.readLine().toInt();
    stData.umin = in.readLine().toDouble();
    stData.umax = in.readLine().toDouble();
    mesh_size = in.readLine().toDouble();
    for(int i = 0; i < 7; i++){
        order[i] = in.readLine().toInt();
    }
#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

void MainWindow::getFigureList(QList<Figure *> list){
    if(!figureList.isEmpty()){
//        foreach(Figure *figure, figureList){
//            scene->removeItem(figure);
//        }
        figureList.clear();
    }
    if(!list.isEmpty()){
        figureList = list;
//        foreach(Figure *figure, list){
//            figureList.append(figure);
//        }
        foreach(Figure *figure, figureList){
            scene->addItem(figure);
        }
    }
}

void MainWindow::slotExit(){
    if(!figureList.isEmpty()){
        foreach(Figure *figure, figureList){
            scene->addItem(figure);
        }
    }
}

void MainWindow::fieldFileWrite(){
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QFile file(fileN + ".PAR");
    QFile fileTXT(fileN + "PAR.txt");
    if (file.open(QFile::WriteOnly)) {
        fileTXT.open(QFile::WriteOnly | QFile::Text);
        QTextStream outTXT(&fileTXT);
        QDataStream out(&file);
        out.setByteOrder(QDataStream::LittleEndian);
        out << 4000 << 4000;
        outTXT << 4000 << "\n" <<4000 << "\n";
        int mesh_number = 1;
        if((mesh_size - 0.0) > 0.0000000000001){
            int node_number = 0;
            foreach(Figure *fig, figureList){
                node_number += ceil(fig->getLength()/mesh_size);
                mesh_number *= ceil(fig->getLength()/mesh_size);
            }
            out << node_number;
            outTXT << node_number << "\n";
        }else{
            return;
        }
        out << 0;
        out << 1;
        outTXT << 0 << "\n";
        outTXT << 1 << "\n";
        if(stData.geomT == 2){
            out << 1;
            outTXT << 1 << "\n";
        }else{
            out << 0;
            outTXT << 0 << "\n";
        }
        out << mesh_number -1;
        outTXT << mesh_number -1 << "\n";
        out << 1;
        outTXT << 1 << "\n";
        out << stData.numb;
        outTXT << stData.numb << "\n";
        out << (int)stData.E;
        out << (int)stData.Q;
        out << (int)stData.H;
        out << 0;
        out << 1;
        out << stData.stream;
        out << (double)coef.len;
        out << (double)coef.pot;
        out <<(double)coef.curr;
        out << (double)coef.mag;
        out << (double)coef.len*0.000001;
        out << (double)coef.curr;
        out << 0;
        out << 0;
        out << 0;
        out << 0;
        out << 0;
        out << 0;
        outTXT << (int)stData.E << "\n";
        outTXT << (int)stData.Q << "\n";
        outTXT << (int)stData.H << "\n";
        outTXT << 0 << "\n";
        outTXT << 1 << "\n";
        outTXT << stData.stream << "\n";
        outTXT << coef.len << "\n";
        outTXT << coef.pot << "\n";
        outTXT << coef.curr << "\n";
        outTXT << coef.mag << "\n";
        outTXT << coef.len*0.000001 << "\n";
        outTXT << coef.curr << "\n";
        outTXT << 0 << "\n";
        outTXT << 0 << "\n";
        outTXT << 0 << "\n";
        outTXT << 0 << "\n";
        outTXT << 0 << "\n";
        outTXT << 0 << "\n";
        for(int i = 1; i <= stData.numb; i++){
            double step_iq = (stData.umax - stData.umin)/(stData.numb + 1.0);
            out << (double)(stData.umin + step_iq*i);
            outTXT << stData.umin + step_iq*i << "\n";
        }
        outTXT << true << "\n";
        outTXT << 0 << "\n";
        outTXT << (double)stData.step << "\n";
        out << true;
        out << 0;
        out << (double)stData.step;
    }
    file.close();
    fileTXT.close();
    QGuiApplication::restoreOverrideCursor();
    QFile fileGeo(fileN + ".GEO");
    QFile fileGeoTXT(fileN + "Geo.txt");
    if (fileGeo.open(QFile::WriteOnly)) {
        fileGeoTXT.open(QFile::WriteOnly | QFile::Text);
        QDataStream out(&fileGeo);
        QTextStream outTXT(&fileGeoTXT);
        out.setByteOrder(QDataStream::LittleEndian);
        out << (int)figureList.length(); //MS
        outTXT << (int)figureList.length() << "\n";
        out << 0; //MX
        out << 0; //MY
        out << stData.geomT; //NDIM
        outTXT << 0 << "\n";
        outTXT << 0 << "\n";
        outTXT << stData.geomT << "\n";
        out << 0.0; //PR
        out << 0.0; //PZ
        out << (int)figureList.length()*14; //IID
        outTXT << (float)0.0 << "\n";
        outTXT << (float)0.0 << "\n";
        outTXT << (int)figureList.count()*14 << "\n";
        out.setFloatingPointPrecision(QDataStream::SinglePrecision);
        for(int i = 0; i < (int)figureList.length(); ++i){
            //NK
           out << 6;
           outTXT << 6 << "\n";
        }
        for(int i = 0; i < (int)figureList.length(); ++i){
            //NN
           out << 9;
           outTXT << 9 << "\n";
        }
        foreach(Figure *fig, figureList){
            //NG
           out << fig->getBound().type;
           outTXT << fig->getBound().type << "\n";
        }
        for(int i = 0; i < 4; ++i){
            //Figure coefi [A, B, C, D]
           double* coef;
           foreach(Figure *fig, figureList){
                coef = fig->getCoeff();
                out << (float)coef[i];
                outTXT << coef[i] << "\n";
           }
        }
        for(int i = 0; i < 2; ++i){
            //Figure coefi [A, B, C, D]
           double* angles;
           foreach(Figure *fig, figureList){
                angles = fig->getAngles();
                out << (float)angles[i];
                outTXT << angles[i] << "\n";
           }
        }
//        for(int i = 0; i < (int)figureList.length(); ++i){
//            //AL
//            out << (float)0.0;
//            outTXT << 0.0 << "\n";
//        }
//        for(int i = 0; i < (int)figureList.length(); ++i){
//            //BT
//            out << (float)1.0;
//            outTXT << 1.0 << "\n";
//        }
        for(int i = 0; i < (int)figureList.length(); ++i){
            //GN
            out << (float)0.0;
            outTXT << 0.0 << "\n";
        }
        for(int i = 0; i < (int)figureList.length(); ++i){
            //GK
            out << (float)0.0;
            outTXT << 0.0 << "\n";
        }
        foreach(Figure *fig, figureList){
            //U1
            out << (float)fig->getBound().value[0];
            outTXT << fig->getBound().value[0] << "\n";
        }
        foreach(Figure *fig, figureList){
            //U2
            if(fig->getBound().method){
                out << (float)fig->getBound().value[1];
                outTXT << fig->getBound().value[1] << "\n";
            }else{
                out << (float)fig->getBound().value[0];
                outTXT << fig->getBound().value[0] << "\n";
            }
        }
        for(int i = 0; i < (int)figureList.length(); ++i){
            //INT
           out << 2;
           outTXT << 2 << "\n";
        }

    }
    fileGeo.close();
    fileGeoTXT.close();
    QFile fileSet(fileN + ".SET");
    QFile fileSetTXT(fileN + "SET.txt");
    if (fileSet.open(QFile::WriteOnly)) {
        fileSetTXT.open(QFile::WriteOnly | QFile::Text);
        QDataStream out(&fileSet);
        QTextStream outTXT(&fileSetTXT);
        if((mesh_size - 0.0) > 0.0000000000001){
            int node_number = 0;
            foreach(Figure *fig, figureList){
                node_number += ceil(fig->getLength()/mesh_size);
            }
            out << node_number;
            out << node_number;
            outTXT << node_number << "\n";
            outTXT << node_number << "\n";
        }else{
            return;
        }
    }
    fileSet.close();
    fileSetTXT.close();
    QFile fileNAM(fileN.mid(0, (fileN.lastIndexOf("/", -1)+1)) + "TASK.NAM");
    if (fileNAM.open(QFile::WriteOnly)) {
        QDataStream out(&fileNAM);
        out.setByteOrder(QDataStream::LittleEndian);
        QString substr = "G:\\PS2Test\\DATA\\" + fileN.mid((fileN.lastIndexOf("/", -1)+1));
        int len = substr.length();
        spaceWr(&out, len);
//        char *int_val = new char[4];
//        std::sprintf(int_val, "%d", len);
////        chWr(&out, int_val, 4);
//        out.writeRawData(int_val, 4);
        qDebug() << len;
        for(int i = 0; i < len; ++i){
            out << substr[i].toLatin1();
            qDebug() << substr[i].toLatin1();
        }
    }
    fileNAM.close();
    statusBar()->showMessage(tr("Files created"), 2000);
}

void MainWindow::spaceWr(QDataStream *in, int n){
    *in << (char)n;
    char empty = '\0';
    *in << empty << empty << empty;
}

void MainWindow::spaceWr(QDataStream *in, float n){
    *in << (char)n;
    char empty = '\0';
    *in << empty << empty << empty;
}

void MainWindow::chWr(QDataStream *in, char *n, int len){
    for(int i = 0; i < len; ++i){
        *in << n[i];
    }
}
