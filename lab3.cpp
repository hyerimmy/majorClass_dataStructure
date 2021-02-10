// LAB3

/* ���α׷� :  

���� �����ߴ� ���Ḯ��Ʈ�� �⺻ ������ �Ͽ�, ����� �������� �� ��尡 ����ǵ��� �Ѵ�. 
��, head node(ù���)�� prior�� ������ ��带 ����Ű��, ������ ����� next�� head node�� ����Ű���� �Ѵ�.

List ADT�� �����ϰ�, ���� �Է�, ����, Ŀ���̵�, �ڸ���, ���̱�, �����ϱ� ����� ����� �����Ѵ�.
����� ������ �� ��忡 ����� �� data�� �� ��带 ����Ű�� prior, �� ��带 ����Ű�� next�� �̷���� �ִ�.

*/

// 2019111309 Ȳ����
// 2020/09/22

#define SWAP(x, y, t) (t=x, x=y, y=t)

listNode:: listNode ()
{ }

// listNode ����
// node�� ���� : data(��忡 ����� ��), prior(�� ��� ����Ŵ), next(�� ��� ����Ŵ)
listNode::listNode(const listData newData, listNode *priorPtr, listNode *nextPtr)
{
	data = newData;
	prior = priorPtr;
	next = nextPtr;
}

// list ����
// list ���� : head(�� �� ���) , current(���� Ŀ���� ��ġ�� ���)
list::list()
{
	setHead(NULL);
	setCurrent(NULL);

}

list:: ~list ()
{
	clear();
}

// current �ٷ� �ڿ� data �߰�
//
void list:: insertNext ( listData newData )
{
    nodePtr p;    

	if (isEmpty()) // ����Ʈ�� ����ִٸ�?
	{
		p = new listNode; //�ӽ������ ��� p ����

		p->data = newData; // p�� ���� �Է¹��� ������ ����
		p->next = p; // �� ���� ��� : next, prior ��� �ڽ�(p)�� ����Ű����
		p->prior = p;
		setHead(p); //�� ���� ��� : head, current ��� p�� ����
		setCurrent(p);

	}
	else // ����Ʈ�� ������� �ʴٸ�?
	{
		p = new listNode; //�ӽ������ ��� p ����

		p->data = newData; // p�� ���� �Է¹��� ������ ����
		// node ���� : current - p(new) - ���� current->next
		p->prior = current; // current �ڷ� p�� �� : p�� prior�� current, p�� next�� current�� next
		p->next = current->next;
		current->next->prior = p;
		current->next = p;
		setCurrent(p);
	}
	size++; //��� �� �� �߰�
	position++; //current �ڿ� �߰��� ��� ��ġ�� position �� �̵�
}

