#define  _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <string.h>
#include "UsedDefinitions.h"

char selfNatureNum[12] = { '0','1','2','3','4','5','6','7','8','9','\0'};

extern int sim_fat[4][100];
extern char sim_disk[4][100];
extern int freshChoice;
extern int current_choice;
extern bool self_create_file;
extern bool self_create_item;

extern void initialize_simfat(int sim_fat[100]);
extern void RightBlock(FolderItem opeItem[4], Fileblock opeBlock[4]);
extern void get_file_fat(int sim_fat[100], FolderItem block);
extern void change_disk_statu(char filedisk[100]);

extern Fileblock item_to_block(FolderItem item);

void drawLeftOn(Fileblock stimuFileBlock, int time) {
	int width1 = 100 / 2 - textwidth(stimuFileBlock.filename) / 2;
	int height1 = 20 / 2 - textheight(stimuFileBlock.filename) / 2;

	//左上矩形
	if (time) {
		setfillcolor(RGB(115, 115, 115));
		for (int i = 0; i < stimuFileBlock.block_number; i++) {
			fillrectangle(30 + 35 * i, 140, 60 + 35 * i, 170);
		}
		settextstyle(18, 0, "楷体");
		char arr2[30];
		_itoa(stimuFileBlock.block_number, arr2, 10);
		int width2 = 40 / 2 - textwidth(arr2) / 2;
		int height2 = 20 / 2 - textheight(arr2) / 2;
		outtextxy(width1 + 72, height1 + 60, stimuFileBlock.filename);
		outtextxy(width2 + 230, height2 + 60, arr2);
		settextstyle(30, 0, "楷体");
		for (int i = 0; i < stimuFileBlock.block_number; i++)
			outtextxy(38 + 35 * i, 140, stimuFileBlock.file_content[i]);
	}
	if (!time) {
		setlinecolor(BLUE);
		fillrectangle(10, 10, 320, 220);
		rectangle(20, 40, 280, 210);
		rectangle(72, 60, 172, 80);
		rectangle(230, 60, 270, 80);
		settextcolor(BLACK);
		settextstyle(18, 0, "楷体");
		setbkmode(TRANSPARENT);
		outtextxy(25, 20, "【仿真】文件");
		outtextxy(35, 60, "文件");
		outtextxy(194, 60, "块数");
		setfillcolor(WHITE);
	}
}

void drawRightOn(FolderItem stimuFolderItem[4]) {
	//右上矩形
	char Number[3][60], temp[30];
	fillrectangle(340, 10, 685, 220);
	settextstyle(18, 0, "楷体");
	outtextxy(355, 20, "【仿真】目录/文件夹");
	rectangle(350, 40, 670, 210);
	outtextxy(360, 60, "文件名------首块号------块数目");

	settextstyle(15, 0, "宋体");
	setlinecolor(RGB(124, 184, 194));
	line(360, 80, 650, 80);

	//初始化第n个文件
	for (int i = 0; i < 3; i++) {
		if (0==strcmp(stimuFolderItem[i].filename , "delete"))
			break;
		_itoa(stimuFolderItem[i].first_index, temp, 10);
		strcpy(Number[i], stimuFolderItem[i].filename);
		strcat(Number[i], "--------");
		strcat(Number[i], temp);
		_itoa(stimuFolderItem[i].block_number, temp, 10);
		strcat(Number[i], "--------");
		strcat(Number[i], temp);
		line(360, 110+30*i, 650, 110+30*i);
		outtextxy(360, 90+30*i, Number[i]);
	}
}

void drawRightOn2(FolderItem stimuFolderItem[4]) {
	char temp[30], Number[60];
	drawRightOn(stimuFolderItem);
	_itoa(stimuFolderItem[3].first_index, temp, 10);
	strcpy(Number, stimuFolderItem[3].filename);
	strcat(Number, "--------");
	strcat(Number, temp);
	_itoa(stimuFolderItem[3].block_number, temp, 10);
	strcat(Number, "--------");
	strcat(Number, temp);
	line(360, 200, 600, 200);
	outtextxy(360, 180, Number);
}


