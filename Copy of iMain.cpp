#include "iGraphics.h"
int page = 0;
int cno[90];
int cyes[90];
int r = 255;
int g = 255;
int b = 255;
int dc = 255;
char str[2];
char stry[2];
char strn[2];
int flag = -1;
int setvo, setsy, setan;
int dx = 0;
int db = 0;
int da = 0;
int dq = 0;
int pn[9];
int apn[9];
int no[9];
int yes[9];
int mode = 0;
typedef struct
{
	char nq[3];
	char q[30];
	char a[30];
} qset;

typedef struct
{
	char username[30];
	char password[9];
} users;
users user[100];

qset sets[90];
char qstr[30];
char astr[30];
char temp_uname[30];
char temp_pass[30];

int index1 = 0;
int index2 = 0;
char g_str1[30];
char g_str2[9];
char currentuser[30];

void free_string(char *str)
{
	int index = strlen(str);
	while (index != 0)
	{
		str[index - 1] = '\0';
		index--;
	}
}

void extract_ques(int n)
{
	FILE *file = fopen("question.txt", "r");
	if (file == NULL)
	{
		perror("error!");
		exit(1);
	}
	int y = 0;
	while (fscanf(file, "%2[^. ]. %29[^:]:%29s\n", sets[y].nq, sets[y].q, sets[y].a))
	{
		y++;
		if (y >= 90)
			break;
	}
	fclose(file);
	strcpy(qstr, sets[n].q);
	strcpy(astr, sets[n].a);
}

int usercount()
{
	FILE *file = fopen("loginfo.txt", "r");
	if (file == NULL)
	{
		perror("error!");
		exit(1);
	}
	int y = 0;
	while (fscanf(file, "%29[^,],%8s\n", user[y].username, user[y].password))
	{
		y++;
		if (y >= 100)
			break;
	}
	fclose(file);
	return y;
}
int i;
int authentication(char *su, char *sp)
{
	for (i = 0; i < usercount(); i++)
	{
		char ahpass[9];
		int n = strlen(user[i].password);
		int k;
		for (k = 0; k < n; k++)
		{
			ahpass[k] = user[i].password[k] - 1;
		}

		if ((strcmp(su, user[i].username) == 0) && (strcmp(sp, ahpass) == 0))
		{
			strcpy(currentuser,user[i].username);
			free_string(g_str1);
			free_string(g_str2);
			free_string(temp_uname);
			free_string(temp_pass);
			index1 = 0;
			index2 = 0;
			return 1;
		}
		else if (k == usercount() - 1)
		{
			return 0;
		}
	}
}

