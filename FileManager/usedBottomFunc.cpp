#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "UsedDefinitions.h"

//获取随机字母（大写）
char RandomCharacter() {
    int asci_of_char;
    while (1)
    {
        asci_of_char = rand() % 91;
        if (asci_of_char < 65)
            continue;
        else
            break;
    }
    return (char)asci_of_char;
}

//获取随机数
int RandomInt() {
    int ranint = rand();
    return ranint;
}

//给文件取名函数
void get_file_name(Fileblock* input, int i) {
    switch (i) {
        case 1: {
            strcpy_s(input->filename, "first");
            break;
        }
        case 2: {
            strcpy_s(input->filename, "second");
            break;
        }
        case 3: {
            strcpy_s(input->filename, "third");
            break;
        }
    }
}

//文件和目录项相互转化的函数
FolderItem block_to_item(Fileblock* block) {
    FolderItem item;
    strcpy_s(item.filename, block->filename);
    item.block_number = block->block_number;
    return item;
}
//获得文件块标签
char get_unique_tag() {
    char tag;
    tag = RandomCharacter();
    return tag;
}
Fileblock item_to_block(FolderItem item) {
    Fileblock block;
    int cirTime, circle;
    strcpy_s(block.filename, item.filename);
    block.block_number = item.block_number;
    for (cirTime = 0; cirTime < block.block_number; ++cirTime) {
        block.file_content[cirTime] = get_unique_tag();
        for (circle = 0; circle < cirTime; circle++)
            if (block.file_content[circle] ==
                block.file_content[cirTime]) {
                cirTime--;
                break;
            }
    }
    return block;
}


//获得仿真文件
void initialize_file(Fileblock selfDefinition[4]) {
    int cirTime, circle;
    for (int i = 0; i < 3; ++i) {
        selfDefinition[i].block_number = RandomInt() % 6 + 2;
        for (cirTime = 0; cirTime < selfDefinition[i].block_number; ++cirTime) {
            selfDefinition[i].file_content[cirTime] = get_unique_tag();
            for (circle = 0; circle < cirTime; circle++)
                if (selfDefinition[i].file_content[circle] ==
                    selfDefinition[i].file_content[cirTime]) {
                    cirTime--;
                    break;
                }
        }
        get_file_name(&selfDefinition[i], i+1);
        selfDefinition[3].block_number = NULL;
        strcpy_s(selfDefinition[3].filename, "");
        strcpy_s(selfDefinition[3].file_content, "");
    }
}

//获得仿真文件夹
void initialize_folderitem(FolderItem folder_item[4],Fileblock opeBlocks[4]) {
    int i, j,k, tmpt;
    for (i = 0; i < 3; i++) {
        strcpy_s(folder_item[i].filename, opeBlocks[i].filename);
        for (k = 0; k < 9; k++)
            folder_item[i].file_content[k] = opeBlocks[i].file_content[k];
        tmpt = 1+RandomInt()%98;
        for (j = 0; j < i; j++)
            if (folder_item[j].first_index == tmpt){
                i--;
                break;
            }
        folder_item[i].first_index = tmpt;
        folder_item[i].block_number = opeBlocks[i].block_number;
    }
    folder_item[3].block_number =0;
    strcpy_s(folder_item[3].filename, "");
    folder_item[3].first_index = 0;
}

//初始化FAT表，所有元素初始值为0，并将第一个元素设为100
void initialize_simfat(int sim_fat[100]) {
    int i;
    for (i = 1; i < 100; i++) {
        sim_fat[i] = 0;
    }
    sim_fat[0] = 100;
}
//初始化磁盘区域,所有元素初始值为0
void initialize_simdisk(char sim_disk[100]) {
    int i;
    for (i = 0; i < 100; i++) 
        sim_disk[i] = NULL;
}
