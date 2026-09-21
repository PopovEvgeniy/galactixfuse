#include "galactixfuse.h"
#include "format.h"
#include "exitcode.h"

void show_intro();
void show_error(const char *message);
void check_name(const char *name,const char *message,const int code);
FILE *open_input_file(const char *name);
FILE *create_output_file(const char *name);
void read_data(void *data,const size_t length,const size_t blocks,FILE *input);
void write_data(const void *data,const size_t length,const size_t blocks,FILE *output);
void go_offset(FILE *target,const unsigned long int offset);
void check_memory(const void *memory);
size_t check_format(FILE *input);
char *get_memory(const size_t length);
void data_dump(FILE *input,FILE *output,const size_t length);
void fast_data_dump(FILE *input,FILE *output,const size_t length);
void write_output_file(FILE *input,const char *name,const size_t length);
char *get_name(const char *path,const char *name);
glb_fat_entry *read_table(FILE *input,const size_t amount);
void work(const char *target,const char *path);

int main(int argc, char *argv[])
{
 show_intro();
 switch (argc)
 {
  case 1:
  puts("You must give a target file name and an output path as the command-line arguments!");
  exit(COMMAND_LINE_ARGUMENTS_ERROR);
  break;
  case 2:
  puts("You don't give the output path");
  exit(COMMAND_LINE_ARGUMENTS_ERROR);
  break;
  case 3:
  check_name(argv[2],"The output path is empty",EMPTY_PATH_ERROR);
  puts("Extracting the files... Please wait");
  work(argv[1],argv[2]);
  puts("The work has been finished");
  break;
  default:
  puts("You gave too many command-line arguments");
  exit(COMMAND_LINE_ARGUMENTS_ERROR);
  break;
 }
 return 0;
}

void show_intro()
{
 putchar('\n');
 puts("Galactix fuse 0.8.9");
 puts("Galactix resource extraction tool by Popov Evgeniy Alekseyevich. 2022-2026 years");
 puts("This tool is intended for Galactix version 1.3");
 puts("This software is distributed under the GNU GENERAL PUBLIC LICENSE (version 2 or later) terms");
 putchar('\n');
}

void show_error(const char *message)
{
 fputc('\n',stderr);
 fputs(message,stderr);
 fputc('\n',stderr);
}

void check_name(const char *name,const char *message,const int code)
{
 size_t length=0;
 if (name!=NULL)
 {
  length=strlen(name);
 }
 if (length==0)
 {
  show_error(message);
  exit(code);
 }

}

FILE *open_input_file(const char *name)
{
 FILE *target=NULL;
 if (name!=NULL)
 {
  target=fopen(name,"rb");
 }
 if (target==NULL)
 {
  show_error("Can't open the input file");
  exit(OPEN_FILE_ERROR);
 }
 return target;
}

FILE *create_output_file(const char *name)
{
 FILE *target=NULL;
 if (name!=NULL)
 {
  target=fopen(name,"wb");
 }
 if (target==NULL)
 {
  show_error("Can't create the output file");
  exit(CREATE_FILE_ERROR);
 }
 return target;
}

void read_data(void *data,const size_t length,const size_t blocks,FILE *input)
{
 if (fread(data,length,blocks,input)<blocks)
 {
  show_error("Can't read data!");
  exit(READ_DATA_ERROR);
 }

}

void write_data(const void *data,const size_t length,const size_t blocks,FILE *output)
{
 if (fwrite(data,length,blocks,output)<blocks)
 {
  show_error("Can't write data!");
  exit(WRITE_DATA_ERROR);
 }

}

void go_offset(FILE *target,const unsigned long int offset)
{
 if (fseek(target,offset,SEEK_SET)!=0)
 {
  show_error("Can't jump to the target offset");
  exit(SET_FILE_POSITION_ERROR);
 }

}

void check_memory(const void *memory)
{
 if (memory==NULL)
 {
  show_error("Can't allocate memory");
  exit(MEMORY_ALLOCATION_ERROR);
 }

}

size_t check_format(FILE *input)
{
 glb_fat_entry head;
 read_data(&head,sizeof(glb_fat_entry),1,input);
 if (strncmp(head.name,"GLIB FILE",9)!=0)
 {
  show_error("The invalid format");
  exit(INVALID_FORMAT_ERROR);
 }
 if (head.length!=0)
 {
  show_error("The invalid format");
  exit(INVALID_FORMAT_ERROR);
 }
 return head.offset;
}

char *get_memory(const size_t length)
{
 char *memory=NULL;
 memory=(char*)calloc(length,sizeof(char));
 check_memory(memory);
 return memory;
}

void data_dump(FILE *input,FILE *output,const size_t length)
{
 char *buffer=NULL;
 size_t current=0;
 size_t elapsed=0;
 size_t block=4096;
 buffer=get_memory(block);
 for (current=0;current<length;current+=block)
 {
  elapsed=length-current;
  if (elapsed<block)
  {
   block=elapsed;
  }
  read_data(buffer,sizeof(char),block,input);
  write_data(buffer,sizeof(char),block,output);
 }
 free(buffer);
}

void fast_data_dump(FILE *input,FILE *output,const size_t length)
{
 char *buffer=NULL;
 buffer=(char*)malloc(length);
 if (buffer==NULL)
 {
  data_dump(input,output,length);
 }
 else
 {
  read_data(buffer,sizeof(char),length,input);
  write_data(buffer,sizeof(char),length,output);
  free(buffer);
 }

}

void write_output_file(FILE *input,const char *name,const size_t length)
{
 FILE *output=NULL;
 output=create_output_file(name);
 fast_data_dump(input,output,length);
 fclose(output);
}

char *get_name(const char *path,const char *name)
{
 char *result=NULL;
 size_t path_length=0;
 size_t name_length=0;
 if (path!=NULL)
 {
  path_length=strlen(path);
 }
 if (name!=NULL)
 {
  name_length=strlen(name);
 }
 if (path_length>0)
 {
  if (name_length>0)
  {
   result=get_memory(path_length+name_length+1);
   strncpy(result,path,path_length);
   strncat(result,name,name_length);
  }

 }
 return result;
}

glb_fat_entry *read_table(FILE *input,const size_t amount)
{
 glb_fat_entry *table=NULL;
 table=(glb_fat_entry*)calloc(amount,sizeof(glb_fat_entry));
 check_memory(table);
 read_data(table,sizeof(glb_fat_entry),amount,input);
 return table;
}

void work(const char *target,const char *path)
{
 FILE *input=NULL;
 glb_fat_entry *table=NULL;
 char *name=NULL;
 size_t index=0;
 size_t amount=0;
 input=open_input_file(target);
 amount=check_format(input);
 table=read_table(input,amount);
 for (index=0;index<amount;++index)
 {
  name=get_name(path,table[index].name);
  go_offset(input,table[index].offset);
  write_output_file(input,name,table[index].length);
  free(name);
 }
 free(table);
 fclose(input);
}