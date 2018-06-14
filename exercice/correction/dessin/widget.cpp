#include "widget.h"

#include "shape.h"
#include "line.h"
#include "circle.h"
#include "rectangle.h"



void Widget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    QStyleOption opt;
    opt.init(this);
    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    this->countPaintEvent++;
    painter.setWindow(0, 0, this->width()*this->zoom, this->height()*this->zoom);

    //affichages des strings
    QString text1;
    text1 = QString("Nombre d'appels de paintEvent() : %1").arg(QString::number(this->countPaintEvent));
    painter.drawText(0,20, text1);
    QString text2;
    text2 = QString("Nombre de formes : %1").arg(QString::number(this->listShapes.data()->count()));
    painter.drawText(0,40, text2);

    QList<QSharedPointer<Shape>>::iterator i;
    for(i = this->listShapes->begin(); i != this->listShapes->end(); i++)
    {
        (*i)->draw(painter);
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(this->isMousePressed && this->shapeTool == ShapeTool::LineTool)
    {
        QPoint endPoint(event->x()*this->zoom, event->y()*this->zoom);
        QSharedPointer<Line> line(new Line(endPoint,this->mouseStartCoordinates, this->borderColor, this->bucketColor, this->thickness));
        this->listShapes->append(line);
        this->update();
        mouseStartCoordinates = endPoint;
        this->comboElement++;
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    this->isMousePressed = false;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    this->isMousePressed = true;
    this->comboElement = 0;

    if(this->shapeTool == ShapeTool::RectangleTool)
    {
        this->comboElement = 1;
        QSharedPointer<Rectangle> rectangle(new Rectangle(20, 20, QPoint(event->x()*this->zoom, event->y()*this->zoom), this->borderColor, this->bucketColor, this->thickness));
        this->listShapes->append(rectangle);
        this->update();
    }
    else if(this->shapeTool == ShapeTool::CircleTool)
    {
        this->comboElement = 1;
        QSharedPointer<Circle> circle(new Circle(50, QPoint(event->x()*this->zoom, event->y()*this->zoom), this->borderColor, this->bucketColor, this->thickness));
        this->listShapes->append(circle);
        this->update();
    }

    this->mouseStartCoordinates = QPoint(event->x(), event->y())*this->zoom;
}

void Widget::setBorderColor(QColor color)
{
    this->borderColor = color;
}

void Widget::setBucketColor(QColor color)
{
    this->bucketColor = color;
}

void Widget::setThickness(int thickness)
{
    this->thickness = thickness;
}

void Widget::setShapeTool(ShapeTool tool)
{
    this->shapeTool = tool;
}

void Widget::reset()
{
    this->listShapes->clear();
    this->update();
}

void Widget::zoomIn()
{
    this->zoom /= 1.1;
    this->update();
}

void Widget::zoomOut()
{
    this->zoom *= 1.1;
    this->update();
}

void Widget::resetZoom()
{
    this->zoom = 1.;
    this->update();
}

void Widget::deleteLastElement()
{
    if(!this->listShapes->isEmpty())
    {
        while(this->comboElement > 0)
        {
            this->listShapes->removeLast();
            this->comboElement--;
        }

        this->update();
    }
}

bool Widget::openFile(QString filename)
{
    QFile file(filename);

    if(file.exists())
    {
        file.open(QIODevice::ReadOnly);

        QDataStream stream(&file);

        stream >> *this;

        file.close();

        this->repaint();

        return true;
    }
    else
    {
        QMessageBox::critical(this, tr("File not found"),
                                       tr("The file couldn't be found"),
                                       QMessageBox::Ok);

        return false;
    }
}

Widget::Widget(QWidget *parent) : QWidget(parent), zoom(1.), comboElement(0), listShapes(new QList<QSharedPointer<Shape>>())
{
    this->countPaintEvent = 0;
    this->thickness = 1;
    this->shapeTool = ShapeTool::RectangleTool;
    this->setStyleSheet("background-color: white;");
}

Widget::~Widget()
{

}

QDataStream &operator>>(QDataStream& stream, Widget& widget)
{
    QSharedPointer<QList<QSharedPointer<Shape>>> list = widget.getListShapes();
    list->clear();

    while(!stream.atEnd())
    {
        int idShape;
        stream >> idShape;
        QSharedPointer<Shape> shape;

        if(idShape == Shape::IdShape::RECT)
        {
            int width;
            int length;
            int thickness;
            QPoint location;
            QColor borderColor;
            QColor bucketColor;

            stream >> borderColor
                   >> bucketColor
                   >> location
                   >> thickness
                   >> length
                   >> width;

            QSharedPointer<Rectangle> rect(new Rectangle(width, length, location, borderColor, bucketColor, thickness));
            shape = rect;
        }
        else if(idShape == Shape::IdShape::LINE)
        {
            int thickness;
            QPoint to;
            QPoint location;
            QColor borderColor;
            QColor bucketColor;

            stream >> borderColor
                   >> bucketColor
                   >> location
                   >> thickness
                   >> to;

            QSharedPointer<Line> line(new Line(to, location, borderColor, bucketColor, thickness));
            shape = line;
        }
        else
        {
            int thickness;
            int radius;
            QPoint location;
            QColor borderColor;
            QColor bucketColor;

            stream >> borderColor
                   >> bucketColor
                   >> location
                   >> thickness
                   >> radius;

            QSharedPointer<Circle> circle(new Circle(radius, location, borderColor, bucketColor, thickness));
            shape = circle;
        }

        list->append(shape);
    }

    return stream;
}
QDataStream &operator<<(QDataStream& stream, Widget& widget)
{    
    foreach (QSharedPointer<Shape> shape, *widget.listShapes)
    {
        if(shape->id() == Shape::IdShape::LINE)
        {
            Line* line = (Line*)shape.data();
            stream << *line;
        }
        else if(shape->id() == Shape::IdShape::RECT)
        {
            Rectangle* rect = (Rectangle*)shape.data();
            stream << *rect;
        }
        else
        {
            Circle* circle = (Circle*)shape.data();
            stream << *circle;
        }
    }

    return stream;
}
