#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"
#include "Walnut/Timer.h"
#include "Renderer.h"

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
     
      auto image = m_Renderer.GetFinalImage();
      if (image)
         ImGui::Image(image->GetDescriptorSet(), { (float)image->GetWidth(), (float)image->GetHeight() }
                ,ImVec2(0,1), ImVec2(1,0));
      ImGui::End();
      ImGui::PopStyleVar();
      //ImGui::ShowDemoWindow();
      Render();  //do repeat
   }

   void Render()
   {
      Timer timer;
      
      m_Renderer.OnResize(m_viewportWidth, m_viewportHeight);

      m_Renderer.Render();

      m_LastRenderTime = timer.ElapsedMillis();
   }
private:
   Renderer m_Renderer;
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