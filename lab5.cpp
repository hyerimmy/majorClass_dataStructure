// LAB5

/* 프로그램 설명

하나 이상의 노드로 이루어진 유한집합 트리 구조를 활용해 이진 산술 트리를 구현한다.
트리의 구조는 root와 current로 되어 있고, 트리의 노드는 left, data, right로 이루어져 있다.


특히 이진트리를 순회하며 일을 수행하는 함수가 많이 정의되어 있다.
순회늰 각 목적에 따라 전위(DLR), 중위(LDR), 후위(LRD) 중 선택해 진행된다.

*/

// 2019111309
// 황혜림
// 자료구조
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

//생성자
etree:: etree ()
{
	setRoot(0);
	setCurrent(0);
}

//소멸자
etree:: ~etree ()
{
	clear();
}

void etree:: build ()
{
	buildSub(root);
}

// 전위 순서로 노드 생성 (<->출력)
// 새로 만든 노드를 기존 노드에 연결하는게 어려움. **
// 값전달 <주소전달 : pointer>, <참조전달 : reference>


void etree:: buildSub ( enodePtr &p )//매개변수 p는 reference
{
	etreeData ch;  

	cin >> ch;
	p = new etreeNode(ch, 0, 0);
	current = p;

	if (!isdigit(p->data)) //연산자일때 재귀호출
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

	if (!isdigit(p->data)) //연산자일때 재귀호출
	{
		readSub(input_file, p->left);
		readSub(input_file, p->right);
	}

}

//goto~
// root, left, right 노드로 이동하는 함수

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

// 현재 트리가 비어있는 트리인지 확인하는 함수 (결국은 root 유무)
bool etree:: isEmpty () 
{
	return root == 0;
}

// 왼쪽 노드가 비어있는지 확인하는 함수
bool etree:: isLeftEmpty () 
{
	return current->left == 0;
}

// 오른쪽 노드가 비어있는지 확인하는 함수
bool etree:: isRightEmpty () 
{
	return current->right == 0;
}

// 현재 노드가 루트 노드인지 확인하는 함수
bool etree:: isRoot () 
{
	return current == root;
}

// 현재 노드가 말단 노드(더이상의 자식 노드가 없음)인지 확인하는 함수
// left, right 모두 자식노드가 없는지 확인
bool etree:: isLeaf (enodePtr p)
{
	return p->left == 0 && p->right == 0;
}
// <--------------------------------------getter------------------------------------>
// get~
// data, current, root 등을 불러와 반환하는 함수

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
// data, current, root 등을 새로운 값으로 설정하는 함수

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

//중위로 출력하는 함수
//연산자냐 피연산자냐를 구분해서 괄호를 여는 것 ( '+':연산자, '3':피연산자 )
//연산자이면 괄호를 열도록 함.
void etree:: expressionSub ( enodePtr p ) 
{
	if (p)
	{
		// 연산자?-> (출력
		if (p->data == '*' || p->data == '/' || p->data == '+' || p->data == '-') //연산자이면
		//if(!isdigit(p->data)) //문자가 숫자를 나타내면 T반환.
			cout << '('; //괄호를 엶
		
		
		expressionSub(p->left);		// L 재귀호출
		cout << p->data;
		expressionSub(p->right);	//R

		if (isdigit(p->data) == 0) //맞는지 한 번 더 확인
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

	//피연산자 -> 문자를 숫자로 변환 : 아스키코드 쓰거나 int로 형변환
	if (isdigit(p->data))
		result = p->data - '0';	//컴파일러가 알아서 아스키코드 찾아서 형변환시켜 계산해줌!!!
		//result = (int)p->data - (int)'0';
	//연산자 -> 재귀호출
	else
	{
		l = calculateSub(p->left);
		r = calculateSub(p->right);
		//D
		// if(p->data == '+') elseif가 3개 이상 나오는 경우 switch구문이 더 좋음
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


// 후위로 삭제하는 함수
// 재귀호출 활용
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

// 후위로 순환
// 재귀호출 활용
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

// 부모 노드로 이동, root랑 found 변수 prarentSub함수로 보냄.
void etree:: gotoParent ()
{  
	bool found = false;   
	parentSub( root, found );
}

// 실질적으로 부모 ㅗ드로 이동하는 기능이 발생되는 함수
// 전위 순서로 p->left나 right가 parent인지 비교하는 연산
//DLR : L에서 찾으면 R을 가지 않음 : found 변수 활용
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

// 형제노드 삭제하는 함수
// 현재 노드를 p에 임시저장해 형제 구분함.
// 부모함수로 간 후, 왼쪽이 본인 노드(p)였다면 오른쪽 노드 삭제, 아니면 왼쪽 삭제
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

//후위로 swap
void etree:: swapSub ( enodePtr p )
{
	enodePtr temp;    

	if (p)
	{
		swapSub(p->left);	// L
		swapSub(p->right);	// R
		SWAP(p->left, p->right, temp);	//temp 이용해서 left와 right 바꿔
	}

}

int etree:: height ()
{
	return heightSub(root);
}

// 후위 LRD
// L과 R 값 반환되면 그 중 큰값보다 1이 더 많도록 함. (D에서)
int etree:: heightSub( enodePtr p )		// postOrder
{
	int l, r, height;

	if (p == 0) //노드가 하나도 없다는 뜻
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

		for ( j = 0 ; j < level ; j++ )					// level 별로 tab 출력
			cout << '\t';
		oldTextColor = GetColor(0);
		if (p == current) 
			SetColor(12);								// 빨간색
		cout << p->data;								// D
		SetColor(oldTextColor);							// 원래 글자색으로!
		// 연결자 출력		
		if ( ( p->left != 0 ) && ( p->right != 0 ) )	// 양쪽 자식?      < 출력
			cout <<'<';
		else if ( p->right != 0 )						// 왼쪽 자식만?    / 출력  
			cout << '/';
		else if ( p->left != 0 )						// 오른쪽 자식만?  \ 출력  
			cout << '\\';
		cout << endl;

		printSub(p->left,level+1);						// L : Output left subtree
	}
}

int etree::size()
{
	return sizeSub(root);
}


int etree::sizeSub(enodePtr p) //p에 root넘어옴
{
	int size;

	// l과 r에 각 L, R 노드 수 저장, D에서 l+r+1
	// 필요하면 int l,r 선언해서 사용해도 됨.
	// height 계산하는 것과 굉장히 유사할 것임.



	if (p == 0) //root==0 과 같은 의미.
		size = 0; // root가 0이라면[비어있는 트리라면] 사이즈 0

	else
	{
		if (isLeaf(p)) //만약 말단 노드라면 사이즈는 1
			size = 1;

		else
			size = sizeSub(p->left) + sizeSub(p->right) + 1; // +1 : D를 마지막에 더한다 (D는 항상 하나)
	}
	return size;

}