void drawLeftUnder(int time,int simfat[100]) {
	//左下矩形

	//预处理
	char charfat[5];
	int i = 0, temp1 = 0, temp2 = 0;

	if (!time) {
		setlinecolor(BLACK);
		fillrectangle(10, 240, 320, 655);
		settextstyle(18, 0, "宋体");
		outtextxy(25, 250, "【仿真】FAT表");
		for (i = 0; i < 11; i++)
		{
			line(50, 300+35*i, 300, 300+35*i);
			line(50+25*i, 300, 50+25*i, 650);
			outtextxy(55+25*i, 280, selfNatureNum[i]);
			outtextxy(30, 305+35*i, selfNatureNum[i]);
		}
	}

	if (time) {
		settextstyle(12, 0, "宋体");
		for (i=0; i < 100; i++) {
			_itoa(simfat[i], charfat, 10);
			if (!strcmp(charfat, "128"))
				strcpy(charfat, "FF");
			outtextxy(56 + 25 * temp1, 305 + 35 * temp2, charfat);
			temp1++;
			if (!((i + 1) % 10)) {
				temp2++;
				temp1 = 0;
			}
		}
	}
}


void drawRightUnder(int time,char sim_disk[100],int sim_fat[100],FolderItem item) {
	//右下矩形
	int i,ten_bit,one_bit,current_index;
	if (!time) {
		setlinecolor(BLACK);
		fillrectangle(340, 240, 685, 655);
		settextstyle(18, 0, "宋体");
		outtextxy(355, 250, "【仿真】磁盘区域");
		setlinecolor(RGB(195, 195, 195));
		for (i = 0; i < 11; i++) {
			line(380, 300 + 35 * i, 680, 300 + 35 * i);
			line(380 + 30 * i, 300, 380 + 30 * i, 650);
			outtextxy(386+i*30, 280, selfNatureNum[i]);
			outtextxy(360, 305+35*i, selfNatureNum[i]);
		}
	}
	if (time) {
		current_index = item.first_index;
		for (i = 0; i < item.block_number; ++i) {
			setfillcolor(RGB(115, 115, 115));
			ten_bit = current_index / 10;
			one_bit = current_index % 10;
			fillrectangle(380 + 30 * one_bit, 300 + 35 * ten_bit,
							410 + 30 * one_bit, 335 + 35 * ten_bit);
			settextstyle(20, 0, "宋体");
			outtextxy(390+30*one_bit, 307+35*ten_bit, item.file_content[i]);
			current_index = sim_fat[current_index];
		}
	}
}

