#include "usedDefinitions.h"
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <graphics.h>

extern char RandomCharacter();
extern int RandomInt();
extern char get_unique_tag();
extern int sim_fat[4][100];
extern char sim_disk[4][100];
extern bool self_create_file;

//计算磁盘剩余空间
int count_available_space(int sim_fat[100]) {
	int i, num_available_blocks = 0;
	for (i = 0; i < 100; i++)
		if (sim_fat[i] == 0)
			num_available_blocks++;
	return num_available_blocks * BLOCK_SIZE;
}

//void print_the_space() {
//	int i, k;
//	printf("The FAT is like this:\n");
//	for (k = 0; k < 100; ++k)
//		if (sim_fat[k] == 128)
//			break;
//	for (i = 0; i < k; i++) {
//		printf("%d\t", sim_fat[i]);
//		if (!((i + 1) % 10))
//			printf("\n");
//	}
//	printf("FF\t");
//	i++;
//	for (i; i < 100; i++) {
//		printf("%d\t", sim_fat[i]);
//		if (!((i + 1) % 10))
//			printf("\n");
//	}
//	printf("\navailable space:%d\n", count_available_space(sim_fat));
//}

//获得文件的fat表和磁盘
void get_file_fat(int sim_fat[100], FolderItem block) {
	int i, temp, randomnum;
	temp = block.first_index;
	for (i = 1; i < block.block_number; i++) {
	AGAIN_:
		randomnum = RandomInt() % 100 + 1;
		if (sim_fat[randomnum])
			goto AGAIN_;
		if (temp == randomnum)
			goto AGAIN_;
		sim_fat[temp] = randomnum;
		temp = sim_fat[temp];
	}
	sim_fat[temp] = 128;
}
void get_file_disk(int sim_fat[100], char* sim_disk, FolderItem block) {
    int circleTime = 0,temp=block.first_index;
    for (circleTime; circleTime < block.block_number; ++circleTime) {
        sim_disk[temp]=block.file_content[circleTime];
        temp = sim_fat[temp];
    }
}


void insert_folder_item(FolderItem opeFolderItem1[4]) {
    FolderItem newItem;
    int cirTime = 0,circle=0, success = 0, temp, fal = 1;
    printf("Input the name of item:");
    fgets(newItem.filename, 50, stdin);
    newItem.filename[strlen(newItem.filename) - 1] = NULL;
    printf("Input the blocknums:");
    scanf_s("%d", &newItem.block_number);
    getchar();
    if (newItem.block_number > 8) {
        printf("Too large to create!");
        return;
    }
    for(int i=0;i<3;i++)
        if (!strcmp(newItem.filename, opeFolderItem1[i].filename)) {
            printf("Invalid name as it exists!");
            return;
        }
    while (fal) {
        temp = 1+RandomInt() % 98;
        for (cirTime = 0; cirTime < 3; cirTime++) {
            if (temp == opeFolderItem1[cirTime].first_index)cirTime = 3;
            if (cirTime == 2)
                fal = 0;
        }
    }
    for (cirTime = 0; cirTime < newItem.block_number; ++cirTime) {
        newItem.file_content[cirTime] = get_unique_tag();
        for (circle = 0; circle < cirTime; circle++)
            if (newItem.file_content[circle] ==
                newItem.file_content[cirTime]) {
                cirTime--;
                break;
            }
    }
    newItem.first_index = temp;
    opeFolderItem1[3] = newItem;
    get_file_fat(sim_fat[3], newItem);
    get_file_disk(sim_fat[3], sim_disk[3],newItem);
}

void retrieve_folder_item(FolderItem opeFolderItem1[4]) {
    //initialize_folderitem(opeFolderItem1);//初始化一张FAT表，包括三个内容文件
    char newFilename[50];
    int cirTime, result;
    printf("filename\tfirstindex\tblocknum\n");
    for (cirTime = 0; cirTime < 3; cirTime++) {
        printf("%s\t\t%d\t\t%d\n", opeFolderItem1[cirTime].filename,
            opeFolderItem1[cirTime].first_index,
            opeFolderItem1[cirTime].block_number);
    }
    printf("Input the name of the file you want:");
    fgets(newFilename, 50, stdin);
    newFilename[strlen(newFilename) - 1] = NULL;
    for (cirTime = 0; cirTime < 3; cirTime++) {
        result = strcmp(newFilename, opeFolderItem1[cirTime].filename);
        if (0 == result) {
            printf("Find the file.");
            cirTime = 0;
            break;
        }
    }
    if (cirTime)
        printf("No such file!\n");
}