int duplicateuser(char *su)
{
	FILE *file = fopen("loginfo.txt", "r");
	if (file == NULL)
	{
		perror("error!");
		exit(1);
	}
	int y = 0;
	while (fscanf(file, "%29[^,],%8s\n", user[y].username, user[y].password))
	{
		y++;
		if (y >= 100)
			break;
	}
	fclose(file);
	for (int i = 0; i < usercount(); i++)
	{
		if (strcmp(su, user[i].username) == 0)
		{
			return 1;
		}
		else if (i == usercount() - 1)
		{
			return 0;
		}
	}
}
char opening[11][15] = {"opening/0.bmp", "opening/1.bmp", "opening/2.bmp", "opening/3.bmp", "opening/4.bmp", "opening/5.bmp", "opening/6.bmp", "opening/7.bmp", "opening/8.bmp", "opening/9.bmp", "opening/10.bmp"};
char butterfly[19][19] = {"butterfly/1.bmp", "butterfly/2.bmp", "butterfly/3.bmp", "butterfly/4.bmp", "butterfly/5.bmp", "butterfly/6.bmp", "butterfly/7.bmp", "butterfly/8.bmp", "butterfly/9.bmp", "butterfly/10.bmp", "butterfly/11.bmp", "butterfly/12.bmp", "butterfly/13.bmp", "butterfly/14.bmp", "butterfly/15.bmp", "butterfly/16.bmp", "butterfly/17.bmp", "butterfly/18.bmp", "butterfly/19.bmp"};
char ans[19][19] = {"answer/1.bmp", "answer/2.bmp", "answer/3.bmp", "answer/4.bmp", "answer/5.bmp", "answer/6.bmp", "answer/7.bmp", "answer/8.bmp", "answer/9.bmp", "answer/10.bmp", "answer/11.bmp", "answer/12.bmp", "answer/13.bmp", "answer/14.bmp", "answer/15.bmp", "answer/16.bmp", "answer/17.bmp", "answer/18.bmp", "answer/19.bmp"};
char ques[19][19] = {"question/1.bmp", "question/2.bmp", "question/3.bmp", "question/4.bmp", "question/5.bmp", "question/6.bmp", "question/7.bmp", "question/8.bmp", "question/9.bmp", "question/10.bmp", "question/11.bmp", "question/12.bmp", "question/13.bmp", "question/14.bmp", "question/15.bmp", "question/16.bmp", "question/17.bmp", "question/18.bmp", "question/19.bmp"};
void pagenumber(int i)
{
	sprintf(str, "%d", pn[i]);
	iSetColor(0, 0, 0);
	iText(234, 460, str);
}
void pagenumbera(int i)
{
	sprintf(str, "%d", apn[i]);
	iSetColor(0, 0, 0);
	iText(234, 460, str);
}
void yescount(int i)
{
	sprintf(stry, "%d", yes[i]);
	iSetColor(255, 255, 255);
	iText(220, 83, stry, GLUT_BITMAP_HELVETICA_12);
}
void nocount(int i)
{
	sprintf(strn, "%d", no[i]);
	iSetColor(255, 255, 255);
	iText(174, 115, strn, GLUT_BITMAP_HELVETICA_12);
}
void blink()
{
	r = g = b = r - dc;
	if (r == 0 || g == 0 || b == 0)
	{
		dc = -255;
	}
	else
		dc = 255;
}
void circleno()
{
	iSetColor(255, 0, 0);
	iFilledCircle(51, 123, 5, 100);
}
void circleyes()
{
	iSetColor(0, 255, 0);
	iFilledCircle(51, 90, 5, 100);
}
int hide = 0;
void iDraw()
{
	// place your drawing codes here
	iClear();
	switch (page)
	{
	case 0:
	{
		if (dx < 10)
			iShowBMP(0, 0, opening[dx]);
		if (dx >= 10)
		{
			iShowBMP(0, 0, butterfly[db]);
		}
		iSetColor(r, g, b);
		iText(40, 20, "Press 'HOME' button to continue......", GLUT_BITMAP_HELVETICA_12);
		break;
	}
	case 1:
		iShowBMP(0, 0, "bmp file/interface.bmp");
		break;
	case 2:
		iShowBMP(0, 0, "bmp file/vocabulary.bmp");
		break;
	case 3:
		iShowBMP(0, 0, "bmp file/synonym.bmp");
		break;
	case 4:
		iShowBMP(0, 0, "bmp file/antonym.bmp");
		break;
	case 5:
	{
		extract_ques(((flag - 1) * 10) + pn[flag - 1] - 1);
		iShowBMP(0, 0, ques[dq]);
		pagenumber(flag - 1);
		nocount(flag - 1);
		iSetColor(0, 0, 0);
		iText(105, 313, qstr, GLUT_BITMAP_HELVETICA_18);
		if (flag >= 1 && flag <= 3)
		{
			iSetColor(135, 206, 235);
			iRectangle(41, 402, 76, 22);
			iSetColor(255, 0, 0);
			iFilledCircle(51, 121, 5, 100);
			iSetColor(255, 255, 255);
			iText(60, 116, "You have mastered     new vocabulary!!", GLUT_BITMAP_HELVETICA_12);
			iSetColor(255, 255, 255);
			iText(47, 409, "Vocabulary: ", GLUT_BITMAP_HELVETICA_12);
			if (yes[flag - 1] > 0)
			{
				iSetColor(0, 255, 0);
				iFilledCircle(51, 88, 5, 100);
				iSetColor(255, 255, 255);
				iText(60, 84, "Amazing! you already know     vocabulary!!", GLUT_BITMAP_HELVETICA_12);
				yescount(flag - 1);
			}
		}
		if (flag >= 4 && flag <= 6)
		{
			iSetColor(135, 206, 235);
			iRectangle(41, 402, 76, 22);
			iSetColor(255, 0, 0);
			iFilledCircle(51, 121, 5, 100);
			iSetColor(255, 255, 255);
			iText(60, 116, "You have mastered     new synonyms!!", GLUT_BITMAP_HELVETICA_12);
			iSetColor(255, 255, 255);
			iText(47, 409, "Synonym: ", GLUT_BITMAP_HELVETICA_12);
			if (yes[flag - 1] > 0)
			{
				iSetColor(0, 255, 0);
				iFilledCircle(51, 88, 5, 100);
				iSetColor(255, 255, 255);
				iText(60, 84, "Amazing! you already know     synonyms!!", GLUT_BITMAP_HELVETICA_12);
				yescount(flag - 1);
			}
		}
		if (flag >= 7 && flag <= 9)
		{
			iSetColor(135, 206, 235);
			iRectangle(41, 402, 76, 22);
			iSetColor(255, 0, 0);
			iFilledCircle(51, 121, 5, 100);
			iSetColor(255, 255, 255);
			iText(60, 116, "You have mastered     new antonyms!!", GLUT_BITMAP_HELVETICA_12);
			iSetColor(255, 255, 255);
			iText(47, 409, "Antonym: ", GLUT_BITMAP_HELVETICA_12);
			if (yes[flag - 1] > 0)
			{
				iSetColor(0, 255, 0);
				iFilledCircle(51, 88, 5, 100);
				iSetColor(255, 255, 255);
				iText(60, 84, "Amazing! you already know     antonym!!", GLUT_BITMAP_HELVETICA_12);
				yescount(flag - 1);
			}
		}
		break;
	}
	case 6:
	{
		extract_ques(((flag - 1) * 10) + pn[flag - 1] - 1);
		if (da <= 19)
			iShowBMP(0, 0, ans[da]);
		pagenumbera(flag - 1);
		iSetColor(0, 0, 0);
		iText(105, 313, astr, GLUT_BITMAP_HELVETICA_18);
		break;
	}
	case 7:
	{
		iShowBMP(0, 0, "bmp file/login.bmp");
		iSetColor(0, 0, 255);
		iText(80, 220, "Password must have 8 characters!!");
		iSetColor(0, 0, 255);
		iRectangle(313, 171, 72, 22);
		if (hide == 1)
		{
			iSetColor(0, 0, 255);
			iText(330, 178, "SHOW");
		}
		else if (hide == 0)
		{
			iSetColor(0, 0, 255);
			iText(330, 178, "HIDE");
		}
		if (mode == 1 || mode == 2)
		{
			if (mode == 1)
			{
				iSetColor(0, 0, 0);
				iRectangle(133, 269, 263, 32);
			}
			else if (mode == 2)
			{
				iSetColor(0, 0, 0);
				iRectangle(133, 166, 263, 32);
			}
			iSetColor(0, 0, 0);
			iText(137, 281, temp_uname, GLUT_BITMAP_HELVETICA_12);
			if (hide == 0)
				iText(137, 179, temp_pass, GLUT_BITMAP_HELVETICA_12);
			else
			{
				char strhide[9];
				if (strlen(temp_pass) == 1)
				{
					strcpy(strhide, "#");
				}
				else if (strlen(temp_pass) == 2)
				{
					strcpy(strhide, "##");
				}
				else if (strlen(temp_pass) == 3)
				{
					strcpy(strhide, "###");
				}
				else if (strlen(temp_pass) == 4)
				{
					strcpy(strhide, "####");
				}
				else if (strlen(temp_pass) == 5)
				{
					strcpy(strhide, "#####");
				}
				else if (strlen(temp_pass) == 6)
				{
					strcpy(strhide, "######");
				}
				else if (strlen(temp_pass) == 7)
				{
					strcpy(strhide, "#######");
				}
				else if (strlen(temp_pass) == 8)
				{
					strcpy(strhide, "########");
				}
				else if (strlen(temp_pass) == 9)
				{
					strcpy(strhide, "#########");
				}
				else if (strlen(temp_pass) == 10)
				{
					strcpy(strhide, "#########");
				}
				else if (strlen(temp_pass) == 11)
				{
					strcpy(strhide, "##########");
				}
				else if (strlen(temp_pass) == 12)
				{
					strcpy(strhide, "###########");
				}
				iText(137, 179, strhide, GLUT_BITMAP_HELVETICA_12);
			}
		}
		break;
	}
	case 8:
	{
		iShowBMP(0, 0, "bmp file/popup.bmp");
		break;
	}
	case 9:
	{
		iShowBMP(0, 0, "bmp file/successful.bmp");
		break;
	}
	case 10:
	{
		iShowBMP(0, 0, "bmp file/invalid.bmp");
		break;
	}
	case 11:
	{
		iShowBMP(0, 0, "bmp file/duplicate.bmp");
		break;
	}
	case 12:
	{
		iShowBMP(0, 0, "bmp file/new.bmp");
		break;
	}
	}

	if (page == 5)
	{
		iSetColor(255, 0, 0);
		iFilledCircle(89, 318, 5, 100);
	}
	else if (page == 6)
	{
		iSetColor(0, 0, 255);
		iFilledCircle(89, 318, 5, 100);
	}
}
//,"question/20.bmp", "question/21.bmp", "question/22.bmp", "question/23.bmp", "question/24.bmp", "question/25.bmp", "question/26.bmp", "question27.bmp", "question/28.bmp", "question/29.bmp","question/30.bmp","question/31.bmp","question/32.bmp","question/33.bmp","question/34.bmp","question/35.bmp"
void change()
{
	dx++; // opening motion
	if (dx >= 10)
		dx = 10;
}
void change1()
{
	db++;
	if (db >= 19)
		db = 0;
	dq++;
	if (dq >= 19)
		dq = 0;
}
void change2()
{
	da++;
	if (da >= 19)
		da = 0;
}