int drawTitle(Fileblock stimuFileBlock[4], FolderItem stimuFolderItem[4], int commandChoice) {
	int go_back_choice = 0;
	//printf("%d\n", current_choice);

	//创建一个窗口，确定窗口大小
	initgraph(900, 700, 1);
	//设置背景颜色
	setbkcolor(YELLOW);
	cleardevice();  //清屏
	//设置填充颜色
	setfillcolor(WHITE);

	if (commandChoice == 0) {
		drawLeftOn(*stimuFileBlock, FILE_OFF);
		drawRightOn(stimuFolderItem);
		drawLeftUnder(FILE_OFF,sim_fat[0]);
		drawRightUnder(FILE_OFF,sim_disk[0], sim_fat[0],stimuFolderItem[0]);
		RightBlock(stimuFolderItem, stimuFileBlock);
	}
	if (commandChoice == 1) {
		current_choice = 1;
		stimuFileBlock[3] = item_to_block(stimuFolderItem[3]);
		drawLeftOn(*stimuFileBlock, FILE_OFF);
		drawRightOn2(stimuFolderItem);
		drawLeftUnder(FILE_OFF,sim_fat[0]);
		drawRightUnder(FILE_OFF,sim_disk[0], sim_fat[0], stimuFolderItem[0]);
		RightBlock(stimuFolderItem, stimuFileBlock);
	}
	if (commandChoice == 2) {
		current_choice = 2;
		if (!self_create_file&&!self_create_item) {
			drawLeftOn(*stimuFileBlock, FILE_OFF);
			drawRightOn(stimuFolderItem);
			drawLeftUnder(FILE_OFF, sim_fat[0]);
			drawRightUnder(FILE_OFF, sim_disk[0], sim_fat[0], stimuFolderItem[0]);
			RightBlock(stimuFolderItem, stimuFileBlock);
		}
		else {
			drawLeftOn(*stimuFileBlock, FILE_OFF);
			drawRightOn2(stimuFolderItem);
			drawLeftUnder(FILE_OFF, sim_fat[0]);
			drawRightUnder(FILE_OFF, sim_disk[0], sim_fat[0], stimuFolderItem[0]);
			RightBlock(stimuFolderItem, stimuFileBlock);
		}
	}
	if (commandChoice == 5) {
		current_choice = 5;
		drawLeftOn(*stimuFileBlock, FILE_OFF);
		drawRightOn2(stimuFolderItem);
		drawLeftUnder(FILE_OFF, sim_fat[0]);
		drawRightUnder(FILE_OFF, sim_disk[0], sim_fat[0], stimuFolderItem[0]);
		RightBlock(stimuFolderItem, stimuFileBlock);
	}
	if (commandChoice == 6) {
		current_choice = 6;
		if (!self_create_file&&!self_create_item) {
			strcpy_s(stimuFileBlock[2].filename, "delete");
			strcpy_s(stimuFileBlock[2].file_content, "");
			stimuFileBlock[2].block_number = NULL;
			strcpy_s(stimuFolderItem[2].filename, "delete");
			strcpy_s(stimuFolderItem[2].file_content, "");
			stimuFolderItem[2].block_number = NULL;
			stimuFolderItem[2].first_index = NULL;
		}
		else {
			strcpy_s(stimuFileBlock[3].filename, "delete");
			strcpy_s(stimuFileBlock[3].file_content, "");
			stimuFileBlock[3].block_number = NULL;
			strcpy_s(stimuFolderItem[3].filename, "delete");
			strcpy_s(stimuFolderItem[3].file_content, "");
			stimuFolderItem[3].block_number = NULL;
			stimuFolderItem[3].first_index = NULL;
		}

		drawLeftOn(*stimuFileBlock, FILE_OFF);
		drawRightOn(stimuFolderItem);
		drawLeftUnder(FILE_OFF, sim_fat[0]);
		drawRightUnder(FILE_OFF, sim_disk[0], sim_fat[0], stimuFolderItem[0]);
		RightBlock(stimuFolderItem, stimuFileBlock);
	}
	if (commandChoice == 9) {
		current_choice = 9;
		if (!self_create_file && !self_create_item) {
			drawLeftOn(*stimuFileBlock, FILE_OFF);
			drawRightOn(stimuFolderItem);
			drawLeftUnder(FILE_OFF, sim_fat[0]);
			drawRightUnder(FILE_OFF, sim_disk[0], sim_fat[0], stimuFolderItem[0]);
			RightBlock(stimuFolderItem, stimuFileBlock);
		}
		else {
			drawLeftOn(*stimuFileBlock, FILE_OFF);
			drawRightOn2(stimuFolderItem);
			drawLeftUnder(FILE_OFF, sim_fat[0]);
			drawRightUnder(FILE_OFF, sim_disk[0], sim_fat[0], stimuFolderItem[0]);
			RightBlock(stimuFolderItem, stimuFileBlock);
		}
	}
	if (commandChoice == 10) {
		int temp = current_choice - 13;
		current_choice =10;
		if (!self_create_file && !self_create_item) {
			drawLeftOn(*stimuFileBlock, FILE_OFF);
			drawRightOn(stimuFolderItem);
			drawLeftUnder(FILE_OFF, sim_fat[0]);
			drawRightUnder(FILE_OFF, sim_disk[0], sim_fat[0], stimuFolderItem[0]);
			change_disk_statu(sim_disk[temp]);
			RightBlock(stimuFolderItem, stimuFileBlock);
		}
		else {
			drawLeftOn(*stimuFileBlock, FILE_OFF);
			drawRightOn2(stimuFolderItem);
			drawLeftUnder(FILE_OFF, sim_fat[0]);
			drawRightUnder(FILE_OFF, sim_disk[0], sim_fat[0], stimuFolderItem[0]);
			change_disk_statu(sim_disk[temp]);
			RightBlock(stimuFolderItem, stimuFileBlock);
		}
	}
	if (commandChoice == 12) {
		current_choice = 12;
		if (!self_create_file && !self_create_item) {
			drawLeftOn(*stimuFileBlock, FILE_OFF);
			drawRightOn(stimuFolderItem);
			drawLeftUnder(FILE_OFF, sim_fat[0]);
			drawRightUnder(FILE_OFF, sim_disk[0], sim_fat[0], stimuFolderItem[0]);
			RightBlock(stimuFolderItem, stimuFileBlock);
		}
		else {
			drawLeftOn(*stimuFileBlock, FILE_OFF);
			drawRightOn2(stimuFolderItem);
			drawLeftUnder(FILE_OFF, sim_fat[0]);
			drawRightUnder(FILE_OFF, sim_disk[0], sim_fat[0], stimuFolderItem[0]);
			RightBlock(stimuFolderItem, stimuFileBlock);
		}
	}
	if (commandChoice == 13) {
		drawLeftOn(stimuFileBlock[0], FILE_OFF);
		if (self_create_file || self_create_item)
			drawRightOn2(stimuFolderItem);
		else
			drawRightOn(stimuFolderItem);
		drawLeftUnder(FILE_OFF,sim_fat[0]);
		drawRightUnder(FILE_OFF,sim_disk[0], sim_fat[0], stimuFolderItem[0]);
		drawLeftOn(stimuFileBlock[0], FILE_ON);
		drawLeftUnder(FILE_ON,sim_fat[0]);
		drawRightUnder(FILE_ON,sim_disk[0], sim_fat[0],stimuFolderItem[0]);
		RightBlock(stimuFolderItem, stimuFileBlock);
	}
	if (commandChoice == 14) {
		drawLeftOn(stimuFileBlock[1], FILE_OFF);
		if (self_create_file || self_create_item)
			drawRightOn2(stimuFolderItem);
		else
			drawRightOn(stimuFolderItem);
		drawLeftUnder(FILE_OFF,sim_fat[1]);
		drawRightUnder(FILE_OFF,sim_disk[1], sim_fat[1], stimuFolderItem[1]);
		drawLeftOn(stimuFileBlock[1], FILE_ON);
		drawLeftUnder(FILE_ON, sim_fat[1]);
		drawRightUnder(FILE_ON, sim_disk[1], sim_fat[1], stimuFolderItem[1]);
		RightBlock(stimuFolderItem, stimuFileBlock);
	}
	if (commandChoice == 15) {
		drawLeftOn(stimuFileBlock[2], FILE_OFF);
		if (self_create_file || self_create_item)
			drawRightOn2(stimuFolderItem);
		else
			drawRightOn(stimuFolderItem);
		drawLeftUnder(FILE_OFF, sim_fat[2]);
		drawRightUnder(FILE_OFF, sim_disk[2], sim_fat[2], stimuFolderItem[2]);
		drawLeftOn(stimuFileBlock[2], FILE_ON);
		drawLeftUnder(FILE_ON, sim_fat[2]);
		drawRightUnder(FILE_ON, sim_disk[2], sim_fat[2], stimuFolderItem[2]);
		RightBlock(stimuFolderItem, stimuFileBlock);
	}
	if (commandChoice == 16) {
		drawLeftOn(stimuFileBlock[3], FILE_OFF);
		drawRightOn2(stimuFolderItem);
		drawLeftUnder(FILE_OFF, sim_fat[3]);
		drawRightUnder(FILE_OFF, sim_disk[3], sim_fat[3], stimuFolderItem[3]);
		if (self_create_file||self_create_item) {
			drawLeftOn(stimuFileBlock[3], FILE_ON);
			drawLeftUnder(FILE_ON, sim_fat[3]);
			drawRightUnder(FILE_ON, sim_disk[3], sim_fat[3], stimuFolderItem[3]);
		}
		RightBlock(stimuFolderItem, stimuFileBlock);
	}
	FRESH_ZONE:
	if (freshChoice == 2)
		go_back_choice = 1;
	if (freshChoice == 1)
		go_back_choice = 2;
	closegraph();
	return go_back_choice;
}