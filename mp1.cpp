
/*
���α׷� ����

MP1�� ���� ���� �����̵带 ���������� ���̴� ���α׷��̴�.
text file�κ��� �����̵带 �а�, �̸� list�� ����� ����Ѵ�.
����Ʈ�� �����ϴ� �����̵带 display�ϰ�, show�� ���� ������ �ð������� �����ؼ� ��������.
�� �ܿ� �����̵带 ���ų� ����, ���� ���� �پ��� ����� �����Ѵ�.

*/

//
//
//
// �����й̵���а�
// 2019111309
// Ȳ����
//
//


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <assert.h>

#include <iomanip>		// setw()
#include <iostream>
#include <fstream>		// open(), close(), eof(), ...


using namespace std;

const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // �ڵ鰪

COORD  Pos;                                              // ��ġ

//-----------------------------------------------------
//  ȭ����� (x, y) ��ǥ ��ġ�� Ŀ�� �̵�
//
void gotoXY(int x, int y)
{
   Pos.X = x - 1;
   Pos.Y = y - 1;
   SetConsoleCursorPosition(hConsole, Pos);
}

// ���� ���� �� ����, 0�� �ؽ�Ʈ ����, 1�̻��� ��� ���� ���� ����
// GetColor(0) => �ؽ�Ʈ ���� ��ȯ, GetColor(1) => ��� ���� ��ȯ
//
int getColor(int area)
{
	CONSOLE_SCREEN_BUFFER_INFO info;

	int color;
	GetConsoleScreenBufferInfo(hConsole, &info);

	if(area) 
		color = (info.wAttributes & 0xf0) >> 4;
	else 
		color = info.wAttributes & 0xf;
	return color;
}

//�ؽ�Ʈ, ��� �� ����
void setColor(int txtcolor, int bgcolor)
{
	txtcolor &= 0xf;
	bgcolor &= 0xf;
	SetConsoleTextAttribute(hConsole, (bgcolor << 4) | txtcolor);
}

// �ؽ�Ʈ �� ����
// ��� ���� GetColor(1)�� ���� ������ �������� ����
void setColor(int txtcolor)
{
	txtcolor &= 0xf;
	int bgcolor = getColor(1);
	SetConsoleTextAttribute(hConsole, (bgcolor << 4) | txtcolor);
}

//-----------------------------------------------------
// ȭ���� �����

void clrScr()
{
	system("cls");
}

//--------------------< sleep >----------------------
// (�־��� �ð�)/1000 �� ���� ������ �����.

void sleep( clock_t wait ) {
   clock_t goal;
   goal = wait + clock();
   while( goal > clock() )
      ;
}

//--------------------< flush() >-----------------------
void flush(char c) {
	while ( c != '\n' ) 
		c=getchar();
}

//--------------------< beep() >-----------------------
 //-�Ҹ� "��" ���
void beep()
{
	putchar(7);
}

//--------------------< menu >-----------------------
// ��ɾ ���� ������ ���δ�.

void menu() 
{
	system("cls");
	cout << "Commands:" << endl;
	cout << "  R Filename : readshow" << endl;
	cout << "  W Filename : writeshow" << endl;
	cout << "  S   : playshow" << endl;
	cout << endl;
	cout << "  >   : gotoNext" << endl;
	cout << "  ) n : gotoNext(n)" << endl;
	cout << "  <   : gotoPrior" << endl;
	cout << "  ( n : gotoPrior(n)" << endl;
	cout << "  [   : gotoFirst" << endl;
	cout << "  ]   : gotoLast" << endl;
	cout << "  G n : gotoNth(n)" << endl;
	cout << endl;
	cout << "  -   : removeCurrent" << endl;
	cout << "  D n : removeCurrent(n)" << endl;
	cout << "  B   : removePrior" << endl;
	cout << "  A n : removePrior(n)" << endl;
	cout << endl;
	cout << "  X n : cutSlides" << endl;
	cout << "  C n : copySlides" << endl;
	cout << endl;
	cout << "  PN  : pastsNext" << endl;	
	cout << "  PP  : pastePrior" << endl;
	cout << endl;
	cout << "  E n1 n2 : swap" << endl;
	cout << "  MS  : move to show" << endl;	
	cout << "  MB  : move to buffer" << endl;	
	cout << endl;
	cout << "  T NewTime : setTime" << endl;
	cout << "  Z   : clear" << endl;	
	cout << "  !   : reverse" << endl;
	cout << "  Q   : Quit" << endl << endl;
	system("pause");
}

