#pragma once
#include "Color.hpp"
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
  public:
    Ball(const Color& color_, const double radius_, bool isCollidable_);
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    Color getColor() const;
    bool getIsCollidable() const;

  private:
    Velocity velocity;
    Point center;
    double radius;
    Color color;
    bool isCollidable;
};
