/*

프로그램 설명: 동적으로 할당 된 메모리의 연결구조로 표현되는 단방향 연결 리스트에 대한 list Abstract Data Type(ADT)을 정의하고 구현

	- 리스트의 각 노드는 listData형의 데이터를 갖는다
	- 리스트엥서 직접 참조할 수 있는 노드는 head node와 current node 두 개가 있다.
	- 문자를 입력하고 커서이동, 지우기, 복사, 자르기, 붙여넣기 등의 기능을 구현하는 프로그램이다.

학번 : 2019111309
이름 : 황혜림
분반 : 화 5-6
수업날짜 : 2020/09/15

*/

#define SWAP(x, y, t) (t=x, x=y, y=t)

listNode::listNode()
{
}

listNode::listNode(listData newData, nodePtr p)
{
	data = newData;
	next = p;
}

list::list()
{
	head = NULL;
	current = 0;
}

list:: ~list()
{
	clear();
}

//current node 다음에 새로운 노드를 추가
// 12(3) > 123(4)
//

void list::insertNext(listData newData)
{
	nodePtr p;

	p = new listNode; //1
	p->data = newData; //2

	if (isEmpty()) //만약 리스트가 비어있다면?
	{
		p->next = 0; //3
		head = p; //4
	}
	else
	{
		p->next = current->next; //3
		current->next = p; //4
	}
	current = p; //5

}

//------------< read: 파일입력 >-------------------------------------
void list::read(ifstream& input_file)
{
	listData c;

	input_file.seekg(0, ios::beg);
	while (input_file.get(c))
		insertNext(c);
	input_file.close();
}


// current 노드 삭제
// 1(2)3 > 1(3)
//
void list::removeCurrent()
{
	listNode* p,
		* before;

	assert(!isEmpty());

	if (isFirst()) //헤드노드를 삭제?
	{
		p = head;
		head = head->next;
		current = current->next; //gotoNext();
		delete p;
	}
	else
	{
		p = current;
		gotoPrior(); before = current; gotoNext(); //2
		before->next = current->next; //3
		//4
		if (isLast())
			gotoFirst();
		else
			gotoNext();
		delete p; //5
	}


}

// current 이전 노드 삭제
// 12(3) > 1(3)
//
void list::removePrior()
{
	assert(!isFirst());
	gotoPrior();
	removeCurrent();
}

void list::setData(listData newData)
{
	current->data = newData;
}

void list::setCurrent(nodePtr newPtr)
{
	current = newPtr;
}

void list::setHead(nodePtr newPtr)
{
	head = newPtr;
}

listData  list::getData()
{
	assert(current);
	return current->data;
}

nodePtr list::getCurrent()
{
	assert(current);
	return current;

}

nodePtr list::getHead()
{
	assert(head);
	return head;
}

// current node를 current node 바로 앞으로 이동
// 12(3)4 > (1)234
//
void list::gotoFirst()
{
	current = head; //setCurrent(head);
}

// current node를 current node 바로 다음으로 이동
// 12(3)4 > 123(4)
//
void list::gotoNext()
{
	current = current->next; //setCurrent(current->next);
}

// current node를 list의 마지막 노드로 이동
// 1(2)34 > 123(4)
//
void list::gotoLast()
{
	while (!isLast())
		gotoNext();
}

// current node를 list의 첫 번째 노드로 이동
// 12(3)4 > (1)234
//
void list::gotoPrior()
{
	nodePtr p;

	p = head;
	while (p->next != current)
		p = p->next;
	current = p;

}

// list가 비었는지 확인
// empty면 true, 아니면 flase 반환
//
bool list::isEmpty()
{

	if (head == 0)
		return true;
	else
		return false;

	//return (head==0);

}

// current node가 헤드노드인지 확인
// 헤드노드이면 true, 아니면 flase 반환
//
bool list::isFirst()
{
	if (head == current)
		return true;
	else
		return false;

	//return (head == current);

}

// current node가 list의 마지막 노드인지 확인
// 마지막노드이면 true, 아니면 flase 반환
//
bool list::isLast()
{
	return (!current->next);
	//return (current->next == 0);
}

// list의 모든 노드 삭제
// 12(3) > 
//
void list::clear()
{
	//gotoFirst();
	while (!isEmpty())
		removeCurrent();
	//head = 0;
	//current = 0;

}

// current node 잘라내기
// 12(3)4 > 12(4) + 3 반환
//
listData list::cut()
{
	listData cutData;
	cutData = current->data;
	removeCurrent();
	return cutData;
}

// current node 복사하기
// 12(3)4 > 12(3)4 + 3 반환
//
listData list::copy()
{
	return current->data;
}


int list::size()
{
	int i = 0;
	listNode* p;

	if (!isEmpty())
	{
		p = head;
		while (p)
		{
			i++;
			p = p->next;
		}
	}
	return(i);
}

int list::position()
{
	int i = 0;
	listNode* p;

	if (!isEmpty())
	{
		i = 1;
		p = head;
		while (p != current)
		{
			i++;
			p = p->next;
		}
	}
	return(i);
}

// list를 출력하되 current 노드는 빨간색으로 출력한다
void list::write()
{
	nodePtr	p;

	if (isEmpty())
		cout << "empty list";
	else
	{
		p = head;
		while (p)
		{
			if (p == current)
			{
				int oldTextColor = GetColor(0);
				SetColor(12);				// 빨간색
				cout << '\t' << p->data;
				SetColor(oldTextColor);		// 원래 글자색으로!
			}
			else
				cout << '\t' << p->data;
			p = p->next;
		} // while
	}
	/*
		for ( p = head ; p != 0 ; p = p->next )
			if ( p == current)
			{
				int oldTextColor = GetColor(0);
				setColor(12);				// 빨간색
				cout << '\t' << p->data;
				SetColor(oldTextColor);		// 원래 글자색으로!
			}
			else
				cout << '\t' << p->data;
	*/
	cout << endl;
}

void list::merge()
{

	if (isEmpty()) //리스트에 입력된 것이 없다면?
	{
		t.gotoLast(); //1
		setHead(t.head); //2
		setCurrent(t.current); //3
		t.setHead(0); //4
		t.setCurrent(0); //5
	}
	else
	{
		nodePtr p;

		p = current->next; //0
		current->next = t.head; //1
		t.gotoLast(); //2
		t.current->next = p; //3
		setCurrent(t.current); //4
		t.setHead(0); //5
		t.setCurrent(0); //6
 
	}

}
