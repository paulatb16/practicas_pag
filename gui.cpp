#include <glad/glad.h>
#include "gui.h"
#include "Renderer.h"
#include "ShaderProgram.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <random>
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

    void gui::inicializar(GLFWwindow* window) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 430");
        fileDialog.SetTitle("Seleccionar modelo 3D"); // Título de la ventanita
        fileDialog.SetTypeFilters({ ".obj", ".OBJ" });
    }

    void gui::render() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);
        if (ImGui::Begin("Mensajes")) {
            ImGui::Text("%s", Renderer::getInstancia().getRendererInfo().c_str());
            ImGui::Text("%s", Renderer::getInstancia().getVendorInfo().c_str());
            ImGui::Text("%s", Renderer::getInstancia().getVersionInfo().c_str());
            ImGui::Text("%s", Renderer::getInstancia().getShadingLanguageVersionInfo().c_str());

            ImGui::BeginChild("Scroll mensajes", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
            for (const auto& msg : mensajes) {
                ImGui::TextUnformatted(msg.c_str());
            }

            if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
                ImGui::SetScrollHereY(1.0f);
            }
            ImGui::EndChild();
        }
        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(350, 10), ImGuiCond_Once);
        if (ImGui::Begin("Fondo")) {
            static float color[4] = { 0.6f, 0.6f, 0.6f, 0.6f };
            ImGuiColorEditFlags flags = ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_AlphaBar;
            if (ImGui::ColorPicker4("Color para el fondo", color, flags)) {
                Renderer::getInstancia().ClearColor(color[0], color[1], color[2], color[3]);
            }
        }
        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(10, 200), ImGuiCond_Once);
        if (ImGui::Begin("Shader Program")) {
            ImGui::InputText("##", nombreShader, sizeof(nombreShader), ImGuiInputTextFlags_AutoSelectAll);

            if (ImGui::Button("Load")) {
                std::string error = "";
                std::string nombreStr(nombreShader);

                bool exito = ShaderProgram::getInstancia().creaShaderProgram(nombreStr, error);

                if (exito) {
                    addMensaje("ÉXITO: Shaders '" + nombreStr + "' compilados y enlazados.");
                } else {
                    addMensaje("ERROR: Fallo al cargar '" + nombreStr + "':\n" + error);
                }
            }
        }
        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(350, 250), ImGuiCond_Once);
        if (ImGui::Begin("Camera")) {
            ImGui::Checkbox("Activar controles de camara", &camaraActiva);

            if (camaraActiva) {
                const char* items[] = { "Zoom", "Pan", "Tilt", "Dolly", "Crane", "Orbit" };
                int current_item = static_cast<int>(movimientoActual);

                if (ImGui::Combo("Movimiento", &current_item, items, IM_ARRAYSIZE(items))) {
                    movimientoActual = static_cast<TipoMovimientoCamara>(current_item);
                }

                if (movimientoActual == TipoMovimientoCamara::ZOOM) {
                    static float anguloZoom = 45.0f;
                    if (ImGui::SliderFloat("Angulo", &anguloZoom, 1.0f, 179.0f)) {
                        Camara::getInstancia().aplicarZoom(glm::radians(anguloZoom));
                    }
                } else if (movimientoActual == TipoMovimientoCamara::PAN) {
                    if (ImGui::Button("izq")) { Camara::getInstancia().aplicarPan(0.05f); }
                    ImGui::SameLine();
                    if (ImGui::Button("der")) { Camara::getInstancia().aplicarPan(-0.05f); }
                } else if (movimientoActual == TipoMovimientoCamara::TILT) {
                    if (ImGui::Button("arriba")) { Camara::getInstancia().aplicarTilt(0.05f); }
                    ImGui::SameLine();
                    if (ImGui::Button("abajo")) { Camara::getInstancia().aplicarTilt(-0.05f); }
                } else if (movimientoActual == TipoMovimientoCamara::DOLLY) {
                    if (ImGui::Button("atrás")) { Camara::getInstancia().aplicarDolly(0.1f, 0.0); }
                    if (ImGui::Button("izq")) { Camara::getInstancia().aplicarDolly(0.0f, 0.1f); }
                    ImGui::SameLine();
                    if (ImGui::Button("derecha")) { Camara::getInstancia().aplicarDolly(0.0f, -0.1f); }
                    if (ImGui::Button("frente")) { Camara::getInstancia().aplicarDolly(-0.1f, 0.0f); }
                } else if (movimientoActual == TipoMovimientoCamara::CRANE) {
                    if (ImGui::Button("arriba")) { Camara::getInstancia().aplicarCrane(0.1f); }
                    if (ImGui::Button("abajo")) { Camara::getInstancia().aplicarCrane(-0.1f); }
                } else if (movimientoActual == TipoMovimientoCamara::ORBIT) {
                    ImGui::Text("Latitud");
                    if (ImGui::Button("norte")) { Camara::getInstancia().aplicarOrbit(0.05f, 0.0f); }
                    ImGui::SameLine();
                    if (ImGui::Button("sur")) { Camara::getInstancia().aplicarOrbit(-0.05f, 0.0f); }
                    ImGui::Text("Longitud");
                    if (ImGui::Button("oeste")) { Camara::getInstancia().aplicarOrbit(0.0f, 0.05f); }
                    ImGui::SameLine();
                    if (ImGui::Button("este")) { Camara::getInstancia().aplicarOrbit(0.0f, -0.05f); }
                }
            }
        }
        ImGui::End();
        //ventana para buscar modelos obj
        ImGui::SetNextWindowPos(ImVec2(10, 400), ImGuiCond_Once);
        if (ImGui::Begin("modelos")) {

            if (ImGui::Button("cargar modelo")) {
                fileDialog.Open();
            }

            fileDialog.Display();

            if (fileDialog.HasSelected()) {
                static std::mt19937 gen(std::random_device{}());
                std::uniform_real_distribution<float> dist(-1.5f, 1.5f);

                std::string ruta = fileDialog.GetSelected().string();

                try {
                    PAG::Model* nuevoModelo = new PAG::Model(ruta, "modelo");
                    float posX = dist(gen);
                    float posZ = dist(gen);

                    nuevoModelo->setPosition(glm::vec3(posX, 0.0f, posZ));
                    PAG::Renderer::getInstancia().addModelo(nuevoModelo);

                    addMensaje(" Modelo cargado desde " + ruta);
                } catch (const std::exception& e) {
                    addMensaje("ERROR al cargar modelo: " + std::string(e.what()));
                }


                fileDialog.ClearSelected();
            }

            ImGui::Separator();

            ImGui::Text("Modelos:");
            auto& modelos = PAG::Renderer::getInstancia().getModelos();

            if (modelos.empty()) {
                ImGui::Text("no hay modelos");
            } else {
                for (size_t i = 0; i < modelos.size(); ++i) {

                        ImGui::PushID(static_cast<int>(i));

                        ImGui::BulletText("Modelo %zu: %s", i, modelos[i]->getName().c_str());
                        ImGui::SameLine();

                        if (ImGui::Button("Eliminar")) {
                            PAG::Renderer::getInstancia().removeModelo(i);
                            ImGui::PopID();
                            break;
                        }

                        ImGui::PopID();

                }
            }
        }
        ImGui::End();

