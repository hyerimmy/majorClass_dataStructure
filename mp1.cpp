
/*
프로그램 설명

MP1은 여러 개의 슬라이드를 순차적으로 보이는 프로그램이다.
text file로부터 슬라이드를 읽고, 이를 list로 만들어 사용한다.
리스트를 구성하는 슬라이드를 display하고, show를 통해 설정한 시간단위로 연속해서 보여진다.
그 외에 슬라이드를 보거나 복사, 삭제 등의 다양한 기능을 구현한다.

*/

//
//
//
// 디지털미디어학과
// 2019111309
// 황혜림
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

const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 핸들값

COORD  Pos;                                              // 위치

//-----------------------------------------------------
//  화면상의 (x, y) 좌표 위치로 커서 이동
//
void gotoXY(int x, int y)
{
   Pos.X = x - 1;
   Pos.Y = y - 1;
   SetConsoleCursorPosition(hConsole, Pos);
}

// 현재 영역 색 추출, 0은 텍스트 영역, 1이상은 배경 영역 색을 리턴
// GetColor(0) => 텍스트 색상 반환, GetColor(1) => 배경 색상 반환
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

//텍스트, 배경 색 설정
void setColor(int txtcolor, int bgcolor)
{
	txtcolor &= 0xf;
	bgcolor &= 0xf;
	SetConsoleTextAttribute(hConsole, (bgcolor << 4) | txtcolor);
}

// 텍스트 색 설정
// 배경 색은 GetColor(1)을 통해 원래의 배경색으로 설정
void setColor(int txtcolor)
{
	txtcolor &= 0xf;
	int bgcolor = getColor(1);
	SetConsoleTextAttribute(hConsole, (bgcolor << 4) | txtcolor);
}

//-----------------------------------------------------
// 화면을 지운다

void clrScr()
{
	system("cls");
}

//--------------------< sleep >----------------------
// (주어진 시간)/1000 초 동안 실행을 멈춘다.

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
 //-소리 "삡" 출력
void beep()
{
	putchar(7);
}

//--------------------< menu >-----------------------
// 명령어에 대한 도움말을 보인다.

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

//----------------< slide의 구조 >----------------
typedef struct 
{
	char name[21];
	int  time;
	char screen[20][71];
} slide;

#define listData slide
typedef char message[80];

#include "mp1list.h"

// 전역 변수

list show;			// show
list buffer;		// buffer
list *currentList ;	// currentList: 현재 리스트를 지시하는 포인터로 show, buffer 중 하나의 주소를 기억
message msg;		// 문자열 메시지를 위한 전역 변수

#include "mp1list.cpp"

//----------------< displayMessage 1 >----------------------
// 문자열 메시지를 2초간 보인다
//
void displayMessage (message msg) 
{
	gotoXY(2, 22);
	int oldTextColor = getColor(0);
	setColor(12);							// 빨간색
	cout <<  msg  << endl;
	sleep( (clock_t)2 * CLOCKS_PER_SEC );	// delay 2 seconds
	setColor(oldTextColor);					// 원래 글자색으로!
}

//----------------< displayMessage 2 >----------------------
// 함수 overloading
// empty 메시지를 2초간 보인다 
//
void displayMessage () 
{
	gotoXY(2, 22);
	int oldTextColor = getColor(0);
	setColor(12);							// 빨간색
	if (currentList->isShow())
		cout << "show is empty" << endl;
	else
		cout << "buffer is empty" << endl;
	sleep( (clock_t)2 * CLOCKS_PER_SEC );	// delay 2 seconds
	setColor(oldTextColor);					// 원래 글자색으로!
}

//----------------< displayMessage 3 >----------------------
// 함수 overloading
// 정수 메시지를 2초간 보인다 
//
void displayMessage (int num) 
{
	gotoXY(2, 22);
	int oldTextColor = getColor(0);
	setColor(12);							// 빨간색
	cout << num << " 개의 슬라이드가 있습니다." << endl;
	sleep( (clock_t)2 * CLOCKS_PER_SEC );	// delay 2 seconds
	setColor(oldTextColor);					// 원래 글자색으로!
}

//------------------< emptyChech() >--------------------
// currentList가 공백이면 메시지 출력 + true 반환
// 아니면 false 반환
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
// 입력된 num 이 양수이고, limit을 초과하지 않으면 true 아니면 false
bool isLimitOK(int num, int limit)
{
	if (num <= limit && num > 0)
		return true;
	else
		return false;
}

//--------------------< readSlide >-----------------------
// 한개의 슬라이드 파일 (time, name, screen) 입력 -> 반환 (s)
// readShow()에서 호출
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
		exit(1); //데이터 맞지 않는 경우 종료
	}
	return s; //입력 받은 슬라이드 반환
}

