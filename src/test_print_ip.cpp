#include <vector>
#include <list>
#include <string>
#include <fstream>
#include "ip_printer.h"

#define BOOST_TEST_MODULE homework4 test
#include <boost/test/included/unit_test.hpp>

bool check_line(std::ifstream &ifs,  std::string&& etalon )
{
    std::string line;
    if (!std::getline(ifs, line)) {
        return false;
    }
    if ( line.compare(etalon) != 0 ) {
        return false;
    }
    return true;
}
 
bool test_print_ip()
{
    std::ofstream out("out.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    print_ip( int8_t{-1} ); // 255
    print_ip( int16_t{0} ); // 0.0
    print_ip( int32_t{2130706433} ); // 127.0.0.1
    print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
    print_ip( std::string{"Hello, World!"} ); // Hello, World!
    print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
    print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
    std::cout.rdbuf(coutbuf); //reset to standard output again
    out.close();
    std::ifstream ifs("out.txt");
    if ( ! check_line(ifs, "255")) return false;
    if ( ! check_line(ifs, "0.0") ) return false;
    if ( ! check_line(ifs, "127.0.0.1") ) return false;
    if ( ! check_line(ifs, "123.45.67.89.101.112.131.41") ) return false;
    if ( ! check_line(ifs, "Hello, World!") ) return false;
    if ( ! check_line(ifs, "100.200.300.400")  ) return false;
    if ( ! check_line(ifs,"400.300.200.100")  ) return false;
    ifs.close();
    return true;
}

BOOST_AUTO_TEST_CASE( tst_print_ip )
{
    BOOST_CHECK( test_print_ip() );
}