//在查找项目的基础上增加的功能
void delete_folder_item(FolderItem* opeItem,Fileblock* opeBlock) {
    char newFilename[50];
    int cirTime, result,circleTime=2;
    if (self_create_file)
        circleTime = 3;
    printf("Input the name of file you wanna delete:");
    fgets(newFilename, 50, stdin);
    newFilename[strlen(newFilename) - 1] = NULL;
    //查找是否存在对应的表，是则删除再打印，否则不操作，只提示
    for (cirTime = 0; cirTime < circleTime+1; cirTime++) {
        //判断是否存在对应项目
        result = strcmp(newFilename, opeItem[cirTime].filename);
        if (0 == result) {
            //将索引前移
            for (; cirTime < circleTime; ++cirTime) {
                strcpy_s(opeItem[cirTime].filename, opeItem[cirTime + 1].filename);
                for (int k = 0; k < opeItem[cirTime+1].block_number; k++)
                    opeItem[cirTime].file_content[k] = 
                        opeItem[cirTime+1].file_content[k];
                opeItem[cirTime].first_index = opeItem[cirTime + 1].first_index;
                opeItem[cirTime].block_number = opeItem[cirTime + 1].block_number;
                strcpy_s(opeBlock[cirTime].filename, opeBlock[cirTime + 1].filename);
                for (int k = 0; k < opeBlock[cirTime+1].block_number; k++)
                    opeBlock[cirTime].file_content[k] = 
                        opeBlock[cirTime+1].file_content[k];
                opeBlock[cirTime].block_number = opeBlock[cirTime + 1].block_number;
                strcpy_s(sim_disk[cirTime], sim_disk[cirTime + 1]);
                for (int i = 0; i<100; ++i)
                    sim_fat[cirTime][i] = sim_fat[cirTime + 1][i];
            }
            for (int temp = 0; temp < 100; temp++) {
                sim_fat[circleTime][temp] = 0;
                sim_disk[circleTime][temp] = NULL;
            }
            printf("Success.\n");
            break;
        }
    }
    if (circleTime+1 == cirTime)
        printf("No such file!\n");
}

//void file_operate(FolderItem opeFolderItem1[4]) {
//    int thechoice;
//    printf("Choose your operation:\n");
//    printf("1.insert 2.retrieve 3.delete\n");
//    scanf_s("%d", &thechoice);
//    getchar();
//    switch (thechoice)
//    {
//    case 1:
//        insert_folder_item(opeFolderItem1);
//        break;
//
//    case 2:
//        retrieve_folder_item(opeFolderItem1);
//        break;
//
//    case 3:
//        delete_folder_item(opeFolderItem1);
//        break;
//
//    default:
//        printf("Invalid choice.");
//        break;
//    }
//}

void change_block_label(Fileblock* blk, FolderItem* itm) {
    int label_num;
    char new_label;
    printf("Input the label number you want to change:");
    scanf_s("%d", &label_num);
    if (label_num > blk->block_number) {
        printf("No such block!\n");
        return;
    }
    getchar();
    label_num--;
    printf("Input the new label:");
    new_label = getchar();
    blk->file_content[label_num] = new_label;
    itm->file_content[label_num] = new_label;
    printf("\nSuccess!\n");
}

void clear_block_label(Fileblock* blk, FolderItem* itm) {
    int label_num;
    char new_label;
    printf("Input the label number you want to clear:");
    scanf_s("%d", &label_num);
    if (label_num > blk->block_number) {
        printf("No such block!\n");
        return;
    }
    getchar();
    label_num--;
    new_label = ' ';
    blk->file_content[label_num] = new_label;
    itm->file_content[label_num] = new_label;
    printf("\nSuccess!\n");
}

void change_disk_statu(char filedisk[100]) {
    int changenum,ten_bit,one_bit;
    printf("Input the disk number you want to change:");
    scanf_s("%d", &changenum);
    ten_bit = changenum / 10;
    one_bit = changenum - 10 * ten_bit;
    if (filedisk[changenum] != NULL) {
        setfillcolor(WHITE);
        fillrectangle(380 + 30 * one_bit, 300 + 35 * ten_bit,
            410 + 30 * one_bit, 335 + 35 * ten_bit);
    }
    else {
        setfillcolor(RGB(115, 115, 115));
        fillrectangle(380 + 30 * one_bit, 300 + 35 * ten_bit,
            410 + 30 * one_bit, 335 + 35 * ten_bit);
    }
}