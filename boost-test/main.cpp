#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iostream>
#include <iterator>

int main(int ac, char* av[])
{
    try {
        std::vector<std::string> v;
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "Produce help message")
            ("add", po::value< std::vector<std::string> >(), "Add values")
            ("sub", po::value< std::vector<std::string> >(), "Subtract values")
            ("mul", po::value< std::vector<std::string> >(), "Multiply values")
            ("div", po::value< std::vector<std::string> >(), "Divide values")
        ;

        po::variables_map vm;        
        po::store(po::command_line_parser(ac, av).options(desc).
                    allow_unregistered().run(), vm);
        po::notify(vm);    

        if (vm.count("help")) {
            std::cout << desc << "\n";
            return 0;
        }

        if (vm.count("add") && ac == 4) {
            std::cout << "Add: " << atoi(av[2]) + atoi(av[3]) << ".\n";
        }
        if (vm.count("sub") && ac == 4) {
            std::cout << "Sub: " << atoi(av[2]) - atoi(av[3]) << ".\n";
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