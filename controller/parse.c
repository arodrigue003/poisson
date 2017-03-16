#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <regex.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
typedef int Function();

#include "aquarium.h"

#define MAX_ARGS 10

/* The names of functions that actually do the manipulation. */
int com_add ();
int com_show (); 
int com_load (char *arg); 
int com_del (); 
int com_save ();
int com_help();
int initialize_readline(){


}
/* A structure which contains information on the commands this program
   can understand. */

typedef struct {
  char *name;			/* User printable name of the function. */
  Function *func;		/* Function to call to do the job. */
  char *doc;			/* Documentation for this function.  */
} COMMAND;

COMMAND commands[] = {
  { "load", com_load, "Chargement de l’aquarium" },
  { "show", com_show, "Affichage de la topologie" },
  { "add", com_add, "Ajouter une vue" },
  { "del", com_del, "Supprimer une vue" },
  { "save", com_save, "Enregistrer / exporter les donnees de l’aquarium actuelle dans un fichier." },
  { (char *)NULL, (Function *)NULL, (char *)NULL }
};

/* Forward declarations. */
char *stripwhite ();
COMMAND *find_command ();

/* The name of this program, as taken from argv[0]. */
char *progname;

/* When non-zero, this global means the user is done using this program. */
int done;


int main (argc, argv)
     int argc;
     char **argv;
{
  char *line, *s;

  progname = argv[0];

  initialize_readline ();	/* Bind our completer. */

  /* Loop reading and executing lines until the user quits. */
  for ( ; done == 0; )
    {
      line = readline ("$ ");

      if (!line)
        break;

      /* Remove leading and trailing whitespace from the line.
         Then, if there is anything left, add it to the history list
         and execute it. */
      s = stripwhite (line);

      if (*s)
        {
          add_history (s);
          execute_line (s);
        }

      free (line);
    }
  exit (0);
}

/* Execute a command line. */
int execute_line (line)
     char *line;
{
  register int i;
  COMMAND *command;
  char *word;

  /* Isolate the command word. */
  i = 0;
  while (line[i] && whitespace (line[i]))
    i++;
  word = line + i;

  while (line[i] && !whitespace (line[i]))
    i++;

  if (line[i])
    line[i++] = '\0';

  command = find_command(word);

  if (!command)
    {
      fprintf (stderr, "%s: No such command for Free-Poisson.\n", word);
      return (-1);
    }

  /* Get argument to command, if any. */
  while (whitespace (line[i]))
    i++;

  word = line + i;

  /* Call the function. */
  return ((*(command->func)) (word));
}

/* Look up NAME as the name of a command, and return a pointer to that
   command.  Return a NULL pointer if NAME isn't a command name. */
COMMAND * find_command (name)
     char *name;
{
  register int i;

  for (i = 0; commands[i].name; i++)
    if (strcmp (name, commands[i].name) == 0)
      return (&commands[i]);

  return ((COMMAND *)NULL);
}

/* Strip whitespace from the start and end of STRING.  Return a pointer
   into STRING. */
char *stripwhite (char *string)
{
  register char *s, *t;

  for (s = string; whitespace (*s); s++)
    ;
    
  if (*s == 0)
    return (s);

  t = s + strlen (s) - 1;
  while (t > s && whitespace (*t))
    t--;
  *++t = '\0';

  return s;
}


/* Return non-zero if ARG is a valid argument for CALLER, else print
   an error message and return zero. */
int valid_argument (char *caller, char *arg)
{
  if (!arg || !*arg)
    {
      fprintf (stderr, "%s: Argument required.\n", caller);
      return (0);
    }
  
  char *array[MAX_ARGS];
  int i = 0;
  array[0] = strtok(arg," ");
  while (array[i]) { array[++i] = strtok(NULL, " ");}
  
  if (strcmp(caller, "load") == 0)
    {
      if (i > 1)
	{
	  fprintf (stderr, "%s: Wrong number of arguments given. 1 needed.\n", caller);
	  return (0);
	}
      return 1;
    }
  
  regex_t regex;
  int err;

  
  if (strcmp(caller, "add") == 0)
    {
      if (i != 3)
	{
	  printf("%d\n",i);
	  fprintf (stderr, "%s: Wrong number of arguments given. 3 needed.\n", caller);
	  return (0);
	}
      
      if (strcmp(array[0], "view") != 0)
	{
	  fprintf (stderr, "%s: Wrong first argument. 'view' expected.\n", caller);
	  return (0);
	}

      err = regcomp(&regex, "N[[:digit:]]", REG_NOSUB);
      if (err) {
	fprintf(stderr, "%s: Could not compile regex\n", caller);
	return 0;
      }
      err = regexec(&regex, array[1], 0, NULL, 0);
      // dimensions
      if (!err)
	{
	  err = regcomp(&regex, "[[:digit:]+]x[[:digit:]+]\\+[[:digit:]+]\\+[[:digit:]+]", REG_NOSUB); //
	  if (err) {
	    fprintf(stderr, "%s: Could not compile regex\n", caller);
	    return 0;
	  }
	  err = regexec(&regex, array[2], 0, NULL, 0);
	  regfree(&regex);
	  if (!err) { return 1;}
	  fprintf(stderr, "%s:  Wrong third argument.\n", caller);
	  return 0;
	}
      fprintf(stderr, "%s:  Wrong second argument.\n", caller);
      return 0;
    }
  if (strcmp(caller, "del") == 0)
    {
      if (i != 2)
	{
	  fprintf (stderr, "%s: Wrong number of arguments given. 2 needed.\n", caller);
	  return (0);
	}
      if (strcmp(array[0], "view") != 0)
	{
	  fprintf (stderr, "%s: Wrong second argument. 'view' expected.\n", caller);
	  return (0);
	}
      err = regcomp(&regex, "N[[:digit:]]", REG_NOSUB);
      if (err) {
	fprintf(stderr, "%s: Could not compile regex\n", caller);
	regfree(&regex);
	return 0;
      }
      err = regexec(&regex, array[1], 0, NULL, 0);
      regfree(&regex);
      if (err) {
	return 1;
      }
      fprintf(stderr, "%s:  Wrong second argument.\n", caller);
      return 0;
    }

  return (1);
}

