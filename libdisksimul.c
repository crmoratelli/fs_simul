#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "libdisksimul.h"

/* Simple library to simul read/write access to disk sectors. */
 
static FILE* simulfile =  NULL;

/**
 * @brief Disk Simulator Init.
 * 
 * Create or open (if it already exist) the simulation file.
 * 
 * @param filename Name of the input/output file.
 * @param sector_size Sector size in number of bytes.
 * @param number_sector Total number of sectors.
 * @param format Force create new file.
 * @return Return 0 on success, otherwise error.
 */
int ds_init(char* filename, int sector_size, int number_sectors, int format){
	struct stat b;
	
	if(format == 0){
		/* Check if the file already exists */
		if( stat(filename, &b) == 0){
			/* File exists, open for read/write. */
			if( (simulfile = fopen(filename, "r+b")) == NULL){
				/* error openning the file */
				perror("fopen: ");
				return 1;
			}
			return 0;
		}
		return 1;
	}

	/* File doesn't exist initialize it. */
	
	/* Create file  */
	if( (simulfile = fopen(filename, "w")) == NULL){
		/* error openning the file */
		perror("fopen: ");
		return 1;
	}
	
	/* Set file size */
	ftruncate(fileno(simulfile), (sector_size*number_sectors));
	
	fclose(simulfile);
	
	/* Reopen the file for input/output */
	if( (simulfile = fopen(filename, "r+b")) == NULL){
		/* error openning the file */
		perror("fopen: ");
		return 1;
	}
	
	return 0;
}

/**
 * Disk Simulator Read Sector.
 * 
 * Read a sector and load the data to the memory in data.
 * 
 * @param sector_number Number of the sector.
 * @param data Pointer to buffer to store the data.
 * @param sector_size Sector size in bytes.
 * @return 0 if success, otherwise error.
 */
int ds_read_sector(int sector_number, void *data, int sector_size){
	int ret;
	/* locate the sector .*/
	if ( (ret = fseek(simulfile, sector_number*sector_size, SEEK_SET)) != 0){
		return ret;
	}
	
	/* read the sector the memory buffer pointed by data. */
	if ( (ret = fread(data, sizeof(char), sector_size, simulfile)) == 0){
		return ret;
	}
	
	return 0;
}

/**
 * Disk Simulator Write Sector.
 * 
 * Write a sector from data in memory.
 * 
 * @param sector_number Number of the sector.
 * @param data Pointer to buffer to store the data.
 * @param sector_size Sector size in bytes.
 * @return 0 if success, otherwise error.
 */
int ds_write_sector(int sector_number, void *data, int sector_size){
	int ret;
	/* locate the sector .*/
	if ( (ret = fseek(simulfile, sector_number*sector_size, SEEK_SET)) != 0){
		return ret;
	}
	
	/* load the sector to the memory buffer pointed by data. */
	if ( (ret = fwrite(data, sizeof(char), sector_size, simulfile)) == 0){
		return ret;
	}
	
	return 0;
}

/**
 * Disk Simulator Stop.
 * 
 * Stop disk simulation. 
 * 
 * @param fp File pointer to the I/O file.
 */
void ds_stop(){
	fclose(simulfile);
	simulfile = NULL;
}
