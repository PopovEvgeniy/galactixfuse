#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "format.h"

void show_intro();
void show_message(const char *message);
FILE *open_input_file(const char *name);
FILE *create_output_file(const char *name);
void go_offset(FILE *file,const unsigned long int offset);
void data_dump(FILE *input,FILE *output,const size_t length);
void fast_data_dump(FILE *input,FILE *output,const size_t length);
void write_output_file(FILE *input,const char *name,const size_t length);
void check_memory(const void *memory);
char *get_string_memory(const size_t length);
char *get_name(const char *path,const char *name);
size_t check_format(FILE *input);
glb_fat_entry *read_table(FILE *input,const size_t amount);
void work(const char *target,const char *path);

int main(int argc, char *argv[])
{
 show_intro();
 if (argc<3)
 {
  show_message("You must give a target file name and output path as command line arguments!");
 }
 else
 {
  show_message("Extracting a files... Please wait");
  work(argv[1],argv[2]);
  show_message("Work finish");
 }
 return 0;
}

void show_intro()
{
 putchar('\n');
 puts("Galactix fuse. Version 0.7");
 puts("Galactix resource extraction tool by Popov Evgeniy Alekseyevich. 2022-2024 years");
 puts("This tool intends for Galactix version 1.3");
 puts("This software distributed under GNU GENERAL PUBLIC LICENSE");
}

void show_message(const char *message)
{
 putchar('\n');
 puts(message);
}

FILE *open_input_file(const char *name)
{
 FILE *target;
 target=fopen(name,"rb");
 if (target==NULL)
 {
  puts("Can't open input file");
  exit(1);
 }
 return target;
}

FILE *create_output_file(const char *name)
{
 FILE *target;
 target=fopen(name,"wb");
 if (target==NULL)
 {
  show_message("Can't create ouput file");
  exit(2);
 }
 return target;
}

void go_offset(FILE *file,const unsigned long int offset)
{
 if (fseek(file,offset,SEEK_SET)!=0)
 {
  show_message("Can't jump to target offset");
  exit(3);
 }

}

void data_dump(FILE *input,FILE *output,const size_t length)
{
 unsigned char data;
 size_t index;
 data=0;
 for (index=0;index<length;++index)
 {
  fread(&data,sizeof(unsigned char),1,input);
  fwrite(&data,sizeof(unsigned char),1,output);
 }

}

void fast_data_dump(FILE *input,FILE *output,const size_t length)
{
 unsigned char *buffer=NULL;
 buffer=(unsigned char*)calloc(length,sizeof(unsigned char));
 if (buffer==NULL)
 {
  data_dump(input,output,length);
 }
 else
 {
  fread(buffer,sizeof(unsigned char),length,input);
  fwrite(buffer,sizeof(unsigned char),length,output);
  free(buffer);
 }

}

void write_output_file(FILE *input,const char *name,const size_t length)
{
 FILE *output;
 output=create_output_file(name);
 fast_data_dump(input,output,length);
 fclose(output);
}

void check_memory(const void *memory)
{
 if(memory==NULL)
 {
  show_message("Can't allocate memory");
  exit(4);
 }

}

char *get_string_memory(const size_t length)
{
 char *memory=NULL;
 memory=(char*)calloc(length+1,sizeof(char));
 check_memory(memory);
 return memory;
}

char *get_name(const char *path,const char *name)
{
 char *result;
 size_t length;
 length=strlen(path)+strlen(name);
 result=get_string_memory(length);
 strcpy(result,path);
 return strcat(result,name);
}

size_t check_format(FILE *input)
{
 glb_fat_entry head;
 fread(&head,sizeof(glb_fat_entry),1,input);
 if (strncmp(head.name,"GLIB FILE",9)!=0)
 {
  puts("Invalid format");
  exit(5);
 }
 if (head.length!=0)
 {
  puts("Invalid format");
  exit(5);
 }
 return head.offset;
}

glb_fat_entry *read_table(FILE *input,const size_t amount)
{
 glb_fat_entry *table;
 table=(glb_fat_entry*)malloc(amount*sizeof(glb_fat_entry));
 check_memory(table);
 fread(table,sizeof(glb_fat_entry),amount,input);
 return table;
}

void work(const char *target,const char *path)
{
 FILE *input;
 glb_fat_entry *table;
 char *name;
 size_t index,amount;
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