// LAB3

/* 프로그램 :  

기존 제작했던 연결리스트를 기본 구조로 하여, 양방향 원형으로 각 노드가 연결되도록 한다. 
즉, head node(첫노드)의 prior이 마지막 노드를 가리키며, 마지막 노드의 next가 head node를 가리키도록 한다.

List ADT를 정의하고, 숫자 입력, 삭제, 커서이동, 자르기, 붙이기, 복사하기 등등의 기능을 구현한다.
노드의 구조는 그 노드에 저장된 값 data와 앞 노드를 가리키는 prior, 뒤 노드를 가리키는 next로 이루어져 있다.

*/

// 2019111309 황혜림
// 2020/09/22

#define SWAP(x, y, t) (t=x, x=y, y=t)

listNode:: listNode ()
{ }

// listNode 정의
// node의 구조 : data(노드에 저장된 값), prior(앞 노드 가리킴), next(뒷 노드 가리킴)
listNode::listNode(const listData newData, listNode *priorPtr, listNode *nextPtr)
{
	data = newData;
	prior = priorPtr;
	next = nextPtr;
}

// list 정의
// list 구조 : head(맨 앞 노드) , current(현재 커서가 위치한 노드)
list::list()
{
	setHead(NULL);
	setCurrent(NULL);

}

list:: ~list ()
{
	clear();
}

// current 바로 뒤에 data 추가
//
void list:: insertNext ( listData newData )
{
    nodePtr p;    

	if (isEmpty()) // 리스트가 비어있다면?
	{
		p = new listNode; //임시저장소 노드 p 생성

		p->data = newData; // p에 새로 입력받은 데이터 저장
		p->next = p; // 한 개의 노드 : next, prior 모두 자신(p)을 가리키도록
		p->prior = p;
		setHead(p); //한 개의 노드 : head, current 모두 p로 지정
		setCurrent(p);

	}
	else // 리스트가 비어있지 않다면?
	{
		p = new listNode; //임시저장소 노드 p 생성

		p->data = newData; // p에 새로 입력받은 데이터 저장
		// node 순서 : current - p(new) - 원래 current->next
		p->prior = current; // current 뒤로 p가 들어감 : p의 prior이 current, p의 next가 current의 next
		p->next = current->next;
		current->next->prior = p;
		current->next = p;
		setCurrent(p);
	}
	size++; //노드 한 개 추가
	position++; //current 뒤에 추가된 노드 위치로 position 값 이동
}

void list:: removeCurrent()
{
    nodePtr p;				

    assert ( head != NULL );    // empty list 여부 확인

	if (size == 1) // 만약 노드가 한 개라면?
	{
		delete head;
		setHead(0);
		setCurrent(0);
		size = 0;
		position = 0;
	}
	else // 노드가 한 개보다 많다면?
	{
		if (isLast()) //current가 마지막 노드라면 current와 position 모두 head 노드로 설정
		{
			setHead(current);
			position = 1;
		}

		p = current->next; 
		current->data = p->data; 
		current->next = p->next;
		p->next->prior = current;
		delete p;
		size--;
	}

}

// current 앞 노드 삭제
// 알고리즘) 앞으로 커서 이동 - current 노드 삭제
void list::removePrior()
{
	gotoPrior();
	removeCurrent();
}

// 리스트의 모든 노드 삭제
// 알고리즘) 리스트가 빌 때 까지 current 노드 삭제
void list::clear()
{

	while (!isEmpty()) 
		removeCurrent();

//	setHead(NULL);
//	setCurrent(NULL);
}

// 제일 첫 노드로 커서이동
void list:: gotoFirst()
{
	current = head;
	position = 1; 

}

// current의 다음 노드로 커서 이동
void list:: gotoNext()
{
	if (isLast()) // 만약 마지막 노드라면?
		position = 1; // position 값 1로
	else
		position++;

	current = current->next;
}

// list의 마지막 노드로 커서 이동
void list:: gotoLast()
{
	//while (!isLast())
	//	gotoNext();
	current = head->prior; // head->prior : 마지막 노드
}

// current의 이전 노드로 커서 이동
void list::gotoPrior()
{
	if (isFirst()) // 만약 current가 첫 노드라면?
		position = size; // 마지막 노드 위치(=size값)로 position 값 변경
	else
		position--;
	setCurrent(current->prior);
}



// ***** --- (Setter) --- *****

