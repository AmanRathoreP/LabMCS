#include "settings.hpp"

bool settings::io::show_window = false;

std::vector<settings::io::io_component> settings::io::input_components;
std::vector<settings::io::io_component> settings::io::output_components;

void settings::io::loop(void)
{
    if (settings::io::show_window)
    {
        ImGui::Begin("Input/Output Settings", &settings::io::show_window);

        if (ImGui::BeginTabBar("MyTabBar"))
        {
            if (ImGui::BeginTabItem("Inputs"))
            {
                // Button to add new input components
                if (ImGui::Button("Add Input"))
                {
                    settings::io::io_component new_component;
                    strcpy(new_component.name, "");
                    strcpy(new_component.id, "");
                    new_component.value_type = settings::io::value_types::INT;
                    new_component.color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                    settings::io::input_components.push_back(new_component);
                }

                // Rendering each input component
                for (size_t i = 0; i < settings::io::input_components.size(); ++i)
                {
                    settings::io::io_component &component = settings::io::input_components[i];

                    ImGui::Text("Input Component %zu", i + 1);
                    ImGui::InputText(("Name##Input" + std::to_string(i)).c_str(), component.name, IM_ARRAYSIZE(component.name));
                    ImGui::InputText(("ID##Input" + std::to_string(i)).c_str(), component.id, IM_ARRAYSIZE(component.id));
                    ImGui::Combo(("Value Type##Input" + std::to_string(i)).c_str(), (int *)&component.value_type, settings::io::value_type_names, IM_ARRAYSIZE(settings::io::value_type_names));
                    ImGui::ColorEdit4(("Colour##Input" + std::to_string(i)).c_str(), (float *)&component.color);
                    ImGui::Separator();
                }

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Outputs"))
            {
                // Button to add new output components
                if (ImGui::Button("Add Output"))
                {
                    settings::io::io_component new_component;
                    strcpy(new_component.name, "");
                    strcpy(new_component.id, "");
                    new_component.value_type = settings::io::value_types::INT;
                    new_component.color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                    settings::io::output_components.push_back(new_component);
                }

                // Rendering each output component
                for (size_t i = 0; i < settings::io::output_components.size(); ++i)
                {
                    settings::io::io_component &component = settings::io::output_components[i];
                    ImGui::Text("Output Component %zu", i + 1);
                    ImGui::InputText(("Name##Output" + std::to_string(i)).c_str(), component.name, IM_ARRAYSIZE(component.name));
                    ImGui::InputText(("ID##Output" + std::to_string(i)).c_str(), component.id, IM_ARRAYSIZE(component.id));
                    ImGui::Combo(("Value Type##Output" + std::to_string(i)).c_str(), (int *)&component.value_type, settings::io::value_type_names, IM_ARRAYSIZE(settings::io::value_type_names));
                    ImGui::ColorEdit4(("Colour##Output" + std::to_string(i)).c_str(), (float *)&component.color);
                    ImGui::Separator();
                }

                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }

        ImGui::End();
    }
}
