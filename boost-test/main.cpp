#include <boost/program_options.hpp>
#include <iostream>
namespace po = boost::program_options;

int main(int ac, char *av[])
{
    try
    {
        po::options_description generic("Generic options");
        generic.add_options()("help", "produce help message")("add", "Add values")(
            "sub", "Subtract values")("mul", "Multiply values")("div", "Divide values");

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
            std::cout << generic << "\n";
            return 0;
        }

        if (vm.count("values"))
        {
            std::vector<int32_t> args(vm["values"].as<std::vector<int32_t>>());
            bool operation = false;
            if (vm.count("add"))
            {
                std::cout << "Add: " << args[0] + args[1] << std::endl;
                operation = true;
            }
            if (vm.count("sub"))
            {
                std::cout << "Sub: " << args[0] - args[1] << std::endl;
                operation = true;
            }
            if (vm.count("mul"))
            {
                std::cout << "Mul: " << args[0] * args[1] << std::endl;
                operation = true;
            }
            if (vm.count("div"))
            {
                std::cout << "Div: " << args[0] / args[1] << std::endl;
                operation = true;
            }

            if (!operation)
            {
                std::cout << "Error: no operation is entered." << std::endl;
            }
        }
        else
        {
            std::cout << "Error: the required arguments are missing." << std::endl;
        }
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}