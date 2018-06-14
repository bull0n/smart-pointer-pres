#pragma once
#include "shape.h"


class Line : public Shape
{
public:
    Line(QPoint to, QPoint location, QColor borderColor, QColor bucketColor, int thickness);
    void draw(QPainter& painter) override;

    IdShape id() override;
private:
    QPoint pointTo;

    friend QDataStream &operator<<(QDataStream &stream, Line &shape);
};

QDataStream &operator<<(QDataStream &stream, Line &shape);
