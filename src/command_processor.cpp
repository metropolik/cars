#include "command_processor.h"
#include "depth_first_search.h"
#include "dijkstra.h"

Command_Processor::Command_Processor() : graph(nullptr), is_input_loop_running(true) {
    cmd_map.insert(std::make_pair("GRAPH", &Command_Processor::cmd_create_graph));
    cmd_map.insert(std::make_pair("DIST", &Command_Processor::cmd_length_of_path));
    cmd_map.insert(std::make_pair("TRIP_MAX_STOPS", &Command_Processor::cmd_number_of_paths_with_stops_smaller_than));
    cmd_map.insert(std::make_pair("TRIP_EQUAL_STOPS", &Command_Processor::cmd_number_of_paths_with_stops_equal_to));
    cmd_map.insert(std::make_pair("TRIP_MAX_DIST", &Command_Processor::cmd_number_of_paths_with_distance_smaller_than));
    cmd_map.insert(std::make_pair("SHORT", &Command_Processor::cmd_length_shortest_path));

    cmd_map.insert(std::make_pair("QUIT", &Command_Processor::cmd_stop_input_loop));
}

Command_Processor::~Command_Processor() {
    if (graph) {
        delete graph;
    }
}
        
void Command_Processor::enter_input_loop() {
    // maybe the quit command was already called before the enter_input_loop
    if (is_input_loop_running) {
        std::cout << "Interactive mode: " << std::endl;
        std::cout << "Possible Commands: GRAPH <Node List in the format \"AB1, BA2\">" << std::endl;
        std::cout << "\t\t   DIST <List of nodes in the format \"A-B-C\">" << std::endl;
        std::cout << "\t\t   TRIP_MAX_STOPS <START_NODE> <END_NODE> <MAX_STOPS>" << std::endl;
        std::cout << "\t\t   TRIP_EQUAL_STOPS <START_NODE> <END_NODE> <MAX_STOPS>" << std::endl;
        std::cout << "\t\t   TRIP_MAX_DIST <START_NODE> <END_NODE> <MAX_DIST>" << std::endl;
        std::cout << "\t\t   SHORT <START_NODE> <END_NODE>" << std::endl;
        std::cout << "\t\t   QUIT" << std::endl;
    }

    while(is_input_loop_running) {
        std::string raw_cmd;
        std::cout << "> ";
        std::getline(std::cin, raw_cmd);
        parse_line(raw_cmd);
    }
    std::cout << "Goodbye!" << std::endl;
}

void Command_Processor::process_batch_commands(std::vector<std::string>& lines) {
    for (auto line : lines) {
        // skip empty lines
        if (line.length() > 0) {
            parse_line(line);
        }
    }
}

void Command_Processor::parse_line(std::string line) {
    // find first space in line
    size_t space_pos = line.find(' ', 0);

    // extract cmd and arguments for cmd from line
    std::string cmd_text = line.substr(0, space_pos);
    std::string argument_text = (space_pos != std::string::npos) ? line.substr(space_pos+1, line.length() - 1) : std::string("");

    std::cout << "cmd: \"" << cmd_text << "\" args: \"" << argument_text << "\"" << std::endl;

    // search for cmd in cmd_map
    auto cmd = cmd_map.find(cmd_text);
    if (cmd == cmd_map.end()) {
        std::cout << "ERROR: Command \"" << cmd_text << "\" unkown! Skipping." << std::endl;
        return;
    }

    // call cmd with arguments
    try {
        (this->*(cmd->second))(argument_text);
    } catch (std::logic_error e) {
        std::cout << "ERROR when processing command: \""
            << line << "\"! " << e.what() << std::endl;
    }
}

bool Command_Processor::check_for_graph() {
    if (graph == nullptr) {
        std::cout << "ERROR: Cannot execute command until graph exists!" << std::endl;
        return false;
    }
    return true;
}


/*/////////////////////////////////////////////////
    This section contains the individual commands
*//////////////////////////////////////////////////

void Command_Processor::cmd_create_graph(std::string argument_text) {
    if (graph) { delete graph; }

    graph = new Directed_Graph(argument_text);
}

void Command_Processor::cmd_length_of_path(std::string argument_text) {
    if (!check_for_graph()) { throw std::domain_error("No graph set!"); }
    std::vector<std::string> args = split_string_by(argument_text, std::string("-"));
    try {
        std::cout << graph->get_route_dist(args) << std::endl;
    } catch (std::domain_error e) {
        // this specifically triggers if an edge on the route does not exist
        // if a node itself does not exist a std::invalid_argument is thrown
        std::cout << "NO SUCH ROUTE" << std::endl;
    }
}

void Command_Processor::cmd_length_shortest_path(std::string argument_text) {
    if (!check_for_graph()) { throw std::domain_error("No graph set!"); }
    std::vector<std::string> args = split_string_by_space(argument_text);
    if (args.size() != 2) {
        throw std::invalid_argument("The number of arguments is not two!");
    }
    Dijkstra dij(graph);
    try {
        std::cout << dij.get_length_of_shortest_path(args[0], args[1]) << std::endl;
    } catch (std::domain_error e) {
        std::cout << "NO SUCH ROUTE" << std::endl;
    }
}

void Command_Processor::cmd_number_of_paths_with_distance_smaller_than(std::string argument_text) {
    if (!check_for_graph()) { throw std::domain_error("No graph set!"); }
    std::vector<std::string> args = split_string_by_space(argument_text);
    if (args.size() != 3) {
        throw std::invalid_argument("The number of arguments is not three!");
    }
    int max_dist = std::stoi(args[2]);
    if (max_dist < 1) {
        throw std::invalid_argument("Max dist must be at least 1!");
    }
    Depth_First_Search dfs(graph);
    std::cout << dfs.get_num_paths_by_max_dist(args[0], args[1], max_dist) << std::endl;
}

void Command_Processor::cmd_number_of_paths_with_stops_smaller_than(std::string argument_text) {
    if (!check_for_graph()) { throw std::domain_error("No graph set!"); }
    std::vector<std::string> args = split_string_by_space(argument_text);
    if (args.size() != 3) {
        throw std::invalid_argument("The number of arguments is not three!");
    }
    int max_stops = std::stoi(args[2]);
    if (max_stops < 1) {
        throw std::invalid_argument("Max stops must be at least 1!");
    }
    Depth_First_Search dfs(graph);
    std::cout << dfs.get_num_paths_by_max_stops(args[0], args[1], (unsigned int)max_stops) << std::endl;
}

void Command_Processor::cmd_number_of_paths_with_stops_equal_to(std::string argument_text) {
    if (!check_for_graph()) { throw std::domain_error("No graph set!"); }
    std::vector<std::string> args = split_string_by_space(argument_text);
    if (args.size() != 3) {
        throw std::invalid_argument("The number of arguments is not three!");
    }
    int max_stops = std::stoi(args[2]);
    if (max_stops < 1) {
        throw std::invalid_argument("Max stops must be at least 1!");
    }
    Depth_First_Search dfs(graph);
    std::cout << dfs.get_num_paths_by_equal_stops(args[0], args[1], (unsigned int)max_stops) << std::endl;
}

void Command_Processor::cmd_stop_input_loop(std::string argument_text) {
    is_input_loop_running = false;
}
