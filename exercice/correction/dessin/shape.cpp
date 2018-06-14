#include "shape.h"

Shape::Shape(QPoint location, QColor borderColor, QColor bucketColor, int thickness) : location(location), borderColor(borderColor), bucketColor(bucketColor), thickness(thickness)
{

}

void Shape::draw(QPainter& painter)
{
    painter.setPen(QPen(this->borderColor, this->thickness));
    painter.setBrush(this->bucketColor);
}
