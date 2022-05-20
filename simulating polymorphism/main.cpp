#include <iostream>

using namespace std;

// Virtual table which is used by the derived classes.
struct ShapeVtable;

// struct shapes which is the parent class.
struct Shape
{
    ShapeVtable* vtable;
};

// contains the function that will be inherited by shapes.
struct ShapeVtable
{
    double (*GetArea) (Shape*); // get the area of shape.
    void (*PrintInfo) (Shape*); // print shape data and area.
    void (*Destroy) (Shape*); // free shape resources.
};

// to implement function GetArea from the virtual table.
double GetArea(Shape* shape)
{
    return shape->vtable->GetArea(shape);
}

// to implement function PrintInfo from the virtual table.
void PrintInfo(Shape* shape)
{
    return shape->vtable->PrintInfo(shape);
}

// to implement function Destroy from the virtual table.
void ShapeDestroy(Shape* shape)
{
    return shape->vtable->Destroy(shape);
}

// shape: circle.
struct Circle
{
    Shape parent; // used to initialize the virtual table
    double radius; // used to initialize the circle radius and to get the area.
};

// calculate circle area.
double CircleGetArea(Circle* circle)
{
    return 3.14*circle->radius*circle->radius; // area = pi*R^2
}

// print circle info.
void CirclePrintInfo(Circle* circle)
{
    cout << "Shape: Circle." << endl;
    cout << "Circle radius = " << circle->radius << endl;
    cout << "Circle area = " << CircleGetArea(circle) << endl << endl;
}

// free shape resources.
void CircleDestroy(Circle* circle)
{
    delete circle;
}

// circle virtual table to use the implemented functions.
ShapeVtable circle_vtable=
{
    (double (*) (Shape*)) CircleGetArea,
    (void (*) (Shape*)) CirclePrintInfo,
    (void (*) (Shape*)) CircleDestroy
};

// initialization for circle to use the virtual table created and the sent radius.
void CircleInitialize(Circle* circle, double radius)
{
     // initializing the value of the virtual table with the virtual table created with the implemented functions.
    circle->parent.vtable=&circle_vtable;

    // initializing the circle radius
    circle->radius=radius;
}

// shape: rectangle
struct Rectangle
{
    Shape parent; // used for initialize the virtual table
    double length, width; // used to initialize the rectangle length and width and to get its area.
};

// to implement function GetArea from the virtual table.
double RectangleGetArea(Rectangle* rectangle)
{
    return rectangle->length*rectangle->width; // area = length*width.
}

// to implement function PrintInfo from the virtual table.
void RectanglePrintInfo(Rectangle* rectangle)
{
    cout << "Shape: Rectangle." << endl;
    cout << "Rectangle Length = " << rectangle->length << endl;
    cout << "Rectangle Width = " << rectangle->width << endl;
    cout << "Rectangle area = " << RectangleGetArea(rectangle) << endl << endl;
}

// to implement function Destroy from the virtual table.
void RectangleDestroy(Rectangle* rectangle)
{
    delete rectangle;
}

// Rectangle virtual table to use the implemented functions.
ShapeVtable rectangle_vtable=
{
    (double (*) (Shape*)) RectangleGetArea,
    (void (*) (Shape*)) RectanglePrintInfo,
    (void (*) (Shape*)) RectangleDestroy

};

// initialization for rectangle to use the virtual table created and the sent length and width.
void RectangleInitialize(Rectangle* rectangle, double length, double width)
{
    // initializing the value of the virtual table with the virtual table created with the implemented functions.
    rectangle->parent.vtable=&rectangle_vtable;

    // initializing rectangle length
    rectangle->length=length;

    // initializing rectangle width
    rectangle->width=width;
}

// Shape: ellipse.
struct Ellipse
{
    Shape parent; // used to initialize the virtual table.
    double a_axis, b_axis; // used to initialize the ellipse a and b axes and to get its area.
};

// calculate ellipse area.
double EllipseGetArea(Ellipse* ellipse)
{
    return 3.14*ellipse->a_axis*ellipse->b_axis; // area = PI*a*b.
}

// Print ellipse info.
void EllipsePrintInfo(Ellipse* ellipse)
{
    cout << "Shape: Ellipse." << endl;
    cout << "Ellipse a-axis = " << ellipse->a_axis << endl;
    cout << "Ellipse b-axis = " << ellipse->b_axis << endl;
    cout << "Ellipse area = " << EllipseGetArea(ellipse) << endl << endl;
}

// free shape resources.
void EllipseDestroy(Ellipse* ellipse)
{
    delete ellipse;
}

// Ellipse virtual table to use the implemented functions.
ShapeVtable ellipse_vtable=
{
    (double (*) (Shape*)) EllipseGetArea,
    (void (*) (Shape*)) EllipsePrintInfo,
    (void (*) (Shape*)) EllipseDestroy

};

// initialization for ellipse to use the virtual table created and the sent a_axis and b_axis.
void EllipseInitialize(Ellipse* ellipse, double a_axis, double b_axis)
{
    // initializing the value of the virtual table with the virtual table created with the implemented functions.
    ellipse->parent.vtable=&ellipse_vtable;

    // initializing a_axis
    ellipse->a_axis=a_axis;

    // initializing b_axis
    ellipse->b_axis=b_axis;
}


int main()
{
    Circle circle;
    CircleInitialize(&circle, 10); // circle with radius 10

    Rectangle rectangle;
    RectangleInitialize(&rectangle, 3,5); // circle with radius 10

    Ellipse ellipse;
    EllipseInitialize(&ellipse, 10, 12); // ellipse with radius 10, 12

    Shape* shapes[3];
    shapes[0]=(Shape*)&circle;
    shapes[1]=(Shape*)&rectangle;
    shapes[2]=(Shape*)&ellipse;

    double total_area=0;

    int i;
    for(i=0;i<3;i++)
    {
        double d=GetArea(shapes[i]);
        total_area+=d;
        PrintInfo(shapes[i]); // prints (cout) the radius if circle, width and height if rectangle, ... etc
    }

    cout<< "Total area=" << total_area<<endl; // check if the value is correct

    return 0;
}

/*int main()
{
    Circle circle;
    CircleInitialize(&circle, 10); // circle with radius 10

    Rectangle rectangle;
    RectangleInitialize(&rectangle, 3, 5); // rectangle with width 3 and height 5

    Ellipse ellipse;
    EllipseInitialize(&ellipse, 10, 12); // ellipse with radius 10, 12

    Shape* shapes[3];
    shapes[0]=(Shape*)&circle ;
    shapes[1]=(Shape*)&rectangle ;
    shapes[2]=(Shape*)&ellipse ;

    double total_area=0;

    int i;
    for(i=0;i<3;i++)
    {
        double d=GetArea(shapes[i]);
        total_area+=d;
        PrintInfo(shapes[i]); // prints (cout) the radius if circle, width and height if rectangle, ... etc
    }

    cout<<total_area<<endl; // check if the value is correct

    return 0;
}
*/
