#pragma once

#include <iostream>
#include <imgui.h>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#define APP_SETTINGS_FILE_NAME_AND_PATH "app_settings.json"
#define IO_INFO_FILE_NAME_AND_PATH "io_info.json"

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
        extern bool show_error_dialog;
        extern std::string error_message;

        void setup(void);
        void loop(void);
        void save_io_info(void);
        // returns an empty string if the inputs and outputs data satisfy the creteria, else returns all the issues with the components
        std::string check_for_dirty_components(std::vector<settings::io::io_component> components, std::string components_are_of_type);
        inline void set_error(const std::string& message);
    }
}
