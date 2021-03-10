#include "Renderer.h"
#include "ImageWriter.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "ModelLoader.h"

#include <chrono>
#include <iostream>

int main(int argc, char** argv) {
    using namespace photon;
    Canvas canvas(1024, 1024, 1.0f);
    Camera camera(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, 1.0f));

    Color red(255, 0, 0);
    Color background_color(25, 128, 240);
    // Geometry
    std::vector<std::unique_ptr<Geometry>> geometry;
    ModelLoader model_loader;
    auto suzanne = model_loader.load_model("Assets/Suzanne.obj", Material(Color(255, 0, 0), 25.0f));
    geometry.emplace_back(std::move(suzanne));

    // Lights
    std::vector<std::unique_ptr<Light>> lights;
    lights.emplace_back(std::make_unique<AmbientLight>(Vec3f(0.1f, 0.1f, 0.1f)));
    lights.emplace_back(std::make_unique<PointLight>(Vec3f(0.05f, -0.05f, 0.0f), Vec3f(0.7f, 0.7f, 0.7f)));

    // Create scene and renderer
    Scene scene(std::move(geometry), std::move(lights));
    Renderer renderer(canvas, camera, background_color);

    // Render scene into an image
    const auto render_start = std::chrono::high_resolution_clock::now();
    const auto image = renderer.render(scene);
    std::chrono::duration<double> render_elapsed = std::chrono::high_resolution_clock::now() - render_start;
    std::cout << "Rendering took " << render_elapsed.count() << "s" << std::endl;
    ImageWriter image_writer;
    image_writer.write_image_to_file(image, "foobar.ppm");
    return 0;
}