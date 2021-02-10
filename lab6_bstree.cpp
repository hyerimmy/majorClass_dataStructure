// LAB6 - bstree.cpp

/* 프로그램 설명

하나 이상의 노드로 이루어진 트리를 이루는 구조이며, 각 노드는 최대 2개의 서브 트리를 가질 수 있다.
트리의 구조는 root와 current로 되어 있고, 트리의 노드는 left, data, right로 이루어져 있다.

특히, lab05와 비교했을 때 각 노드는 비교 연산의 기준이 되는 KEY 값을 갖는다는 점이 차별점이다.
자신의 왼쪽 서브트리의 노드들은 자신의 key값 보다 작은 key 값들을, 오른쪽은 큰 key 값들을 갖는다.

+ setData 함수(current값 원하는 값으로 변경하는 함수) 없는것이 lab05와의 다른 특징이다.
+ lab06에만의 전용함수가 추가되었다. (insert, remove, find, count)

이진트리를 순회하며 일을 수행하는 함수가 많이 정의되어 있다.
순회는 각 목적에 따라 전위(DLR), 중위(LDR), 후위(LRD) 중 선택해 진행된다.

*/

// 2019111309
// 황혜림
// 자료구조
// 2020/10/13




// bstreeNode 생성자
bstreeNode::bstreeNode()
{}

bstreeNode::bstreeNode(bstreeData newData, bnodePtr lptr, bnodePtr rptr)
{
	data = newData;
	left = lptr;
	right = rptr;
}

// bstree 생성자
bstree::bstree()
{
	setRoot(0);
	setCurrent(0);
}

// bstree 소멸자
bstree::~bstree()
{
	clear();
}


// insert = 추가함수
// bstree newData.key값 존재하면 update
// bstree newData.key값 존재하지 않는다면 key값을 갖는 노드 트리에 추가 & current

void bstree::insert(bstreeData newData)
{
	insertSub(root, newData);
}

void bstree::insertSub(bnodePtr& p, bstreeData newData)
{

	if (p == 0)
	{
		p = new bstreeNode(newData, 0, 0);
		assert(p != 0);
		setCurrent(p);
	}
	else if (newData.key < p->data.key)
		insertSub(p->left, newData);
	else if (newData.key > p->data.key)
		insertSub(p->right, newData);
	else
		p->data = newData;


}


void bstree::read(ifstream& input_file)
{
	bstreeKey inputKey;
	bstreeData inputData;

	input_file.seekg(0, ios::beg);
	while (input_file >> inputKey)
	{
		inputData.key = inputKey;
		insert(inputData);
	}
}

// find = 찾기함수
// bstree key값 존재하면 found는 true값 반환 & current지정, 아니면 false값만 반환
bool bstree::find(bstreeKey searchKey)
{
	return findSub(root, searchKey);
}

bool bstree::findSub(bnodePtr p, bstreeKey searchKey)
{
	bool found;

	if (p == 0) //p값이 없다면 false 반환
		found = 0;

		// level 하나씩 내려감. (최대 단말노드까지 내려가며 찾음)
	else if (searchKey < p->data.key)
		found = findSub(p->left, searchKey);
	else if (searchKey > p->data.key)
		found = findSub(p->right, searchKey);

	else // 존재한다면 found true로 반환, current 노드로 설정
	{
		found = 1;
		setCurrent(p);
	}

	return found;

}

// remove = 삭제 함수
// bstree key값 존재하면 key값 갖는 노드 삭제 + root 노드 current 노드 / 아니라면 삭제연산 수행X
void bstree::remove(bstreeKey removeKey)

{
	bool deleted = true;
	removeSub(root, removeKey, deleted);
	if (deleted)
		setCurrent(root);
}

void bstree::removeSub(bnodePtr& p, bstreeKey removeKey, bool& deleted)
{
	bnodePtr q;

	if (p == 0) //존재하지 않음을 의미
	{
		deleted = false;
		cout << removeKey << " not found " << endl;
	}
	else if (removeKey < p->data.key)
		removeSub(p->left, removeKey, deleted);
	else if (isLeaf(p))
	{
		delete p;
		p = NULL;
	}
	else if (p->right == 0) //왼쪽 서브트리밖에 없다
	{
		q = p;
		p = p->left;
		delete q;
	}
	else if (p->left == 0) //오른쪽 서브트리밖에 없다
	{
		q = p;
		p = p->right;
		delete q;
	}
	else
	{
		q = findMax(p->left);
		p->data = q->data;
		removeSub(p->left, p->data.key, deleted);

		//q = findMin(p->right);
		//p->data = q->data;
		//removeSub(p->right, p->data.key, deleted);
	}

}

