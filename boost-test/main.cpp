#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <fstream>
#include <iostream>
#include <iterator>
using namespace std;

// A helper function to simplify the main part.
template<class T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    copy(v.begin(), v.end(), ostream_iterator<T>(os, " "));
    return os;
}

int main(int ac, char *av[])
{
    try
    {
        po::options_description generic("Generic options");
        generic.add_options()("help", "produce help message");

        po::options_description config("Configuration");
        config.add_options()("values,O", po::value<vector<int>>()->multitoken(), "values");

        po::options_description hidden("Hidden options");
        hidden.add_options()("operation", po::value<vector<string>>(), "operation");

        po::options_description cmdline_options;
        cmdline_options.add(generic).add(hidden).add(config);

        po::options_description visible("Allowed options");
        visible.add(generic).add(config);

        po::positional_options_description p;
        p.add("operation", -1);

        po::variables_map vm;
        store(po::command_line_parser(ac, av).options(cmdline_options).positional(p).run(), vm);
        notify(vm);

        if (vm.count("help"))
        {
            cout << visible << "\n";
            return 0;
        }

        if (vm.count("values"))
        {
            cout << "values: " << vm["values"].as<vector<int>>() << "\n";
        }

        if (vm.count("operation"))
        {
            cout << "operation: " << vm["operation"].as<vector<string>>() << "\n";
        }
    }
    catch (exception &e)
    {
        cout << e.what() << "\n";
        return 1;
    }
    return 0;
}