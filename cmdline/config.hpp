#ifndef SEMESTRALKA_CONFIG_HPP
#define SEMESTRALKA_CONFIG_HPP

struct config {
    bool help;

    bool svg;
    std::string svg_destination;

    bool random;
    int random_amount;

    bool multithreaded;
    int threads;

    enum class IO {
        CONSOLE, FILE
    };

    IO input;
    std::string input_destination;

    IO output;
    std::string output_destination;

    config(){
        help = false;
        svg = false;
        random = false;
        multithreaded = false;
        input = IO::CONSOLE;
        output = IO::CONSOLE;
    }
};

#endif //SEMESTRALKA_CONFIG_HPP
