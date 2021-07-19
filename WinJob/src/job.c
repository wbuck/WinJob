#include "job.h"
#include <stdlib.h>

#define FREE_AND_NULL(p) do { free(p); p = NULL; } while(0)

typedef struct Job {
	HANDLE handle; /* Handle to the process. */
} Job;

WINJOB_API Job* job_init( const wchar_t* job_name ) {
	Job* job = NULL;
	if ( ( job = malloc( sizeof * job ) ) == NULL ) {
		return NULL;
	}

	if ( ( job->handle = CreateJobObjectW( NULL, job_name ) ) == NULL ) {
		free( job );
		return NULL;
	}
	else if ( GetLastError( ) == ERROR_ALREADY_EXISTS ) {
		free( job );
		return NULL;
	}

	JOBOBJECT_EXTENDED_LIMIT_INFORMATION info = {
		.BasicLimitInformation = {
			.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE
		}
	};

	const DWORD size = ( DWORD )sizeof( JOBOBJECT_EXTENDED_LIMIT_INFORMATION );

	if ( SetInformationJobObject( job->handle,
		JobObjectExtendedLimitInformation, &info, size ) == 0 ) {
		CloseHandle( job->handle );
		FREE_AND_NULL( job );
	}

	return job;
}

WINJOB_API long job_add_process( Job* job, HANDLE process ) {
	return ( long )AssignProcessToJobObject( job->handle, process );
}

WINJOB_API void job_free( Job* job ) {
	CloseHandle( job->handle );
	free( job );
}

