#include "Renderer.h"
#include "Image.h"

#include <optional>
#include <vector>
#include <cmath>
#include <algorithm>

#include <iostream>

namespace photon {

    Renderer::Renderer(const Canvas& canvas, const Camera& camera, const Color& background_color)
        : canvas(canvas), camera(camera), background_color(background_color) {}

    Image Renderer::render(const Scene& scene) const {
        std::vector<ImagePixel> pixels(canvas.width * canvas.height);
        std::int32_t half_width = canvas.width / 2.0f;
        std::int32_t half_height = canvas.height / 2.0f;
        const auto x_range = Pair(-half_width + 1, half_width);
        const auto y_range = Pair(-half_height + 1, half_height);
        std::uint32_t counter = 0;
        for (std::int32_t y = y_range.first; y <= y_range.second; ++y) {
            for (std::int32_t x = x_range.first; x <= x_range.second; ++x) {
                auto canvas_point = to_canvas_point(x, y);
                const auto ray = Ray(camera.position, canvas_point);
                std::optional<Pair<float, Geometry*>> closest_intersection;
                // Try to intersect the ray with every geometry in the scene
                for (const auto& geometry : scene.geometry) {
                    const auto intersection = geometry->intersect(ray);
                    if (!intersection) {
                        continue;
                    }
                    if (!closest_intersection || *intersection < closest_intersection->first) {
                        closest_intersection = Pair(*intersection, geometry.get());
                    }
                }

                // If there were no intersections use background color to color the pixel
                if (!closest_intersection) {
                    pixels[counter++] = background_color;
                    continue;
                }

                const auto geometry = closest_intersection->second;
                const auto intersection_point = ray.point_at(closest_intersection->first);
                const auto normal = geometry->get_normal_at_point(intersection_point).normalize();
                // Compute the color at the intersection
                Vec3f intensities;
                for (const auto& light : scene.lights) {
                    // Handle ambient light sources
                    if (light->type == LightType::AMBIENT) {
                        intensities += light->intensity;
                    } else {
                        // Handle point and directional light sources
                        Vec3f point_to_light;
                        if (light->type == LightType::POINT) {
                            point_to_light = static_cast<PointLight*>(light.get())->position - intersection_point;
                        }
                        else if (light->type == LightType::DIRECTIONAL) {
                            point_to_light = static_cast<DirectionalLight*>(light.get())->direction;
                        }

                        // Check if we intersect with anything before intersecting
                        // with the light. If so the intensity contribution of this
                        // light source should be zero because the current pixel
                        // is shadowed by an object in the scene.
                        bool is_shadowed = false;
                        Ray light_ray(intersection_point, point_to_light);
                        for (const auto& other_geometry : scene.geometry) {
                            if (other_geometry.get() == geometry) continue;
                            const auto shadow_intersection = other_geometry->intersect(light_ray);
                            if (shadow_intersection && *shadow_intersection <= point_to_light.length()) {
                                is_shadowed = true;
                                break;
                            }
                        }
                        if (is_shadowed) {
                            continue;
                        }

                        const auto nl_dot_product = normal.dot(point_to_light);
                        // Below 0 dot product means that the light illuminates
                        // the other (non-visible) side of the object, skip it.
                        if (nl_dot_product < 0.0f) {
                            continue;
                        }

                        // Handle diffuse lighting
                        const auto diffuse_intensity = nl_dot_product / (normal.length() * point_to_light.length());
                        // Handle specular lighting
                        const auto shininess = geometry->material.shininess;
                        const auto reflection = normal * 2.0f * nl_dot_product - point_to_light;
                        const auto rv_dot_product = std::max(reflection.dot(-intersection_point), 0.0f);
                        const auto specular_intensity = std::powf(rv_dot_product / (reflection.length() * intersection_point.length()), shininess);

                        const auto total_intensity = diffuse_intensity + specular_intensity;
                        intensities.x += light->intensity.x * total_intensity; 
                        intensities.y += light->intensity.y * total_intensity; 
                        intensities.z += light->intensity.z * total_intensity;
                    }
                }

                // Clamp and multiply color values
                const auto& geometry_color = geometry->material.color;
                Color pixel_color(
                    std::clamp(intensities.x, 0.0f, 1.0f) * geometry_color.r,
                    std::clamp(intensities.y, 0.0f, 1.0f) * geometry_color.g,
                    std::clamp(intensities.z, 0.0f, 1.0f) * geometry_color.b
                );

                // Write color to memory
                pixels[counter++] = pixel_color;
            }
        }

        return Image(canvas.width, canvas.height, pixels);
    }

    Vec3f Renderer::to_canvas_point(float x, float y) const {
        return Vec3f(
            x / canvas.width,
            y / canvas.height,
            canvas.distance
        );
    }

}