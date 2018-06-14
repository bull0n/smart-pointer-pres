#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "ui_mainwindow.h"
#include "widget.h"


class MainWindow : public QMainWindow, private Ui_MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void selectColor();
    void selectBucketColor();
    void selectThickness();
    void selectTool();
    void openFile();
    void saveFile();
    void save();
signals:
    void setColor(QColor color);
    void setBucketColor(QColor color);
    void setThickness(int thickness);
private:
    QSharedPointer<Widget> widget;
    QSettings settings;
    QString currentFile;
    QStringList listLastFiles;

    void createActionFilename();
    void connectAction();
    void groupShapeActions();
    void saveSettings();
    void openSettings();
    void insertFilenameIntoSetting(QString filename);
    void rebuildFileMenu();
};

#endif // MAINWINDOW_H
