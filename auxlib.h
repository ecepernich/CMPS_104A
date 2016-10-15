#include <assert.h>
#include <errno.h>
#include <libgen.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

#include "auxlib.h"

string exec::execname;
int exec::exit_status = EXIT_SUCCESS;

const char* debugflags = "";
bool alldebugflags = false;

static void eprint_signal (const char* kind, int signal) {
   eprintf (", %s %d", kind, signal);
   const char* sigstr = strsignal (signal);
   if (sigstr != NULL) fprintf (stderr, " %s", sigstr);
}

int get_existstaus(void)
{
  return EXIT_SUCCESS;
}

void eprint_status (const char* command, int status) {
   if (status == 0) return; 
   eprintf ("%s: status 0x%04X", command, status);
   if (WIFEXITED (status)) {
      eprintf (", exit %d", WEXITSTATUS (status));
   }
   if (WIFSIGNALED (status)) {
      eprint_signal ("Terminated", WTERMSIG (status));
      #ifdef WCOREDUMP
      if (WCOREDUMP (status)) eprintf (", core dumped");
      #endif
   }
   if (WIFSTOPPED (status)) {
      eprint_signal ("Stopped", WSTOPSIG (status));
   }
   if (WIFCONTINUED (status)) {
      eprintf (", Continued");
   }
   eprintf ("\n");
}

void veprintf (const char* format, va_list args) {
   assert (exec::execname.size() != 0);
   assert (format != NULL);
   fflush (NULL);
   if (strstr (format, "%:") == format) {
      fprintf (stderr, "%s: ", exec::execname.c_str());
      format += 2;
   }
   vfprintf (stderr, format, args);
   fflush (NULL);
}

void eprintf (const char* format, ...) {
   va_list args;
   va_start (args, format);
   veprintf (format, args);
   va_end (args);
}

void errprintf (const char* format, ...) {
   va_list args;
   va_start (args, format);
   veprintf (format, args);
   va_end (args);
   exec::exit_status = EXIT_FAILURE;
}

void syserrprintf (const char* object) {
   errprintf ("%:%s: %s\n", object, strerror (errno));
}

void __stubprintf (const char* file, int line, const char* func,
                   const char* format, ...) {
   va_list args;
   fflush (NULL);
   printf ("%s: %s[%d] %s: ", exec::execname.c_str(), file, line, func);
   va_start (args, format);
   vprintf (format, args);
   va_end (args);
   fflush (NULL);
}     



void set_debugflags (const char* flags) {
   debugflags = flags;
   if (strchr (debugflags, '@') != NULL) alldebugflags = true;
   DEBUGF ('x', "Debugflags = \"%s\", all = %d\n",
           debugflags, alldebugflags);
}

bool is_debugflag (char flag) {
   return alldebugflags or strchr (debugflags, flag) != NULL;
}

void __debugprintf (char flag, const char* file, int line,
                    const char* func, const char* format, ...) {
   va_list args;
   if (not is_debugflag (flag)) return;
   fflush (NULL);
   va_start (args, format);
   fprintf (stderr, "DEBUGF(%c): %s[%d] %s():\n",
             flag, file, line, func);
   vfprintf (stderr, format, args);
   va_end (args);
   fflush (NULL);
}
bash-95$ cat auxlib.h
#ifndef __AUXLIB_H__
#define __AUXLIB_H__

#include <string>
using namespace std;

#include <stdarg.h>

//
// DESCRIPTION
//    Auxiliary library containing miscellaneous useful things.
//

//
// Error message and exit status utility.
//

struct exec {
   static string execname;
   static int exit_status;
};


int get_exitstatus(void);

void veprintf (const char* format, va_list args);
// Prints a message to stderr using the vector form of 
// argument list.

void eprintf (const char* format, ...);
// Print a message to stderr according to the printf format
// specified.  Usually called for debug output.
// Precedes the message by the program name if the format
// begins with the characters `%:'.

void errprintf (const char* format, ...);
// Print an error message according to the printf format
// specified, using eprintf.
// Sets the exitstatus to EXIT_FAILURE.

void syserrprintf (const char* object);
// Print a message resulting from a bad system call.  The
// object is the name of the object causing the problem and
// the reason is taken from the external variable errno.
// Sets the exit status to EXIT_FAILURE.

void eprint_status (const char* command, int status);
// Print the status returned by wait(2) from a subprocess.



//
// Support for stub messages.
//
#define STUBPRINTF(...) \
        __stubprintf (__FILE__, __LINE__, __func__, __VA_ARGS__)
void __stubprintf (const char* file, int line, const char* func,
                   const char* format, ...);

//
// Debugging utility.
//

void set_debugflags (const char* flags);
// Sets a string of debug flags to be used by DEBUGF statements.
// Uses the address of the string, and does not copy it, so
// it must not be dangling.  If a particular debug flag has
// been set, messages are printed.  The format is identical to
// printf format.  The flag "@" turns on all flags.

bool is_debugflag (char flag);
// Checks to see if a debugflag is set.

#ifdef NDEBUG
// Do not generate any code.
#define DEBUGF(FLAG,...)   /**/
#define DEBUGSTMT(FLAG,STMTS) /**/
#else
// Generate debugging code.
void __debugprintf (char flag, const char* file, int line,
                    const char* func, const char* format, ...);
#define DEBUGF(FLAG,...) \
        __debugprintf (FLAG, __FILE__, __LINE__, __func__, \
                       __VA_ARGS__)
#define DEBUGSTMT(FLAG,STMTS) \
        if (is_debugflag (FLAG)) { DEBUGF (FLAG, "\n"); STMTS }
#endif

#endif
