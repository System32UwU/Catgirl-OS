#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#define MAX_FILES 32
#define MAX_FILENAME 32
#define MAX_FILE_SIZE 4096
#define SECTOR_SIZE 512

typedef struct {
    char name[MAX_FILENAME];
    unsigned int size;
    unsigned int start_sector;
    unsigned int flags;  // 0x01 = directory, 0x02 = file
    unsigned int created_time;
    unsigned int modified_time;
} file_entry_t;

typedef struct {
    unsigned char boot_signature[3];
    char oem_name[8];
    unsigned short bytes_per_sector;
    unsigned char sectors_per_cluster;
    unsigned short reserved_sectors;
    unsigned char num_fats;
    unsigned short root_entries;
    unsigned short total_sectors;
    unsigned char media_descriptor;
    unsigned short sectors_per_fat;
    unsigned short sectors_per_track;
    unsigned short num_heads;
    unsigned int hidden_sectors;
    unsigned int total_sectors_32;
} __attribute__((packed)) boot_sector_t;

typedef struct {
    file_entry_t files[MAX_FILES];
    unsigned int file_count;
    unsigned int total_size;
} filesystem_t;

extern filesystem_t global_fs;

// Filesystem operations
void init_filesystem(void);
int fs_create_file(const char* filename, const unsigned char* data, unsigned int size);
int fs_delete_file(const char* filename);
int fs_read_file(const char* filename, unsigned char* buffer, unsigned int max_size);
int fs_list_files(void);
int fs_find_file(const char* filename);

#endif
