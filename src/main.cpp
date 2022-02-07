#include "command_processor.h"
#include <fstream>
#include <iostream>
#include <sstream>

void process_file(Command_Processor& cp, std::string file_path) {
    std::ifstream test_file(file_path);
    if (!test_file.good()) {
        std::cout << "Provided argument is not a file!" << std::endl;
        return;
    }

    // read file
    std::vector<std::string> lines;
    std::string tmp;
    while (std::getline(test_file, tmp)) {
        lines.push_back(tmp);
    }

    // process individual commands
    cp.process_batch_commands(lines);
}

int main (int argc, char* argv[]) {
    Command_Processor cp;

    if (argc > 1) {
        // check if the second argument is a file that exists
        // if so treat its content as commands
        process_file(cp, std::string(argv[1]));
    }
    cp.enter_input_loop();
}