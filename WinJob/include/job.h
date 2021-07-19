#ifndef JOB_H
#define JOB_H

#ifdef WINJOB_EXPORTS
#define WINJOB_API __declspec(dllexport)
#else
#define WINJOB_API __declspec(dllimport)
#endif

#include <stddef.h>
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Opaque pointer to a job object. */
typedef struct Job Job;

/* Initializes a job object. 
   If the name is NULL a job object is created without a name. */
WINJOB_API Job* job_init( const wchar_t* job_name );

/* Adds a process to the job object. */
WINJOB_API long job_add_process( Job* job, HANDLE process );

/* Frees the job object. */
WINJOB_API void job_free( Job* job );

#ifdef __cplusplus
}
#endif

#endif
