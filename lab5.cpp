// LAB5

/* ���α׷� ����

�ϳ� �̻��� ���� �̷���� �������� Ʈ�� ������ Ȱ���� ���� ��� Ʈ���� �����Ѵ�.
Ʈ���� ������ root�� current�� �Ǿ� �ְ�, Ʈ���� ���� left, data, right�� �̷���� �ִ�.


Ư�� ����Ʈ���� ��ȸ�ϸ� ���� �����ϴ� �Լ��� ���� ���ǵǾ� �ִ�.
��ȸ�� �� ������ ���� ����(DLR), ����(LDR), ����(LRD) �� ������ ����ȴ�.

*/

// 2019111309
// Ȳ����
// �ڷᱸ��
// 2020/10/06

#define SWAP(x, y, t) (t=x, x=y, y=t)

etreeNode:: etreeNode ()
{}

etreeNode:: etreeNode (etreeData newData, enodePtr lptr, enodePtr rptr)
{
	data = newData;
	left = lptr;
	right = rptr;
}

//������
etree:: etree ()
{
	setRoot(0);
	setCurrent(0);
}

//�Ҹ���
etree:: ~etree ()
{
	clear();
}

void etree:: build ()
{
	buildSub(root);
}

// ���� ������ ��� ���� (<->���)
// ���� ���� ��带 ���� ��忡 �����ϴ°� �����. **
// ������ <�ּ����� : pointer>, <�������� : reference>


void etree:: buildSub ( enodePtr &p )//�Ű����� p�� reference
{
	etreeData ch;  

	cin >> ch;
	p = new etreeNode(ch, 0, 0);
	current = p;

	if (!isdigit(p->data)) //�������϶� ���ȣ��
	{
		buildSub(p->left);
		buildSub(p->right);
	}
}

void etree:: read (ifstream  &input_file)
{
	readSub( input_file, root );
}

void etree:: readSub ( ifstream  &input_file, enodePtr &p )
{
	etreeData ch;   

	input_file >> ch;
	p = new etreeNode(ch, 0, 0);
	current = p;

	if (!isdigit(p->data)) //�������϶� ���ȣ��
	{
		readSub(input_file, p->left);
		readSub(input_file, p->right);
	}

}

//goto~
// root, left, right ���� �̵��ϴ� �Լ�

void etree:: gotoRoot() 
{
	current = root;
}

void etree:: gotoLeft() 
{
	current = current->left;
}

void etree:: gotoRight()
{
	current = current->right;
}

// ���� Ʈ���� ����ִ� Ʈ������ Ȯ���ϴ� �Լ� (�ᱹ�� root ����)
bool etree:: isEmpty () 
{
	return root == 0;
}

// ���� ��尡 ����ִ��� Ȯ���ϴ� �Լ�
bool etree:: isLeftEmpty () 
{
	return current->left == 0;
}

// ������ ��尡 ����ִ��� Ȯ���ϴ� �Լ�
bool etree:: isRightEmpty () 
{
	return current->right == 0;
}

// ���� ��尡 ��Ʈ ������� Ȯ���ϴ� �Լ�
bool etree:: isRoot () 
{
	return current == root;
}

// ���� ��尡 ���� ���(���̻��� �ڽ� ��尡 ����)���� Ȯ���ϴ� �Լ�
// left, right ��� �ڽĳ�尡 ������ Ȯ��
bool etree:: isLeaf (enodePtr p)
{
	return p->left == 0 && p->right == 0;
}
// <--------------------------------------getter------------------------------------>
// get~
// data, current, root ���� �ҷ��� ��ȯ�ϴ� �Լ�

etreeData etree:: getData() 
{
	return current->data;
}

enodePtr etree:: getCurrent()		 
{
	return current;
}

enodePtr etree:: getRoot()		 
{
	return root;
}

// <--------------------------------------setter------------------------------------>
// set~
// data, current, root ���� ���ο� ������ �����ϴ� �Լ�

void etree:: setData ( etreeData newData ) 
{
	current->data = newData;
}

void etree:: setCurrent(enodePtr newPtr)
{
	current = newPtr;
}

void etree:: setRoot(enodePtr newPtr)
{
	root = newPtr;
}

void etree:: expression () 
{
	expressionSub(root);
}

//������ ����ϴ� �Լ�
//�����ڳ� �ǿ����ڳĸ� �����ؼ� ��ȣ�� ���� �� ( '+':������, '3':�ǿ����� )
//�������̸� ��ȣ�� ������ ��.
void etree:: expressionSub ( enodePtr p ) 
{
	if (p)
	{
		// ������?-> (���
		if (p->data == '*' || p->data == '/' || p->data == '+' || p->data == '-') //�������̸�
		//if(!isdigit(p->data)) //���ڰ� ���ڸ� ��Ÿ���� T��ȯ.
			cout << '('; //��ȣ�� ��
		
		
		expressionSub(p->left);		// L ���ȣ��
		cout << p->data;
		expressionSub(p->right);	//R

		if (isdigit(p->data) == 0) //�´��� �� �� �� Ȯ��
			cout << ')';
	}

}

double etree:: calculate ()
{
	return calculateSub(root);
}