void signup(char *s1, char *s2)
{
	char hpass[9];
	int n = strlen(s2);
	int i;
	for (i = 0; i < n; i++)
	{
		hpass[i] = s2[i] + 1;
	}

	FILE *file = fopen("loginfo.txt", "a");
	if (file == NULL)
	{
		perror("error occured!");
		exit(1);
	}
	fprintf(file, "%s,%s\n", s1, hpass);
	fclose(file);
	free_string(g_str1);
	free_string(g_str2);
	free_string(temp_uname);
	free_string(temp_pass);
	free_string(hpass);
	index1 = 0;
	index2 = 0;
}

void iMouseMove(int mx, int my)
{
}

void page5next(int i, int x, int y)
{
	if (x >= 436 && x <= 476 && y >= 453 && y <= 482)
	{
		pn[flag - 1]++;
		if (pn[flag - 1] == 11)
		{
			if (flag >= 1 && flag <= 3)
			{
				page = 2;
				pn[flag - 1] = 1;
			}
			if (flag >= 4 && flag <= 6)
			{
				page = 3;
				pn[flag - 1] = 1;
			}
			if (flag >= 7 && flag <= 9)
			{
				page = 4;
				pn[flag - 1] = 1;
			}
		}
	}
}
void page5prev(int i, int x, int y)
{
	if (x >= 20 && x <= 61 && y >= 453 && y <= 482)
	{
		pn[flag - 1]--;
		if (pn[flag - 1] == 0)
		{
			if (flag >= 1 && flag <= 3)
			{
				page = 2;
				pn[flag - 1] = 1;
			}
			if (flag >= 4 && flag <= 6)
			{
				page = 3;
				pn[flag - 1] = 1;
			}
			if (flag >= 7 && flag <= 9)
			{
				page = 4;
				pn[flag - 1] = 1;
			}
		}
	}
}
void answer(int flag, int x, int y)
{
	if (x >= 202 && x <= 286 && y >= 16 && y <= 62)
	{
		page = 5;
	}
}

