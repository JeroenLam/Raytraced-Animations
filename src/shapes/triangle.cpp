#include "triangle.h"

Hit Triangle::intersect(Ray const &ray)
{
    // edges
    Vector e0 = v1 - v0, e1 = v2 - v1, e2 = v0 - v2;
    // bra size of the last plane parameter (ax+by+cz+d=0)
    Vector tempN = N;
    double d = -tempN.dot(v0);
    if (tempN.dot(ray.D) < 0.001 && tempN.dot(ray.D) > 0.001)
    {
        return Hit::NO_HIT();
    }
    double t = - (tempN.dot(ray.O) + d) / tempN.dot(ray.D);
    Point intersection = ray.O + t * ray.D;
    Vector ray0 = intersection - v0,
        ray1 = intersection - v1,
        ray2 = intersection - v2; 
    if (t >= 0 &&
        tempN.dot(e0.cross(ray0)) >= 0 && 
        tempN.dot(e1.cross(ray1)) >= 0 && 
        tempN.dot(e2.cross(ray2)) >= 0)
    {
        tempN = (N.dot(ray.D) > 0)? -N: N; // Case in which the normal is directed away from the camera
        return Hit(t,tempN);
    }
    return Hit::NO_HIT();
}

Triangle::Triangle(Point const &v0,
                   Point const &v1,
                   Point const &v2)
:
    v0(v0),
    v1(v1),
    v2(v2),
    N(((v2-v1).cross(v0-v1)).normalized())
{
}