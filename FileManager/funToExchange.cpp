#include <stdlib.h>
#include <stdio.h>
#include <graphics.h>
#include <easyx.h>
#include "UsedDefinitions.h"

extern int freshChoice;
extern bool self_create_file;
extern bool self_create_item;
extern bool delete_once;
extern int userChoice; 
extern int current_choice;

extern void insert_folder_item(FolderItem opeFolderItem1[4]);
extern void retrieve_folder_item(FolderItem opeFolderItem1[4]);
extern void delete_folder_item(FolderItem* opeItem, Fileblock* opeBlock);

extern void change_block_label(Fileblock* blk, FolderItem* itm);
extern void clear_block_label(Fileblock* blk, FolderItem* itm);

void RightBlock(FolderItem opeItem[4],Fileblock opeBlock[4]) {
	//功能按键
	int i = 3;

	setfillcolor(WHITE);
	setlinecolor(BLACK);
	settextstyle(18, 0, "宋体");
	outtextxy(700, 20, "【仿真】文件项");
	fillrectangle(700, 40, 860, 150);
	setfillcolor(BLACK);
	fillcircle(705, 55, 2);
	fillcircle(705, 80, 2);
	fillcircle(705, 105, 2);
	fillcircle(705, 130, 2);
	setfillcolor(RGB(207, 207, 207));
	fillroundrect(715, 45, 850, 65, 5, 5);
	fillroundrect(715, 70, 850, 90, 5, 5);
	fillroundrect(715, 95, 850, 115, 5, 5);
	fillroundrect(715, 120, 850, 140, 5, 5);
	settextstyle(12, 0, "宋体");
	char arr11[] = "创建文件";
	int width11 = 90 / 2 - textwidth(arr11) / 2;
	int height11 = 25 / 2 - textheight(arr11) / 2;
	outtextxy(width11 + 697, height11 + 45, arr11);
	char arr12[] = "更改文件块标签";
	int width12 = 90 / 2 - textwidth(arr12) / 2;
	int height12 = 25 / 2 - textheight(arr12) / 2;
	outtextxy(width12 + 715, height12 + 70, arr12);
	char arr13[] = "自动保存到磁盘";
	int width13 = 90 / 2 - textwidth(arr13) / 2;
	int height13 = 25 / 2 - textheight(arr13) / 2;
	outtextxy(width13 + 715, height13 + 95, arr13);
	char arr14[] = "自动读取文件";
	int width14 = 90 / 2 - textwidth(arr14) / 2;
	int height14 = 25 / 2 - textheight(arr14) / 2;
	outtextxy(width14 + 710, height14 + 120, arr14);

	setfillcolor(WHITE);
	settextstyle(18, 0, "宋体");
	outtextxy(700, 160, "【仿真】文件夹");
	fillrectangle(700, 180, 860, 265);
	setfillcolor(BLACK);
	fillcircle(705, 195, 2);
	fillcircle(705, 220, 2);
	fillcircle(705, 245, 2);
	setfillcolor(RGB(207, 207, 207));
	fillroundrect(715, 185, 850, 205, 5, 5);
	fillroundrect(715, 210, 850, 230, 5, 5);
	fillroundrect(715, 235, 850, 255, 5, 5);
	settextstyle(12, 0, "宋体");
	char arr21[] = "创建目录项";
	int width21 = 80 / 2 - textwidth(arr21) / 2;
	int height21 = 25 / 2 - textheight(arr21) / 2;
	outtextxy(width21 + 715, height21 + 185, arr21);
	char arr22[] = "删除目录项";
	int width22 = 80 / 2 - textwidth(arr22) / 2;
	int height22 = 25 / 2 - textheight(arr22) / 2;
	outtextxy(width22 + 715, height22 + 210, arr22);
	char arr23[] = "更改目录信息";
	int width23 = 80 / 2 - textwidth(arr23) / 2;
	int height23 = 25 / 2 - textheight(arr23) / 2;
	outtextxy(width23 + 715, height23 + 235, arr23);

	settextstyle(18, 0, "宋体");
	outtextxy(700, 270, "【仿真】FAT表");
	setfillcolor(WHITE);
	fillrectangle(700, 290, 860, 325);
	setfillcolor(BLACK);
	fillcircle(705, 305, 2);
	setfillcolor(RGB(207, 207, 207));
	fillroundrect(715, 295, 850, 315, 5, 5);
	settextstyle(12, 0, "宋体");
	char arr31[] = "更改表项";
	int width31 = 60 / 2 - textwidth(arr31) / 2;
	int height31 = 25 / 2 - textheight(arr31) / 2;
	outtextxy(width31 + 715, height31 + 295, arr31);

	setfillcolor(WHITE);
	settextstyle(18, 0, "宋体");
	outtextxy(700, 330, "【仿真】磁盘区域");
	fillrectangle(700, 350, 860, 460);
	setfillcolor(BLACK);
	fillcircle(705, 390, 2);
	fillcircle(705, 415, 2);
	fillcircle(705, 365, 2);
	fillcircle(705, 440, 2);
	setfillcolor(RGB(207, 207, 207));
	fillroundrect(715, 355, 850, 375, 5, 5);
	fillroundrect(715, 380, 850, 400, 5, 5);
	fillroundrect(715, 405, 850, 425, 5, 5);
	fillroundrect(715, 430, 850, 450, 5, 5);
	settextstyle(12, 0, "宋体");
	char arr41[] = "更改磁盘块标签";
	int width41 = 130 / 2 - textwidth(arr41) / 2;
	int height41 = 25 / 2 - textheight(arr41) / 2;
	outtextxy(width41 + 715, height41 + 355, arr41);
	char arr42[] = "更改磁盘块占用/非占用";
	int width42 = 130 / 2 - textwidth(arr42) / 2;
	int height42 = 25 / 2 - textheight(arr42) / 2;
	outtextxy(width42 + 715, height42 + 380, arr42);
	char arr43[] = "自动为已占用添加标签";
	int width43 = 130 / 2 - textwidth(arr43) / 2;
	int height43 = 25 / 2 - textheight(arr43) / 2;
	outtextxy(width43 + 715, height43 + 405, arr43);
	char arr44[] = "清除标签";
	int width44 = 130 / 2 - textwidth(arr44) / 2;
	int height44 = 25 / 2 - textheight(arr44) / 2;
	outtextxy(width44 + 715, height44 + 430, arr44);

	setfillcolor(WHITE);
	settextstyle(18, 0, "宋体");
	outtextxy(700, 470, "刷新");
	fillrectangle(700, 490, 860, 570);
	setfillcolor(BLACK);
	fillcircle(705, 510, 2);
	fillcircle(705, 545, 2);
	setfillcolor(RGB(207, 207, 207));
	fillroundrect(715, 495, 850, 525, 5, 5);
	fillroundrect(715, 530, 850, 560, 5, 5);
	settextstyle(12, 0, "宋体");
	char arr51[] = "点击刷新界面";
	char arr52[] = "点击重启应用程序";
	int width51 = 130 / 2 - textwidth(arr51) / 2;
	int height51 = 25 / 2 - textheight(arr51) / 2;
	outtextxy(width44 + 705, height44 + 495, arr51);
	outtextxy(width44 + 705, height44 + 530, arr52);

	while (1)
	{
		if (MouseHit)
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				if (msg.x > 715 && msg.x < 850 && msg.y > 45 && msg.y < 65)
				{
					if (self_create_file) {
						printf("You have create a new file.Please refresh.\n");
						continue;
					}
					if (self_create_item) {
						printf("You have create a item.Please refresh.\n");
						continue;
					}
					insert_folder_item(opeItem);
					if (opeItem[3].first_index)
						self_create_file = true;
					else
						continue;
					userChoice = 1;
					freshChoice = 1;
					break;

					//创建文件
				}
				if (msg.x > 715 && msg.x < 850 && msg.y > 70 && msg.y < 90)
				{
					if (current_choice == 13 || current_choice == 14 ||
						current_choice == 15 || current_choice == 16) {
						int temp = current_choice - 13;
						change_block_label(&opeBlock[temp], &opeItem[temp]);
						userChoice = 2;
						freshChoice = 1;
						break;
					}
					else
						printf("Please open a file first.\n");
					
					//更改文件块标签
				}
				if (msg.x > 715 && msg.x < 850 && msg.y > 95 && msg.y < 115)
				{
					printf("Successfully saved!\n");
					userChoice = 3;
					//自动保存到磁盘
				}
				if (msg.x > 715 && msg.x < 850 && msg.y > 120 && msg.y < 140)
				{
					printf("Please wait the update.\n");
					userChoice = 4;
					//自动读取文件
				}
				if (msg.x > 715 && msg.x < 850 && msg.y > 185 && msg.y < 205)
				{
					if (self_create_file) {
						printf("You have create a new file.Please refresh.\n");
						continue;
					}
					if (self_create_item) {
						printf("You have create a item.Please refresh.\n");
						continue;
					}
					insert_folder_item(opeItem);
					self_create_item = true;
					userChoice = 5;
					freshChoice = 1;
					break;
					//创建目录项
				}
				if (msg.x > 715 && msg.x < 850 && msg.y > 210 && msg.y < 230)
				{
					if (delete_once) {
						printf("You have delete a file.Please refresh.");
						continue;
					}
					delete_folder_item(opeItem,opeBlock);
					delete_once = true;
					userChoice = 6;
					freshChoice = 1;
					break;
					//删除目录项
				}
				if (msg.x > 715 && msg.x < 850 && msg.y > 235 && msg.y < 255)
				{
					printf("666g");
					userChoice = 7;
					//更改目录项信息
				}
				if (msg.x > 715 && msg.x < 850 && msg.y > 295 && msg.y < 315)
				{
					printf("666h");
					userChoice = 8;
					//更改表项
				}
				if (msg.x > 715 && msg.x < 850 && msg.y > 355 && msg.y < 375)
				{
					if (current_choice == 13 || current_choice == 14 ||
						current_choice == 15 || current_choice == 16) {
						int temp = current_choice - 13;
						change_block_label(&opeBlock[temp], &opeItem[temp]);
						userChoice = 9;
						freshChoice = 1;
						break;
					}
					else
						printf("Please open a file first.\n");
					//更改磁盘块标签
				}
				if (msg.x > 715 && msg.x < 850 && msg.y > 380 && msg.y < 400)
				{
					int temp = current_choice - 13;
					if (temp < 0) 
						printf("Please open a file first.");
					else {
						userChoice = 10;
						freshChoice = 1;
						break;
					}
					//更改磁盘块占用/非占用
				}
				if (msg.x > 715 && msg.x < 850 && msg.y > 405 && msg.y < 425)
				{
					printf("Please wait the update.\n");
					userChoice = 11;
					//自动为已占用添加标签
				}
				if (msg.x > 715 && msg.x < 850 && msg.y > 430 && msg.y < 450)
				{
					if (current_choice == 13 || current_choice == 14 ||
						current_choice == 15 || current_choice == 16) {
						int temp = current_choice - 13;
						userChoice = 12;
						clear_block_label(&opeBlock[temp], &opeItem[temp]);
						freshChoice = 1;
						break;
					}
					else
						printf("Please open a file first.\n");
					//清除标签
				}
				if (msg.x > 360 && msg.x < 650 && msg.y>80 && msg.y < 110) {
					if (userChoice == 13)
						continue;
					userChoice = 13;
					freshChoice = 1;
					current_choice = 13;
					break;
				}
				if (msg.x > 360 && msg.x < 650 && msg.y>110 && msg.y < 140) {
					if (userChoice == 14)
						continue;
					userChoice = 14;
					freshChoice = 1;
					current_choice = 14;
					break;
				}
				if (msg.x > 360 && msg.x < 650 && msg.y>140 && msg.y < 170) {
					if (userChoice == 15)
						continue;
					if (delete_once) 
						if (!self_create_file || !self_create_item)
							continue;
					userChoice = 15;
					freshChoice = 1;
					current_choice = 15;
					break;
				}
				if (msg.x > 360 && msg.x < 650 && msg.y>170 && msg.y < 200) {
					if (userChoice == 16)
						continue;
					if (!self_create_file&&!self_create_item)
						continue;
					if (delete_once)
						continue;
					userChoice = 16;
					freshChoice = 1;
					current_choice = 16;
					break;
				}
				if (msg.x > 715 && msg.x < 850 && msg.y>495 && msg.y < 525) {
					//刷新界面
					freshChoice = 1;
					break;
				}
				if (msg.x > 715 && msg.x < 850 && msg.y>530 && msg.y < 560) {
					//重启程序
					freshChoice = 2;
					break;
				}
				}
			}
		}		
}