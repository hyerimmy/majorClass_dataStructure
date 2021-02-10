/*

���α׷� ����: �������� �Ҵ� �� �޸��� ���ᱸ���� ǥ���Ǵ� �ܹ��� ���� ����Ʈ�� ���� list Abstract Data Type(ADT)�� �����ϰ� ����

	- ����Ʈ�� �� ���� listData���� �����͸� ���´�
	- ����Ʈ���� ���� ������ �� �ִ� ���� head node�� current node �� ���� �ִ�.
	- ���ڸ� �Է��ϰ� Ŀ���̵�, �����, ����, �ڸ���, �ٿ��ֱ� ���� ����� �����ϴ� ���α׷��̴�.

�й� : 2019111309
�̸� : Ȳ����
�й� : ȭ 5-6
������¥ : 2020/09/15

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

//current node ������ ���ο� ��带 �߰�
// 12(3) > 123(4)
//

void list::insertNext(listData newData)
{
	nodePtr p;

	p = new listNode; //1
	p->data = newData; //2

	if (isEmpty()) //���� ����Ʈ�� ����ִٸ�?
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

//------------< read: �����Է� >-------------------------------------
void list::read(ifstream& input_file)
{
	listData c;

	input_file.seekg(0, ios::beg);
	while (input_file.get(c))
		insertNext(c);
	input_file.close();
}


// current ��� ����
// 1(2)3 > 1(3)
//
void list::removeCurrent()
{
	listNode* p,
		* before;

	assert(!isEmpty());

	if (isFirst()) //����带 ����?
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

// current ���� ��� ����
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

// current node�� current node �ٷ� ������ �̵�
// 12(3)4 > (1)234
//
void list::gotoFirst()
{
	current = head; //setCurrent(head);
}

// current node�� current node �ٷ� �������� �̵�
// 12(3)4 > 123(4)
//
void list::gotoNext()
{
	current = current->next; //setCurrent(current->next);
}

// current node�� list�� ������ ���� �̵�
// 1(2)34 > 123(4)
//
void list::gotoLast()
{
	while (!isLast())
		gotoNext();
}

// current node�� list�� ù ��° ���� �̵�
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

// list�� ������� Ȯ��
// empty�� true, �ƴϸ� flase ��ȯ
//
bool list::isEmpty()
{

	if (head == 0)
		return true;
	else
		return false;

	//return (head==0);

}

// current node�� ��������� Ȯ��
// ������̸� true, �ƴϸ� flase ��ȯ
//
bool list::isFirst()
{
	if (head == current)
		return true;
	else
		return false;

	//return (head == current);

}

// current node�� list�� ������ ������� Ȯ��
// ����������̸� true, �ƴϸ� flase ��ȯ
//
bool list::isLast()
{
	return (!current->next);
	//return (current->next == 0);
}

// list�� ��� ��� ����
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

// current node �߶󳻱�
// 12(3)4 > 12(4) + 3 ��ȯ
//
listData list::cut()
{
	listData cutData;
	cutData = current->data;
	removeCurrent();
	return cutData;
}

// current node �����ϱ�
// 12(3)4 > 12(3)4 + 3 ��ȯ
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

// list�� ����ϵ� current ���� ���������� ����Ѵ�
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
				SetColor(12);				// ������
				cout << '\t' << p->data;
				SetColor(oldTextColor);		// ���� ���ڻ�����!
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
				setColor(12);				// ������
				cout << '\t' << p->data;
				SetColor(oldTextColor);		// ���� ���ڻ�����!
			}
			else
				cout << '\t' << p->data;
	*/
	cout << endl;
}

void list::merge()
{

	if (isEmpty()) //����Ʈ�� �Էµ� ���� ���ٸ�?
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
