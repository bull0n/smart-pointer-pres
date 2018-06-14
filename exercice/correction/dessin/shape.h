#pragma once

#include <QtWidgets>

class Shape
{
protected:
    QColor borderColor;
    QColor bucketColor;
    QPoint location;
    int thickness;
public:
    enum IdShape {
        RECT = 1,
        LINE = 2,
        CIRCLE = 3
    };

    Shape(QPoint location, QColor borderColor, QColor bucketColor, int thickness);
    virtual void draw(QPainter& painter);
    virtual IdShape id() = 0;
};
