/*

프로그램 설명: 문자열의 다양한 기능을 구현하는 token class를 구현
	- 키보드에서 문자열을 읽어 토큰에 저장 : setElement()
	- 화면에 토큰 출력 : getElement()
	- 두 개의 토큰의 내용이 같으면 true, 아니면 false값 반환 : isEqual(token t)
	- 토큰의 내용을 모두 지움 : clear()
	- 현재 토큰 뒤에 token t를 추가 : merge(token t)
	- 토큰의 내용을 역으로 만듦 : reverse()
	- 토큰 내 문자열 중 from부터 count개의 문자열을 공백 토큰 sub에 복사 : subToken(token &sub, int from, int coung)
	* 반복문을 이용해 기존 토큰 내 문자열을 뒤에 역으로 추가 : toMirror1()
	* 기존 함수(subToken, reverse, merge)를 활용해 문자열을 뒤에 역으로 추가 : toMirror2()
	
학번 : 2019111309
이름 : 황혜림
분반 : 화 5-6 
날짜 : 2020/09/14

*/

#define SWAP(x, y, t) (t=x, x=y, y=t)

//------------------< Constructor >---------------------
token::token()
{
	length = 0;
	//setLength(0);
}

//------------------< Destructor  >---------------------
token::~token()
{
	length = 0;
	//setLength(0);
}

void token::setLength(int len)
{
	length = len;
}


void token::setElement()
{
	tokenData c;

	while (1)
	{
		cin.get(c); //cin>>c;는 space 인식 불가

		//종료조건(space, \n, 배열길이 넘는 문자열) 아니면 추가
		if (c != ' ' && c != '\n' && length < Max)
		{
			element[length] = c;
			length++;
		}
		//종료조건 맞으면 종료
		else
		{
			break;
		}

		//마지막 널문자추가
		element[length] = '\0';
	}


	// 나머지 입력 데이터 처리 	
	if (c != '\n')
		cin.ignore(80, '\n');

	//  혹은
	//	while ( c != '\n' )	
	//		cin.get(c);
}


int token::getLength()
{
	return length;
}

// element 속 내용 출력
// <>로 구분
// ex. 123 ==> <123>
//
void token::getElement()
{
	cout << '<';
	for (int i = 0; i < length; i++)
	{
		cout << element[i];
	}
	cout << '>';

}


void token::clear()
{
	length = 0;
	//setLength(0);
}

// 관찰자
// 매개변수 token t2와 내용이 같으면 true, 아니면 false값 반환하는 함수
//
bool token::isEqual(token t2)
{
	bool  equal;

	//길이 다르면 false
	if (length != t2.length)
		equal = false;

	//길이 같으면 loop로 각 내용이 같은지 확인
	else {
		equal = true;
		for (int i = 0; i < length; i++)
		{
			if (element[i] != t2.element[i])
			{
				equal = false;
				break;
			}
		}
		return equal;
	}

}

// 변환자
// 현재 토큰 뒤에 매개변수 token t2 를 추가
// ex. <123> + <45> ==> <12345>
//
void token::merge(token t2)
{
	int limit; //변수

	limit = Max - length;
	if (limit > t2.length)
		limit = t2.length;

	for (int i = 0; i < limit; i++)
	{
		element[length++] = t2.element[i];
		//length++;
	}

	//마지막에 널문자 추가
	element[length] = '\0';


}
// 변환자
// 토큰의 내용을 역으로 만듦
// 0<->n, 1<->n-2, 2<->n-2, ...
// ex. <123> ==> <321>
//
void token::reverse()
{
	int temp;

	for (int i = 0; i < length / 2; i++)
	{
		SWAP(element[i], element[length - 1 - i], temp);
	}

}

long token::intValue()
{
	long value = 0;

	for (int i = 0; i < length; i++)
	{
		value = value * 10 + ((int)element[i] - (int)'0');

	}
	return value;

}

// 관찰자
// 토큰 내 문자열 중 from부터 count개의 문자열을 공백 토큰 sub에 복사 
// ex. <123456> , from : 2, count : 3 ==> <234>
//
void token::subToken(token& sub, int from, int count)
{

	for (int i = 0; i < count; i++)
	{
		sub.element[i] = element[from - 1];
		sub.length++;
		from++;
	}

}


//과제1
//반복문을 이용해 기존 토큰 내 문자열을 뒤에 역으로 추가
// ex. <123> ==> <123321>
//
void token::toMirror1()
{

	length = length * 2;

	for (int i = 0; i < length / 2; i++)
	{
		element[length - 1 - i] = element[i];
	}
	element[length] = '\0';

}

// 과제2
// 기존 함수(subToken, reverse, merge)를 활용해 문자열을 뒤에 역으로 추가
// subToken 활용해 temp에 저장 ==> temp를 reverse함수 활용해 역으로 바꿈 ==> merge함수를 활용해 기존 문자열에 temp를 추가
// ex. <123> ==> <123321>
//
void token::toMirror2()
{
	token temp;
	subToken(temp, 1, length);
	temp.reverse();
	merge(temp);
}


