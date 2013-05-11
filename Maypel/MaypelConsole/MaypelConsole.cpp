#include "MaypelConsole.h"

#include <io.h>
// (CreateProcess(MSpath, " WebStart", IntPtr.Zero, IntPtr.Zero, false, 4, IntPtr.Zero, null, ref StartupInfo, out ProcessInfo))
/**
	This function is used to launch MapleStory, directly.
*/
::DWORD Maypel::LaunchMaple( ::HANDLE &out_MSProcHandle )
{
	::DWORD Ret = 0;

	// Ensure out_MSProcHandle is a valid handle.
	if( out_MSProcHandle == INVALID_HANDLE_VALUE  )
		return Ret;

	::STARTUPINFO			MSStartUpInfo;
	::PROCESS_INFORMATION	MSProcInfo;

	// Initialize the members of MSStartUpInfo and MSProcInfo by
	// setting them to zeroes.
	::ZeroMemory( &MSStartUpInfo, sizeof( MSStartUpInfo ) );
	::ZeroMemory( &MSProcInfo, sizeof( MSProcInfo ) );

	MSStartUpInfo.cb = sizeof( MSStartUpInfo );

	// Attempt to directly launch MapleStory.
	if( ! ::CreateProcess( TEXT( "MapleStory.exe" ),
			       TEXT( " WebStart" ), // 64bit = GameLaunching, 32bit =  WebStart.
			       NULL,
			       NULL,
			       FALSE,
			       NULL,
			       NULL,
			       NULL,
			       &MSStartUpInfo,
			       &MSProcInfo ) )
	{
		Ret = ::GetLastError();
	}
	else {
		out_MSProcHandle = ::OpenProcess( PROCESS_ALL_ACCESS, FALSE, MSProcInfo.dwProcessId );
		Ret = 1;
	}

	// Clean-up.
	::CloseHandle( MSProcInfo.hThread );
	::CloseHandle( MSProcInfo.hProcess );

	return Ret;
};

/**
	This function is used to load MaypelW.dll into the newly created MapleStory
	process, which should be the one that was created by function LaunchMaple.
*/
::BOOL Maypel::LoadMaypelW( const ::HANDLE out_MSProcHandle )
{
	if( _access( "MaypelW.dll", 0 ) == -1 )
		return FALSE;

	if( out_MSProcHandle == INVALID_HANDLE_VALUE )
		return -1;

	char		Buffer[ 50 ] = { 0 };
	::LPVOID	RemoteString = NULL;
	::LPVOID	LoadLibAddress = NULL;
	const size_t LoadMaypelWStrLen = strlen( "MaypelW.dll" );

	LoadLibAddress = ( ::LPVOID )::GetProcAddress( ::GetModuleHandle( "Kernel32.dll" ), "LoadLibraryA" );

	RemoteString = ( ::LPVOID )::VirtualAllocEx( out_MSProcHandle,
		NULL, LoadMaypelWStrLen, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE );

	::WriteProcessMemory( out_MSProcHandle, (LPVOID)RemoteString, "MaypelW.dll", LoadMaypelWStrLen, NULL );

	::CreateRemoteThread( out_MSProcHandle,
						  NULL,
						  NULL,
						  ( ::LPTHREAD_START_ROUTINE )LoadLibAddress,
						  ( ::LPVOID )RemoteString,
						  NULL,
						  NULL );

	::CloseHandle( out_MSProcHandle );

	return TRUE;
};
