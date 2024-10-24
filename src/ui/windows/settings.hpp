#pragma once

#include <iostream>
#include <imgui.h>
#include <fstream>
#include <vector>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#define APP_SETTINGS_FILE_NAME_AND_PATH "app_settings.json"

namespace settings
{
    namespace app
    {
        extern bool show_window;
        extern float font_weight;

        void setup(void);
        void loop(void);
        void save_settings(void);
    }

    namespace communication
    {
        extern bool show_window;
        void loop(void);
    }

    namespace io
    {
        extern bool show_window;

        enum value_types
        {
            BOOL,
            INT,
            FLOAT
        };

        static const char *value_type_names[] = {"BOOL", "INT", "FLOAT"};

        struct io_component
        {
            char name[32];
            char id[32];
            value_types value_type;
            ImVec4 color;
        };

        extern std::vector<io_component> input_components;
        extern std::vector<io_component> output_components;

        void loop(void);
    }
}
