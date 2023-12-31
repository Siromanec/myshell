// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "internal_commands-POSIX.hpp"
#include "options_parser.h"
#include <iostream>
#include "unistd.h"
#include "ScriptRunner.hpp"
#include "AbstractRunner.hpp"
#include "boost/program_options.hpp"
#include "HistorySaver.hpp"
#include <filesystem>
//TODO main-like implementations of internal commands
namespace po = boost::program_options;

std::tuple<po::variables_map, po::options_description> get_variables_map (int argc, char *argv[]) {
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help,h", "produce help message")
            ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    return std::tuple<po::variables_map, po::options_description>{vm, desc};
}

static bool is_valid_name(std::string name) {
    for(auto s: name) {
        if(!isdigit(s) && !isalpha(s) && s != '_') {
            return false;
        }
    }
    return true;
}

int merrno(int argc, char *argv[]) {
    std::tuple<po::variables_map, po::options_description> info = get_variables_map(argc, argv);
    if (std::get<0>(info).count("help")) {
        std::cout << std::get<1>(info) << "\n";
        return 0;
    }
    if (argc != 1) {
        std::cerr << "merrno: too many arguments" << std::endl;
        AbstractRunner::merrno = -1;
        return -1;
    }
    std::cout << AbstractRunner::merrno << std::endl;
    AbstractRunner::merrno = 0;
    return 0;
}

int mpwd(int argc, char *argv[]) {
    std::tuple<po::variables_map, po::options_description> info = get_variables_map(argc, argv);
    if (std::get<0>(info).count("help")) {
        std::cout << std::get<1>(info) << "\n";
        return 0;
    }
    std::cout << boost::filesystem::current_path() << std::endl;
    return 0;
}

int mcd(int argc, char *argv[]) {
    std::tuple<po::variables_map, po::options_description> info = get_variables_map(argc, argv);
    if (std::get<0>(info).count("help")) {
        std::cout << std::get<1>(info) << "\n";
        return 0;
    }
    if (argc > 2) {
        std::cerr << "mcd: too many arguments" << std::endl;
        return -1;
    }
    try {
        boost::filesystem::current_path(argv[1]);
    }
    catch (std::exception) {
            std::cerr << "mcd: " << argv[1] << ": No such file or directory" << std::endl;
            return - 1;
        }
    return 0;
}

int mexit(int argc, char *argv[]) {
    std::tuple<po::variables_map, po::options_description> info = get_variables_map(argc, argv);
    if (std::get<0>(info).count("help")) {
        std::cout << std::get<1>(info) << "\n";
        return 0;
    }
    if (argc == 1){
        HistorySaver::save();
        exit(EXIT_SUCCESS);
    }
    for(size_t i = 0; i < strlen(argv[1]); ++i) {
        if(!isdigit(argv[1][i])) {
            std::cerr << "mexit: " << argv[1]<< ": numeric argument required" << std::endl;
            AbstractRunner::merrno = -1;
            HistorySaver::save();
            exit(EXIT_FAILURE);
        }
    }
    HistorySaver::save();
    exit(atoi(argv[1]));
}

int mecho(int argc, char *argv[]) {
    std::tuple<po::variables_map, po::options_description> info = get_variables_map(argc, argv);
    if (std::get<0>(info).count("help")) {
        std::cout << std::get<1>(info) << "\n";
        return 0;
    }
    if (argc > 1) {
        for (size_t i = 1; i < argc - 1; ++i) {
            std::cout << argv[i] << " ";
        }
        std::cout << argv[argc - 1] << std::endl;
    }
    else {
        std::cout << std::endl;
    }
    return 0;
}

int mexport(int argc, char *argv[]) {
    std::tuple<po::variables_map, po::options_description> info = get_variables_map(argc, argv);
    if (std::get<0>(info).count("help")) {
        std::cout << std::get<1>(info) << "\n";
        return 0;
    }
    std::string name, value;
    char * token;
    for (size_t i = 1; i < argc; ++i) {
        auto location = strchr(argv[i], '=');
        bool found = location != nullptr;
        if (found && (isalpha(argv[i][0]) || argv[i][0] == '_')) {
            token = strtok(argv[i], "=");
            name = token;
            token = strtok(NULL, "=");
            if (token == NULL) {
                value = " ";
            }
            else {
                value = token;
            }
            if (is_valid_name(name)) {
                setenv(name.data(), value.data(), true);
            }
            else {
                std::cerr << "mexport: '" << name << "': not a valid identifier";
                return -1;
            }
        }
        else {
            std::cerr << "mexport: '" << argv[i] << "': not a valid identifier";
            return -1;
        }
    }
    return 0;
}

int mdot_command(int argc, char *argv[]) {
    ScriptRunner(argc - 1, argv + 1).run();
}

int mdummy_command(int argc, char *argv[]) {
#ifdef DEBUG
  std::cout<<"i did nothing"<<std::endl;
#endif
    return 0;
}

