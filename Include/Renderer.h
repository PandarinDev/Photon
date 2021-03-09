#pragma once

#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "MathUtils.h"
#include "Image.h"

namespace photon {

    struct Renderer {

        const Canvas& canvas;
        const Camera& camera;
        const Color background_color;

        Renderer(const Canvas& canvas, const Camera& camera, const Color& background_color);

        Image render(const Scene& scene) const;

    private:

        Vec3f to_canvas_point(double x, double y) const;

        std::vector<ImagePixel> render_part(
            const Scene& scene,
            std::size_t start_pixel,
            std::size_t end_pixel) const;

    };

}