#include "Renderer.h"
#include "ImageWriter.h"

int main(int argc, char** argv) {
    using namespace photon;
    Canvas canvas(1024, 1024, 1.0f);
    Camera camera(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, 1.0f));

    Color red(255, 0, 0);
    Color background_color(25, 128, 240);
    std::vector<std::unique_ptr<Light>> lights;
    lights.emplace_back(std::make_unique<AmbientLight>(Vec3f(0.1f, 0.1f, 0.1f)));
    lights.emplace_back(std::make_unique<PointLight>(Vec3f(0.0f, 0.0f, 10.0f), Vec3f(1.0f, 1.0f, 1.0f)));
    Scene scene({ Sphere(Vec3f(0.0f, 0.0f, 50.0f), 10.f, Material(Color(255, 0, 0))) }, std::move(lights));
    Renderer renderer(canvas, camera, background_color);
    const auto image = renderer.render(scene);
    ImageWriter image_writer;
    image_writer.write_image_to_file(image, "foobar.ppm");
    return 0;
}