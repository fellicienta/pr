#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

const std::map<std::string, std::function<int32_t(const int32_t, const int32_t)>> CALCULATOR = {
    {"add", [](int32_t a, int32_t b) { return a + b; }},
    {"sub", [](int32_t a, int32_t b) { return a - b; }},
    {"mul", [](int32_t a, int32_t b) { return a * b; }},
    {"div", [](int32_t a, int32_t b) { return a / b; }}};

const std::map<std::string, std::string> OPERATIONS = {{"add", "Add values"},
                                                       {"sub", "Subtract values"},
                                                       {"mul", "Multiply values"},
                                                       {"div", "Divide values"}};

void print_operation(const std::string operation, const int32_t arg1, const int32_t arg2)
{
    std::cout << operation << ": " << CALCULATOR.at(operation)(arg1, arg2) << std::endl;
}

int main(int ac, char *av[])
{
    try
    {
        po::options_description generic("Generic options");
        generic.add_options()("help", "Produce help message");

        for (auto x : OPERATIONS)
            generic.add_options()(x.first.c_str(), x.second.c_str());

        po::options_description hidden("Hidden options");
        hidden.add_options()("values", po::value<std::vector<int32_t>>(), "values");

        po::options_description cmdline_options;
        cmdline_options.add(generic).add(hidden);

        po::positional_options_description p;
        p.add("values", -1);

        po::variables_map vm;
        store(po::command_line_parser(ac, av).options(cmdline_options).positional(p).run(), vm);
        notify(vm);

        if (vm.count("help"))
        {
            std::cout << generic << std::endl;
            return 0;
        }
        if (!vm.count("values"))
        {
            std::cout << "Error: the required arguments are missing." << std::endl;
            return 1;
        }

        std::vector<int32_t> args(vm["values"].as<std::vector<int32_t>>());
        if (args.size() != 2)
        {
            std::cout << "Error: invalid number of arguments." << std::endl;
            return 1;
        }

        bool option = false; // is any operation entered ?

        for (auto x : OPERATIONS)
        {
            if (vm.count(x.first))
            {
                print_operation(x.first, args[0], args[1]);
                option = true;
            }
        }

        if (!option)
            std::cout << "Error: no option is entered." << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}