#pragma once

#include "Walnut/Image.h"
#include <memory>
#include <glm/glm.hpp>
class Renderer
{
public:
   Renderer() = default;
   ~Renderer() {};

   void OnResize(uint32_t widht, uint32_t height);
   void Render();

   std::shared_ptr<Walnut::Image> GetFinalImage() const { return m_FinalImage; }
private:
   uint32_t perPixel(glm::vec2 coord);
   std::shared_ptr<Walnut::Image> m_FinalImage;
   uint32_t* m_imageData = nullptr;

};

