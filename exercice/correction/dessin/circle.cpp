#include "circle.h"

Circle::Circle(int radius, QPoint location, QColor borderColor, QColor bucketColor, int thickness) : radius(radius), Shape(location, borderColor, bucketColor, thickness)
{

}

void Circle::draw(QPainter &painter)
{
    Shape::draw(painter);
    painter.drawEllipse(QRect(this->location.x(), this->location.y(), this->radius, this->radius));
}

Shape::IdShape Circle::id()
{
    return IdShape::CIRCLE;
}

QDataStream &operator<<(QDataStream &stream, Circle &shape)
{
    stream << shape.id()
           << shape.borderColor
           << shape.bucketColor
           << shape.location
           << shape.thickness
           << shape.radius;

    return stream;
}
