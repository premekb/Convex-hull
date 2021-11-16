#ifndef SEMESTRALKA_COMMANDS_HPP
#define SEMESTRALKA_COMMANDS_HPP

#include <string>

struct help_command{
    help_command() = default;
};

struct random_command{
    random_command(int &pointsAmount) : points_amount(pointsAmount) {}

    int points_amount;
};

struct svg_command{
    svg_command(std::string &destination) : destination(destination) {}

    std::string destination;
};

struct output_command{
    output_command(std::string &destination) : destination(destination) {}

    std::string destination;
};

struct input_command{
    input_command(std::string &destination) : destination(destination) {}

    std::string destination;
};

#endif //SEMESTRALKA_COMMANDS_HPP
