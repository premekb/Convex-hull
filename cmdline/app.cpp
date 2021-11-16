#include <vector>
#include "config.hpp"

void start_app(std::vector<std::string>& commands);
config parse_commands(std::vector<std::string>& commands);
std::vector<std::string> split(std::string const &line, char delim);
void print_help();

void start_app(std::vector<std::string>& commands){
    config cfg = parse_commands(commands);
    if (cfg.help) print_help();
}

config parse_commands(std::vector<std::string>& commands){
    config cfg;

    for (const std::string& string_command : commands){
        auto args = split(string_command, ':');
        if (string_command == "--help") cfg.help = true;
        else if (string_command == "--multithreaded") {
            cfg.multithreaded = true;
        }
        else if (string_command == "--random") {
            cfg.random = true;
        }
        else if (string_command == "--svg") {
            cfg.svg = true;
        }
        else if (string_command == "--input") {
            cfg.input = config::IO::FILE;
        }
        else if (string_command == "--output") {
            cfg.input = config::IO::FILE;
        }
        else{
            throw std::logic_error("Unknown command line option passed.");
        }
    }

    return cfg;
}

void print_help(){
    std::cout << "Quickhull semestral project, Premek Bělka" << std::endl;
    std::cout << "--------------------------------------------------------------------------------------" << std::endl;

    std::cout << "The input format for points is: point_x_axis, point_y_axis endline" << std::endl;
    std::cout << "Accepts only positive integers" << std::endl << std::endl; // TODO mozna ne

    std::cout << "Available command line options, uppercase letters, that follow after a colon need to be replaced with a value:" << std::endl;
    std::cout << "--help [prints info about command line options]" << std::endl;
    std::cout << "--random:AMOUNT_OF_POINTS [generates random set of points in a 2D plane and finds their convex hull]" << std::endl;
    std::cout << "--svg:FILENAME [visualises the result by exporting it into an svg file]" << std::endl;
    std::cout << "--multithreaded:AMOUNT_OF_THREADS [executes a multithreaded version of quickhull]" << std::endl;
    std::cout << "--input:FILENAME [reads the set of points from a file instead of a cmd]" << std::endl;
    std::cout << "--output:FILENAME [writes the set of points to a file instead of a cmd]" << std::endl;
}

/**
 * Copied from the Symcalc assignment
 * @param line
 * @param delim
 * @return
 */
std::vector<std::string> split(std::string const &line, char delim) {
    std::vector<std::string> res;
    if (line.empty())
        return res;
    size_t first = 0;
    size_t last;
    while ((last = line.find(delim, first)) != std::string::npos) {
        res.push_back(line.substr(first, last-first));
        first = last+1;
    }
    res.push_back(line.substr(first));
    return res;
}