void list:: setData(listData newData)
{
    assert ( head != NULL );    // empty list 여부 확인
	current->data = newData;
}

void list:: setCurrent(nodePtr newPtr)
{
	current = newPtr;
}

void list:: setHead(nodePtr newPtr)
{
	head = newPtr;
}

// ***** --- (Getter) --- *****

listData  list:: getData()
{
	assert(current);
	return current->data;
}

nodePtr list:: getCurrent()		
{
	assert(current);
	return current;
}

nodePtr list:: getHead()		
{
	assert(head);
	return head;
}

int list::getSize()
{
	return size;
}

int list::getPosition()
{
	return position;
}

// 리스트가 비어있는가?
// 비어있다면 true 반환
bool list:: isEmpty()
{
    return ( head == NULL );
}

// current가 리스트의 첫 노드인가?
// 맞다면 true 반환
bool list:: isFirst()
{
    assert ( head != NULL );    // empty list 여부 확인
	return (head == current);
}

// current가 리스트의 마지막 노드인가?
// 맞다면 true 반환
bool list:: isLast()
{
    assert ( head != NULL );    // empty list 여부 확인
	return (current->next == head);
	//return (head->prior == current);
}

// 노드 역순으로 순서 변경
// ex) 1 2 (3) > (3) 2 1
void list::reverse()
{
	nodePtr	 p,       // next와 prior를 교환 할 노드를 지시
		temp;    // SWAP 매크로에 사용 할 임시 변수
	int oldPosition = getPosition();	// **

	p = head;
	for (int i = 0; i < getSize(); i++)
	{
		SWAP(p->next, p->prior, temp);
		p = p->prior;
	}
	head = head->next;
	position = getSize() - oldPosition + 1; // **
}

// current node 자르기
// 자른 데이터 반환
listData list::cut() 
{
	listData cutData;

	cutData = getData();
	removeCurrent();
	return cutData;
}

// current node 복사하기
// 복사한 데이터 반환
listData list::copy() 
{
	return getData();
}

//------------------< write() >----------------------
// list를 출력하되 current 노드는 빨간색으로 출력한다
void list:: write () 
{
	nodePtr		p;   
//	int cp;

	if (isEmpty()) 
		cout << "empty list" << endl;
	else 
	{
		p = getCurrent();					// current 위치 저장 
		gotoFirst();						// 헤드 노드부터 시작 
		while (1) 
		{
			if ( p == current)
			{
				int oldTextColor = GetColor(0);
				SetColor(12);				// 빨간색
				cout << '\t' << getData();
				SetColor(oldTextColor);		// 원래 글자색으로!
			}
			else
				cout << '\t' << getData();
			if ( isLast() )					// 완료 ?
				break;
			else
				gotoNext();					// 전진 
		} // while
		setCurrent(p);						// current 위치 복원
	} // else
	cout << endl;
}




//------------< read: 파일입력 >-------------------------------------
//
void list:: read ( ifstream &input_file ) 
{
	listData c;

	input_file.seekg(0, ios::beg);
	while ( input_file.get(c) ) 
		insertNext(c);
	input_file.close();
}

// removeNextPrior
// current 노드 앞과 뒤 노드 하나씩 삭제
// ex) 1 2 (3) 4 5 > 1 (3) 5

void list::removeNextPrior1()
{
	nodePtr p, q;

	p = current->prior; //삭제할 current->prior 노드를 p로
	q = current->next ; //삭제할 current->next 노드를 p로

	// p 앞 노드와 current 연결
	p->prior->next = current; 
	current->prior = p->prior;

	// q 뒤 노드와 current 연결
	q->next->prior = current;
	current->next = q->next;

	// 헤드를 삭제하는 경우	
	if (position == 2)	// if (current->prior == head)
		head = head->next;

	// size, position update
	position--;
	size = size - 2;


	// 지우고자 했던 노드 p,q 삭제
	delete p;
	delete q;

}

// 기존 list ADT 함수 호출로만 구현
// 기능은 removeNextPrior1()과 동일
void list::removeNextPrior2()
{

	removePrior(); // 앞 노드 삭제 ( = current->prior 삭제)
	gotoNext(); // 뒤로 커서 이동 (current 뒷 노드로 이동)
	removeCurrent(); // 현재 노드 삭제  ( = current->next 삭제)
	gotoPrior(); // 다시 앞으로 커서 이동 (current 노드로 원위치)

}
