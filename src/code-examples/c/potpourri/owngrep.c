#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

const char *szCommand = "<not yet set>";
FILE *szLogFile = NULL;

void cleanup()
{
  if ( szLogFile )
  {
    if ( fclose( szLogFile ) == EOF )
    {
      (void) fprintf(
		     stderr,
		     "%s: standard output error: %s\n",
		     szCommand,
		     strerror( errno ) );
      exit( EXIT_FAILURE );			
    }
  }
  szLogFile = NULL;
}

void usage()
{
  (void) fprintf(
		 stderr,
		 "Usage: %s string [ -l <logfile> ] [ file1 ] [ file2 ] ...\n",
		 szCommand );
  cleanup();
  exit( EXIT_FAILURE );
}

void grep( FILE *fp, char *filename, char *searchString )
{
  char line[ 256 ];
  int lineno = 1;
  while( fgets( line, sizeof( line ), fp ) != NULL )
  {
    if ( szLogFile )
    {
      if ( fprintf(
	    szLogFile,
	    "l: Processing File: %s, line %d\n",
	    filename,
	    lineno ) < 0 )
      {
	(void) fprintf(
		       stderr,
		       "%s: error occoured while writing to logfile",
		       szCommand );
	cleanup();
	exit( EXIT_FAILURE );
      }
    }

    if ( strstr( line, searchString ) != NULL )
    {
      if ( szLogFile )
      {
	if ( fprintf(
	      szLogFile,
	      "f: Found pattern %s in File: %s, line %d.\n",
	      searchString, filename, lineno ) < 0 )
	{
	  (void) fprintf(
			 stderr,
			 "%s: error occoured while writing to logfile",
			 szCommand );
	  cleanup();
	  exit( EXIT_FAILURE );
	}
      }

      if ( printf( "%s", line ) < 0 )
      {
	(void) fprintf(
		       stderr,
		       "%s: standard output error: %s\n",
		       szCommand,
		       strerror( errno ) );
	cleanup();
	exit( EXIT_FAILURE );
      }
    }
    lineno++;
  }

  if ( ferror( fp ) )
  {
    (void) fprintf(
		   stderr,
		   "%s: file read error: %s\n",
		   szCommand,
		   strerror( errno ) );
    cleanup();
    exit( EXIT_FAILURE );
  }
}

int main ( int argc, char **argv )
{
  int opt;
  int bError = 0;
  FILE *fp = NULL;
  char *szSearchString = NULL;

  szCommand = argv[0];
  if ( szCommand && strrchr( szCommand, '/' ))
    szCommand = strrchr( szCommand, '/' ) + 1;

  while (( opt = getopt( argc, argv, "l:" )) != -1 )
  {
    switch( opt )
    {
      case 'l':
	if ( szLogFile )
	{
	  bError = 1;
	  break;
	}
	if ( ( szLogFile = fopen( optarg, "w" ) ) == NULL )
	{
	  (void) fprintf(
			 stderr,
			 "%s: cannot open file %s: %s\n",
			 szCommand,
			 argv[optind],
			 strerror( errno ) );
	  cleanup();
	  exit( EXIT_FAILURE );
	}
	break;
      default:
	bError = 1;
	break;
    }
  }

  if ( bError )
  {
    usage();
  }

  szSearchString = argv[optind++];

  if ( argc - optind == 0 )
  {
    grep( stdin, "stdin", szSearchString );
  }
  else
  {
    while ( optind < argc )
    {
      if ( ( fp = fopen( argv[optind], "r" ) ) == NULL )
      {
	(void) fprintf(
		       stderr,
		       "%s: cannot open file %s: %s\n",
		       szCommand,
		       argv[optind],
		       strerror( errno ) );
      }
      else
      {
	grep( fp, argv[optind], szSearchString );
      }

      if ( fp != NULL )
      {
	if ( fclose( fp ) == EOF )
	{
	  (void) fprintf(
			 stderr,
			 "%s: standard output error: %s\n",
			 szCommand,
			 strerror( errno ) );
	  exit( EXIT_FAILURE );
	}
	fp = NULL;
      }
      optind++;
    }
  }

  cleanup();
  exit( EXIT_SUCCESS );
}
