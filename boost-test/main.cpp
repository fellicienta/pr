#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iostream>
#include <iterator>

int main(int ac, char* av[])
{
    try {

        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "Produce help message")
            ("add", po::value<int32_t>(), "Add values")
            ("sub", po::value<int32_t>(), "Subtract values")
            ("mul", po::value<int32_t>(), "Multiply values")
            ("div", po::value<int32_t>(), "Divide values")
        ;

        po::variables_map vm;        
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);    

        if (vm.count("help")) {
            std::cout << desc << "\n";
            return 0;
        }

        if (vm.count("add") && ac == 4) {
            std::cout << atoi(av[2]) + atoi(av[3]) << ".\n";
        }
        else if (vm.count("sub") && ac == 4) {
            std::cout << atoi(av[2]) - atoi(av[3]) << ".\n";
        } 
        else if (vm.count("mul") && ac == 4) {
            std::cout << atoi(av[2]) * atoi(av[3]) << ".\n";
        }
        else if (vm.count("div")&& ac == 4) {
            std::cout << atof(av[2]) / atof(av[3]) << ".\n";
        } 
        else {
            std::cout << "Error: no option is entered or the required argument is missing.\n";
        }
    }
    catch(std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    catch(...) {
        std::cerr << "Exception of unknown type!\n";
    }

    return 0;
}