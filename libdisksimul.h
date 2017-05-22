#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>



int ds_init(char* filename, int sector_size, int number_sectors, int format);
int ds_read_sector(int sector_number, void *data, int sector_size);
int ds_write_sector(int sector_number, void *data, int sector_size);
void ds_stop();

