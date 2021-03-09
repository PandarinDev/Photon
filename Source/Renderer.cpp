#include "Renderer.h"
#include "Image.h"

#include <optional>
#include <vector>
#include <cmath>
#include <algorithm>
#include <thread>
#include <future>

namespace photon {

    Renderer::Renderer(const Canvas& canvas, const Camera& camera, const Color& background_color)
        : canvas(canvas), camera(camera), background_color(background_color) {}

    Image Renderer::render(const Scene& scene) const {
        std::vector<ImagePixel> pixels(canvas.width * canvas.height);
        std::int32_t half_width = canvas.width / 2.0f;
        std::int32_t half_height = canvas.height / 2.0f;
        const auto x_range = Pair(-half_width + 1, half_width);
        const auto y_range = Pair(-half_height + 1, half_height);
        const auto num_threads = std::thread::hardware_concurrency();
        const auto pixel_per_thread = pixels.size() / num_threads;
        // Split work among threads
        std::vector<std::future<std::vector<ImagePixel>>> workers;
        for (std::size_t i = 0; i < num_threads; ++i) {
            workers.emplace_back(std::async(std::launch::async, [this, &scene, &pixels, i, pixel_per_thread, num_threads] {
                // For the last workers the end pixel needs to be pixels.size() - 1, otherwise
                // if we use i * pixel_per_thread + pixel_per_thread - 1 we are subject to rounding errors.
                const auto end_pixel = i != num_threads - 1
                    ? i * pixel_per_thread + pixel_per_thread - 1
                    : pixels.size() - 1;
                return render_part(scene, i * pixel_per_thread, end_pixel);
            }));
        }
        // Join and merge results
        std::size_t counter = 0;
        for (std::size_t i = 0; i < num_threads; ++i) {
            const auto rendered_pixels = workers[i].get();
            for (const auto& pixel : rendered_pixels) {
                pixels[counter++] = pixel;
            }
        }
        return Image(canvas.width, canvas.height, pixels);
    }

    std::vector<ImagePixel> Renderer::render_part(const Scene& scene, std::size_t start_pixel, std::size_t end_pixel) const {
        std::vector<ImagePixel> pixels(end_pixel - start_pixel + 1);
        double half_canvas_width = canvas.width / 2.0;
        double half_canvas_height = canvas.height / 2.0;
        std::size_t counter = 0;
        for (std::size_t pixel = start_pixel; pixel <= end_pixel; ++pixel) {
            double x = pixel % canvas.width - half_canvas_width + 1;
            double y = pixel / canvas.width - half_canvas_height + 1;
            auto canvas_point = to_canvas_point(x, y);
            const auto ray = Ray(camera.position, canvas_point);
            std::optional<Pair<Intersection, Geometry*>> closest_intersection;
            // Try to intersect the ray with every geometry in the scene
            for (const auto& geometry : scene.geometry) {
                const auto intersection = geometry->intersect(ray);
                if (!intersection) {
                    continue;
                }
                if (!closest_intersection || intersection->t < closest_intersection->first.t) {
                    closest_intersection = Pair(*intersection, geometry.get());
                }
            }

            // If there were no intersections use background color to color the pixel
            if (!closest_intersection) {
                pixels[counter++] = background_color;
                continue;
            }

            const auto geometry = closest_intersection->second;
            const auto intersection_point = ray.point_at(closest_intersection->first.t);
            const auto normal = closest_intersection->first.normal;
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
                        const auto shadow_intersection = other_geometry->intersect(light_ray);
                        if (!shadow_intersection || std::abs(shadow_intersection->t) < 1e-4f) {
                            continue;
                        }
                        if (shadow_intersection->t <= point_to_light.length()) {
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
                    const auto rv_dot_product = std::max(reflection.dot(-intersection_point), 0.0);
                    const auto specular_intensity = std::pow(rv_dot_product / (reflection.length() * intersection_point.length()), shininess);

                    const auto total_intensity = diffuse_intensity + specular_intensity;
                    intensities.x += light->intensity.x * total_intensity; 
                    intensities.y += light->intensity.y * total_intensity; 
                    intensities.z += light->intensity.z * total_intensity;
                }
            }

            // Clamp and multiply color values
            const auto& geometry_color = geometry->material.color;
            Color pixel_color(
                std::clamp(intensities.x, 0.0, 1.0) * geometry_color.r,
                std::clamp(intensities.y, 0.0, 1.0) * geometry_color.g,
                std::clamp(intensities.z, 0.0, 1.0) * geometry_color.b
            );

            // Write color to memory
            pixels[counter++] = pixel_color;
        }

        return pixels;
    }

    Vec3f Renderer::to_canvas_point(double x, double y) const {
        return Vec3f(
            x / canvas.width,
            y / canvas.height,
            canvas.distance
        );
    }

}
