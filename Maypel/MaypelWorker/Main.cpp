#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <Psapi.h>

::DWORD EmptyWorkingSetThread();

::DWORD EmptyWorkingSetThread() {
	::HANDLE CurProcHandle = NULL;

	while( true ) {
		::Sleep( 30000 );
		if( ( CurProcHandle = ::GetCurrentProcess() ) != NULL ) {
			if( ! ::EmptyWorkingSet( CurProcHandle ) ) {
				MessageBox( NULL, TEXT( "An error has occured:\nUnable to remove pages!" ), TEXT( "Maypel" ), MB_OK );
				::CloseHandle( CurProcHandle );
				break;
			}
		}
	}

	::CloseHandle( CurProcHandle );
	return 0;
};

::BOOL WINAPI DllMain( ::HINSTANCE in_InstanceHandle, ::DWORD in_CallReason, ::LPVOID in_Reserved )
{
	if( in_CallReason == DLL_PROCESS_ATTACH ) {
		// MessageBox( NULL, TEXT(""), TEXT(""), 0 );
		::CreateThread( NULL, NULL, ( ::LPTHREAD_START_ROUTINE )EmptyWorkingSetThread, 0, 0, 0 );
	}
	return TRUE;
};