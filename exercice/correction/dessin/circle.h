#pragma once

#include "shape.h"

class Circle : public Shape
{
public:
    Circle(int radius, QPoint location, QColor borderColor, QColor bucketColor, int thickness);
    int radius;

    void draw(QPainter& painter) override;
    IdShape id() override;

    friend QDataStream &operator<<(QDataStream &stream, Circle &shape);
};

QDataStream &operator<<(QDataStream& stream, Circle& widget);
