#pragma once
#include <map>
#include <string>
#include <iostream>
#include <functional>
#include <utility>
#include <vector>
#include "directed_graph.h"
#include "utils.h"


class Command_Processor {
    typedef void (Command_Processor::*Cmd_Funcptr)(std::string);

    public:
        Command_Processor();
        ~Command_Processor();
        
        void enter_input_loop();
        void process_batch_commands(std::vector<std::string>& lines);
        void parse_line(std::string line);

        bool check_for_graph();

        // commands
        void cmd_create_graph(std::string argument_text);
        void cmd_length_of_path(std::string argument_text);
        void cmd_length_shortest_path(std::string argument_text);
        void cmd_number_of_paths_with_distance_smaller_than(std::string argument_text);
        void cmd_number_of_paths_with_stops_smaller_than(std::string argument_text);
        void cmd_number_of_paths_with_stops_equal_to(std::string argument_text);

        void cmd_stop_input_loop(std::string argument_text);

    private:


        Directed_Graph* graph;
        std::map<std::string, Cmd_Funcptr> cmd_map;
        bool is_input_loop_running;
};