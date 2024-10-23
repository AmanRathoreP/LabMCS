#include "settings.hpp"

bool settings::app::show_window = false;
float settings::app::font_weight = 19.0f;

void settings::app::save_settings()
{
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("font_weight", settings::app::font_weight, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);


    std::ofstream ofs(APP_SETTINGS_FILE_NAME_AND_PATH);
    if (ofs.is_open())
    {
        ofs << buffer.GetString();
        ofs.close();
    }
}

void settings::app::setup(void)
{
    std::ifstream ifs(APP_SETTINGS_FILE_NAME_AND_PATH);
    if (ifs.is_open())
    {
        // Load the file into a string
        std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
        ifs.close();

        // Parse the JSON data
        rapidjson::Document doc;
        if (doc.Parse(content.c_str()).HasParseError() == false)
        {
            if (doc.HasMember("font_weight") && doc["font_weight"].IsFloat())
            {
                settings::app::font_weight = doc["font_weight"].GetFloat();
            }
        }
    }
}

void settings::app::loop(void)
{
    if (settings::app::show_window)
    {
        ImGui::Begin("Application Settings", &settings::app::show_window);
        ImGui::SliderFloat("Font Size", &settings::app::font_weight, 10.0f, 35.0f, "%.1f");

        // Optionally save the settings after modifying
        if (ImGui::Button("Save Settings"))
        {
            save_settings();
        }

        ImGui::End();
    }
}
