#ifndef REVERSI_POINT_H
#define REVERSI_POINT_H

#include <ostream>
class Point {
 private:
  int x_, y_;

 public:
  // Constructor for point by two coordinates.
  Point(int x, int y);

  // Destructor for point.
  ~Point();

  // Returns the point's x coordinate.
  int getX() const;

  // Returns the point's y coordinate.
  int getY() const;

  // Sets the point's x coordinate as given coordinate.
  void setX(int x);

  // Sets the point's y coordinate as given coordinate.
  void setY(int y);

  // Compares two points.
  bool operator==(const Point &point) const;

  // Compares two points.
  bool operator!=(const Point &point) const;
};

// Prints the point as '(x, y)'.
std::ostream &operator<<(std::ostream &out, Point const &point);

#endif //REVERSI_POINT_H