bnodePtr bstree::findMax(bnodePtr p)
{
	if (p->right == NULL)
		return p;
	else
		return (findMax(p->right));
}

bnodePtr bstree::findMin(bnodePtr p)
{
	return ((p->left) ? findMin(p->left) : p);
}

// bstree 노드들 key값에 따른 오름차순 출력
// 트리가 비어있다면 'empty tree' 출력
void bstree::writeAscending()
{
	ascendingSub(root); //root 노드 매개변수로 전달
	cout << endl;
}

//중위로 출력 (LDR)
void bstree::ascendingSub(bnodePtr p)
{

	if (p)
	{
		ascendingSub(p->left); //L
		cout << p->data.key << " "; //데이터출력
		ascendingSub(p->right); //R
	}
	else //트리가 비어있다면 empty tree 출력
	{
		cout << "empty tree";
	}
}

// bstree 노드 모두 삭제
void bstree::clear()
{
	clearSub(root);
	setRoot(NULL);
}

// 후위로 삭제 (LRD)
void bstree::clearSub(bnodePtr p)

{
	if (p != 0) //p가 비어있지 않다면
	{
		clearSub(p->left);	//L	
		clearSub(p->right);	//R
		delete p;			//노드 삭제	
	}
}

// goto~ : current 노드를 ~노드로 변경하는 함수

// current를 root노드로 변경
void bstree::gotoRoot()
{
	current = root;
}

// current를 current의 왼쪽 자식 노드로 변경
void bstree::gotoLeft()
{
	current = current->left;
}

// current를 current의 오른쪽 자식 노드로 변경
void bstree::gotoRight()
{
	current = current->right;
}

// current를 current의 부모 노드로 변경
void bstree::gotoParent()
{
	bool found = false;
	parentSub(root, found);
}


void bstree::parentSub(bnodePtr p, bool& found)
{
	if (!isRoot()) { // ! head node ? 
		if ((p->left == current) || (p->right == current)) // D
		{
			found = true;
			setCurrent(p);
		}
		else
		{
			if (p->left != 0)
				parentSub(p->left, found);				// L
			if (!found && (p->right != 0))
				parentSub(p->right, found);				// R
		}
	}
}

// is~ : 조건 ~을 만족하는지 묻는 함수

// current의 왼쪽 자식 노드가 비어있는가?
bool bstree::isLeftEmpty()
{
	return (!current->left);
}

// current의 오른쪽 자식 노드가 비어있는가?
bool bstree::isRightEmpty()
{
	return (!current->right);
}

// current가 root노드인가?
bool bstree::isRoot()
{
	return (current == root);
}

// tree가 비어있는가? (= root가 없는가?)
bool bstree::isEmpty()

{
	return (root == 0);
}

// 단말노드인가? (= 왼쪽과 오른쪽에 자식 노드가 없는가?)
bool bstree::isLeaf(bnodePtr p)
{
	return (p->left == 0 && p->right == 0);
}

// --------------- getter & setter ------------------
bstreeData bstree::getData()
{
	return(current->data);
}

bnodePtr bstree::getCurrent()
{
	return(current);
}

void bstree::setCurrent(bnodePtr newPtr)
{
	current = newPtr;
}

bnodePtr bstree::getRoot()
{
	return(root);
}

void bstree::setRoot(bnodePtr newPtr)
{
	root = newPtr;
}


int bstree::leafCount()
{
	return leafSub(root); //root노드부터 시작
}

// 단말의 노드를 확인하는 함수
int bstree::leafSub(bnodePtr p)
{
	int leaves; //단말노드 수 저장하는 변수

	if (p == 0) // p가 없다면 (자식노드 없음)
		leaves = 0;
	else
	{
		if (isLeaf(p))
			leaves = 1;
		else
		{
			leaves = leafSub(p->left) + leafSub(p->right);
			//leafSub(p->left) + leafSub(p->right) + 0; //p 자식 수 셈. p불포함
		}
		return leaves;
	}
}

