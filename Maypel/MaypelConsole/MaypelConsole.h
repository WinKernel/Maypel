#ifndef MAYPEL_CONSOLE_H
#define MAYPEL_CONSOLE_H

#define WIN32_LEAN_AND_MEAN

#ifdef UNICODE
#	undef UNICODE
#endif // UNICODE

// #define DEBUG

#include <Windows.h>

namespace Maypel
{
	/**
		This function is used to launch MapleStory, directly.
	*/
	::DWORD LaunchMaple( ::HANDLE &out_MSProcHandle );
	/**
		This function is used to load MaypelW.dll into the newly created
		MapleStory process, which should be the one that was created by
		function LaunchMaple.
	*/
	::BOOL LoadMaypelW( const ::HANDLE out_MSProcHandle );
};

#endif // MAYPEL_CONSOLE_H