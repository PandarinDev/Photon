#include "Renderer.h"
#include "Image.h"

#include <optional>
#include <vector>
#include <algorithm>

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
                std::optional<Pair<float, Sphere>> closest_intersection;
                // Try to intersect the ray with every sphere in the scene
                for (const auto& sphere : scene.spheres) {
                    const auto intersections = sphere.intersect(ray);
                    if (!intersections) {
                        continue;
                    }
                    // Check the first intersection
                    if (intersections->first > canvas.distance && (!closest_intersection || intersections->first < closest_intersection->first)) {
                        closest_intersection = Pair(intersections->first, sphere);
                    }

                    // Check the second intersection
                    if (intersections->second > canvas.distance && (!closest_intersection || intersections->second < closest_intersection->first)) {
                        closest_intersection = Pair(intersections->second, sphere);
                    }
                }

                // If there were no intersections use background color to color the pixel
                if (!closest_intersection) {
                    pixels[counter++] = background_color;
                    continue;
                }

                const auto sphere = closest_intersection->second;
                const auto intersection_point = ray.point_at(closest_intersection->first);
                const auto normal = (intersection_point - sphere.position).normalize();
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
                        const auto dot_product = normal.dot(point_to_light);
                        // Below 0 dot product means that the light illuminates
                        // the other (non-visible) side of the object, skip it.
                        if (dot_product < 0.0f) {
                            continue;
                        }

                        intensities.x += light->intensity.x * dot_product / (normal.length() * point_to_light.length()); 
                        intensities.y += light->intensity.y * dot_product / (normal.length() * point_to_light.length()); 
                        intensities.z += light->intensity.z * dot_product / (normal.length() * point_to_light.length()); 
                    }
                }

                // Clamp and multiply color values
                const auto& sphere_color = sphere.material.diffuse_color;
                Color pixel_color(
                    std::clamp(intensities.x, 0.0f, 1.0f) * sphere_color.r,
                    std::clamp(intensities.y, 0.0f, 1.0f) * sphere_color.g,
                    std::clamp(intensities.z, 0.0f, 1.0f) * sphere_color.b
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