//----------------< slide�� ���� >----------------
typedef struct 
{
	char name[21];
	int  time;
	char screen[20][71];
} slide;

#define listData slide
typedef char message[80];

#include "mp1list.h"

// ���� ����

list show;			// show
list buffer;		// buffer
list *currentList ;	// currentList: ���� ����Ʈ�� �����ϴ� �����ͷ� show, buffer �� �ϳ��� �ּҸ� ���
message msg;		// ���ڿ� �޽����� ���� ���� ����

#include "mp1list.cpp"

//----------------< displayMessage 1 >----------------------
// ���ڿ� �޽����� 2�ʰ� ���δ�
//
void displayMessage (message msg) 
{
	gotoXY(2, 22);
	int oldTextColor = getColor(0);
	setColor(12);							// ������
	cout <<  msg  << endl;
	sleep( (clock_t)2 * CLOCKS_PER_SEC );	// delay 2 seconds
	setColor(oldTextColor);					// ���� ���ڻ�����!
}

//----------------< displayMessage 2 >----------------------
// �Լ� overloading
// empty �޽����� 2�ʰ� ���δ� 
//
void displayMessage () 
{
	gotoXY(2, 22);
	int oldTextColor = getColor(0);
	setColor(12);							// ������
	if (currentList->isShow())
		cout << "show is empty" << endl;
	else
		cout << "buffer is empty" << endl;
	sleep( (clock_t)2 * CLOCKS_PER_SEC );	// delay 2 seconds
	setColor(oldTextColor);					// ���� ���ڻ�����!
}

//----------------< displayMessage 3 >----------------------
// �Լ� overloading
// ���� �޽����� 2�ʰ� ���δ� 
//
void displayMessage (int num) 
{
	gotoXY(2, 22);
	int oldTextColor = getColor(0);
	setColor(12);							// ������
	cout << num << " ���� �����̵尡 �ֽ��ϴ�." << endl;
	sleep( (clock_t)2 * CLOCKS_PER_SEC );	// delay 2 seconds
	setColor(oldTextColor);					// ���� ���ڻ�����!
}

//------------------< emptyChech() >--------------------
// currentList�� �����̸� �޽��� ��� + true ��ȯ
// �ƴϸ� false ��ȯ
//
bool emptyCheck()
{
	if (currentList->isEmpty())
	{
		displayMessage();
		return true;
	}
	else
		return false;
}

//------------------< isLimitOK(num, limit) >------------------------
// �Էµ� num �� ����̰�, limit�� �ʰ����� ������ true �ƴϸ� false
bool isLimitOK(int num, int limit)
{
	if (num <= limit && num > 0)
		return true;
	else
		return false;
}

//--------------------< readSlide >-----------------------
// �Ѱ��� �����̵� ���� (time, name, screen) �Է� -> ��ȯ (s)
// readShow()���� ȣ��
listData readSlide(ifstream& infile)
{
	slide s;
	char id[6] = "";  // "SLIDE"

	infile >> id >> s.time;
	infile.getline(s.name, 40, '\n');

	if (!strcmp(id, "SLIDE"))
		for (int j = 0; j < 20; j++)
			infile.getline(s.screen[j], 71, '\n');
	else
	{
		cout << "slide format error\n" << endl;
		exit(1); //������ ���� �ʴ� ��� ����
	}
	return s; //�Է� ���� �����̵� ��ȯ
}

//--------------------< writeSlide >----------------------
// �Ѱ��� �����̵带 ���Ͽ� ���
// writeShow () ���� ȣ��
//
void writeSlide(ofstream& outfile, slide S)
{
	int j;

	outfile << "SLIDE " << S.time << " " << S.name << endl;
	for (j = 0; j < 20; j++)
	{
		// outfile.write(S.screen[j], (streamsize)strlen(S.screen[j]));	// �� ���� ���
		outfile.write(S.screen[j], strlen(S.screen[j]));	// �� ���� ���
		outfile << endl;
	}
}

