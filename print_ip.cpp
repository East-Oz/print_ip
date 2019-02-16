#include <vector>
#include <list>
#include <type_traits>
#include <iostream>
#include <string>

enum class ETYPE
{
	list = 1,
	vector = 2,
	integral = 3,
	string = 4,
	unknown = 255

};

template<typename T>
struct type_of_arg
{
	static const ETYPE eType = (std::is_integral<T>::value) ? ETYPE::integral : ((std::is_same<T, std::string>::value) ? ETYPE::string : ETYPE::unknown);
};


template<typename T, typename Alloc>
struct type_of_arg<std::list<T, Alloc>>
{
	static const ETYPE eType = ETYPE::list;
};

template <typename T, typename Alloc>
struct type_of_arg<std::vector<T, Alloc> >
{
	static const ETYPE eType = ETYPE::vector;
};


template<typename T>
void print_ip( const T t )
{
	auto type = type_of_arg<T>::eType;

	if( type == ETYPE::integral ) 
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
};

//template<>
//void print_ip( const char* _s )
//{
//	std::cout << _s << std::endl;
//}


template<>
void print_ip( const std::string  _s )
{
	std::cout << _s << std::endl;
}

template<typename T, typename Alloc>
void print_ip( std::list<T, Alloc> c)
{
	print_collection( c );
}

template<typename T, typename Alloc>
void print_ip( std::vector<T, Alloc> c )
{
	print_collection( c );
}


template<typename T>
void print_collection( T c )
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

int main()
{
	print_ip( char( -1 ) );
	//std::cout << "--------------------------------" << std::endl;
	print_ip( short( 0 ) );
	//std::cout << "--------------------------------" << std::endl;
	print_ip( int( 2130706433 ) );
	//std::cout << "--------------------------------" << std::endl;
	print_ip( long long( 8875824491850138409 ) );
	//std::cout << "--------------------------------" << std::endl;

	print_ip( std::string( "192.168.0.1" ) );
	//std::cout << "--------------------------------" << std::endl;
	
	print_ip( std::vector<int>{ 192,168,20,56 } );
	//std::cout << "--------------------------------" << std::endl;
	print_ip( std::list<int>{ 104, 215, 148, 63 } );
	//std::cout << "--------------------------------" << std::endl;

    return 0;
}

