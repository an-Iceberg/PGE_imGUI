// TODO: make this work with OpenGL 3
// #define OLC_GFX_OPENGL33
#define GLEW_STATIC
#define OLC_PGEX_DEAR_IMGUI_IMPLEMENTATION
#include "imgui_impl_pge.h"

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <string>

class Example : public olc::PixelGameEngine
{
private:
  olc::imgui::PGE_ImGUI pge_imgui;
  int m_GameLayer;
  int counter = 0;
  bool open = true;
  bool close = false;

public:
  //PGE_ImGui can automatically call the SetLayerCustomRenderFunction by passing
  //true into the constructor.  false is the default value.
  Example() : pge_imgui(false)
  {
    sAppName = "Dear ImGui x olc::PixelGameEngine Test Application";
  }

public:
  bool OnUserCreate() override
  {
    //Create a new Layer which will be used for the game
    m_GameLayer = CreateLayer();

    //The layer is not enabled by default, so we need to enable it
    EnableLayer(m_GameLayer, true);

    //Set a custom render function on layer 0. Since DrawUI is a member of
    //our class, we need to use std::bind
    //If the pge_imgui was constructed with _register_handler = true, this line is not needed
    SetLayerCustomRenderFunction(0, std::bind(&Example::DrawUI, this));

    return true;
  }

  bool OnUserUpdate(float fElapsedTime) override
  {
    //Change the Draw Target to not be Layer 0
    SetDrawTarget((uint8_t)m_GameLayer);

    //Game Drawing code here
    //Create and react to your UI here, it will be drawn during the layer draw function
    // ImGui::ShowDemoWindow();

    ImGui::StyleColorsClassic();

    ImGuiStyle& roundBorders = ImGui::GetStyle();
    roundBorders.WindowBorderSize = 1;
    roundBorders.ChildBorderSize = 1;
    roundBorders.PopupBorderSize = 1;
    roundBorders.FrameBorderSize = 1;
    roundBorders.TabBorderSize = 1;
    roundBorders.WindowRounding = 12;
    roundBorders.ChildRounding = 12;
    roundBorders.FrameRounding = 12;
    roundBorders.PopupRounding = 12;
    roundBorders.ScrollbarRounding = 12;
    roundBorders.GrabRounding = 12;
    roundBorders.TabRounding = 12;
    roundBorders.Colors[0] = ImVec4(1, 2, 3, 1);

    ImGui::BeginMainMenuBar();
    {
      ImGui::Text("Sample Text");
      ImGui::Separator();

      if (ImGui::BeginMenu("Menu"))
      {
        ImGui::MenuItem("Label", "", false, false);
        if (ImGui::Button("Increment"))
        {
          counter++;
        }
        ImGui::Separator();
        ImGui::MenuItem("Label");
        ImGui::EndMenu();
      }

      ImGui::Separator();
    }
    ImGui::EndMainMenuBar();

    ImGuiWindowFlags windowFlags = 0;
    windowFlags |= ImGuiWindowFlags_NoMove;
    windowFlags |= ImGuiWindowFlags_NoCollapse;
    windowFlags |= ImGuiWindowFlags_NoResize;

    ImGui::SetNextWindowPos(ImVec2(0, 19));
    ImGui::SetNextWindowSize(ImVec2(ScreenWidth() / 2, ScreenHeight() - 19));
    ImGui::Begin("Name", NULL, windowFlags);
    {
      ImGui::Text("Some Text");
      if (ImGui::Button("Increment"))
      {
        counter++;
      }
      ImGui::SameLine();
      // ImGui::Text can be used the same way as printf
      ImGui::Text("%i", counter);
    }
    ImGui::End();

    Clear(olc::Pixel(128, 0, 255));

    DrawStringProp(ScreenWidth() / 2, ScreenHeight() / 2, std::to_string(GetFPS()), olc::CYAN, 2);

    return true;
  }

  void DrawUI(void)
  {
    //This finishes the Dear ImGui and renders it to the screen
    pge_imgui.ImGui_ImplPGE_Render();
  }
};

int main()
{
  Example demo;

  if (demo.Construct(1280, 720, 1, 1))
  {
    demo.Start();
  }

  return 0;
}