void list:: removeCurrent()
{
    nodePtr p;				

    assert ( head != NULL );    // empty list ���� Ȯ��

	if (size == 1) // ���� ��尡 �� �����?
	{
		delete head;
		setHead(0);
		setCurrent(0);
		size = 0;
		position = 0;
	}
	else // ��尡 �� ������ ���ٸ�?
	{
		if (isLast()) //current�� ������ ����� current�� position ��� head ���� ����
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

// current �� ��� ����
// �˰���) ������ Ŀ�� �̵� - current ��� ����
void list::removePrior()
{
	gotoPrior();
	removeCurrent();
}

// ����Ʈ�� ��� ��� ����
// �˰���) ����Ʈ�� �� �� ���� current ��� ����
void list::clear()
{

	while (!isEmpty()) 
		removeCurrent();

//	setHead(NULL);
//	setCurrent(NULL);
}

// ���� ù ���� Ŀ���̵�
void list:: gotoFirst()
{
	current = head;
	position = 1; 

}

// current�� ���� ���� Ŀ�� �̵�
void list:: gotoNext()
{
	if (isLast()) // ���� ������ �����?
		position = 1; // position �� 1��
	else
		position++;

	current = current->next;
}

// list�� ������ ���� Ŀ�� �̵�
void list:: gotoLast()
{
	//while (!isLast())
	//	gotoNext();
	current = head->prior; // head->prior : ������ ���
}

// current�� ���� ���� Ŀ�� �̵�
void list::gotoPrior()
{
	if (isFirst()) // ���� current�� ù �����?
		position = size; // ������ ��� ��ġ(=size��)�� position �� ����
	else
		position--;
	setCurrent(current->prior);
}



// ***** --- (Setter) --- *****

void list:: setData(listData newData)
{
    assert ( head != NULL );    // empty list ���� Ȯ��
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

// ����Ʈ�� ����ִ°�?
// ����ִٸ� true ��ȯ
bool list:: isEmpty()
{
    return ( head == NULL );
}

// current�� ����Ʈ�� ù ����ΰ�?
// �´ٸ� true ��ȯ
bool list:: isFirst()
{
    assert ( head != NULL );    // empty list ���� Ȯ��
	return (head == current);
}

// current�� ����Ʈ�� ������ ����ΰ�?
// �´ٸ� true ��ȯ
bool list:: isLast()
{
    assert ( head != NULL );    // empty list ���� Ȯ��
	return (current->next == head);
	//return (head->prior == current);
}

// ��� �������� ���� ����
// ex) 1 2 (3) > (3) 2 1
void list::reverse()
{
	nodePtr	 p,       // next�� prior�� ��ȯ �� ��带 ����
		temp;    // SWAP ��ũ�ο� ��� �� �ӽ� ����
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

// current node �ڸ���
// �ڸ� ������ ��ȯ
listData list::cut() 
{
	listData cutData;

	cutData = getData();
	removeCurrent();
	return cutData;
}

// current node �����ϱ�
// ������ ������ ��ȯ
listData list::copy() 
{
	return getData();
}

//------------------< write() >----------------------
// list�� ����ϵ� current ���� ���������� ����Ѵ�
void list:: write () 
{
	nodePtr		p;   
//	int cp;

	if (isEmpty()) 
		cout << "empty list" << endl;
	else 
	{
		p = getCurrent();					// current ��ġ ���� 
		gotoFirst();						// ��� ������ ���� 
		while (1) 
		{
			if ( p == current)
			{
				int oldTextColor = GetColor(0);
				SetColor(12);				// ������
				cout << '\t' << getData();
				SetColor(oldTextColor);		// ���� ���ڻ�����!
			}
			else
				cout << '\t' << getData();
			if ( isLast() )					// �Ϸ� ?
				break;
			else
				gotoNext();					// ���� 
		} // while
		setCurrent(p);						// current ��ġ ����
	} // else
	cout << endl;
}




//------------< read: �����Է� >-------------------------------------
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
// current ��� �հ� �� ��� �ϳ��� ����
// ex) 1 2 (3) 4 5 > 1 (3) 5

void list::removeNextPrior1()
{
	nodePtr p, q;

	p = current->prior; //������ current->prior ��带 p��
	q = current->next ; //������ current->next ��带 p��

	// p �� ���� current ����
	p->prior->next = current; 
	current->prior = p->prior;

	// q �� ���� current ����
	q->next->prior = current;
	current->next = q->next;

	// ��带 �����ϴ� ���	
	if (position == 2)	// if (current->prior == head)
		head = head->next;

	// size, position update
	position--;
	size = size - 2;


	// ������� �ߴ� ��� p,q ����
	delete p;
	delete q;

}

// ���� list ADT �Լ� ȣ��θ� ����
// ����� removeNextPrior1()�� ����
void list::removeNextPrior2()
{

	removePrior(); // �� ��� ���� ( = current->prior ����)
	gotoNext(); // �ڷ� Ŀ�� �̵� (current �� ���� �̵�)
	removeCurrent(); // ���� ��� ����  ( = current->next ����)
	gotoPrior(); // �ٽ� ������ Ŀ�� �̵� (current ���� ����ġ)

}
