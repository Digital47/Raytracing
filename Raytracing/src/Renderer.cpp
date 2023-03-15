#include "Renderer.h"

#include "Walnut/Random.h"
using namespace Walnut;

void Renderer::OnResize(uint32_t width, uint32_t height)
{
   if (m_FinalImage)
   {
      //check resize necessary
      if (m_FinalImage->GetWidth() == width && m_FinalImage->GetHeight() == height)
         return;
      m_FinalImage->Resize(width, height);
   }
   else
      m_FinalImage = std::make_shared<Image>(width, height, ImageFormat::RGBA);

   delete[] m_imageData;
   m_imageData = new uint32_t[width * height];
}

void Renderer::Render()
{
   for (uint32_t y = 0; y < m_FinalImage->GetHeight(); y++)
   {
      for (uint32_t x = 0; x < m_FinalImage->GetWidth(); x++)
      {
         //convering pixel x,y to 0,1
         glm::vec2 coord = { (float)x / (float)m_FinalImage->GetWidth(), (float)y / (float)m_FinalImage->GetHeight() };
         coord = coord * 2.0f - 1.0f;   //0-1  ==> -1,1
         m_imageData[x + y * m_FinalImage->GetWidth()] = perPixel(coord);
      }
   }

   m_FinalImage->SetData(m_imageData);
}

uint32_t Renderer::perPixel(glm::vec2 coord)
{
   /*uint8_t r = (uint8_t)(coord.x * 255.0f);
   uint8_t g = (uint8_t)(coord.y * 255.0f);*/

   glm::vec3 rayOrigin(0.0f, 0.0f, -2.0f);
   glm::vec3 rayDirection(coord.x, coord.y, -1.0f);
   glm::normalize(rayDirection);
   float radius = 0.5f;
   //a == ray origin
   //b == ray direction
   //r -  radius
   //t - hit distance
   // (bx^2 + by^2)t^2 + 2(axbx + ayby)t + (ax^2 + ay^2 - r^2) = 0


   //Qudaradic formaula
   //b^2 -4ac
   float a = glm::dot(rayDirection, rayDirection);
   float b = 2.0f * glm::dot(rayOrigin, rayDirection);
   float c = glm::dot(rayOrigin, rayOrigin) - radius * radius;

   float discriminant = b * b - 4.0f * a * c;

   if (discriminant >= 0)
      return 0xffff00ff;
   return 0xff000000;
}
