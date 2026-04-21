/*
This code is based on the format description from the DOS Game Modding Wiki:
https://moddingwiki.shikadi.net/wiki/GLB_Format_(Galactix)
*/

#pragma pack(push, 1)
typedef struct
{
 unsigned int offset;
 char name[22];
 unsigned short int length;
} glb_fat_entry;
#pragma pack(pop)