// MP1���� ���� �����ϴ� ����Ʈ �Լ���!


// current ��� ����ϴ� �Լ�
void list:: displaySlide ()
{
	slide s;
	int j;

	clrScr();

	// 1.s�� ���� ��� �� �о����
	s = getData();

	// 2. s�� screen 20�� ��� ���������� ���
	for (j = 0; j < 20; j++)
	{
		cout << s.screen[j] << endl;
	}

	// 3. screen �ϴ����� ��ġ �̵�
	gotoXY(2,21);

	// 4. ��ũ���� �������� ���
	if (isShow())
		cout << "show�� ";
	else
		cout << "buffer�� ";
	cout << position() << "/" << size() << "�� ���, �����̵�� : ";
	cout << s.name;
	cout << "�ð� = " << s.time * 0.1 << "��";

	

}


// readSlide�Լ� Ȱ���� show�� �о���� �Լ�
void list:: readShow(ifstream  &infile)  
{
	slide s;

	int i, count;	

	// 1. count �Է¹ޱ� (�����Ͱ� �� �� �ִ��� �о��)
	infile >> count;

	for (i = 0; i < count; i++) 
	{
		// 2. show �б�
		s = readSlide(infile); 

		// 3. ���� show�� ����Ʈ�� current �ڷ� �߰��ϱ�
		insertNext(s); 
	}
	
}

// ����Ʈ�� �����̵带 ���������� ���̴� �Լ�
//  displaySlide() �Լ��� Ȱ����, ȭ���� ���������� ���δ�.
//�� �����̵忡 ������ time ��ŭ �����Ѵ�.
void list:: playShow ()
{
	nodePtr p;
	slide s;
	
	
	if (!isEmpty())
	{
		// +. ���� current �� ����
		p = getCurrent();

		// 0. head ���� �̵�
		gotoFirst();

		// 1. current ȭ�鿡  ���
		// 2. current�� �������� �̵�
		for (int i = 0; i < size(); i++)
		{
			displaySlide();
			s = getData();
			sleep(s.time*100);
			gotoNext();
		}

		// +. ���� current ������ �ٽ� ����
		current = p;
		beep();
	}

}

//  ���ο� show�� �ۼ��ϴ� �Լ�
void list:: writeShow (ofstream  &outfile) 
{
	slide S;
	listNode *p;			

	// 0. �����̵� ��
	outfile << size() << endl;

	// current ����
	p = getCurrent();

	while (1)
	{
		// 1. ���� �� ���� current �̵�
		current = head;

		// 2. current�� �����͸� S�� ����
		S = current->data;

		// 3. S�� ������ ������ ���
		writeSlide(outfile, S);

		// 4. current ���� ���� �̵�
		if (isLast())
			break;
		else
			gotoNext();

	}

	// current ����
	setCurrent(p);

}


// �����ε�

// ���� �����̵� ����
void list:: removeCurrent(int num)
{
	for (int i = 0; i < num; i++)
		removeCurrent();
}

// ���� �����̵� ����
void list:: removePrior(int num) 
{
	for (int i = 0; i < num; i++)
		removePrior();

}

// ���� �����̵�� �̵�
void list:: gotoNext(int num) 
{
	for (int i = 0; i < num; i++)
		gotoNext();
}

// ���� �����̵�� �̵�
void list:: gotoPrior(int num) 
{
	for (int i = 0; i < num; i++)
		gotoPrior();
}


// show����Ʈ�� current���� n���� ��� �߶󳻴� �Լ� (buffer ����Ʈ current �ڷ� ����)
void list::cutSlides(int n) 
{
	listData cutData;

	for (int i = 0; i < n; i++)
	{
		// 1. this ����Ʈ�� current ��带 cutData�� ����
		cutData = this->getData();

		// 2. buffer ����Ʈ current �ڷ� cutData ����

		buffer.insertNext(cutData);

		// 3. this ����Ʈ�� current ����
		this->removeCurrent();
	}

}


