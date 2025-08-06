
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include "manager.h"
#include "modules/gui/ipanel.h"
#include "modules/gui/panelRegistry.h"

static GLFWwindow *g_pWindow = nullptr;
using namespace Gui;

void Manager::initialize()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return;
    }

    const char *glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    g_pWindow = glfwCreateWindow(1280, 720, "Trade Manager", nullptr, nullptr);
    if (!g_pWindow)
    {
        std::cerr << "Failed to create GLFW window\n";
        return;
    }

    glfwMakeContextCurrent(g_pWindow);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(g_pWindow, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    for (auto &panel : m_lstPanels)
    {
        panel->onInit();
    }
}

void Manager::onRender()
{
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Panel Manager");
    for (auto &panel : m_lstPanels)
    {
        bool visible = panel->isVisible();
        if (ImGui::Checkbox(panel->name().data(), &visible))
        {
            panel->setVisible(visible);
        }
    }
    ImGui::End();

    for (auto &panel : m_lstPanels)
    {
        if (panel->isVisible())
        {
            ImGui::Begin(panel->name().data());
            panel->onRender();
            ImGui::End();
        }
    }

    ImGui::Render();
    int iDisplayWidth, iDisplayHeight;
    glfwGetFramebufferSize(g_pWindow, &iDisplayWidth, &iDisplayHeight);
    glViewport(0, 0, iDisplayWidth, iDisplayHeight);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(g_pWindow);
}

bool Manager::shouldClose() const
{
    return glfwWindowShouldClose(g_pWindow);
}

void Manager::shutDown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(g_pWindow);
    glfwTerminate();
}

void Manager::addPanel(std::unique_ptr<IPanel> pPanel)
{
    m_lstPanels.push_back(std::move(pPanel));
}