double etree:: calculateSub ( enodePtr p )
{
	double l, r,result;	

	//�ǿ����� -> ���ڸ� ���ڷ� ��ȯ : �ƽ�Ű�ڵ� ���ų� int�� ����ȯ
	if (isdigit(p->data))
		result = p->data - '0';	//�����Ϸ��� �˾Ƽ� �ƽ�Ű�ڵ� ã�Ƽ� ����ȯ���� �������!!!
		//result = (int)p->data - (int)'0';
	//������ -> ���ȣ��
	else
	{
		l = calculateSub(p->left);
		r = calculateSub(p->right);
		//D
		// if(p->data == '+') elseif�� 3�� �̻� ������ ��� switch������ �� ����
		switch (p->data) 
		{
		case '*': result = l * r; break;
		case '+': result = l + r; break;
		case '-': result = l - r; break;
		case '/': result = l / r; break;
		}
	}
	return result;
}

void etree:: clear ()
{
	clearSub(root);
	setRoot(NULL);
}


// ������ �����ϴ� �Լ�
// ���ȣ�� Ȱ��
void etree:: clearSub ( enodePtr p )
{
	if (p != 0)
	{
		clearSub(p->left);	//L
		clearSub(p->right);	//R
		delete p;			//D
	}

}

void etree::postfix()
{
	postfixSub(root);
}

// ������ ��ȯ
// ���ȣ�� Ȱ��
void etree::postfixSub(enodePtr p)
{
	//if (p != 0)
	if (p)
	{
		postfixSub(p->left);
		postfixSub(p->right);
		cout << p->data;
	}

}

// �θ� ���� �̵�, root�� found ���� prarentSub�Լ��� ����.
void etree:: gotoParent ()
{  
	bool found = false;   
	parentSub( root, found );
}

// ���������� �θ� �ǵ�� �̵��ϴ� ����� �߻��Ǵ� �Լ�
// ���� ������ p->left�� right�� parent���� ���ϴ� ����
//DLR : L���� ã���� R�� ���� ���� : found ���� Ȱ��
void etree:: parentSub( enodePtr p, bool &found)
{
	if (!isRoot())	//D
	{
		if (p->left == current || p->right == current)
		{
			found = true;
			current = p;
		}
		else
		{
			if (p->left != 0)	//L
				parentSub(p->left, found);
			if (!found && p->left != 0)		//R
				parentSub(p->right, found);

		}
	}
	

}

// ������� �����ϴ� �Լ�
// ���� ��带 p�� �ӽ������� ���� ������.
// �θ��Լ��� �� ��, ������ ���� ���(p)���ٸ� ������ ��� ����, �ƴϸ� ���� ����
void etree::removeSubtree()
{
	enodePtr p;
	if (isRoot())
		clear();
	else
	{
		p = getCurrent();
		gotoParent();
		if (current->left == p)
			current->left = NULL;
		else
			current->right = NULL;
		clearSub(p);
	}
}


void etree:: swap ()
{
	swapSub(root);
}

//������ swap
void etree:: swapSub ( enodePtr p )
{
	enodePtr temp;    

	if (p)
	{
		swapSub(p->left);	// L
		swapSub(p->right);	// R
		SWAP(p->left, p->right, temp);	//temp �̿��ؼ� left�� right �ٲ�
	}

}

int etree:: height ()
{
	return heightSub(root);
}

// ���� LRD
// L�� R �� ��ȯ�Ǹ� �� �� ū������ 1�� �� ������ ��. (D����)
int etree:: heightSub( enodePtr p )		// postOrder
{
	int l, r, height;

	if (p == 0) //��尡 �ϳ��� ���ٴ� ��
		height = 0;
	else if (isLeaf(p))
		height = 1;
	else
	{
		l = heightSub(p->left);
		r = heightSub(p->right);
		if (l > r)
			height = l + 1;

		else
			height = r + 1;
	}

	return height;

}

void etree:: print() 

{
	if ( isEmpty() )
		cout << "Empty tree" << endl;
	else
	{
		cout << endl;
		printSub(root, 1);
		cout << endl;
	}
}

void etree:: printSub ( enodePtr p, int level ) 
{
	int j, oldTextColor;   

	if ( p != 0 )
	{
		printSub(p->right,level+1);						// R : Output right subtree

		for ( j = 0 ; j < level ; j++ )					// level ���� tab ���
			cout << '\t';
		oldTextColor = GetColor(0);
		if (p == current) 
			SetColor(12);								// ������
		cout << p->data;								// D
		SetColor(oldTextColor);							// ���� ���ڻ�����!
		// ������ ���		
		if ( ( p->left != 0 ) && ( p->right != 0 ) )	// ���� �ڽ�?      < ���
			cout <<'<';
		else if ( p->right != 0 )						// ���� �ڽĸ�?    / ���  
			cout << '/';
		else if ( p->left != 0 )						// ������ �ڽĸ�?  \ ���  
			cout << '\\';
		cout << endl;

		printSub(p->left,level+1);						// L : Output left subtree
	}
}

int etree::size()
{
	return sizeSub(root);
}


int etree::sizeSub(enodePtr p) //p�� root�Ѿ��
{
	int size;

	// l�� r�� �� L, R ��� �� ����, D���� l+r+1
	// �ʿ��ϸ� int l,r �����ؼ� ����ص� ��.
	// height ����ϴ� �Ͱ� ������ ������ ����.



	if (p == 0) //root==0 �� ���� �ǹ�.
		size = 0; // root�� 0�̶��[����ִ� Ʈ�����] ������ 0

	else
	{
		if (isLeaf(p)) //���� ���� ����� ������� 1
			size = 1;

		else
			size = sizeSub(p->left) + sizeSub(p->right) + 1; // +1 : D�� �������� ���Ѵ� (D�� �׻� �ϳ�)
	}
	return size;

}
