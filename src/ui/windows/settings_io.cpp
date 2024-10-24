#include "settings.hpp"

bool settings::io::show_window = false;

std::vector<settings::io::io_component> settings::io::input_components;
std::vector<settings::io::io_component> settings::io::output_components;

void settings::io::loop(void)
{
    if (settings::io::show_window)
    {
        ImGui::Begin("Input/Output Settings", &settings::io::show_window);

        // Save IO info button
        if (ImGui::Button("Save IO info"))
            settings::io::save_io_info();

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

// Function to save input/output settings to JSON
void settings::io::save_io_info()
{
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();

    // Saving output components
    rapidjson::Value input_array(rapidjson::kArrayType);
    for (const auto &component : settings::io::input_components)
    {
        rapidjson::Value obj(rapidjson::kObjectType);
        obj.AddMember("name", rapidjson::Value(component.name, allocator), allocator);
        obj.AddMember("id", rapidjson::Value(component.id, allocator), allocator);
        obj.AddMember("value_type", (int)component.value_type, allocator);

        rapidjson::Value color_array(rapidjson::kArrayType);
        color_array.PushBack(component.color.x, allocator);
        color_array.PushBack(component.color.y, allocator);
        color_array.PushBack(component.color.z, allocator);
        color_array.PushBack(component.color.w, allocator);
        obj.AddMember("color", color_array, allocator);

        input_array.PushBack(obj, allocator);
    }
    doc.AddMember("inputs", input_array, allocator);

    // Saving output components
    rapidjson::Value output_array(rapidjson::kArrayType);
    for (const auto &component : settings::io::output_components)
    {
        rapidjson::Value obj(rapidjson::kObjectType);
        obj.AddMember("name", rapidjson::Value(component.name, allocator), allocator);
        obj.AddMember("id", rapidjson::Value(component.id, allocator), allocator);
        obj.AddMember("value_type", (int)component.value_type, allocator);

        rapidjson::Value color_array(rapidjson::kArrayType);
        color_array.PushBack(component.color.x, allocator);
        color_array.PushBack(component.color.y, allocator);
        color_array.PushBack(component.color.z, allocator);
        color_array.PushBack(component.color.w, allocator);
        obj.AddMember("color", color_array, allocator);

        output_array.PushBack(obj, allocator);
    }
    doc.AddMember("outputs", output_array, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    std::ofstream ofs(IO_INFO_FILE_NAME_AND_PATH);
    if (ofs.is_open())
    {
        ofs << buffer.GetString();
        ofs.close();
    }
}

void settings::io::setup()
{
    // Open the IO settings file
    std::ifstream ifs(IO_INFO_FILE_NAME_AND_PATH);
    if (ifs.is_open())
    {
        // Load the file into a string
        std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
        ifs.close();

        // Parse the JSON data
        rapidjson::Document doc;
        if (!doc.Parse(content.c_str()).HasParseError())
        {
            // Read input components
            if (doc.HasMember("inputs") && doc["inputs"].IsArray())
            {
                const rapidjson::Value &inputs = doc["inputs"];
                for (rapidjson::SizeType i = 0; i < inputs.Size(); ++i)
                {
                    const rapidjson::Value &obj = inputs[i];
                    settings::io::io_component new_component;

                    // Read component data
                    if (obj.HasMember("name") && obj["name"].IsString())
                        strcpy(new_component.name, obj["name"].GetString());

                    if (obj.HasMember("id") && obj["id"].IsString())
                        strcpy(new_component.id, obj["id"].GetString());

                    if (obj.HasMember("value_type") && obj["value_type"].IsInt())
                        new_component.value_type = (settings::io::value_types)obj["value_type"].GetInt();

                    if (obj.HasMember("color") && obj["color"].IsArray() && obj["color"].Size() == 4)
                    {
                        const rapidjson::Value &color_array = obj["color"];
                        new_component.color = ImVec4(
                            color_array[0].GetFloat(),
                            color_array[1].GetFloat(),
                            color_array[2].GetFloat(),
                            color_array[3].GetFloat());
                    }

                    // Add the new component to the input components vector
                    settings::io::input_components.push_back(new_component);
                }
            }

            // Read output components
            if (doc.HasMember("outputs") && doc["outputs"].IsArray())
            {
                const rapidjson::Value &outputs = doc["outputs"];
                for (rapidjson::SizeType i = 0; i < outputs.Size(); ++i)
                {
                    const rapidjson::Value &obj = outputs[i];
                    settings::io::io_component new_component;

                    // Read component data
                    if (obj.HasMember("name") && obj["name"].IsString())
                        strcpy(new_component.name, obj["name"].GetString());

                    if (obj.HasMember("id") && obj["id"].IsString())
                        strcpy(new_component.id, obj["id"].GetString());

                    if (obj.HasMember("value_type") && obj["value_type"].IsInt())
                        new_component.value_type = (settings::io::value_types)obj["value_type"].GetInt();

                    if (obj.HasMember("color") && obj["color"].IsArray() && obj["color"].Size() == 4)
                    {
                        const rapidjson::Value &color_array = obj["color"];
                        new_component.color = ImVec4(
                            color_array[0].GetFloat(),
                            color_array[1].GetFloat(),
                            color_array[2].GetFloat(),
                            color_array[3].GetFloat());
                    }

                    // Add the new component to the output components vector
                    settings::io::output_components.push_back(new_component);
                }
            }
        }
    }
}
