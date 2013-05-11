#include <iostream>

#include "MaypelConsole.h"
#include "Resource.h"

int main( int argc, char* argv[] )
{
	::SetConsoleTitle( "MaypelConsole Version 1.0" );

	std::cout << "MaypelConsole - Version 1.0\n"
			  << "Written By Kernel (Kernel.Win@aol.com)\n"
			  << "www.CCPlz.net"
			  << std::endl
			  << std::endl;

	::HANDLE MapleProcHandle = NULL;
	::DWORD LaunchRet = NULL;

	std::cout << "Attempting to launch MapleStory...\n";

	LaunchRet = Maypel::LaunchMaple( MapleProcHandle );
	if( LaunchRet != 1 ) {
		std::cerr << "\t\tFailed.\nError: Unable to launch Maple! Error Code = " << LaunchRet << std::endl;
		std::getchar();
		return -1;
	} else {
		std::cout << "\t\tSuccess!\n"
				  << std::endl
				  << "Attempting to load MaypelW.dll..."
				  << std::endl;
		
		if( Maypel::LoadMaypelW( MapleProcHandle ) != TRUE ) {
			std::cerr << "\t\tFailed.\nError: Unable to load MaypelW.dll! Error Code = " << LaunchRet << std::endl;
			std::getchar();
			return -2;
		}
		else { std::cout << "\t\tSuccess!\n\n"; }
	}

#ifdef DEBUG
	std::getchar();
#else
	::Sleep( 30000 );
#endif // DEBUG

	return 0;
};