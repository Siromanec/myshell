//
// Created by ADMIN on 11-Oct-23.
//
#include <unistd.h>
#include <sys/wait.h>

#include "ExternalCommand.hpp"
#include "AbstractRunner.hpp"


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
        if (WIFEXITED(status)) {
            AbstractRunner::merrno = WEXITSTATUS(status);
        }
#ifdef DEBUG
        std::cout << "Parent: child stopped, exit code: " << status << std::endl;
#endif
    }
    else{
        // We are the child
        execvp(getArgv()[0], const_cast<char* const*>(getArgv()));

        std::cerr << "Parent: Failed to execute " << getArgv()[0] << " \n\tCode: " << errno << std::endl;
        exit(EXIT_FAILURE);   // exec never returns
    }

}