int com_add (char *arg){
  //add view N5 400x400+400+200
  if (!valid_argument("add", arg))
    {
      return 0;
    }
  struct view *view;
  if (!AQUARIUM)
    {
      fprintf (stderr, "%s: command unavaible. Try to load before adding\n", "add");
      return 0;
    }
  if (0 && !add_view(view,AQUARIUM))
    {
      fprintf (stderr, "%s: command error. View cannot be added.\n", "add");
      return 0;
    }
  printf("\t-> view added\n"); 
  return 1;
}
 
int com_show (){
  if (!AQUARIUM)
    {
      fprintf (stderr, "%s: command unavaible. Try to load before showing\n", "show");
      return (0); 
    }
  //show_aquarium(AQUARIUM);
  return 1;
} 
int com_load (char *arg){
  if (AQUARIUM)
    {
      fprintf (stderr, "%s: Cannot load the aquarium. The aquarium has already been loaded.\n", "load");
      return (0); 
    }
  if (1 || !load_aquarium(AQUARIUM))
    {
    fprintf (stderr, "%s: Cannot load the aquarium. Check out the config file.\n", "load");
    return (0); 
    }
  printf("\t-> %s loaded ( %d display view ) !\n", arg,(*AQUARIUM).aquarium_views); //
  return 1;
}

int com_del (char * arg){
  // view N5 deleted
   if (!valid_argument("del", arg))
    {
      return 0;
    }
 if (!AQUARIUM)
    {
      fprintf (stderr, "%s: command error. Retry\n", "del");
      return (0); 
    }
  if (0 && !del_view(5,AQUARIUM))
    {
      
      fprintf (stderr, "%s: Cannot delete this view. Retry\n", "del");
      return (0);
    }
  printf("\t-> view N%d deleted\n",5);
  return 1;
} 
int com_save (){
  // save aquarium log  
  if (!AQUARIUM)
    {
      fprintf (stderr, "%s:  Cannot save. An aquarium should be loaded before saving\n", "save");
      return (0); 
    }
  //save_aquarium(AQUARIUM);
  printf("\t-> Aquarium saved ! ( %d display view ) \n", (*AQUARIUM).aquarium_views);
  return 1;
}




/****** Implémentation des fonctions de l'aquarium ******/

/*  int load_aquarium(struct aquarium* aquarium); */
/* int save_aquarium(struct aquarium* aquarium); */


 /* int del_view(int view, struct aquarium* aquarium){ */
 /*   free((*aquarium).views[view]); */
 /*   (*aquarium).views[view] = NULL; */
 /* } */

 /* int add_view(int view_rank, struct view *view, struct aquarium* aquarium){ */
 /*   if (!(*aquarium).views[view_rank]){ */
 /*     fprintf (stderr, "%s:  Cannot add. This view is already used.\n", "add"); */
 /*     return 0; */
 /*   } */
 /*   (*aquarium).views[view_rank] = view; */
 /*   (*aquarium).aquarium_views++; */
 /*   return 1; */
 /* } */

 /* int show_aquarium(struct aquarium* aquarium){ */
 /*   printf("%dx%d\n", (*aquarium).aquarium_width,  (*aquarium).aquarium_height); */
 /*   for (int i = 0; i < MAX_VIEWS; i++){ */
 /*     if ( !(*aquarium).views[i]) */
 /*       printf("N%d %dx%d+%d+%d\n", i,  views[i].view_x, views[i].view_y, views[i].view_width,views[i].view_height);  */
 /*   } */
 /* } */