void newfile(char *str)
{
	strcat(str, ".txt");
	FILE *file = fopen(str, "a");
	// printf("%s",str);
	if (file == NULL)
	{
		exit(1);
	}
}
void iMouse(int button, int state, int mx, int my)
{
	printf("%s",currentuser);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (page == 1)
		{
			if (mx >= 81 && mx <= 417 && my >= 307 && my <= 397)
			{
				page = 2;
			}
			if (mx >= 81 && mx <= 417 && my >= 194 && my <= 285)
			{
				page = 3;
			}
			if (mx >= 81 && mx <= 417 && my >= 84 && my <= 171)
			{
				page = 4;
			}
			if (mx >= 370 && mx <= 421 && my >= 19 && my <= 47)
			{
				page = 7;
			}
		}
		else if (page == 2)
		{
			if (mx >= 20 && mx <= 63 && my >= 454 && my <= 481)
			{
				page = 1;
			}
			if (mx >= 115 && mx <= 340 && my >= 330 && my <= 448)
			{
				page = 5;
				setvo = 1;
				flag = 1;
			}
			if (mx >= 115 && mx <= 340 && my >= 194 && my <= 311)
			{
				page = 5;
				setvo = 2;
				flag = 2;
			}
			if (mx >= 115 && mx <= 340 && my >= 52 && my <= 171)
			{
				page = 5;
				setvo = 3;
				flag = 3;
			}
		}
		else if (page == 3)
		{
			if (mx >= 20 && mx <= 63 && my >= 454 && my <= 481)
			{
				page = 1;
			}
			if (mx >= 115 && mx <= 340 && my >= 330 && my <= 448)
			{
				setsy = 1;
				page = 5;
				flag = 4;
			}
			if (mx >= 115 && mx <= 340 && my >= 194 && my <= 311)
			{
				setsy = 2;
				page = 5;
				flag = 5;
			}
			if (mx >= 115 && mx <= 340 && my >= 52 && my <= 171)
			{
				setsy = 3;
				page = 5;
				flag = 6;
			}
		}
		else if (page == 4)
		{
			if (mx >= 20 && mx <= 63 && my >= 454 && my <= 481)
			{
				page = 1;
			}
			if (mx >= 115 && mx <= 340 && my >= 330 && my <= 448)
			{
				page = 5;
				setan = 1;
				flag = 7;
			}
			if (mx >= 115 && mx <= 340 && my >= 194 && my <= 311)
			{
				setan = 2;
				page = 5;
				flag = 8;
			}
			if (mx >= 115 && mx <= 340 && my >= 52 && my <= 171)
			{
				page = 5;
				setan = 3;
				flag = 9;
			}
		}
		if (page == 5)
		{
			page5next(flag, mx, my);
			page5prev(flag, mx, my);
			if (mx >= 201 && mx <= 285 && my >= 13 && my <= 62)
			{
				page = 1;
			}
			if (mx >= 89 && mx <= 189 && my >= 177 && my <= 229)
			{
				if (cyes[((flag - 1) * 10) + pn[flag - 1] - 1] == 0 && cno[((flag - 1) * 10) + pn[flag - 1] - 1] == 0)
				{
					if (pn[flag - 1] == 10 && mx >= 436 && mx <= 476 && my >= 453 && my <= 482)
						yes[flag - 1] = 0;
					yes[flag - 1]++;
					cyes[((flag - 1) * 10) + pn[flag - 1] - 1] = 1;
					// page5next(flag, mx, my);
				}
			}
			if (mx >= 315 && mx <= 404 && my >= 177 && my <= 229)
			{

				if (cyes[((flag - 1) * 10) + pn[flag - 1] - 1] == 0 && cno[((flag - 1) * 10) + pn[flag - 1] - 1] == 0)
				{
					if (pn[flag - 1] == 10 && mx >= 436 && mx <= 476 && my >= 453 && my <= 482)
						no[flag - 1] = 0;
					no[flag - 1]++;
					cno[((flag - 1) * 10) + pn[flag - 1] - 1] = 1;
					// page5next(flag, mx, my);
				}
			}
			if (mx >= 315 && mx <= 404 && my >= 177 && my <= 229)
			{
				page = 6;
				apn[flag - 1] = pn[flag - 1];
			}
			if (page == 2 || page == 3 || page == 4 && mx >= 436 && mx <= 476 && my >= 453 && my <= 482)
			{
				no[flag - 1] = 0;
				yes[flag - 1] = 0;
			}
		}
		if (page == 6)
		{
			answer(flag, mx, my);
		}
		else if (page == 7)
		{
			if (mx >= 313 && mx <= 385 && my >= 171 && my <= 193 && hide == 1)
			{ // 313 171 385 193
				hide = 0;
			}
			else if (mx >= 313 && mx <= 385 && my >= 171 && my <= 193 && hide == 0)
			{
				hide = 1;
			}

			if (mx >= 381 && mx <= 450 && my >= 38 && my <= 70)
			{
				page = 1;
				free_string(g_str1);
				free_string(g_str2);
				free_string(temp_uname);
				free_string(temp_pass);
				index1 = 0;
				index2 = 0;
			}
			if (mx >= 290 && mx <= 376 && my >= 113 && my <= 142)
			{
				// sign up
				if (duplicateuser(temp_uname))
				{
					if (temp_uname[0] == '\0' || temp_pass[0] == '\0' || strlen(temp_pass) != 8)
						page = 8;
					else
						page = 11;
					free_string(g_str1);
					free_string(temp_uname);
					index1 = 0;
				}
				else
				{
					if (temp_uname[0] == '\0' || temp_pass[0] == '\0' || strlen(temp_pass) != 8)
						page = 8;
					else
					{
						signup(temp_uname, temp_pass);
						page = 9;
					}
				}
			}
			if (mx >= 101 && mx <= 178 && my >= 113 && my <= 147)
			{
				// for login
				if (temp_uname[0] == '\0' || temp_pass[0] == '\0' || strlen(temp_pass) != 8)
					page = 10;
				else
				{
					if (authentication(temp_uname, temp_pass))
					{
						page = 12;
						newfile(user[i].username);
					}
					else
						page = 10;
				}
			}
			if (mx >= 126 && mx <= 399 && my >= 260 && my <= 314)
			{
				mode = 1;
			}
			if (mx >= 125 && mx <= 406 && my >= 158 && my <= 212)
			{
				mode = 2;
			}
		}
		else if (page == 8)
		{
			if (mx >= 213 && mx <= 272 && my >= 190 && my <= 225)
			{
				page = 7;
			}
		}
		else if (page == 9)
		{
			if (mx >= 213 && mx <= 272 && my >= 190 && my <= 225)
			{
				page = 7;
			}
		}
		else if (page == 10 || page == 11)
		{
			if (mx >= 213 && mx <= 272 && my >= 190 && my <= 225)
			{
				page = 7;
			}
		}
		else if (page == 12)
		{
			if (mx >= 403 && mx <= 467 && my >= 446 && my <= 481)
			{
				page = 1;
				free_string(currentuser);
			}
		}
	}
}

