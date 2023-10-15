//
// Created by ADMIN on 11-Oct-23.
//

#include "ExternalCommand.hpp"

void ExternalCommand::execute() {
    pid_t parent = getpid();
    pid_t pid = fork();

    if (pid == -1)
    {
        std::cerr << "Failed to fork()" << std::endl;
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        // We are parent process
#ifdef DEBUG
        std::cout << "Parent: Hello from parent" << std::endl;
        std::cout << "Parent: Parent PID: " << parent << ", child PID: " << pid << std::endl;
#endif
        int status;
        waitpid(pid, &status, 0);
#ifdef DEBUG
        std::cout << "Parent: child stopped, exit code: " << status << std::endl;
#endif
    }
    else{
        // We are the child
        std::vector<std::string> args = getArgvAsStrings();
        std::string victim_name(args[0]);
        std::vector<const char*> arg_for_c;
        for(const auto& s: args)
            arg_for_c.push_back(s.c_str());
        arg_for_c.push_back(nullptr);

        execvp(victim_name.c_str(), const_cast<char* const*>(arg_for_c.data()));

        std::cerr << "Parent: Failed to execute " << victim_name << " \n\tCode: " << errno << std::endl;
        exit(EXIT_FAILURE);   // exec never returns
    }

}
