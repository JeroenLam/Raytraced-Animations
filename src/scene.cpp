#include "scene.h"

#include "hit.h"
#include "image.h"
#include "material.h"
#include "ray.h"

#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

pair<ObjectPtr, Hit> Scene::castRay(Ray const &ray) const
{
    // Find hit object and distance
    Hit min_hit(numeric_limits<double>::infinity(), Vector());
    ObjectPtr obj = nullptr;
    for (unsigned idx = 0; idx != objects.size(); ++idx)
    {
        Hit hit(objects[idx]->intersect(ray));
        if (hit.t < min_hit.t)
        {
            min_hit = hit;
            obj = objects[idx];
        }
    }

    return pair<ObjectPtr, Hit>(obj, min_hit);
}

Color Scene::trace(Ray const &ray, unsigned depth)
{
    pair<ObjectPtr, Hit> mainhit = castRay(ray);
    ObjectPtr obj = mainhit.first;
    Hit min_hit = mainhit.second;

    // No hit? Return background color.
    if (!obj)
        return Color(0.0, 0.0, 0.0);

    Material const &material = obj->material;
    Point hit = ray.at(min_hit.t);
    Vector V = -ray.D;

    // Pre-condition: For closed objects, N points outwards.
    Vector N = min_hit.N;

    // The shading normal always points in the direction of the view,
    // as required by the Phong illumination model.
    Vector shadingN;
    if (N.dot(V) >= 0.0)
        shadingN = N;
    else
        shadingN = -N;

    Color matColor;
    if (material.hasTexture) {
        Vector texel = obj->toUV(hit);
        // texel.x == u, texel.y == v
        matColor = material.texture.colorAt(texel.x, 1.0 - texel.y);
    } else {
        matColor = material.color;
    }
    
    // Add ambient once, regardless of the number of lights.
    Color color = material.ka * matColor;

    // Move the hitpoint for shadow calculations
    Point shadowP = hit + epsilon * shadingN;

    // Add diffuse and specular components.
    for (auto const &light : lights)
    {
        Vector L = (light->position - hit).normalized();

        // Construct and cast a ray to the light
        Vector shadowL = (light->position - shadowP).normalized();
        Ray shadowRay = Ray(shadowP, shadowL);
        pair<ObjectPtr, Hit> shadowHit = castRay(shadowRay);
        double distanceToLight = (light->position - shadowP).length();

        // Cell shader border
        //if (V.dot(shadingN) < 0.21)
        //    return 0 * color;

        // If the ray hits anything OR if the light is before the hit object OR if the setting is off
        //  then we do not use the diffusive and specular component
        if (!shadowHit.first || distanceToLight < shadowHit.second.t || !renderShadows)
        {

            // Add diffuse.
            double dotNormal = shadingN.dot(L);
            double diffuse = std::max(dotNormal, 0.0);
            color += diffuse * material.kd * light->color * matColor;

            // Add specular.
            if(dotNormal > 0)
            {
                Vector reflectDir = reflect(-L, shadingN); // Note: reflect(..) is not given in the framework.
                double specAngle = std::max(reflectDir.dot(V), 0.0);
                double specular = std::pow(specAngle, material.n);

                color += specular * material.ks * light->color;
            }
        }
    }

    // Computing the reflection vector from the hitpoint
    Vector R = 2 * (shadingN.dot(V)) * shadingN - V;

    // The object is transparent, and thus refracts and reflects light.
    // Use Schlick's approximation to determine the ratio between the two.
    if (depth > 0 and material.isTransparent)
    {
        // Schlick approximation variables
        double n_outside = (V.dot(N) > 0) ? 1.0 : material.nt;
        double n_inside = (V.dot(N) > 0) ? material.nt : 1.0;
        double Phi_i = acos(shadingN.dot(V));

        double Kr0 = pow( (n_outside - n_inside)/(n_outside + n_inside) , 2);
        double Kr = (1 + Kr0) * pow((1 - cos(Phi_i)), 5);
        double Kt = 1 - Kr;

        // Trace reflected part
        color += Kr * trace(Ray(shadowP, R), depth - 1);

        // Trace transmitted part
        Vector D = ray.D;
        Vector T = (n_outside * (D - (D.dot(shadingN) * shadingN))) / n_inside - shadingN * sqrt(1 - pow(n_outside, 2) * (1 - pow(D.dot(shadingN), 2)) / pow(n_inside, 2) );
        color += Kt * trace(Ray(hit - epsilon * shadingN , T), depth - 1);
    }
    // The object is not transparent, but opaque.
    else if (depth > 0 and material.ks > 0.0)
    {
        // Recursively call the trace function
        color += material.ks * trace(Ray(shadowP, R), depth - 1);
    }

    return color;
}

void Scene::render(Image &img)
{
    unsigned w = img.width();
    unsigned h = img.height();
    for (unsigned y = 0; y < h; ++y)
        for (unsigned x = 0; x < w; ++x)
        {
            // Split each pixel up into supersamples
            Color tempCol;
            for (double ssX = 0; ssX < supersamplingFactor; ++ssX)
            {
                for (double ssY = 0; ssY < supersamplingFactor; ++ssY)
                {
                    Point pixel(x - 0.5 * w + (0.5+ssX)/supersamplingFactor, h - 1 - y - 0.5 * h + (0.5+ssY)/supersamplingFactor, 0);
                    Ray ray(eye, (pixel - eye).normalized());
                    Color col = trace(ray, recursionDepth);
                    col.clamp();
                    tempCol += col;
                }
            }
            tempCol /= pow(supersamplingFactor, 2);
            //int cellFactor = 8;
            //tempCol = (cellFactor * tempCol).floor() / cellFactor;
            img(x, y) = tempCol;
        }
}

// --- Misc functions ----------------------------------------------------------

// Defaults
Scene::Scene()
:
    objects(),
    lights(),
    eye(),
    renderShadows(false),
    recursionDepth(0),
    supersamplingFactor(1)
{}

void Scene::addObject(ObjectPtr obj)
{
    objects.push_back(obj);
}

void Scene::addLight(Light const &light)
{
    lights.push_back(LightPtr(new Light(light)));
}

void Scene::setEye(Triple const &position)
{
    eye = position;
}

unsigned Scene::getNumObject()
{
    return objects.size();
}

unsigned Scene::getNumLights()
{
    return lights.size();
}

void Scene::setRenderShadows(bool shadows)
{
    renderShadows = shadows;
}

void Scene::setRecursionDepth(unsigned depth)
{
    recursionDepth = depth;
}

void Scene::setSuperSample(unsigned factor)
{
    supersamplingFactor = factor;
}
