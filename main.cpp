// $Id: main.cpp,v 1.2 2016-08-18 15:13:48-07 - - $    
// Elizabeth Cepernich
// eceperni // 1316976
// CMPS 104a Fall, 2016
// October 10, 2016                                                         

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

/*public values*/

//Values from cppstrtok.cpp
const string cpp="/usr/bin/cpp";
string cpp_line=cpp; //Not from cppstrtok.cpp
constexpr size_t LINESIZE=1024; 

//values for flag checks
int yy_flex_debug=0; //The flag used for -l
int yydebug=0; //The flag used for -y
string d_flag=""; //The flag used for -D___
string a_flag=""; //The flad used for -@___

//values for file names
const char* file_name=NULL; //get .oc file name
char* base_name=NULL; //get file name without suffix - use for functions
string base_string=""; //get file name without suffix - use for string manipulation

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
      for (int tokenct = 1;; ++tokenct) {
         char* token = strtok_r (bufptr, " \t\n", &savepos); //get each token
         bufptr = NULL;
         if (token == NULL) break;
         string_set::intern (token); //intern each token into the string set
      }
      ++linenr; //cycle through every line until EOF
   }
}


int main (int argc, char** argv) {
   int x; //x is the int for the getopt function

   //Flag checks 
   while ((x=getopt(argc, argv, "ly@:D:")) != -1) //read flags up to the argc'th arg
   {										  //in argv, looking for l, y, D_, or @_
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
   if (argc==optind) //If the current position argument = total arguments
   //if (argc==x) //If the current position argument = total arguments
   {
   		fprintf(stderr, "Error: No file listed.\n"); //Error for no file
   		exit(1); //Failure and exit if no file is listed
   }
   else if (argc>optind+1) //If total aruments are greater than the current 
   //else if (argc>x+1) //If total aruments are greater than the current 
   {					   //argument plus 1 (all the flags plus the file)
   		fprintf(stderr, "Error: Too many files listed. \n"); //Error for 2+ files
   		exit(1); //Failure and exit if too many files are listed
   }
   else //The last argument is the file
   {
   		file_name=argv[optind]; //Get file name argument from optind (current arg)
   		if (strstr(file_name, ".oc")) //the string file_name contains .oc
   		{
   			cpp_line=cpp_line+" "+file_name; //add file_name to the command
   			//base_name=basename(cpp_line); //get the base name of the file
   			
   			char* temp_name=basename((char*)file_name); //get the base name of the file
   			base_string=temp_name; //put temp_name into base_string for editing
   			int len=base_string.size(); //find size of base_string for substring cut
   			base_string=base_string.substr(0,len-3); //cut the last 3 characters off
   										 //the end of base_string, removing .oc
   			char* copying=new char[base_string.length()+1]; //copy string into char*
   			strcpy(copying,base_string.c_str());
   			base_name=copying; //update base_name so the base file name can be used in c functions
   		}
   		else //the string file_name does not contain .oc
   		{
   			fprintf(stderr, "Error: %s is not a .oc file.\n",file_name); //error message
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
   		fprintf(stderr, "Error: %s does not exist.\n",file_name); //print error message
   		exit(1); //Failure and exit because .oc file does not exist
   }
   cpp_line=cpp+" "+d_flag+" "+file_name; //add that to the cpp 
   FILE* pipe=popen(cpp_line.c_str(),"r"); //open a FILE caled pipe and pipe
   										   //open the /usr/bin/cpp/prog.cpp
   if(pipe==NULL) //file does not exist
   {
   		fprintf(stderr, "Error: %s does not exist.\n",file_name);
   		exit(1); //Failure and exit because the file was not found
   }
   else //File does exist
   {
   		cpplines(pipe, (char*)file_name); //use cpplines on the file
   		int closepipe=pclose(pipe); //close the pipe for the file
   		eprint_status(cpp_line.c_str(), closepipe); //check command status
   }

   strcat(base_name,".str"); //add the .str suffix to your base filename for writing

   FILE* output=NULL; //create output file
   output=fopen(base_name,"w"); //open file with name program.str to write
   string_set::dump (output); //write the string set to the output file
   fclose(output); //close program.str - the file is now reitten
   return EXIT_SUCCESS; //Success and exit with file written
}

