//有关的宏定义
#define BLOCK_SIZE 64
#define MAX_BLOCKS 100
#define MAX_FILES 50

#define FILE_ON 1
#define FILE_OFF 0

//有关结构体定义
typedef struct {
	char filename[50];
	char file_content[9];
	int block_number;
}Fileblock;

typedef struct {
	char filename[50];
	char file_content[9];
	int block_number;
	int first_index;
}FolderItem;