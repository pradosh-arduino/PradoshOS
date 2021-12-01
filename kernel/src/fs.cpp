/*
#######################################
#                                     #
# VFS (sort of)                       #
#                                     #
# This Code is from Peko              #
# HUGE THANKS TO HER                  #
#                                     #
#######################################
*/

#include "fs.h"
#include "MemoryMgmt.h"
#include "malloc.h"
#include "cstr.h"
#include "addons.h"

char* files_adress[100] = {0};
int files_length[100] = {0};
int address_index = 0;
int f_index = 0;
char *file_names[100];
char *fs;
void init_fs()
{
 
}
void create_file(char *name, char *content)
{
  int content_length = strlen(content);
  char *temp = (char *)(fs + address_index);
  for (int i = 0; i < content_length; i++)
  {
    temp[i] = content[i];
  }
  files_adress[f_index] = temp;
  files_length[f_index] = content_length;
  set((int *)file_names[f_index], (int *)name);
  f_index += 1;
  address_index += content_length + 1;
}
char *read_file_at(int index)
{
  char *temp = files_adress[index];
  return temp;
}
char *read_file(char *name)
{
  for (int i = 0; i < f_index; i++)
  {
    if (equal(file_names[i], name))
    {
      return read_file_at(i);
    }
  }
  return "\0\1";
}
void write_file_at(int at, char *content, int content_length)
{
  char *temp = (char *)(1 + fs + address_index);
  for (int i = 0; i < content_length; i++)
  {
    temp[i] = content[i];
  }
  files_adress[at] = temp;
  files_length[at] = content_length;
  address_index += content_length + 1;
}
void *write_file(char *name, char *content, int content_length)
{
  for (int i = 0; i < f_index; i++)
  {
    if (equal(file_names[i], name))
    {
      write_file_at(i, content, content_length);
    }
  }
}
void delete_file_at(int at)
{
  for (int i = at; i < f_index; i++)
  {
    file_names[i] = file_names[i + 1];
    files_adress[i] = files_adress[i + 1];
    files_length[i] = files_length[i + 1];
  }
  f_index--;
}
void delete_file(char *name)
{
  for (int i = 0; i < f_index; i++)
  {
    if (equal(file_names[i], name))
    {
      delete_file_at(i);
    }
  }
}
int get_file_size_at(int at)
{
  return files_length[at];
}

int get_file_size(char *name)
{
  for (int i = 0; i < f_index; i++)
  {
    if (equal(file_names[i], name))
    {
      return get_file_size_at(i);
    }
  }
}
void rename_file(char *name, char *to)
{
  for (int i = 0; i < f_index; i++)
  {
    if (equal(file_names[i], name))
    {
      set((int *)file_names[i], (int *)to);
    }
  }
}
char *get_file_name_at(int at)
{
  return file_names[at];
}
int does_file_exists(char *name)
{
  for (int i = 0; i < f_index; i++)
  {
    if (equal(file_names[i], name))
    {
      return 1;
    }
  }
  return 0;
}
char *get_file_type_of(char *fn)
{
  int point_is_on = 0;
  for (int i = 0; i < 32; i++)
  {
    if (fn[i] == '.')
    {
      point_is_on = i;
      break;
    }
  }
  return (char *)(fn + point_is_on + 1);
}
void create_file_from_ramdisk()
{
 //int ta = 0;
 //for (int i = 0; i < total_files; i++)
 //{
 //  create_file(names[i], (char *)0x0 + (ramdisk_start + ta), file_lengths[i]);
 //  ta += file_lengths[i];
 //}
}

void ls(){
  for(int i = 0; i < f_index; i++){
    GlobalRenderer->Print(file_names[i]);
    GlobalRenderer->PutChar(' ');
    GlobalRenderer->Print(to_string((float)get_file_size_at(i)));
    GlobalRenderer->Print(" Bytes");
    GlobalRenderer->Next();
  }
}

int length(const char* abc)
{
	for (int i = 0;; i++)
		if (abc[i] == '\0')
			return i;
}

int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}
int equal(const char* a, const char* b)
{
	for (int i = 0; i < max(length(a), length(b)); i++)
		if (a[i] != b[i])
			return 0;
	return 1;
}
void set(int *a, int *b)
{
	for (int i = 0; b[i] != 0; i++)
	{
		a[i] = b[i];
	}
}

char *malloc(int len)
{
   int last_index;
	int out = last_index;
	char *temp = (char *)0x0;
	for (int i = 0; i < len; i++)
	{
		temp[last_index + i] = 0;
	}
	last_index += len;
	return (char *)out;
}