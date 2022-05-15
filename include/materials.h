#ifndef MATERIALS_H
#define MATERIALS_H

#include "raytracer.h"
#include "hittable.h"


class material {
public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};

class lambertian: public material {
public:
    color albedo;
public:
    lambertian(const color& a): albedo(a) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        auto scatter_direction = rec.normal + random_unit_vector();

        if(scatter_direction.near_zero()) {
            scatter_direction = rec.normal;
        }

        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }
};


class metal : public material {
public:
    color albedo;
public:
    metal(const color& a) : albedo(a) {};

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected);
        attenuation = albedo;

        return dot(scattered.direction(), rec.normal) > 0;
    }
};

#endif //MATERIALS_H
