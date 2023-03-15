#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"
#include "Walnut//Random.h"
#include "Walnut/Timer.h"
using namespace Walnut;
class ExampleLayer : public Walnut::Layer
{
public:
   virtual void OnUIRender() override
   {
      ImGui::Begin("Job");
      ImGui::Text("renderTime %.3fms", m_LastRenderTime);
      if (ImGui::Button("render"))
      {
         Render();
      }
      ImGui::End();

      ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
      ImGui::Begin("viewport");
      m_viewportWidth = ImGui::GetContentRegionAvail().x;
      m_viewportHeight = ImGui::GetContentRegionAvail().y;
      if (m_image)
         ImGui::Image(m_image->GetDescriptorSet(), { (float)m_image->GetWidth(), (float)m_image->GetHeight() });
      ImGui::End();
      ImGui::PopStyleVar();
      //ImGui::ShowDemoWindow();
      Render();
   }

   void Render()
   {
      Timer timer;
      if (!m_image || m_viewportWidth != m_image->GetWidth() || m_viewportHeight != m_image->GetHeight())
      {
         m_image = std::make_shared<Image>(m_viewportWidth, m_viewportHeight, ImageFormat::RGBA);
         delete m_imageData;
         m_imageData = new uint32_t[m_viewportWidth * m_viewportHeight];
      }
     
      for (uint32_t i = 0; i < m_viewportWidth * m_viewportHeight; i++)
      {
         m_imageData[i] = Random::UInt();
         m_imageData[i] |= 0xff000000;
      }
      m_image->SetData(m_imageData);

      m_LastRenderTime = timer.ElapsedMillis();
   }
private:
   std::shared_ptr<Image> m_image = nullptr;
   uint32_t* m_imageData = nullptr;
   uint32_t m_viewportWidth = 0;
   uint32_t m_viewportHeight = 0;
   float m_LastRenderTime = 0.0f;
};




Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
   Walnut::ApplicationSpecification spec;
   spec.Name = "Raytracing Example";

   Walnut::Application* app = new Walnut::Application(spec);
   app->PushLayer<ExampleLayer>();
   app->SetMenubarCallback([app]()
      {
         if (ImGui::BeginMenu("File"))
         {
            if (ImGui::MenuItem("Exit"))
            {
               app->Close();
            }
            ImGui::EndMenu();
         }
      });
   return app;
}