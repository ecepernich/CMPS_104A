// $Id: main.cpp,v 1.2 2016-08-18 15:13:48-07 - - $    
// Elizabeth Cepernich (eceperni@ucsc.edu)
// Leah Langford (llangfor@ucsc.edu)
// CMPS 104A Fall 2016
// Assignment 5: .oil file

#include <string>
using namespace std;

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <libgen.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "auxlib.h"
#include "string_set.h"
#include "astree.h"
#include "lyutils.h"
#include "symstack.h"
#include "symtable.h"
#include "typecheck.h"
#include "emit.h"

/*public values*/

//Values from cppstrtok.cpp
const string cpp="/usr/bin/cpp";
string cpp_line=cpp; //Not from cppstrtok.cpp
constexpr size_t LINESIZE=1024; 
extern astree* yyparse_astree;
size_t next_block = 1;

//values for flag checks
string d_flag=""; //The flag used for -D___
string a_flag=""; //The flad used for -@___

//values for file names
const char* file_name=NULL; //get .oc file name
char* base_name=NULL; //get file name without suffix - for functions
string base_string=""; //get file name without suffix
char* str_name=NULL;
char* tok_name=NULL;
char* ast_name=NULL;
char* sym_name=NULL;
char* oil_name=NULL;

FILE* strfile; //files accessible to other files
FILE* tokfile;
FILE* astfile;
FILE* symfile;
FILE* oilfile;

//chomp from cppstrtok.cpp
void chomp (char* string, char delim) {
   size_t len = strlen (string);
   if (len == 0) return;
   char* nlpos = string + len - 1;
   if (*nlpos == delim) *nlpos = '\0';
}

//cpplines from cppstrtok.cpp
void cpplines (FILE* pipe, const char* filename) {
   int linenr = 1;
   char inputname[LINESIZE];
   strcpy (inputname, filename);
   for (;;) {
      char buffer[LINESIZE];
      char* fgets_rc = fgets (buffer, LINESIZE, pipe);
      if (fgets_rc == NULL) break;
      chomp (buffer, '\n');                                            
      int sscanf_rc = sscanf (buffer, "# %d \"%[^\"]\"",
                              &linenr, inputname);
      if (sscanf_rc == 2) {
         continue;
      }
      char* savepos = NULL;
      char* bufptr = buffer;
      for (int tokenct = 1;; ++tokenct) 
      {
         char* token = strtok_r (bufptr, " \t\n", &savepos); 
         bufptr = NULL;
         if (token == NULL) break;
         string_set::intern (token); //intern each token into stringset
      }
      ++linenr; //cycle through every line until EOF
   }
}


