/*
This code bases on the format description from DOS Game Modding Wiki:
https://moddingwiki.shikadi.net/wiki/GLB_Format_(Galactix)
*/

#pragma pack(push, 1)
typedef struct
{
 unsigned long int offset:32;
 char name[22];
 unsigned short int length:16;
} glb_fat_entry;
#pragma pack(pop)