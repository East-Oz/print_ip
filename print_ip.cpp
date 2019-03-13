#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <stdint.h>
#include <type_traits>
#include <algorithm>

/**
* @brief print_ip - ip-address as std::string
* @param ip - ip-adress is represented as a string
*/
void print_ip( const std::string& ip )
{
	std::cout << ip << std::endl;
}


/**
* @brief print_ip - ip-address as stl container
* @tparam T - container list<T> or vector<T>
* @param ip - ip-address is represented as a stl container
*/
template<typename T>
typename std::enable_if_t<std::is_same<T, std::vector<typename T::value_type>>::value ||
	std::is_same<T, std::list<typename T::value_type>>::value, void>
print_ip( const T& c )
{
	for( auto it = c.cbegin(); it != c.cend(); ++it )
	{
		std::cout << *it;
		auto it1 = it;
		if( ++it1 != c.cend() )
			std::cout << ".";
	}
	std::cout << std::endl;
}


/**
* @brief print_ip - ip-address as integral type
* @tparam T - intergral type
* @param ip - ip-address is represented as a integral value
*/
template<typename T>
typename std::enable_if_t<std::is_integral<T>::value, void>
print_ip( const T& t )
{
	char* p = ( char* )&t;
	for( int i = sizeof( t ) - 1; i >= 0; --i )
	{
		std::cout << std::to_string( ( unsigned char )p[ i ] );
		if( i > 0 )
			std::cout << ".";
	}
	std::cout << std::endl;
}


/**
* @brief main function
*/
int main()
{
	print_ip( char( -1 ) );
	//std::cout << "--------------------------------" << std::endl;
	print_ip( short( 0 ) );
	//std::cout << "--------------------------------" << std::endl;
	print_ip( int( 2130706433 ) );
	//std::cout << "--------------------------------" << std::endl;
	print_ip( int64_t( 8875824491850138409 ) );
	//std::cout << "--------------------------------" << std::endl;

	print_ip( std::string( "192.168.0.1" ) );
	//std::cout << "--------------------------------" << std::endl;
	
	print_ip( std::vector<int>{ 192,168,20,56 } );
	//std::cout << "--------------------------------" << std::endl;
	print_ip( std::list<int>{ 104, 215, 148, 63 } );
	//std::cout << "--------------------------------" << std::endl;

    return 0;
}