//--------------------< writeSlide >----------------------
// 한개의 슬라이드를 파일에 출력
// writeShow () 에서 호출
//
void writeSlide(ofstream& outfile, slide S)
{
	int j;

	outfile << "SLIDE " << S.time << " " << S.name << endl;
	for (j = 0; j < 20; j++)
	{
		// outfile.write(S.screen[j], (streamsize)strlen(S.screen[j]));	// 한 줄을 출력
		outfile.write(S.screen[j], strlen(S.screen[j]));	// 한 줄을 출력
		outfile << endl;
	}
}

// MP1에서 새로 구현하는 리스트 함수들!


// current 노드 출력하는 함수
void list:: displaySlide ()
{
	slide s;
	int j;

	clrScr();

	// 1.s에 현재 노드 값 읽어오기
	s = getData();

	// 2. s의 screen 20줄 모두 순차적으로 출력
	for (j = 0; j < 20; j++)
	{
		cout << s.screen[j] << endl;
	}

	// 3. screen 하단으로 위치 이동
	gotoXY(2,21);

	// 4. 스크린의 마지막줄 출력
	if (isShow())
		cout << "show의 ";
	else
		cout << "buffer의 ";
	cout << position() << "/" << size() << "번 노드, 슬라이드명 : ";
	cout << s.name;
	cout << "시간 = " << s.time * 0.1 << "초";

	

}


// readSlide함수 활용해 show를 읽어오는 함수
void list:: readShow(ifstream  &infile)  
{
	slide s;

	int i, count;	

	// 1. count 입력받기 (데이터가 몇 개 있는지 읽어옴)
	infile >> count;

	for (i = 0; i < count; i++) 
	{
		// 2. show 읽기
		s = readSlide(infile); 

		// 3. 읽은 show를 리스트의 current 뒤로 추가하기
		insertNext(s); 
	}
	
}

// 리스트의 슬라이드를 순차적으로 보이는 함수
//  displaySlide() 함수를 활용해, 화면을 연속적으로 보인다.
//각 슬라이드에 설정된 time 만큼 지속한다.
void list:: playShow ()
{
	nodePtr p;
	slide s;
	
	
	if (!isEmpty())
	{
		// +. 기존 current 값 저장
		p = getCurrent();

		// 0. head 노드로 이동
		gotoFirst();

		// 1. current 화면에  출력
		// 2. current를 다음으로 이동
		for (int i = 0; i < size(); i++)
		{
			displaySlide();
			s = getData();
			sleep(s.time*100);
			gotoNext();
		}

		// +. 기존 current 값으로 다시 복원
		current = p;
		beep();
	}

}

//  새로운 show를 작성하는 함수
void list:: writeShow (ofstream  &outfile) 
{
	slide S;
	listNode *p;			

	// 0. 슬라이드 수
	outfile << size() << endl;

	// current 저장
	p = getCurrent();

	while (1)
	{
		// 1. 제일 앞 노드로 current 이동
		current = head;

		// 2. current의 데이터를 S에 저장
		S = current->data;

		// 3. S에 저장한 데이터 출력
		writeSlide(outfile, S);

		// 4. current 다음 노드로 이동
		if (isLast())
			break;
		else
			gotoNext();

	}

	// current 복구
	setCurrent(p);

}


// 오버로딩

// 현재 슬라이드 삭제
void list:: removeCurrent(int num)
{
	for (int i = 0; i < num; i++)
		removeCurrent();
}

// 이전 슬라이드 삭제
void list:: removePrior(int num) 
{
	for (int i = 0; i < num; i++)
		removePrior();

}

// 다음 슬라이드로 이동
void list:: gotoNext(int num) 
{
	for (int i = 0; i < num; i++)
		gotoNext();
}

// 이전 슬라이드로 이동
void list:: gotoPrior(int num) 
{
	for (int i = 0; i < num; i++)
		gotoPrior();
}


// show리스트의 current부터 n개의 노드 잘라내는 함수 (buffer 리스트 current 뒤로 저장)
void list::cutSlides(int n) 
{
	listData cutData;

	for (int i = 0; i < n; i++)
	{
		// 1. this 리스트의 current 노드를 cutData로 저장
		cutData = this->getData();

		// 2. buffer 리스트 current 뒤로 cutData 저장

		buffer.insertNext(cutData);

		// 3. this 리스트의 current 삭제
		this->removeCurrent();
	}

}


