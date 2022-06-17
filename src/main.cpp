#define OLC_PGEX_DEAR_IMGUI_IMPLEMENTATION
#include "imgui_impl_pge.h"

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class Example : public olc::PixelGameEngine
{
  olc::imgui::PGE_ImGUI pge_imgui;
  int m_GameLayer;

public:
  //PGE_ImGui can automatically call the SetLayerCustomRenderFunction by passing
  //true into the constructor.  false is the default value.
  Example() : pge_imgui(false)
  {
    sAppName = "Test Application";
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
    ImGui::ShowDemoWindow();

    Clear(olc::Pixel(128, 0, 255));

    if (GetKey(olc::A).bPressed)
    {
      // Redraws screen but seems a bit buggy
      SetScreenSize(600, 1000);
    }

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

  if (demo.Construct(1000, 600, 1, 1))
  {
    demo.Start();
  }

  return 0;
}
