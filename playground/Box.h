#pragma once
#ifndef BOX_H
#define BOX_H

#include <string>

class Box;  // Forward Declaration

std::ostream& operator<<(std::ostream&, const Box&);
std::istream& operator>>(std::istream&, Box&);

class Box {
 private:
    double length;
    double width;
    double height;
    std::string material;

 public:
    Box();
    Box(double, double, double, std::string);

    double getLength() { return length; }
    double getWidth() { return width; }
    double getHeight() { return height; }
    std::string getMaterial() { return material; }

    void setLength(double);  // defined in Box.cpp
    void setWidth(double);  // defined in Box.cpp
    void setHeight(double);  // defined in Box.cpp
    void setMaterial(std::string a) { material = a; }

    double volume() const { return length * width * height; }

    const std::string toString();  // defined in Box.cpp

    // overloading comparison operators
    bool operator>(const Box& b);
    bool operator<(const Box& b);
    bool operator>=(const Box& b);
    bool operator<=(const Box& b);
    bool operator!=(const Box& b);
    bool operator==(const Box& b);

    // overloading addition operator
    Box operator+(const Box&);

    // overloading subtraction operator
    Box operator-(const Box&);

    friend std::ostream& operator<<(std::ostream&, const Box&);
    friend std::istream& operator>>(std::istream&, Box&);
};

#endif