int bstree::nonleafCount()
{
	return nonleafSub(root);
}

// 비단말 노드 확인하는 함수
int bstree::nonleafSub(bnodePtr p)
{
	int nonleaves;  //비단말 노드 수 저장하는 변수

	if (p == 0) // p가 없다면 (자식노드 없음)
		nonleaves = 0;
	else
	{
		if (isLeaf(p))
			nonleaves = 0;
		else
			nonleaves = nonleafSub(p->left) + nonleafSub(p->right) + 1; //자식이 있기 때문에 p는 비단말. p 포함됨
	}
	return nonleaves;



}

// bstree의 모든 노드 개수 반환하는 함수

int bstree::totalCount()
{
	return totalSub(root); //root 노드부터 탐색 시작
}

int bstree::totalSub(bnodePtr p)
{
	int total; // 노드 개수 저장하는 변수

	if (p == 0) // 노드가 존재하지 않는다면 0반환
		total = 0;
	else
	{
		if (isLeaf(p)) //단말노드라면 1반환
			total = 1;
		else
			total = totalSub(p->left) + totalSub(p->right) + 1; // (단말노드가 아니라면) 왼쪽 노드 수 + 오른쪽 노드 수 + 본인
	}
	return total;
}

// 트리의 height 값 반환하는 함수
int bstree::height()
{
	return heightSub(root); // root 노드부터 탐색
}

int bstree::heightSub(bnodePtr p)
{
	int l, r, height;

	if (p == NULL)
		height = 0;
	else
	{
		l = heightSub(p->left);		// 왼쪽 노드의 height
		r = heightSub(p->right);		// 오른쪽 노드의 height
		if (l > r)
			height = l + 1;				// 왼쪽 노드가 더 높으면 왼쪽노드 + 본인 = height
		else
			height = r + 1;				// 오른쪽 노드가 더 높으면 오른쪽노드 + 본인 = height
	}
	return height;
}

//-------------------< print() >------------------------------

void bstree::print()
{
	if (root == 0)
		cout << "Empty tree" << endl;
	else
	{
		cout << endl;
		printSub(root, 1);
		cout << endl;
	}
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// 순회순서: Reverse InOrder (RDL)
// Recursive partner of the showStringsubucture() function. 
// 포인터 p가 지시하는 노드로 시작하는 서브트리를 출력한다.
// 인자 level은 이진검색트리에서의 레벨을 의미한다.

void bstree::printSub(bnodePtr p, int level)
{
	int j, oldTextColor;

	if (p != 0)
	{
		printSub(p->right, level + 1);				// R : Output right subtree

		for (j = 0; j < level; j++)					// level 별로 tab 출력
			cout << '\t';
		oldTextColor = getColor(0);
		if (p == current)
			setColor(12);							// 빨간색
		cout << p->data.key;						// D
		setColor(oldTextColor);						// 원래 글자색으로!
													// 연결자 출력		
		if ((p->left != 0) && (p->right != 0))		// 양쪽 자식?      < 출력
			cout << '<';
		else if (p->right != 0)						// 왼쪽 자식만?    / 출력  
			cout << '/';
		else if (p->left != 0)						// 오른쪽 자식만?  \ 출력  
			cout << '\\';
		cout << endl;

		printSub(p->left, level + 1);				// L : Output left subtree
	}
}

void bstree::writeMoreThan(bstreeKey searchKey)
{
	writeMoreThanSub(root, searchKey); // root 노드부터 탐색, searchKey(기준key) 매개변수로 함께 전달
}

// 과제함수
// bstree에서 searchKey보다 큰 key값을 갖는 노드들을 오름차순으로 출력하는 함수
// 오름차순 정렬이기 때문에 중위 LDR 사용
// searchKey가 p data 보다 더 크면?! 왼쪽에는 없단는 이야기. 오른쪽만 돌아도 된다.

void bstree::writeMoreThanSub(bnodePtr p, bstreeKey searchKey)
{

	if (p)
	{
		
		if (p->data.key > searchKey) //만약 searchKey보다 key값이 크다면?
		{
			writeMoreThanSub(p->left, searchKey); //L
			cout << p->data.key << " "; //데이터출력

		}
		writeMoreThanSub(p->right, searchKey); //R
	}
}