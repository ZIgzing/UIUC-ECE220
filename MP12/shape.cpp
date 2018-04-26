/*----------------------------------------------------------------------------------------------------------------------------
C++ Shape Objects

Written by Marc Harvey
UIUC ECE 220 MP12
042618

There are many functions in this file for a couple different classes. The first functions are the Shape constructor and
getName, which both belong to the Shape class. The next functions are constructors, operators + and -, get value functions,
getArea, and getVolume, which every subclass of shape has. After that, there is the createShapes function, which creates a
vector of poitners to shapes based on an input file, and also the functions maxArea and maxVolume.

All the shape subclass specific functions are very self explanatory, but the createShapes function is not quite as such.
It starts by initializing a vector, and then iterating through the file, line by line, reading the name and specs given,
and then adding a new instance of whatever class's name appears with the specs as parameters.

The maxArea and maxVolume functions just iterate through the created vector, using the getArea and getVolume functions
respectively to get the new values. They then return whichever value is the largest.

----------------------------------------------------------------------------------------------------------------------------*/

#include "shape.hpp"

//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable

Shape::Shape(string name) {
    name_ = name;
}
string Shape::getName() {return name_;}


//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

Rectangle::Rectangle(double width, double length):Shape("Rectangle") {  // Constructor given two parameters
   width_ = width;
   length_ = length;
}
Rectangle Rectangle::operator+ (const Rectangle& r2) {  // Plus operator
    Rectangle newRect( (this->width_) + r2.width_ , (this->length_) + r2.length_ );  // Sum the widths and lengths
    return newRect;
}
Rectangle Rectangle::operator- (const Rectangle& r2) {  // Minus operator
    Rectangle newRect( fmax(0.0, (this->width_) - r2.width_) , fmax(0.0, (this->length_) - r2.length_) );  // Subtract second values from first values, but have minimum result be zero
    return newRect;
}
double Rectangle::getWidth() const{return width_;}
double Rectangle::getLength() const{return length_;}
double Rectangle::getArea() const{  // Area of rectangle is width * length
    return width_ * length_;
}
double Rectangle::getVolume() const{return 0.0;}  // Volume is zero because no height


//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

Circle::Circle(double radius):Shape("Circle") {  // Constructor given one parameters
    radius_ = radius;
}
Circle Circle::operator+ (const Circle& c2) {  // Plus operator
    Circle newCirc( (this->radius_) + c2.radius_ );  // Sum the radii
    return newCirc;
}
Circle Circle::operator- (const Circle& c2) {  // Minus operator
    Circle newCirc( fmax(0.0, (this->radius_) - c2.radius_) );  // Subtract second radius from first radius, but minimum result is zero
    return newCirc;
}
double Circle::getRadius() const{return radius_;}
double Circle::getArea() const{  // Area of circle is pi*r^2
    return pow(radius_, 2) * M_PI;
}
double Circle::getVolume() const{return 0.0;}  // Volume is zero becauses no height


//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

Sphere::Sphere(double radius):Shape("Sphere") {  // Constructor given one parameters
    radius_ = radius;
}
Sphere Sphere::operator+ (const Sphere& s2) {  // Plus operator
    Sphere newSphere( (this->radius_) + s2.radius_ );  // Sum the radii
    return newSphere;
}
Sphere Sphere::operator- (const Sphere& s2) {  // Minus operator
    Sphere newSphere( fmax(0.0, (this->radius_) - s2.radius_) );  // Subtract seconds radius from first radius, but minimum result is zero
    return newSphere;
}
double Sphere::getRadius() const{return radius_;}
double Sphere::getArea() const{  // Surface area of sphere is 4*pi*r^2
    return 4.0 * pow(radius_, 2) * M_PI;
}
double Sphere::getVolume() const{  // Volume of sphere is (4/3)pi*r^3
    return (4.0 / 3.0) * pow(radius_, 3) * M_PI;
}

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

RectPrism::RectPrism(double width, double length, double height):Shape("RectPrism") {  // Constructor given three parameters
    width_ = width;
    length_ = length;
    height_ = height;
}
RectPrism RectPrism::operator+ (const RectPrism& rp2) {  // Plus operator
    RectPrism newRp( (this->width_) + rp2.width_ , (this->length_) + rp2.length_ , (this->height_) + rp2.height_ );  // Sum widths, lengths, and heights
    return newRp;
}
RectPrism RectPrism::operator- (const RectPrism& rp2) {  // Minus operator
    RectPrism newRp( fmax(0.0, (this->width_) - rp2.width_) , fmax(0.0, (this->length_) - rp2.length_) , fmax(0.0, (this->height_) - rp2.height_) );  // Subtract second values from first values, but minimum results are zero
    return newRp;
}
double RectPrism::getWidth() const{return width_;}
double RectPrism::getHeight() const{return height_;}
double RectPrism::getLength() const{return length_;}
double RectPrism::getArea() const{  // Surface area of a rectangluar prism is 2 * (w*l + w*h + l*h)
    return 2 * ( (length_ * height_) + (length_ * width_) + (width_ * height_) );
}
double RectPrism::getVolume() const {  // Volume of a rectangular prism is w*l*h
    return width_ * length_ * height_;
}


// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
vector<Shape*> CreateShapes(char* file_name) {
    //@@Insert your code here

    string name;

    ifstream file (file_name, std::ifstream::in);  // Start file stream

    int size;
    file >> size;  // Get first number from file, which indicates size
    vector<Shape*> result;  // Initialize vector to be returned

    double width, length, height, radius;

    for (int i = 0; i < size; i++) {  // Iterate through every line of file
        file >> name;  // Get first string of line (name of shape)
        if (name == "Rectangle") {  // If shape is a rectangle
            file >> width >> length;  // Read three double parameters
            result.push_back(new Rectangle(width, length));  // Push new rectangle pointer with given parameters to end of vector
        }
        else if (name == "Circle") {  // If shape is a circle
            file >> radius;  // Read one double parameter
            result.push_back(new Circle(radius));  // Push new circle pointer with given parameter to end of vector
        }
        else if (name == "Sphere") {  // If shape is a sphere
            file >> radius;  // Read one double parameter
            result.push_back(new Sphere(radius));  // Push new sphere pointer with given parameter to end of vector
        }
        else if (name == "RectPrism") {  // If shape is a rectangular prism
            file >> width >> length >> height;  // Read three double parameters
            result.push_back(new RectPrism(width, length, height));  // Push new rectangular prism pointer with given parameters to end of vector
        }
    }

    file.close();  // Close the open file

    return result;
}

// call getArea() of each object
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
        double cur_area;

	for (int i = 0; i < shapes.size(); i++) {  // Iterate through every shape in shapes vector
            cur_area = shapes[i]->getArea();  // Set cur_area to the area of the current shape
            if (cur_area > max_area) {  // If current area is greater than current max area, change max area
                max_area = cur_area;
            }
        }

        return max_area;
}


// call getVolume() of each object
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;
	double cur_volume;

        for (int i = 0; i < shapes.size(); i++) {  // Iterate through every shape in shapes vector
            cur_volume = shapes[i]->getVolume();  // Set cur_volume to the volume of the current shape
            if (cur_volume > max_volume) {  // If current volume is greater than current max volume, change max volume
                max_volume = cur_volume;
            }
        }

        return max_volume;
}

