#ifndef REVERSI_POINT_H
#define REVERSI_POINT_H
#include <string>
#include <ostream>
class Point {
 private:
  int x_, y_;

 public:
  // Constructor for point by string.
  Point(char point[]);

  // Constructor for point by two coordinates.
  Point(int x = -1, int y = -1);

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

  Point decrease();

  // Compares two points.
  bool operator==(const Point &point) const;

  // Compares two points.
  bool operator!=(const Point &point) const;

  // Converts point to string.
  std::string toString();
};

// Prints the point as '(x, y)'.
std::ostream &operator<<(std::ostream &out, Point const &point);

#endif //REVERSI_POINT_H
