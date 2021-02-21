#include "Renderer.h"
#include "ImageWriter.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "ModelLoader.h"

int main(int argc, char** argv) {
    using namespace photon;
    Canvas canvas(1024, 1024, 1.0f);
    Camera camera(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, 1.0f));

    Color red(255, 0, 0);
    Color background_color(25, 128, 240);
    // Geometry
    std::vector<std::unique_ptr<Geometry>> geometry;
    // geometry.emplace_back(std::make_unique<Sphere>(Vec3f(0.0f, 0.0f, 3.0f), 1.4f, Material(Color(255, 0, 0), 15.0f)));
    // geometry.emplace_back(std::make_unique<Sphere>(Vec3f(0.0f, 0.0f, 0.15f), 0.05f, Material(Color(0, 0, 255), 3.0f)));
    // geometry.emplace_back(std::make_unique<Plane>(Vec3f(0.0f, 0.01f, 0.0f), Vec3f(0.0f, -1.0f, 0.0f), Material(Color(0, 255, 0), 20.0f)));
    // geometry.emplace_back(std::make_unique<Triangle>(Vec3f(-0.3f, 0.0f, 3.0f), Vec3f(0.3f, 0.0f, 3.0f), Vec3f(0.0f, -0.6f, 3.0f), Material(Color(255, 0, 0), 3.0f)));
    ModelLoader model_loader;
    auto suzanne = model_loader.load_model("Assets/Suzanne.obj", Material(Color(255, 0, 0), 15.0f));
    geometry.emplace_back(std::move(suzanne));

    // Lights
    std::vector<std::unique_ptr<Light>> lights;
    lights.emplace_back(std::make_unique<AmbientLight>(Vec3f(0.1f, 0.1f, 0.1f)));
    lights.emplace_back(std::make_unique<PointLight>(Vec3f(0.05f, -0.05f, 0.0f), Vec3f(0.7f, 0.7f, 0.7f)));

    // Create scene and renderer
    Scene scene(std::move(geometry), std::move(lights));
    Renderer renderer(canvas, camera, background_color);

    // Render scene into an image
    const auto image = renderer.render(scene);
    ImageWriter image_writer;
    image_writer.write_image_to_file(image, "foobar.ppm");
    return 0;
}