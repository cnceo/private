#ifndef CRC32_H
#define CRC32_H                            1

unsigned long CalculateCrc32(const unsigned char *,unsigned long );
unsigned long Reflect(unsigned long , char );
void InitCrc32Table();


#endif


