#include "line.h"

Line::Line(QPoint to, QPoint location, QColor borderColor, QColor bucketColor, int thickness) : pointTo(to), Shape(location, borderColor, bucketColor, thickness)
{

}

void Line::draw(QPainter& painter)
{
    Shape::draw(painter);
    painter.drawLine(this->location, this->pointTo);
}

Shape::IdShape Line::id()
{
    return IdShape::LINE;
}

QDataStream &operator<<(QDataStream &stream, Line &shape)
{
    stream << shape.id()
           << shape.borderColor
           << shape.bucketColor
           << shape.location
           << shape.thickness
           << shape.pointTo;
    return stream;
}
