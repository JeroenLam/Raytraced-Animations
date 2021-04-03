#include "mesh.h"

#include "../objloader.h"
#include "../vertex.h"
#include "triangle.h"

#include <cmath>
#include <iostream>
#include <limits>

using namespace std;

Hit Mesh::intersect(Ray const &ray)
{
    // Find hit object and distance
    Hit min_hit(numeric_limits<double>::infinity(), Vector());
    int flag = 0;
    for (unsigned idx = 0; idx != d_tris.size(); ++idx)
    {
        Hit hit(d_tris[idx]->intersect(ray));
        if (hit.t < min_hit.t)
        {
            min_hit = hit;
            flag = 1;
        }
    }
    if (flag == 0)
        return Hit::NO_HIT();
    return min_hit;
}

Mesh::Mesh(string const &filename, Point const &position, Vector const &rotation, Vector const &scale)
{
    OBJLoader model(filename);
    d_tris.reserve(model.numTriangles());
    vector<Vertex> vertices = model.vertex_data();
    for (size_t tri = 0; tri != model.numTriangles(); ++tri)
    {
        Vertex one = vertices[tri * 3];
        Point v0(one.x, one.y, one.z);

        Vertex two = vertices[tri * 3 + 1];
        Point v1(two.x, two.y, two.z);

        Vertex three = vertices[tri * 3 + 2];
        Point v2(three.x, three.y, three.z);

        // Apply non-uniform scaling, rotation and translation to the three points
        // of the triangle (v0, v1, and v2) here.

        // Non-uniform scaling
        v0 = v0 * scale;
        v1 = v1 * scale;
        v2 = v2 * scale;

        // Rotation
        // around x
        v0 = Triple(v0.x,
                    v0.y * cos(rotation.x) - v0.z * sin(rotation.x),
                    v0.y * sin(rotation.x) + v0.z * cos(rotation.x)
                    );
        v1 = Triple(v1.x,
                    v1.y * cos(rotation.x) - v1.z * sin(rotation.x),
                    v1.y * sin(rotation.x) + v1.z * cos(rotation.x)
                    );
        v2 = Triple(v2.x,
                    v2.y * cos(rotation.x) - v2.z * sin(rotation.x),
                    v2.y * sin(rotation.x) + v2.z * cos(rotation.x)
                    );
        // around y
        v0 = Triple(v0.x * cos(rotation.y) + v0.z * sin(rotation.y),
                    v0.y,
                    - v0.x * sin(rotation.y) + v0.z * cos(rotation.y)
                    );
        v1 = Triple(v1.x * cos(rotation.y) + v1.z * sin(rotation.y),
                    v1.y,
                    - v1.x * sin(rotation.y) + v1.z * cos(rotation.y)
                    );
        v2 = Triple(v2.x * cos(rotation.y) + v2.z * sin(rotation.y),
                    v2.y,
                    - v2.x * sin(rotation.y) + v2.z * cos(rotation.y)
                    );
        // around z
        v0 = Triple(v0.x * cos(rotation.z) - v0.y * sin(rotation.z),
                    v0.x * sin(rotation.z) + v0.y * cos(rotation.z),
                    v0.z
                    );
        v1 = Triple(v1.x * cos(rotation.z) - v1.y * sin(rotation.z),
                    v1.x * sin(rotation.z) + v1.y * cos(rotation.z),
                    v1.z
                    );
        v2 = Triple(v2.x * cos(rotation.z) - v2.y * sin(rotation.z),
                    v2.x * sin(rotation.z) + v2.y * cos(rotation.z),
                    v2.z
                    );

        // Translation
        v0 = v0 + position;
        v1 = v1 + position;
        v2 = v2 + position;
        
        d_tris.push_back(ObjectPtr(new Triangle(v0, v1, v2)));
    }

    cout << "Loaded model: " << filename << " with " <<
        model.numTriangles() << " triangles.\n";
}
