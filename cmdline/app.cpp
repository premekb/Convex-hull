#include <vector>
#include "config.hpp"

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
    validate_cfg(cfg);

    if (cfg.help) print_help();

    std::vector<point> points = get_points(cfg);

    std::vector<point> result = start_quickhull(cfg, points);

    print_result(cfg, points, result);
}

std::vector<point> get_points(const config& cfg){
    if (cfg.random){
        points_generator gen(cfg.random_amount, 10000);
        return *gen.get_points();
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
    std::string::const_iterator it = line.begin();
    while (it != line.end() && (std::isdigit(*it) || *it == ',')){
        ++it;
        if (*it == ','){
            coma_counter++;
        }
        if (coma_counter == 1 && std::isdigit(*it)) number_after_coma = true;
        if (coma_counter == 0 && std::isdigit(*it)) number_before_coma = true;
    }
    if (!(!line.empty() && it == line.end() && coma_counter == 1 && number_after_coma && number_before_coma)) {
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
    convex_hull_solver solver = convex_hull_solver(&points);
    std::vector<point> result = solver.quickhull();
    return result;
}

config parse_commands(std::vector<std::string>& commands){
    config cfg;

    for (const std::string& command_with_option : commands){
        auto args = split(command_with_option, ':');
        auto cmd = args.at(0);
        if (cmd == "--help") cfg.help = true;
        else if (cmd == "--multithreaded") {
            cfg.multithreaded = true;
            try{
                cfg.random_amount = std::stoi(args.at(1));
                if (cfg.random_amount <= 0) throw std::invalid_argument("Invalid amount of threads..");
            }
            catch(...){
                throw std::invalid_argument("Invalid --mutlithreaded argument. Run program with --help for more info.");
            }
        }
        else if (cmd == "--random") {
            cfg.random = true;
            try{
                cfg.random_amount = std::stoi(args.at(1));
                if (cfg.random_amount < 0) throw std::invalid_argument("Amoount of points to be generated randomly cannot be negative.");
            }
            catch(...){
                throw std::invalid_argument("Invalid --random argument. Run program with --help for more info.");
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