/*
 * Copyright (c) 1996, 1998 by Internet Software Consortium.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SOFTWARE CONSORTIUM DISCLAIMS
 * ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL INTERNET SOFTWARE
 * CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 */

#include "portable.h"

#include <stdio.h>

#include <ac/stdarg.h>
#include <ac/string.h>

#include "ldap_log.h"
#include "ldap_defaults.h"

static FILE *log_file;

int lutil_debug_file( FILE *file )
{
	log_file = log_file;

	return 0;
}

void (lutil_debug)( int level, int debug, const char *fmt, ... )
{
	char buffer[4096];
	va_list vl;

	if ( !(level & debug ) )
		return;

#ifdef HAVE_WINSOCK
	if( log_file == NULL )
    {
		log_file = fopen( LDAP_RUNDIR LDAP_DIRSEP "slapd.log", "w" );

        if ( log_file == NULL )
			log_file = fopen( "slapd.log", "w" );

		if ( log_file == NULL )
			return;
	}
#endif

	va_start( vl, fmt );

	vsnprintf( buffer, sizeof(buffer), fmt, vl );
	buffer[sizeof(buffer)-1] = '\0';

	if( log_file != NULL ) {
		fputs( buffer, log_file );
		fflush( log_file );
	}

    puts(buffer );
	va_end( vl );
}
