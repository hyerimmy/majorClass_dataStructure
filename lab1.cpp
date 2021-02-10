/*

���α׷� ����: ���ڿ��� �پ��� ����� �����ϴ� token class�� ����
	- Ű���忡�� ���ڿ��� �о� ��ū�� ���� : setElement()
	- ȭ�鿡 ��ū ��� : getElement()
	- �� ���� ��ū�� ������ ������ true, �ƴϸ� false�� ��ȯ : isEqual(token t)
	- ��ū�� ������ ��� ���� : clear()
	- ���� ��ū �ڿ� token t�� �߰� : merge(token t)
	- ��ū�� ������ ������ ���� : reverse()
	- ��ū �� ���ڿ� �� from���� count���� ���ڿ��� ���� ��ū sub�� ���� : subToken(token &sub, int from, int coung)
	* �ݺ����� �̿��� ���� ��ū �� ���ڿ��� �ڿ� ������ �߰� : toMirror1()
	* ���� �Լ�(subToken, reverse, merge)�� Ȱ���� ���ڿ��� �ڿ� ������ �߰� : toMirror2()
	
�й� : 2019111309
�̸� : Ȳ����
�й� : ȭ 5-6 
��¥ : 2020/09/14

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
		cin.get(c); //cin>>c;�� space �ν� �Ұ�

		//��������(space, \n, �迭���� �Ѵ� ���ڿ�) �ƴϸ� �߰�
		if (c != ' ' && c != '\n' && length < Max)
		{
			element[length] = c;
			length++;
		}
		//�������� ������ ����
		else
		{
			break;
		}

		//������ �ι����߰�
		element[length] = '\0';
	}


	// ������ �Է� ������ ó�� 	
	if (c != '\n')
		cin.ignore(80, '\n');

	//  Ȥ��
	//	while ( c != '\n' )	
	//		cin.get(c);
}


int token::getLength()
{
	return length;
}

// element �� ���� ���
// <>�� ����
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

// ������
// �Ű����� token t2�� ������ ������ true, �ƴϸ� false�� ��ȯ�ϴ� �Լ�
//
bool token::isEqual(token t2)
{
	bool  equal;

	//���� �ٸ��� false
	if (length != t2.length)
		equal = false;

	//���� ������ loop�� �� ������ ������ Ȯ��
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

// ��ȯ��
// ���� ��ū �ڿ� �Ű����� token t2 �� �߰�
// ex. <123> + <45> ==> <12345>
//
void token::merge(token t2)
{
	int limit; //����

	limit = Max - length;
	if (limit > t2.length)
		limit = t2.length;

	for (int i = 0; i < limit; i++)
	{
		element[length++] = t2.element[i];
		//length++;
	}

	//�������� �ι��� �߰�
	element[length] = '\0';


}
// ��ȯ��
// ��ū�� ������ ������ ����
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

// ������
// ��ū �� ���ڿ� �� from���� count���� ���ڿ��� ���� ��ū sub�� ���� 
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


//����1
//�ݺ����� �̿��� ���� ��ū �� ���ڿ��� �ڿ� ������ �߰�
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

// ����2
// ���� �Լ�(subToken, reverse, merge)�� Ȱ���� ���ڿ��� �ڿ� ������ �߰�
// subToken Ȱ���� temp�� ���� ==> temp�� reverse�Լ� Ȱ���� ������ �ٲ� ==> merge�Լ��� Ȱ���� ���� ���ڿ��� temp�� �߰�
// ex. <123> ==> <123321>
//
void token::toMirror2()
{
	token temp;
	subToken(temp, 1, length);
	temp.reverse();
	merge(temp);
}


