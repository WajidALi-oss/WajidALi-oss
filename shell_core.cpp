#include "shell_core.h"
#include <sstream>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <fcntl.h>

using namespace std;

vector<string> parse_command(string& input) {
    stringstream ss(input);
    string token;
    vector<std::string> tokens;
    while (ss >> token)
        tokens.push_back(token);
    return tokens;
}
string run_command(const std::string& input) {
    vector<string> args = parse_command(input);
    if (args.empty()) return "";

    if (args[0] == "cd") {
        if (args.size() < 2) return "cd: missing argument\n";
        if (chdir(args[1].c_str()) != 0) return "cd: failed\n";
        return "";
    }

    if (args[0] == "exit") {
        exit(0);
    }

    if (args[0] == "help") {
        return "Built-in commands:\n cd <dir>\n help\n exit\n";
    }

    // Convert args to char* array
    vector<char*> exec_args;
    for (string& arg : args)
        exec_args.push_back(strdup(arg.c_str()));
    exec_args.push_back(nullptr);

    int pipefd[2];
    pipe(pipefd);

    int pid = fork();
    if (pid == 0) {
        close(pipefd[0]); // close read end
        dup2(pipefd[1], STDOUT_FILENO);
        dup2(pipefd[1], STDERR_FILENO);
        execvp(exec_args[0], exec_args.data());
        cout<<"execvp failed";
        exit(1);
    } else {
        close(pipefd[1]); // close write end
        waitpid(pid, nullptr, 0);

        char buffer[1024];
        string output;
        ssize_t n;
        while ((n = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
            output.append(buffer, n);
        }
        close(pipefd[0]);

        for (char* arg : exec_args) free(arg);
        return output;
    }
}