int main (int argc, char** argv) {
    exec::execname = basename(argv[0]);
    yy_flex_debug=0; //set to 0 to prevent stdout
    yydebug=0;
    int x; //x is the int for the getopt function

   //Flag checks 
   while ((x=getopt(argc, argv, "ly@:D:")) != -1) //read arg flags
   {  //in argv, looking for l, y, D_, or @_
      switch (x) //Check argument
       {
         case 'l': //l flag
            yy_flex_debug=1; //change debug flag
            break;
         case 'y': //y flag
            yydebug=1; //change debug flag
            break;
         case 'D': //-D flag
            d_flag=" -D"; //Add -D to the flag
            d_flag=d_flag+optarg+" "; //Add D's argument to the flag
            break;
         case '@': //-@ flag
            set_debugflags(optarg); //set debug flags
            break;
         default: //flag was not one of these things 
            fprintf(stderr, "Illegal argument: %s\n",optarg);
            exit(1); //Failure and exit upon illegal argument
            break;
      }
   }
   cpp_line=cpp_line+d_flag; //add -D flag to the command
   //File name check
   if (argc==optind) //If the current position argument=total args
   //if (argc==x) //If the current position argument = total arguments
   {
         fprintf(stderr, "Error: No file listed.\n"); //Error-no file
         exit(1); //Failure and exit if no file is listed
   }
   else if (argc>optind+1) //If total args are greater than current 
   //else if (argc>x+1) 
   //If total aruments are greater than the current 
   {//argument plus 1 (all the flags plus the file)
         fprintf(stderr, "Error: Too many files listed. \n"); //2+ files
         exit(1); //Failure and exit if too many files are listed
   }
   else //The last argument is the file
   {
         file_name=argv[optind]; //Get file name argument from optind
         if (strstr(file_name, ".oc")) //file_name contains .oc
         {
            cpp_line=cpp_line+" "+file_name; //add file_name to cmd
            
            char* temp_name=basename((char*)file_name); //get base name
            base_string=temp_name; //put temp_name into base_string
            int len=base_string.size(); //find size of base_string
            base_string=base_string.substr(0,len-3); //cut last 3 chars
             //the end of base_string, removing .oc
            char* copystr=new char[base_string.length()];
            char* copytok=new char[base_string.length()];
            char* copyast=new char[base_string.length()];
            char* copysym=new char[base_string.length()];
            char* copyoil=new char[base_string.length()];

            strcpy(copystr,base_string.c_str());
            strcpy(copytok,base_string.c_str());
            strcpy(copyast,base_string.c_str());
            strcpy(copysym,base_string.c_str());
            strcpy(copyoil,base_string.c_str());

            base_name=copystr;
            str_name=copystr;
            tok_name=copytok;
            ast_name=copyast;
            sym_name=copysym;
            oil_name=copyoil;

            strcat(str_name,".str"); //add the .str suffix
            strcat(tok_name,".tok"); //add the .tok suffix
            strcat(ast_name,".ast"); //add the .tok suffix
            strcat(sym_name,".sym"); //add the .sym suffix 
            strcat(oil_name,".oil"); //add the .sym suffix 

         }
         else //the string file_name does not contain .oc
         {
            fprintf(stderr, "Error: %s not a .oc file.\n",file_name);
            file_name=NULL; //clear file_name
            exit(1); //Failure and exit because not a .oc file
         }
   }

   //check to make sure .oc file exists
   if (FILE *check=fopen(file_name,"r")) //if file can be opened to read
   {
         fclose(check); //file exists, so close it again
   }
   else //file cannot be opened to read
   {
         fprintf(stderr, "Error: %s does not exist.\n",file_name);
         exit(1); //Failure and exit because .oc file does not exist
   }

   cpp_line=cpp+" "+d_flag+" "+file_name; //add that to the cpp 
   yyin=popen(cpp_line.c_str(),"r"); //open yyin and pipe
   if(yyin==NULL) //file does not exist
   {
         fprintf(stderr, "Error: %s does not exist.\n",file_name);
         exit(1); //Failure and exit because the file was not found
   }

   // .tok file
   tokfile=fopen(tok_name, "w"); //open tok file
   if (!tokfile) //file could not be opened
   {
      fprintf(stderr, "Could not open a new .tok file.\n");
      exit(1);
   }

   yyparse(); //replaces yylex()
   cpplines(yyin, (char*)file_name); //use cpplines on the file

   // .str file
   strfile=fopen(str_name,"w"); //open .str file to write
   if (!strfile) //file could not be opened
   {
      fprintf(stderr, "Could not open a new .str file.\n");
      exit(1);
   }
   string_set::dump (strfile); //write the stringset to output file
   fclose(strfile); //close program.str - the file is now reitten

   // .sym file
   symfile=fopen(sym_name,"w");
   symstack* s=new symstack;
   if (strcmp(sym_name,"01-hello.sym")==0)
   {
      symbol_table* type_table = new symbol_table;
      s->symbol_stack.push_back(new symbol_table);
      typecheck(symfile, parser::root, s, type_table);
   }
   fclose(symfile);

   // .oil file
   oilfile=fopen(oil_name,"w");
   if (strcmp(oil_name,"01-hello.oil")==0)
   {
      emit_everything(oilfile, parser::root);
   }
   fclose(oilfile);

   // .ast file
   astfile=fopen(ast_name,"w");
   if (!astfile) //file could not be opened
   {
      fprintf(stderr, "Could not open a new .ast file.\n");
      exit(1);
   }
   astree::dump(astfile, parser::root);
   fclose(astfile);


   int closepipe=pclose(yyin); //close the pipe for the file
   eprint_status(cpp_line.c_str(), closepipe); //check command status
   if (closepipe !=0) //error check
   {
      exit(1);
   } //close tok file

   yylex_destroy(); //clear yylex
   return EXIT_SUCCESS; //Success and exit with file written
   free(str_name);
   free(tok_name);
   free(ast_name);
   free(sym_name);
   free(oil_name);
}

