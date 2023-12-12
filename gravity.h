#include <stdio.h>
#include <math.h>

#define G_CONST 1
#define NEAR_ZERO 2

struct Vector2D
{
    Vector2D(double x, double y) : x(x), y(y) {};
    Vector2D operator+(const Vector2D& other) const { return Vector2D(x + other.x, y + other.y); }
    Vector2D operator-(const Vector2D& other) const { return Vector2D(x - other.x, y - other.y); }
    Vector2D operator*(const Vector2D& other) const { return Vector2D(x * other.x, y * other.y); }
    friend Vector2D operator*(const Vector2D& r, const double number) { return Vector2D(r.x * number, r.y * number); }
    friend Vector2D operator*(const double number, const Vector2D& r) { Vector2D vec(number * r.x, number * r.y); return vec; }
    Vector2D& operator+=(const Vector2D& r) { (*this) = (*this) + r; return *this; }

    double length() { return sqrt(x * x + y * y); }
    void reset() { x = 0; y = 0; }
    void Display() { printf(" %f, %f,", x, y); }
    double x, y;
};

struct NBODY
{
    int nMass;
    Vector2D fPosition;
    Vector2D fSpeed;
    Vector2D fAcceleration;
};

void InitNbody(NBODY* pNbody, int NMass, Vector2D centerPos);
void calAcceleration(NBODY* pNbody, int NMass);
void calSpeed(NBODY* pNbody, int NMass, double dt);
void calPosition(NBODY* pNbody, int NMass, double dt);
void printVector(NBODY* pNbody, int NMass);
int gravity(int NMass, Vector2D centerPos);



