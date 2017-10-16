#define SECTOR_SIZE		512
#define NUMBER_OF_SECTORS	2048
#define FILENAME 		"simul.fs"


/* Filesystem structures. */
/**
 * Sector 0.
 */
struct sector_0{
	unsigned int free_sectors_list;
	unsigned char unused[508];	
};

/**
 * File or directory entry. 
 */
struct file_dir_entry{
	unsigned int dir; 		/**< File or directory representation. Use 1 for directory 0 for file. */
	char name[20]; 			/**< File or directorty name. */
	unsigned int size_bytes; 	/**< Size of the file in bytes. Use 0 for directories. */
	unsigned int sector_start;	/**< Initial sector of the file ou sector of the directory table. */
};

/**
 * Directory table.
 */
struct table_directory{
	struct file_dir_entry entries[16]; 	/**< List of file or directories. */
};

/**
 * Sector data.
 */
struct sector_data{
	unsigned char data[508];	/**< File data. */
	unsigned int next_sector;	/**< Next sector. Use 0 if it is the last sector. */
};


int fs_format();
int fs_create(char* input_file, char* simul_file);
int fs_read(char* output_file, char* simul_file);
int fs_del(char* simul_file);
int fs_ls(char *dir_path);
int fs_mkdir(char* directory_path);
int fs_rmdir(char *directory_path);
int fs_free_map(char *log_f);

