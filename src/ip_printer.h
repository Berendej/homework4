#include <iostream>
#include <type_traits>
#include <cstdint>
using std::cout;

/*
    print_ip( int8_t{-1} ); // 255
    print_ip( int16_t{0} ); // 0.0
    print_ip( int32_t{2130706433} ); // 127.0.0.1
    print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
    print_ip( std::string{“Hello, World!”} ); // Hello, World!
    print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
    print_ip( std::list<shot>{400, 300, 200, 100} ); // 400.300.200.100
    print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0
*/

/**
 * \brief Determine big/little platform endianess.
 *
 * Endians constexpr'es big/little help to choose iteration direction
 * while scanning integral types byte by byte.
 */
class Endian
{
private:
    static constexpr uint32_t uint32_ = 0x01020304;
    static constexpr uint8_t magic_ = (const uint8_t&)uint32_;
public:
    static constexpr bool little = magic_ == 0x04;
    static constexpr bool big = magic_ == 0x01;
};

/*
1. Адрес может быть представлен в виде произвольного целочисленного типа. Выводить
побайтово в беззнаковом виде, начиная со старшего байта, с символом `.` (символ точки) в качестве разделителя. Выводятся все байты числа.
*/

/**
 * \brief Print integral types such as int64_t int32_t and so on
 * 
 * Uses helper union aux_uni which allows detecting offset of highest/lowest byte.
 * Depending on platform big/little endianess iterates union's bytes upward from
 * [0] to [last] (big endian) or downward from [last] to [0] (little endian)
 * Uses SFINAE. It's a special case for all integral types
 * 
 * \param i - rvalue reference to integral value
 */
template<typename T, typename std::enable_if< std::is_integral<T>::value >::type* = nullptr>
void print_ip(T&& i)
{
    constexpr auto sz = sizeof(T);
    constexpr auto last_ix = sz - 1;
    union aux_uni
    {
        std::uint8_t arr[sizeof(T)];
        T             v;
        aux_uni(T _v) : v(_v) {}
    };
    aux_uni aux{i};
    if ( Endian::big )
    { // big endian architectures
        for( int ix = 0 ; ix < last_ix; ix++ )
        {
            cout << (unsigned int)aux.arr[ix] << ((last_ix == ix)? "\n" : ".");
        }
    }
    else
    {  // little endian x86 etc
        for( int ix = last_ix; ix >= 0; ix-- )
        {
            cout << (unsigned int)aux.arr[ix] << ((0 == ix)? "\n" : ".");
        }
    }
}

/*
2. Адрес может быть представлен в виде строки. Выводится как есть, вне зависимости от
содержимого.
*/

/**
 * \brief Print std::string (special case) as is
 * 
 * Special case for std::string. Not a template function.
 * 
 * \param s The string rvalue reference.
 */
void print_ip(std::string&& s)
{
    cout << s << std::endl;
}


/*
3. Адрес может быть представлен в виде контейнеров `std::list`, `std::vector`.
Выводится полное содержимое контейнера поэлементно и разделяется `.` (символом
точка). Элементы выводятся как есть.
*/

/**
 * \brief Output to std::cout containers content each item separated with dot symbol
 * 
 * Uses SFINAE. In fact it's not a special case for CONTAINERS, rather it's intended for everything
 * else but integral types and std::string. 
 * 
 * \param cont rvalue reference to  containter
 */
template<typename T, typename std::enable_if< !std::is_integral<T>::value >::type* = nullptr>
void print_ip(T&& cont)
{
    typename T::iterator it = cont.begin();
    while( it != cont.end())
    {
        cout << *it++ << ((it != cont.end()) ? "." : "\n");
    }
}
