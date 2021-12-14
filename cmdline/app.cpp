#include <vector>
#include <chrono>
#include <thread>
#include "config.hpp"
#include "../quickhull_parallel_future/convex_hull_solver_parallel_future.hpp"

void start_app(std::vector<std::string>& commands);
config parse_commands(std::vector<std::string>& commands);
std::vector<std::string> split(std::string const &line, char delim);
void print_help();
std::vector<point> start_quickhull(const config& cfg, std::vector<point>& points);
std::vector<point> get_points(const config& cfg);
void print_result(const config& cfg, const std::vector<point>& points, const std::vector<point>& result);
void print_points(std::ostream& out, const std::vector<point>& points, const std::vector<point>& result);
void validate_cfg(config& cfg);
void validate_line(std::string& line);
std::vector<point> start_quickhull_comparison(const config& cfg, std::vector<point>& points);

template <typename TimePoint>
std::chrono::milliseconds to_ms(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}

void validate_cfg(config& cfg){
    if (cfg.random && cfg.input_file){
        throw std::logic_error("Cannot generate random points and read from file at the same time.");
    }

    if (!cfg.random && !cfg.input_file){
        throw std::logic_error("You need to specify either the --random cmd option, or the --input cmd option.");
    }
}

void start_app(std::vector<std::string>& commands){
    config cfg = parse_commands(commands);
    std::vector<point> result;
    validate_cfg(cfg);

    //if (cfg.help) print_help();

    std::vector<point> points = get_points(cfg);

    if (cfg.comparison_mode){
         result = start_quickhull_comparison(cfg, points);
    }

    else{
        result = start_quickhull(cfg, points);
        print_result(cfg, points, result);
    }
}

std::vector<point> get_points(const config& cfg){
    if (cfg.random){
        points_generator gen(cfg.random_amount, 10000);
        return gen.get_points();
    }

    else if (cfg.input_file){
        std::fstream input_file(cfg.input_filename, std::fstream::in);
        if (!input_file.good()){
            throw std::logic_error("Input file does not exist");
        }
        std::string line;
        int x_axis, y_axis;
        std::vector<std::string> split_line;
        std::vector<point> points;

        while (std::getline(input_file, line)){
            validate_line(line);
              split_line = split(line, ',');
              x_axis = std::stoi(split_line.at(0));
              y_axis = std::stoi(split_line.at(1));
              points.push_back(point(x_axis, y_axis));
        }

        return points;
    }
}

void validate_line(std::string& line){
    int coma_counter = 0;
    bool number_after_coma = false;
    bool number_before_coma = false;
    bool contains_forbidden_characters = false;

    for (char ch : line){
        if (ch == ','){
            coma_counter++;
            continue;
        }

        if (ch == ' '){
            continue;
        }

        if (!std::isdigit(ch)) {
            contains_forbidden_characters = true;
            break;
        }

        if (coma_counter == 1 && std::isdigit(ch)) number_after_coma = true;
        if (coma_counter == 0 && std::isdigit(ch)) number_before_coma = true;
    }
    if (coma_counter == 0 || !number_after_coma || !number_before_coma || contains_forbidden_characters){
        throw std::logic_error("Invalid input format. The required format is as follows: \n"
                               "point1.x_axis, point1.y_axis\n"
                               "point2.x_axis, point2.y_axis\n"
                               "...\n");
    }
}

void print_result(const config& cfg, const std::vector<point>& points, const std::vector<point>& result){
    if (cfg.svg){
        std::fstream file(cfg.svg_filename + ".svg", std::fstream::out);
        svg_helper y(&file);
        y.export_to_svg_file(points, result);
    }

    if (cfg.output == config::IO::CONSOLE){
        print_points(std::cout, points, result);
    }

    else if (cfg.output == config::IO::FILE){
        std::fstream file( cfg.output_filename + ".txt", std::fstream::out);
        print_points(file, points, result);
    }
}

void print_points(std::ostream& out, const std::vector<point>& points, const std::vector<point>& result){
    out << "Input points set:" << std::endl;
    for (const point& p : points){
        out << p;
    }
    out << "##################################" << std::endl;
    out << "Convex hull:" << std::endl;
    for (const point& p : result){
        out << p;
    }
}

