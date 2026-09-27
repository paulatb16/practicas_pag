#include "gui.h"
#include "Renderer.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace PAG {
    gui* gui::instancia = nullptr;

    gui::gui() {}
    gui::~gui() {}

    gui& gui::getInstancia() {
        if (!instancia) {
            instancia = new gui();
        }
        return *instancia;
    }
    //INICIALIZO
    void gui::inicializar(GLFWwindow* window) {
        // Inicialización básica de ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 430");
    }

    //DIBUJO VENTANAS
    void gui::render() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once); //ventana de los mensajes
        if (ImGui::Begin("Mensajes")) {
            ImGui::Text("%s", Renderer::getInstancia().getRendererInfo().c_str());
            ImGui::Text("%s", Renderer::getInstancia().getVendorInfo().c_str());
            ImGui::Text("%s", Renderer::getInstancia().getVersionInfo().c_str());
            ImGui::Text("%s", Renderer::getInstancia().getShadingLanguageVersionInfo().c_str());

            ImGui::BeginChild("Scroll mensajes", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
            for (const auto& msg : mensajes) {
                ImGui::TextUnformatted(msg.c_str());
            }

            //esto sirve para que se vaya viendo siempre el mensaje mas reciente
            if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
                ImGui::SetScrollHereY(1.0f);
            }
            ImGui::EndChild();
        }

        ImGui::End();



    ImGui::SetNextWindowPos(ImVec2(350, 10), ImGuiCond_Once); //ventana del color picker
    if (ImGui::Begin("Fondo")) {
        static float color[4] = { 0.6f, 0.6f, 0.6f,0.6f};
        ImGuiColorEditFlags flags = ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_AlphaBar; //esto es para que sea la rueda en vez del cuadrado y para que aparezca la barra de alpha
        if (ImGui::ColorPicker4("Color para el fondo", color,flags)) {

            Renderer::getInstancia().ClearColor(color[0], color[1], color[2], color[3]);
        }
    }
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

    //FINALIZO
void gui::finalizar() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

//GESTIONO CAPTURA DE EVENTOS EN CALLBACKS

    bool gui::capturaRaton() {
        return ImGui::GetIO().WantCaptureMouse;
    }
    bool gui::capturaTeclado() {
    return ImGui::GetIO().WantCaptureKeyboard;
}
    void gui::addMensaje(const std::string& texto) {
    mensajes.push_back(texto);
}

}