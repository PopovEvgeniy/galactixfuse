#include "galactixfuse.h"
#include "format.h"

void show_intro();
void show_message(const char *message);
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
 if (argc<3)
 {
  show_message("You must give a target file name and an output path as the command-line arguments!");
 }
 else
 {
  show_message("Extracting the files... Please wait");
  work(argv[1],argv[2]);
  show_message("The work has been finished");
 }
 return 0;
}

void show_intro()
{
 putchar('\n');
 puts("Galactix fuse. Version 0.8.1");
 puts("Galactix resource extraction tool by Popov Evgeniy Alekseyevich. 2022-2026 years");
 puts("This tool is intended for Galactix version 1.3");
 puts("This software is distributed under the GNU GENERAL PUBLIC LICENSE");
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
  puts("Can't open the input file");
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
  show_message("Can't create the ouput file");
  exit(2);
 }
 return target;
}

void read_data(void *data,const size_t length,const size_t blocks,FILE *input)
{
 fread(data,length,blocks,input);
 if (ferror(input)!=0)
 {
  putchar('\n');
  puts("Can't read data!");
  exit(3);
 }

}

void write_data(const void *data,const size_t length,const size_t blocks,FILE *output)
{
 fwrite(data,length,blocks,output);
 if (ferror(output)!=0)
 {
  putchar('\n');
  puts("Can't write data!");
  exit(4);
 }

}

void go_offset(FILE *target,const unsigned long int offset)
{
 if (fseek(target,offset,SEEK_SET)!=0)
 {
  show_message("Can't jump to the target offset");
  exit(5);
 }

}

void check_memory(const void *memory)
{
 if(memory==NULL)
 {
  show_message("Can't allocate memory");
  exit(6);
 }

}

size_t check_format(FILE *input)
{
 glb_fat_entry head;
 read_data(&head,sizeof(glb_fat_entry),1,input);
 if (strncmp(head.name,"GLIB FILE",9)!=0)
 {
  puts("The invalid format");
  exit(7);
 }
 if (head.length!=0)
 {
  puts("The invalid format");
  exit(7);
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
 char *buffer;
 size_t current,elapsed,block;
 elapsed=0;
 block=4096;
 buffer=get_memory(block);
 for (current=0;current<length;current+=block)
 {
  elapsed=length-current;
  if (elapsed<block)
  {
   block=elapsed;
  }
  read_data(buffer,block,sizeof(char),input);
  write_data(buffer,block,sizeof(char),output);
 }
 free(buffer);
}

void fast_data_dump(FILE *input,FILE *output,const size_t length)
{
 char *buffer;
 buffer=(char*)malloc(length);
 if (buffer==NULL)
 {
  data_dump(input,output,length);
 }
 else
 {
  read_data(buffer,length,sizeof(char),input);
  write_data(buffer,length,sizeof(char),output);
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

char *get_name(const char *path,const char *name)
{
 char *result;
 size_t length;
 length=strlen(path)+strlen(name);
 result=get_memory(length+1);
 sprintf(result,"%s%s",path,name);
 return result;
}

glb_fat_entry *read_table(FILE *input,const size_t amount)
{
 glb_fat_entry *table;
 table=(glb_fat_entry*)calloc(amount,sizeof(glb_fat_entry));
 check_memory(table);
 read_data(table,sizeof(glb_fat_entry),amount,input);
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