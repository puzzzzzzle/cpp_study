//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include <boost/program_options.hpp>
#include <iostream>
#include <iterator>

using namespace std;

TEST(test_test, 1)
{
    EXPECT_EQ(1, 1);
}
// A helper function to simplify the main part.
template<class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    copy(v.begin(), v.end(), ostream_iterator<T>(os, " "));
    return os;
}
int main(int argc, char **argv)
{
    int iRet = 0;
//    iRet = beforeRun();
//    if(iRet){
//        std::cerr<<"init fail with "<<iRet<<std::endl;
//    }
//    testing::InitGoogleTest(&argc,argv);
//    iRet = RUN_ALL_TESTS();
    namespace po = boost::program_options;
    try
    {

        po::options_description desc("Allowed options");
        desc.add_options()
                ("help,h", "produce help message")
                ("int,i", po::value<int>()->default_value(1), "int value")
                ("double,d", po::value<double>()->default_value(2.2), "double value")
                ("float,f", po::value<float>()->default_value(3.3), "float value")
                ("string,s", po::value<string>()->default_value("str"), "string value")
                // -v str1 -v str2 -v str3 ...
                ("vector,v", po::value<vector<string>>()->composing(), "vector value");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help"))
        {
            cout << desc << "\n";
            return 0;
        }

        if (vm.count("int"))
        {
            cout << "int was set to "
                 << vm["int"].as<int>() << ".\n";
        } else
        {
            cout << "int was not set.\n";
        }

        if (vm.count("double"))
        {
            cout << "double was set to "
                 << vm["double"].as<double>() << ".\n";
        } else
        {
            cout << "double was not set.\n";
        }

        if (vm.count("float"))
        {
            cout << "float was set to "
                 << vm["float"].as<float>() << ".\n";
        } else
        {
            cout << "float was not set.\n";
        }

        if (vm.count("string"))
        {
            cout << "string was set to "
                 << vm["string"].as<string>() << ".\n";
        } else
        {
            cout << "string was not set.\n";
        }

        if (vm.count("vector"))
        {
//            auto v = vm["vector"].as<vector<string>>();
//            cout << "str vector :[";
//            for (auto &it : v)
//            {
//                cout << it << ",";
//            }
//            cout << "]";
            cout << "vector string are: "
                 << vm["vector"].as< vector<string> >() << "\n";
        } else
        {
            cout << "vector was not set.\n";
        }

    }
    catch (exception &e)
    {
        cerr << "error: " << e.what() << "\n";
        iRet = 1;
    }
    catch (...)
    {
        cerr << "Exception of unknown type!\n";
    }

    return iRet;
}