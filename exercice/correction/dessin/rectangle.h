#pragma once

#include "shape.h"

class Rectangle : public Shape
{
public:
    Rectangle(int width, int length, QPoint location, QColor borderColor, QColor bucketColor, int thickness);
    void draw(QPainter& painter) override;
    IdShape id() override;
private:
    int length;
    int width;

    friend QDataStream &operator<<(QDataStream &stream, Rectangle &shape);
};

QDataStream &operator<<(QDataStream &stream, Rectangle &shape);
