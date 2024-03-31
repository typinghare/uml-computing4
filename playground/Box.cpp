// Implementation file for the Box class.
#include "Box.h"

#include <sstream>
#include <string>

Box::Box() {
  length = 0;
  width = 0;
  height = 0;
  material = "undefined";
}

Box::Box(double len, double wid, double hei, std::string mat) {
  if (len < 0) {
    length = 1;
  } else {
    length = len;
  }

  if (wid < 0) {
    width = 1;
  } else {
    width = wid;
  }

  if (hei < 0) {
    height = 1;
  } else {
    height = hei;
  }

  material = mat;
};

void Box::setLength(double a) {
  if (a < 0) {
    length = 1;
  } else {
    length = a;
  }
}

void Box::setWidth(double a) {
  if (a < 0) {
    width = 1;
  } else {
    width = a;
  }
}

void Box::setHeight(double a) {
  if (a < 0) {
    height = 1;
  } else {
    height = a;
  }
}

std::string Box::toString() {
  std::stringstream ss;
  ss << "The box is " << getLength() << " meters long.\n";
  ss << "The box is " << getWidth() << " meters wide.\n";
  ss << "The box is " << getHeight() << " meters high.\n";
  return ss.str();
}

bool Box::operator>(const Box &right) {
  bool status;
  if ((*this).volume() > right.volume()) {
    status = true;
  } else {
    status = false;
  }
  return status;
}

bool Box::operator<(const Box &right) {
  bool status;
  if ((*this).volume() < right.volume()) {
    status = true;
  } else {
    status = false;
  }
  return status;
}

bool Box::operator>=(const Box &right) {
  bool status;
  if ((*this).volume() >= right.volume()) {
    status = true;
  } else {
    status = false;
  }
  return status;
}

bool Box::operator<=(const Box &right) {
  bool status;
  if ((*this).volume() <= right.volume()) {
    status = true;
  } else {
    status = false;
  }
  return status;
}

bool Box::operator!=(const Box &right) {
  bool status;
  if ((*this).volume() != right.volume()) {
    status = true;
  } else {
    status = false;
  }
  return status;
}

bool Box::operator==(const Box &right) {
  bool status;
  if (length == right.length && width == right.width &&
      height == right.height) {
    status = true;
  } else {
    status = false;
  }
  return status;
}

Box Box::operator+(const Box &right) {
  Box temp = *this;
  if (right.length == length && right.width == width) {
    temp.height += right.height;
    temp.material.append(" and ");
    temp.material += right.material;
  } else if (right.height == height && right.length == length) {
    temp.width += right.width;
    temp.material.append(" and ");
    temp.material += right.material;
  } else if (right.height == height && right.width == width) {
    temp.length += right.length;
    temp.material.append(" and ");
    temp.material += right.material;
  }
  return temp;
}

Box Box::operator-(const Box &right) {
    Box temp = *this;
    if (right.length == length && right.width == width && material == right.material && (length>temp.length)) {
    temp.height -= right.height;
  } else if (right.height == height && right.length == length && material == right.material&& (length>temp.length)) {
    temp.width -= right.width;
  } else if (right.height == height && right.width == width && material == right.material&& (length>temp.length)) {
    temp.length -= right.length;
  }
  return temp;
}

std::ostream &operator << (std::ostream &strm, const Box &obj) {
   /* strm << "This Box is "<< obj.length << "long,\n";
    strm << obj.width << "wide,\n";
    strm << obj.height << "tall,\n";
    strm << "made of "<< obj.material << ".\n";
    strm <<*/
    strm << obj.toString(); 
}

std::istream &operator >> (std::istream &strm, Box &obj) {
    strm >> obj.length;
    strm >> obj.width;
    strm >> obj.height;
    strm >> obj.material;
}
