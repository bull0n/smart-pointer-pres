#include "rectangle.h"

Rectangle::Rectangle(int width, int length, QPoint location, QColor borderColor, QColor bucketColor, int thickness) : Shape(location, borderColor, bucketColor, thickness), width(width), length(length)
{

}

void Rectangle::draw(QPainter &painter)
{
    Shape::draw(painter);
    painter.drawRect(QRect(this->location, QSize(this->width, this->length)));
}

Shape::IdShape Rectangle::id()
{
    return IdShape::RECT;
}

QDataStream &operator<<(QDataStream &stream, Rectangle &shape)
{
    stream << shape.id()
           << shape.borderColor
           << shape.bucketColor
           << shape.location
           << shape.thickness
           << shape.length
           << shape.width;
    return stream;
}