// show����Ʈ�� current���� n���� ��� �����ϴ� �Լ�  (buffer ����Ʈ current �ڷ� ����)
void list::copySlides(int n) 
{
	listData copyData;
	nodePtr p;

	if (isShow())
	{
		// current�� ����
		p = getCurrent();

		for (int i = 0; i < n; i++)
		{
			// 1. this ����Ʈ�� current ��带 copyData�� ����
			copyData = this->getData();

			// 2. buffer ����Ʈ current �ڷ� copyData ����

			buffer.insertNext(copyData);

			// 3. this ����Ʈ�� current�� ���� ���� �̵�
			this->gotoNext();
		}

		// current�� ����
		current = p;
	}

}


// buffer����Ʈ�� ��带 show����Ʈ�� current�� ������ �ٿ��ִ� �Լ�
// 1 2 (3) 4 5 -> 1 2 3 a b (c) 4 5
void list::pasteNext()
{
	slide s;

	// 1. current�� head���� �̵�
	buffer.gotoFirst();

	while (1) 
	{
		// 2. current�� �����͸� s�� ���� ����
		s = buffer.getData();

		// 3. ������ s�� show�� current��� �ڷ� �ٿ��ֱ�
		insertNext(s);
		
		// 4. current�� ���� ���� �̵�
		if (buffer.isLast())
			break;
		else
			buffer.gotoNext();
	}

	// 5. buffer�� ��ü ��� ����
	buffer.clear();
}


// buffer����Ʈ�� ��带 show����Ʈ�� current�� ������ �ٿ��ִ� �Լ�
// 1 2 (3) 4 5 -> 1 2 a b (c) 3 4 5
// pasteNext()�Լ��� Ȱ��
void list::pastePrior()
{
	slide s;

	// #1. show�� ������ ���
	if (isEmpty())
	{
		// 1. buffer�� ��� ��� show����Ʈ�� �ٿ��ֱ�

		pasteNext();
	}

	// #2. show�� ������ �ƴ� ��� + current�� ������ �̵��� ������ ���
	else if (!isFirst())
	{
		// 1. �� ���� �̵�
		gotoPrior();

		// 2. buffer�� ��� ��� show����Ʈ�� �ٿ��ֱ�

		pasteNext();
	}

	// #3. show�� ������ �ƴ� ��� + current�� ������ �̵��� �Ұ����� ���
	else
	{
		// 1. current data�� �տ� �Ȱ��� �߰�
		insertNext(current->data);

		// 2. �� ���(���� �߰��� ���)�� current �̵�
		gotoPrior();

		// 3. buffer�� current�� buffer�� head�� �̵�
		buffer.current = buffer.head;

		// 4. show�� head����� ���� buffer�� head ��� ������ �̵�
		show.head->data = buffer.head->data;

		// 5. buffer�� ��� ��带 show�� current ��� �ڷ� �̵�
		pasteNext();
	}
	
}


// �ð��� �����ϴ� �Լ�
void list::setTime (int newTime) 
{
	slide s;

	// 1. current data�� ���� s�� �ҷ���
	s = getData();

	// 2. �ҷ��� s���� time�� ���� newTime���� ����
	s.time = newTime;

	// 3. curret data ���� s�� ������ ����
	setData(s);

}

// currentList ������ ���� ��ü�� �ּҸ� �����ϴ� �Լ�
// this : ���� ��ü�� �ּ� (&show, &buffer)
void list::setCurrentlist() 
{
	currentList = this;
}

// ���� ����Ʈ�� show ����Ʈ���� ��ȯ�ϴ� �Լ�
bool list::isShow() 
{
	return (currentList == &show);
}

// ���� ����Ʈ�� buffer ����Ʈ���� ��ȯ�ϴ� �Լ�
bool list::isBuffer() 
{
	return (currentList == &buffer);
}


// �Է¹��� n��° ���� �̵��ϴ� �Լ�
void list:: gotoNth(int n)
{
	// 1. head���� �̵�
	setCurrent(head);

	// 2. �������� �̵� (n-1�� �ݺ�)
	for (int i = 0; i < n - 1; i++)
		gotoNext();
}