// show리스트의 current부터 n개의 노드 복사하는 함수  (buffer 리스트 current 뒤로 저장)
void list::copySlides(int n) 
{
	listData copyData;
	nodePtr p;

	if (isShow())
	{
		// current값 저장
		p = getCurrent();

		for (int i = 0; i < n; i++)
		{
			// 1. this 리스트의 current 노드를 copyData로 저장
			copyData = this->getData();

			// 2. buffer 리스트 current 뒤로 copyData 저장

			buffer.insertNext(copyData);

			// 3. this 리스트의 current를 다음 노드로 이동
			this->gotoNext();
		}

		// current값 복원
		current = p;
	}

}


// buffer리스트의 노드를 show리스트의 current의 다음에 붙여넣는 함수
// 1 2 (3) 4 5 -> 1 2 3 a b (c) 4 5
void list::pasteNext()
{
	slide s;

	// 1. current를 head노드로 이동
	buffer.gotoFirst();

	while (1) 
	{
		// 2. current의 데이터를 s에 따로 저장
		s = buffer.getData();

		// 3. 저장한 s를 show의 current노드 뒤로 붙여넣기
		insertNext(s);
		
		// 4. current를 다음 노드로 이동
		if (buffer.isLast())
			break;
		else
			buffer.gotoNext();
	}

	// 5. buffer의 전체 노드 삭제
	buffer.clear();
}


// buffer리스트의 노드를 show리스트의 current의 이전에 붙여넣는 함수
// 1 2 (3) 4 5 -> 1 2 a b (c) 3 4 5
// pasteNext()함수를 활용
void list::pastePrior()
{
	slide s;

	// #1. show가 공백인 경우
	if (isEmpty())
	{
		// 1. buffer의 모든 노드 show리스트로 붙여넣기

		pasteNext();
	}

	// #2. show가 공백이 아닌 경우 + current를 앞으로 이동이 가능한 경우
	else if (!isFirst())
	{
		// 1. 앞 노드로 이동
		gotoPrior();

		// 2. buffer의 모든 노드 show리스트로 붙여넣기

		pasteNext();
	}

	// #3. show가 공백이 아닌 경우 + current를 앞으로 이동이 불가능한 경우
	else
	{
		// 1. current data를 앞에 똑같이 추가
		insertNext(current->data);

		// 2. 앞 노드(새로 추가한 노드)로 current 이동
		gotoPrior();

		// 3. buffer의 current를 buffer의 head로 이동
		buffer.current = buffer.head;

		// 4. show의 head노드의 값을 buffer의 head 노드 값으로 이동
		show.head->data = buffer.head->data;

		// 5. buffer의 모든 노드를 show의 current 노드 뒤로 이동
		pasteNext();
	}
	
}


// 시간을 설정하는 함수
void list::setTime (int newTime) 
{
	slide s;

	// 1. current data의 값을 s에 불러옴
	s = getData();

	// 2. 불러온 s에서 time의 값을 newTime으로 수정
	s.time = newTime;

	// 3. curret data 값을 s의 값으로 변경
	setData(s);

}

// currentList 변수에 현재 객체의 주소를 저장하는 함수
// this : 현재 객체의 주소 (&show, &buffer)
void list::setCurrentlist() 
{
	currentList = this;
}

// 현재 리스트가 show 리스트인지 반환하는 함수
bool list::isShow() 
{
	return (currentList == &show);
}

// 현재 리스트가 buffer 리스트인지 반환하는 함수
bool list::isBuffer() 
{
	return (currentList == &buffer);
}


// 입력받은 n번째 노드로 이동하는 함수
void list:: gotoNth(int n)
{
	// 1. head노드로 이동
	setCurrent(head);

	// 2. 다음으로 이동 (n-1번 반복)
	for (int i = 0; i < n - 1; i++)
		gotoNext();
}


