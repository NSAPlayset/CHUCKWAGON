#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <argp.h>

const char *argp_program_version = "chuckwagon 0.1";
const char *argp_program_bug_address = "support@cryptotronix.com";

static char doc[] =
  "Chuckwagon utility\n";

static char args_doc[] = "DIRECTION";
#define NUM_ARGS 1

struct arguments
{
  char *args[NUM_ARGS];
};

static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;
     
  switch (key)
    {
    case ARGP_KEY_ARG:

      if (state->arg_num >= NUM_ARGS)
	{
	  /* Too many arguments. */
	  argp_usage (state);
	}
     
      arguments->args[state->arg_num] = arg;
      
      break;
     
    case ARGP_KEY_END:

      if (state->arg_num < NUM_ARGS)
	{
	  /* Not enough arguments. */
	  argp_usage (state);
	}

      break;
     
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}


static struct argp argp = {0, parse_opt, args_doc, doc};

int
main(int argc, char **argv){

  struct arguments arguments;

  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  if (*arguments.args[0] == 'r' || *arguments.args[0] == 'w')
    {
      // Arguments match
    }
  else
    {
      printf ("Must specify r or w, see help\n");
      exit (1);
    }
  
  char *bus = "/dev/i2c-1"; 
  int addr = 0x42;          
  char buf[32] = {0};
  int fd = 0;
  int result = 0;

  if ((fd = open(bus, O_RDWR)) < 0) {
    /* ERROR HANDLING: you can check errno to see what went wrong */
    perror("Failed to open the i2c bus");
    exit(1);
  }


 if (ioctl(fd, I2C_SLAVE, addr) < 0) {
   perror("Failed to acquire bus access and/or talk to slave.\n");
   /* ERROR HANDLING; you can check errno to see what went wrong */
   exit(1);
 }

 if (*arguments.args[0] == 'w')
   {
     int num_read = 0;
     num_read = read (0, buf, sizeof(buf));

     if (num_read > 0);
     {
       result = write (fd, buf, num_read);
     }
   }
 else
   {
     int num_read = 0;
     num_read = read (fd, buf, sizeof(buf));

     int end_of_string = 0;
     int x = 0;

     /* Truncate the string to the first newline */
     for (x = 0; x < num_read; x++)
       {
	 if (buf[x] == '\n' && 0 == end_of_string)
	   {
	     end_of_string = (x == num_read) ? num_read : x + 1;
	   }
       }

     if (num_read > 0)
       {
	 result = write (1, buf, end_of_string);
       }

   }
 
 close (fd);

 result = (result > 0) ? 0 : result;

 return result;

}