void iKeyboard(unsigned char key)
{
	if (mode == 1)
	{
		if (key == '\n')
			mode = 2;
		if (key != '\b')
		{
			g_str1[index1] = key;
			index1++;
			g_str1[index1] = '\0';
		}
		else
		{
			if (index1 <= 0)
				index1 = 0;
			else
			{
				index1--;
				g_str1[index1] = '\0';
			}
		}
		strcpy(temp_uname, g_str1);
	}
	else if (mode == 2)
	{
		// free_string(g_str1);
		if (key != '\b')
		{
			g_str2[index2] = key;
			index2++;
			g_str2[index2] = '\0';
		}
		else
		{
			if (index2 <= 0)
				index2 = 0;
			else
			{
				index2--;
				g_str2[index2] = '\0';
			}
		}
		strcpy(temp_pass, g_str2);
		if (key == '\n')
			signup(temp_uname, temp_pass);
	}
}

void iSpecialKeyboard(unsigned char key)
{
	if (key == GLUT_KEY_HOME)
		page = 1;
	if (key == GLUT_KEY_RIGHT)
	{
		pn[flag - 1]++;
		if (pn[flag - 1] == 11)
		{
			if (flag >= 1 && flag <= 3)
			{
				page = 2;
				pn[flag - 1] = 1;
			}
			if (flag >= 4 && flag <= 6)
			{
				page = 3;
				pn[flag - 1] = 1;
			}
			if (flag >= 7 && flag <= 9)
			{
				page = 4;
				pn[flag - 1] = 1;
			}
		}
	}
	if (key == GLUT_KEY_LEFT)
	{
		pn[flag - 1]--;
		if (pn[flag - 1] == 0)
		{
			if (flag >= 1 && flag <= 3)
			{
				page = 2;
				pn[flag - 1] = 1;
			}
			if (flag >= 4 && flag <= 6)
			{
				page = 3;
				pn[flag - 1] = 1;
			}
			if (flag >= 7 && flag <= 9)
			{
				page = 4;
				pn[flag - 1] = 1;
			}
		}
	}
}

int main()
{
	if (page == 0)
		iSetTimer(800, blink);
	for (int i = 0; i < 9; i++)
	{
		pn[i] = apn[i] = 1;
		yes[i] = no[i] = 0;
	}
	if (page == 0 && dx < 10)
	{
		iSetTimer(40, change);
	}
	if (page == 0 && db != 21)
	{
		iSetTimer(200, change1);
	}
	if (page != 6 && da != 21)
	{
		iSetTimer(150, change2);
	}

	for (int i = 0; i < 90; i++)
	{
		cno[i] = 0;
		cyes[i] = 0;
	}
	if (no[flag - 1] > 10)
		no[flag - 1] = 0;
	if (yes[flag - 1] > 10)
		yes[flag - 1] = 0;
	// place your own initialization codes here.
	iInitialize(500, 500, "flashcard");
	return 0;
}