std::vector<point> start_quickhull(const config& cfg, std::vector<point>& points){
    if (cfg.multithreaded){
        convex_hull_solver_parallel solver = convex_hull_solver_parallel(points, cfg.threads);
        std::vector<point> result = solver.quickhull_parallel();
        return result;
    }

    else{
        convex_hull_solver solver = convex_hull_solver(points);
        std::vector<point> result = solver.quickhull();
        return result;
    }
}

std::vector<point> start_quickhull_comparison(const config& cfg, std::vector<point>& points){
    auto start_single = std::chrono::high_resolution_clock::now();
    convex_hull_solver solver = convex_hull_solver(points);
    std::vector<point> result = solver.quickhull();
    auto end_single = std::chrono::high_resolution_clock::now();
    std::cout << "Single thread: needed " << to_ms(end_single - start_single).count() << " ms to finish.\n";

    auto start_parallel_mutex = std::chrono::high_resolution_clock::now();
    convex_hull_solver_parallel solver_parallel_mutex = convex_hull_solver_parallel(points, cfg.threads);
    std::vector<point> result_parallel_mutex = solver_parallel_mutex.quickhull_parallel();
    auto end_parallel_mutex = std::chrono::high_resolution_clock::now();
    std::cout << "Parallel-mutex version: needed " << to_ms(end_parallel_mutex - start_parallel_mutex).count() << " ms to finish.\n";

    auto start_parallel_future = std::chrono::high_resolution_clock::now();
    convex_hull_solver_parallel_future solver_parallel_future = convex_hull_solver_parallel_future(points, cfg.threads);
    std::vector<point> result_parallel_future = solver_parallel_future.quickhull_parallel();
    auto end_parallel_future = std::chrono::high_resolution_clock::now();
    std::cout << "Parallel-future version: needed " << to_ms(end_parallel_future - start_parallel_future).count() << " ms to finish.\n";

    return result;
}

config parse_commands(std::vector<std::string>& commands){
    config cfg;

    for (const std::string& command_with_option : commands){
        auto args = split(command_with_option, ':');
        auto cmd = args.at(0);
        if (cmd == "--help") {
            cfg.help = true;
            print_help();
        }
        else if (cmd == "--multithreaded") {
            cfg.multithreaded = true;
            cfg.threads = std::thread::hardware_concurrency();
        }
        else if (cmd == "--random") {
            cfg.random = true;
            try{
                cfg.random_amount = std::stoi(args.at(1));
                if (cfg.random_amount < 0) throw std::invalid_argument("");
            }
            catch(...){
                throw std::invalid_argument("Amoount of points to be generated randomly cannot be negative.\n Invalid --random argument. Run program with --help for more info.");
            }
        }
        else if (cmd == "--svg") {
            cfg.svg = true;
            try{
                cfg.svg_filename = args.at(1);
            }
            catch(...){
                throw std::invalid_argument("Invalid --svg argument. Run program with --help for more info.");
            }
        }
        else if (cmd == "--input") {
            cfg.input_file = true;
            try{
                cfg.input_filename = args.at(1);
            }
            catch(...){
                throw std::invalid_argument("Invalid --input argument. Run program with --help for more info.");
            }
        }
        else if (cmd == "--output") {
            cfg.output = config::IO::FILE;
            try{
                cfg.output_filename = args.at(1);
            }
            catch(...){
                throw std::invalid_argument("Invalid --output argument. Run program with --help for more info.");
            }
        }
        else if (cmd == "--comparison") {
            cfg.comparison_mode = true;
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
    std::cout << "Accepts only positive integers" << std::endl << std::endl;

    std::cout << "Available command line options, uppercase letters, that follow after a colon need to be replaced with a value:" << std::endl;
    std::cout << "--help [prints info about command line options]" << std::endl;
    std::cout << "--random:AMOUNT_OF_POINTS [generates random set of points in a 2D plane and finds their convex hull]" << std::endl;
    std::cout << "--svg:FILENAME [visualises the result by exporting it into an svg file]" << std::endl;
    std::cout << "--multithreaded [executes a multithreaded version of quickhull, the version using mutexes is used]" << std::endl;
    std::cout << "--input:FILENAME [reads the set of points from a file instead of a cmd]" << std::endl;
    std::cout << "--output:FILENAME [writes the set of points to a file instead of a cmd]" << std::endl;
    std::cout << "--comparison [runs single threaded and multithreaded version and compares the times]" << std::endl;
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