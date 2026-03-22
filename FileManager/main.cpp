#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "UsedDefinitions.h"

int sim_fat[4][100];
int backup_sim_fat[4][100];
char sim_disk[4][100];
int userChoice;
int freshChoice;
int current_choice;
bool self_create_file = false;
bool self_create_item = false;
bool delete_once = false;
char waste = '0';

extern void initialize_file(Fileblock selfDefinition[4]);
extern void initialize_folderitem(FolderItem folder_item[4], Fileblock opeBlocks[4]);
extern void initialize_simfat(int sim_fat[100]);
extern void initialize_simdisk(char sim_disk[100]);

extern void get_file_fat(int sim_fat[100], FolderItem block);
extern void get_file_disk(int sim_fat[100], char* sim_disk, FolderItem block);

extern int drawTitle(Fileblock stimuFileBlock[4],
					FolderItem stimuFolderItem[4], int commandChoice);

int main()
{
	srand(time(0));
	//首先初始化需要的文件
	int returnChoice,circleTime;
	Fileblock stimuFileBlock[4];
	FolderItem stimuFolderItem[4];

IF_REFRESH:
	system("cls");
	returnChoice = 0;
	userChoice = 0;
	freshChoice = 0;
	current_choice = 0;
	self_create_file = false;
	self_create_item = false;
	delete_once = false;

	initialize_file(stimuFileBlock);//初始化文件  
	initialize_folderitem(stimuFolderItem,stimuFileBlock);//初始化文件夹
	//初始化FAT和磁盘
	for (circleTime = 0; circleTime < 4; ++circleTime) {
		initialize_simfat(sim_fat[circleTime]);
		initialize_simdisk(sim_disk[circleTime]);
	}
	//获得文件和对应磁盘
	for (circleTime = 0; circleTime < 3; ++circleTime) {
		get_file_fat(sim_fat[circleTime], stimuFolderItem[circleTime]);
		get_file_disk(sim_fat[circleTime], sim_disk[circleTime],
						stimuFolderItem[circleTime]);
	}
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 100; j++)
			backup_sim_fat[i][j] = sim_fat[i][j];

	RESHOW_AND_OPERATE:
	returnChoice = drawTitle(stimuFileBlock, stimuFolderItem,userChoice);
	switch (returnChoice) {
		case 0:
			break;
		case 1: {
			goto IF_REFRESH; 
			break;
		}
		case 2: {
			goto RESHOW_AND_OPERATE; 
			break;
		}
	}
	return 0;

}