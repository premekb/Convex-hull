#ifndef SEMESTRALKA_CONFIG_HPP
#define SEMESTRALKA_CONFIG_HPP

struct config {
    bool help;

    bool svg;
    std::string svg_filename;

    bool random;
    int random_amount;

    bool input_file;
    std::string input_filename;

    bool multithreaded;
    int threads;

    bool comparison_mode;

    enum class IO {
        CONSOLE, FILE
    };

    IO output;
    std::string output_filename;

    config(){
        help = false;
        svg = false;
        random = false;
        multithreaded = false;
        input_file = false;
        comparison_mode = false;
        output = IO::CONSOLE;
        threads = 2;
    }
};

#endif //SEMESTRALKA_CONFIG_HPP
