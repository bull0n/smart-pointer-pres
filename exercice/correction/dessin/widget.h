#pragma once

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QList>
#include <QSharedPointer>

class Shape;
class Circle;
class Rectangle;
class Line;



class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    QSharedPointer<QList<QSharedPointer<Shape>>> getListShapes()
    {
        return this->listShapes;
    }

    ~Widget();
    enum ShapeTool
    {
        LineTool = 0,
        RectangleTool = 1,
        CircleTool = 2
    };
private:
     //methods
     void paintEvent(QPaintEvent* event);
     void mouseMoveEvent(QMouseEvent* event);
     void mouseReleaseEvent(QMouseEvent* event);
     void mousePressEvent(QMouseEvent* event);
     //members
     int countPaintEvent;
     double zoom;
     bool isMousePressed;
     QPoint mouseStartCoordinates;
     int comboElement;

     QSharedPointer<QList<QSharedPointer<Shape>>> listShapes;
     QColor borderColor;
     QColor bucketColor;
     int thickness;
     ShapeTool shapeTool;
     QSharedPointer<QPainter> painter;
public slots:
     void setBorderColor(QColor color);
     void setBucketColor(QColor color);
     void setThickness(int thickness);
     void setShapeTool(Widget::ShapeTool tool);
     void reset();
     void zoomIn();
     void zoomOut();
     void resetZoom();
     void deleteLastElement();
     bool openFile(QString filename);

    friend QDataStream &operator>>(QDataStream& stream, Widget& widget);
    friend QDataStream &operator<<(QDataStream& stream, Widget& widget);
};

QDataStream &operator>>(QDataStream& stream, Widget& widget);
QDataStream &operator<<(QDataStream& stream, Widget& widget);
