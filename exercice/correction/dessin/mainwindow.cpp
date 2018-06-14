#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    settings("Lucas Bulloni", "HE-ARC"),
    listLastFiles(),
    widget(new Widget())
{
    this->setupUi(this);

    this->currentFile = "new";

    this->openSettings();

    this->setCentralWidget(this->widget.data());

    this->groupShapeActions();
    this->connectAction();

    this->actionRectangle->setChecked(true);
}

MainWindow::~MainWindow()
{
    this->saveSettings();
}

void MainWindow::selectColor()
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    if(color.isValid())
    {
        emit this->setColor(color);
    }
}

void MainWindow::selectBucketColor()
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    if(color.isValid())
    {
        emit this->setBucketColor(color);
    }
}

void MainWindow::selectThickness()
{
    bool isValid;
    int thickness = QInputDialog::getInt(this, tr("Select a thickness"), tr("thickness"), 1, 1, 100, 1, &isValid);

    if(isValid)
    {
        emit this->setThickness(thickness);
    }
}

void MainWindow::selectTool()
{
    if(this->actionCircle->isChecked())
    {
        this->widget->setShapeTool(Widget::ShapeTool::CircleTool);
    }
    else if(this->actionRectangle->isChecked())
    {
        this->widget->setShapeTool(Widget::ShapeTool::RectangleTool);
    }
    else if(this->actionLigne->isChecked())
    {
        this->widget->setShapeTool(Widget::ShapeTool::LineTool);
    }
}

void MainWindow::openFile()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open drawing"), "", tr("Drawing shape (*.shp)"));

    this->widget->openFile(filename);

    this->widget->repaint();
    this->insertFilenameIntoSetting(filename);
}



void MainWindow::saveFile()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save drawing"), "", tr("Drawing shape (*.shp)"));



    this->insertFilenameIntoSetting(filename);
}

void MainWindow::save()
{
    if(this->currentFile == "new")
    {
        this->saveFile();
    }
    else
    {
        QFile file(this->currentFile);
        file.open(QIODevice::ReadWrite | QIODevice::Truncate);

        QDataStream stream(&file);
        stream << *(this->widget);

        file.close();
    }
}

void MainWindow::createActionFilename()
{
    QActionGroup* displayGroup = new QActionGroup(this);

    for (int i = 0; i < 5 && i < this->listLastFiles.size(); i++)
    {
        QString filename = this->listLastFiles[i];

        QAction *action = this->menuFichier->addAction(filename, widget.data(), [this, filename]()
        {
            this->widget.data()->openFile(filename);
        });

        displayGroup->addAction(action);
    }
}

void MainWindow::connectAction()
{
    connect(this->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(this->actionNew, &QAction::triggered, this->widget.data(), &Widget::reset);
    connect(this->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
    connect(this->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(this->actionColor, &QAction::triggered, this, &MainWindow::selectColor);
    connect(this->actionColorBucket, &QAction::triggered, this, &MainWindow::selectBucketColor);
    connect(this->actionThickness, &QAction::triggered, this, &MainWindow::selectThickness);
    connect(this->actionCircle, &QAction::triggered, this, &MainWindow::selectTool);
    connect(this->actionRectangle, &QAction::triggered, this, &MainWindow::selectTool);
    connect(this->actionLigne, &QAction::triggered, this, &MainWindow::selectTool);
    connect(this->actionZoom_In, &QAction::triggered, this->widget.data(), &Widget::zoomIn);
    connect(this->actionZoom_Out, &QAction::triggered, this->widget.data(), &Widget::zoomOut);
    connect(this->actionReset_Zoom, &QAction::triggered, this->widget.data(), &Widget::resetZoom);
    connect(this->actionCancel, &QAction::triggered, this->widget.data(), &Widget::deleteLastElement);
    connect(this->actionSave_2, &QAction::triggered, this, &MainWindow::save);

    connect(this, &MainWindow::setColor, this->widget.data(), &Widget::setBorderColor);
    connect(this, &MainWindow::setBucketColor, this->widget.data(), &Widget::setBucketColor);
    connect(this, &MainWindow::setThickness, this->widget.data(), &Widget::setThickness);
}

void MainWindow::groupShapeActions()
{
    this->actionCircle->setCheckable(true);
    this->actionRectangle->setCheckable(true);
    this->actionLigne->setCheckable(true);

    QActionGroup* groupeShapes = new QActionGroup(this);
    groupeShapes->addAction(this->actionCircle);
    groupeShapes->addAction(this->actionRectangle);
    groupeShapes->addAction(this->actionLigne);
}

void MainWindow::saveSettings()
{
    settings.setValue("dimension", this->size());
    settings.setValue("position", this->pos());

    settings.setValue("last-files", (QStringList)this->listLastFiles.mid(0, 5));
}

void MainWindow::openSettings()
{
    this->resize(this->settings.value("dimension", QSize(400, 400)).toSize());
    this->move(this->settings.value("position", QPoint(400, 400)).toPoint());
    this->listLastFiles = this->settings.value("last-files", QStringList()).toStringList();
    this->createActionFilename();

    if(this->listLastFiles.size() > 0)
    {
        if(!this->widget->openFile(this->listLastFiles[0]))
        {
            this->listLastFiles.removeOne(this->listLastFiles[0]);
        }
    }
}

void MainWindow::insertFilenameIntoSetting(QString filename)
{
    if(filename != "new")
    {
        this->listLastFiles.removeAll(filename);
        this->listLastFiles.prepend(filename);
        this->rebuildFileMenu();
    }
}

void MainWindow::rebuildFileMenu()
{
    this->menuFichier->clear();

    this->menuFichier->addAction(this->actionNew);
    this->menuFichier->addAction(this->actionOpen);
    this->menuFichier->addAction(this->actionSave);
    this->menuFichier->addAction(this->actionQuit);

    this->createActionFilename();
}

