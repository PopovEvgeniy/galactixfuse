#pragma pack(push, 1)
typedef struct
{
 char signature[22];
 unsigned long int amount:32;
 unsigned short int junk:16;
} glb_head;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
 unsigned short int junk:16;
 char name[22];
 unsigned long int offset:32;
 unsigned short int length:16;
} glb_fat_entry;
#pragma pack(pop)