ImGui::SetNextWindowPos(ImVec2(350, 400), ImGuiCond_Once);
if (ImGui::Begin("Transformaciones")) {

    auto& modelos = PAG::Renderer::getInstancia().getModelos();

    if (modelos.empty()) {
        ImGui::Text("elige un modelo para modificar");
    } else {

        static int modeloSeleccionado = 0;


        if (modeloSeleccionado >= static_cast<int>(modelos.size())) {
            modeloSeleccionado = static_cast<int>(modelos.size()) - 1;
        }
        std::vector<std::string> nombresModelos;
        std::vector<const char*> itemsCombo;
        for (size_t i = 0; i < modelos.size(); ++i) {
            nombresModelos.push_back("Modelo " + std::to_string(i) + ": " + modelos[i]->getName());
        }
        for (const auto& nombre : nombresModelos) {
            itemsCombo.push_back(nombre.c_str());
        }


        ImGui::Combo("Modelo activo", &modeloSeleccionado, itemsCombo.data(), static_cast<int>(itemsCombo.size()));

        ImGui::Separator();

        PAG::Model* modeloActivo = modelos[modeloSeleccionado];

        //trasladar
        ImGui::Text("Traslacion:");
        ImGui::DragFloat3("##Pos", &modeloActivo->getPosition().x, 0.05f);

        //rotar
        ImGui::Text("Rotacion:");
        ImGui::SliderFloat3("##Rot", &modeloActivo->getRotation().x, -180.0f, 180.0f);

        //escalado
        ImGui::Text("Escala:");
        ImGui::DragFloat3("##Esc", &modeloActivo->getScale().x, 0.01f, 0.01f, 10.0f);

        ImGui::Separator();



    }
}
ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }



    void gui::finalizar() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

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