// i번째 노드와 j번째 노드의 순서를 바꾼다.
void list:: swapSlide(int i, int j)
{
	listData d1, d2;
	int cp;
	nodePtr p;
	
	// current 저장
	p = current;

	// 1. i번쨰 노드로 이동
	gotoNth(i);

	// 2. i번째 노드의 값을 d1에 저장
	d1 = current->data;

	// 3. j번째 노드로 이동
	gotoNth(j);

	// 4. j번째 노드의 값을 d2에 저장
	d2 = current->data;

	// 5. j번째 노드의 값을 d1으로 변경
	setData(d1);

	// 6. i번째 노드로 이동
	gotoNth(i);

	// 7. i번째 노드의 값을 d2으로 변경
	setData(d2);
	
	// current 복구
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


	show.setCurrentlist();	// currentList의 초기값은 show 

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

			if (!emptyCheck())	//공백검사
			{
				outfile.open(FileName);
				currentList->writeShow(outfile);
				outfile.close();
			}
				
			break;


		case 'S' :	// playShow()								
			if (!emptyCheck())	//공백검사
				currentList->playShow();
			break;


		case '[' :	// gotoFirst()
			if (!emptyCheck())	//공백검사
				currentList->gotoFirst();
			break;


		case ']' :	// gotoLast()
			if (!emptyCheck())	//공백검사
				currentList->gotoLast();
			break;


		case '>' :	// gotoNext()

			if (!emptyCheck())	//공백검사
			{
				if (currentList->isLast())
					currentList->gotoFirst();
				else
					currentList->gotoNext();
			}
			break;



		case '<' :		// gotoPrior()
			
			if (!emptyCheck())	//공백검사
			{
				if (currentList->isFirst())
					currentList->gotoLast();
				else
					currentList->gotoPrior();
			}
			break;



		case 'G' :	// gotoNth(n)

			if (!emptyCheck())	//공백검사
			{
				limit = currentList->size(); //limit 설정
				if (isLimitOK(num, limit)) // 범위검사
					currentList->gotoNth(num); // OK
				else
					displayMessage(limit); //오류메시지 출력
			}
			break;



		case ')' :	// gotoNext(n)		

			if (!emptyCheck())	//공백검사
			{
				limit = currentList->size() - currentList->position(); //limit 설정
				if(isLimitOK(num, limit)) // 범위검사
					currentList->gotoNext(num); // OK
				else
					displayMessage(limit); //오류메시지 출력
			}
			break;



		case '(' :	// gotoPrior(n)									
			
			if (!emptyCheck())	//공백검사
			{
				limit = currentList->position() - 1; //limit 설정
				if (isLimitOK(num, limit)) // 범위검사
					currentList->gotoPrior(num); // OK
				else
					displayMessage(limit); //오류메시지 출력
			}
			break;


		case '-' :	// removeCurrent()				
			
			if (!emptyCheck())	//공백검사
			{
				currentList->removeCurrent();
			}

			break;



		case 'B' :	// removePrior()
			
			if (!emptyCheck())	//공백검사
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
			
			if (!emptyCheck())	//공백검사
			{
				limit = currentList->position() - 1; //limit 설정
				if (isLimitOK(num, limit)) // 범위검사
					currentList->removePrior(num); // OK
				else
					displayMessage(limit); //오류메시지 출력
			}

			break;



		case 'D' :	// removeCurrent(n)
			
			if (!emptyCheck())	//공백검사
			{
				limit = currentList->size() - currentList->position() + 1; //limit 설정
				if (isLimitOK(num, limit)) // 범위검사
					currentList->removeCurrent(num); // OK
				else
					displayMessage(limit); //오류메시지3 출력
			}

			break;



		case 'X' :	// cutSlides

			if (emptyCheck())	//공백검사
				displayMessage(); //오류메시지1 출력
			else
			{
				limit = currentList->size() - currentList->position() + 1; //limit 설정
				if (isLimitOK(num, limit)) // 범위검사
					currentList->cutSlides(num); // OK
				else
					displayMessage(limit); //오류메시지3 출력
			}
			
			break;



		case 'C' :	// copySlides

			if (emptyCheck())	//공백검사
				displayMessage(); //오류메시지1 출력
			else
			{
				limit = currentList->size() - currentList->position() + 1; //limit 설정
				if (isLimitOK(num, limit)) // 범위검사
					currentList->copySlides(num); // OK
				else
					displayMessage(limit); //오류메시지3 출력
			}

			break;



		case 'P' :	// PP : pastePrior (앞에 붙여넣기)	PN : pasteNext (뒤에 붙여넣기)
			
			if (buffer.isEmpty())	//공백검사 (buffer가 비었는지 확인)
				displayMessage(); //오류메시지1 출력 
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
					strcpy_s(msg, "잘못된 명령어 입니다.");
					displayMessage(msg);
					break;
				}
			}

			break;



		case 'M' :	// MS, MB : show, buffer로 이동 - setCurrentList 활용						

			// 공백검사 하지 않음.

			switch (cmd2)
			{
			case 'S':
				show.setCurrentlist();
				break;

			case 'B':
				buffer.setCurrentlist();
				break;

			default:
				strcpy_s(msg, "잘못된 명령어 입니다.");
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

			if (!emptyCheck())	//공백검사
			{
				limit = currentList->size() - currentList->position() + 1; //limit 설정
				if (isLimitOK(s1, limit) && isLimitOK(s2, limit)) // s1, s2범위검사
					currentList->swapSlide(s1, s2); // OK
				else
					displayMessage(limit); //오류메시지3 출력
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
			strcpy_s(msg, "잘못된 명령어 입니다.");
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