// i��° ���� j��° ����� ������ �ٲ۴�.
void list:: swapSlide(int i, int j)
{
	listData d1, d2;
	int cp;
	nodePtr p;
	
	// current ����
	p = current;

	// 1. i���� ���� �̵�
	gotoNth(i);

	// 2. i��° ����� ���� d1�� ����
	d1 = current->data;

	// 3. j��° ���� �̵�
	gotoNth(j);

	// 4. j��° ����� ���� d2�� ����
	d2 = current->data;

	// 5. j��° ����� ���� d1���� ����
	setData(d1);

	// 6. i��° ���� �̵�
	gotoNth(i);

	// 7. i��° ����� ���� d2���� ����
	setData(d2);
	
	// current ����
	current = p;

}

//---------------------< processCommands >---------------------------
void processCommands() 
{
	
	char cmd1, cmd2;		
	char FileName[25];		
	int  newTime;			
	int  s1, s2;	
	int  num;				
	int  limit;			

	ifstream  infile;		
	ofstream  outfile;		


	show.setCurrentlist();	// currentList�� �ʱⰪ�� show 

	while (1) 
	{
		if ( !currentList->isEmpty() )
			currentList->displaySlide();
		else 
			system("cls");
		
		gotoXY(2, 23);
		cout << "Command: " ; 
		cin >> cmd1 ;
		cmd1 = toupper(cmd1);
			
		if (cmd1 == 'R' || cmd1 == 'W')
			cin >> FileName;
		else if (cmd1 == 'T')
			cin >> newTime;
		else if (cmd1 == 'D' || cmd1 == 'C' || cmd1 == 'X'|| cmd1 == 'A'|| cmd1 == ')'|| cmd1 == '(' || cmd1 == 'G')
			cin >> num;
		else if ((cmd1 == 'P') || (cmd1 == 'M'))
			cin >> cmd2;
		else if (cmd1 == 'E')
			cin >> s1 >> s2;

		switch (cmd1) 
		{
		case 'R': // readShow()
			infile.open(FileName, ios_base::in);
			if (infile)
			{
				show.readShow(infile);
				show.setCurrentlist();
				infile.close();
			}
			else
			{
				strcpy_s(msg, "file not exists...");
				displayMessage(msg);
			}
			break;

		case 'W' :	//writeShow()		

			if (!emptyCheck())	//����˻�
			{
				outfile.open(FileName);
				currentList->writeShow(outfile);
				outfile.close();
			}
				
			break;


		case 'S' :	// playShow()								
			if (!emptyCheck())	//����˻�
				currentList->playShow();
			break;


		case '[' :	// gotoFirst()
			if (!emptyCheck())	//����˻�
				currentList->gotoFirst();
			break;


		case ']' :	// gotoLast()
			if (!emptyCheck())	//����˻�
				currentList->gotoLast();
			break;


		case '>' :	// gotoNext()

			if (!emptyCheck())	//����˻�
			{
				if (currentList->isLast())
					currentList->gotoFirst();
				else
					currentList->gotoNext();
			}
			break;



		case '<' :		// gotoPrior()
			
			if (!emptyCheck())	//����˻�
			{
				if (currentList->isFirst())
					currentList->gotoLast();
				else
					currentList->gotoPrior();
			}
			break;



		case 'G' :	// gotoNth(n)

			if (!emptyCheck())	//����˻�
			{
				limit = currentList->size(); //limit ����
				if (isLimitOK(num, limit)) // �����˻�
					currentList->gotoNth(num); // OK
				else
					displayMessage(limit); //�����޽��� ���
			}
			break;



		case ')' :	// gotoNext(n)		

			if (!emptyCheck())	//����˻�
			{
				limit = currentList->size() - currentList->position(); //limit ����
				if(isLimitOK(num, limit)) // �����˻�
					currentList->gotoNext(num); // OK
				else
					displayMessage(limit); //�����޽��� ���
			}
			break;



		case '(' :	// gotoPrior(n)									
			
			if (!emptyCheck())	//����˻�
			{
				limit = currentList->position() - 1; //limit ����
				if (isLimitOK(num, limit)) // �����˻�
					currentList->gotoPrior(num); // OK
				else
					displayMessage(limit); //�����޽��� ���
			}
			break;


		case '-' :	// removeCurrent()				
			
			if (!emptyCheck())	//����˻�
			{
				currentList->removeCurrent();
			}

			break;



		case 'B' :	// removePrior()
			
			if (!emptyCheck())	//����˻�
			{
				if (currentList->isFirst())
				{
					currentList->gotoLast();
					currentList->removeCurrent();
				}
				else
					currentList->removePrior();
			}

			break;
			

		case 'A' :	// removePrior(n)
			
			if (!emptyCheck())	//����˻�
			{
				limit = currentList->position() - 1; //limit ����
				if (isLimitOK(num, limit)) // �����˻�
					currentList->removePrior(num); // OK
				else
					displayMessage(limit); //�����޽��� ���
			}

			break;



		case 'D' :	// removeCurrent(n)
			
			if (!emptyCheck())	//����˻�
			{
				limit = currentList->size() - currentList->position() + 1; //limit ����
				if (isLimitOK(num, limit)) // �����˻�
					currentList->removeCurrent(num); // OK
				else
					displayMessage(limit); //�����޽���3 ���
			}

			break;



		case 'X' :	// cutSlides

			if (emptyCheck())	//����˻�
				displayMessage(); //�����޽���1 ���
			else
			{
				limit = currentList->size() - currentList->position() + 1; //limit ����
				if (isLimitOK(num, limit)) // �����˻�
					currentList->cutSlides(num); // OK
				else
					displayMessage(limit); //�����޽���3 ���
			}
			
			break;



		case 'C' :	// copySlides

			if (emptyCheck())	//����˻�
				displayMessage(); //�����޽���1 ���
			else
			{
				limit = currentList->size() - currentList->position() + 1; //limit ����
				if (isLimitOK(num, limit)) // �����˻�
					currentList->copySlides(num); // OK
				else
					displayMessage(limit); //�����޽���3 ���
			}

			break;



		case 'P' :	// PP : pastePrior (�տ� �ٿ��ֱ�)	PN : pasteNext (�ڿ� �ٿ��ֱ�)
			
			if (buffer.isEmpty())	//����˻� (buffer�� ������� Ȯ��)
				displayMessage(); //�����޽���1 ��� 
			else
			{
				switch (cmd2)
				{
				case 'P':
					currentList->pastePrior();
					break;

				case 'N':
					currentList->pasteNext();
					break;

				default:
					strcpy_s(msg, "�߸��� ��ɾ� �Դϴ�.");
					displayMessage(msg);
					break;
				}
			}

			break;



		case 'M' :	// MS, MB : show, buffer�� �̵� - setCurrentList Ȱ��						

			// ����˻� ���� ����.

			switch (cmd2)
			{
			case 'S':
				show.setCurrentlist();
				break;

			case 'B':
				buffer.setCurrentlist();
				break;

			default:
				strcpy_s(msg, "�߸��� ��ɾ� �Դϴ�.");
				displayMessage(msg);
				break;
			}

			break;



		case 'Z' :	// clear

			if (!emptyCheck())
				currentList->clear();

			break;



		case 'T' :	// setTime

			if (!emptyCheck())
				currentList->setTime(newTime);

			break;



		case '!' :	// reverse



			break;
			
		case 'E' :	// swapSlide	e 3 5									

			if (!emptyCheck())	//����˻�
			{
				limit = currentList->size() - currentList->position() + 1; //limit ����
				if (isLimitOK(s1, limit) && isLimitOK(s2, limit)) // s1, s2�����˻�
					currentList->swapSlide(s1, s2); // OK
				else
					displayMessage(limit); //�����޽���3 ���
			}
				
			else
			{
				displayMessage(); 
			}

			break;




		case 'Q' :										// quit
			if ( !show.isEmpty() )
				show.clear();
			if ( !buffer.isEmpty() )
				buffer.clear();
			exit(1);
			break;
			
		case '?' :										// menu
			menu();	
			break;
			
		default:
			strcpy_s(msg, "�߸��� ��ɾ� �Դϴ�.");
			displayMessage(msg);
			break;
			
		} // switch
	} // while

} // process commands

int main() 
{
   processCommands();
   return 0;
}
