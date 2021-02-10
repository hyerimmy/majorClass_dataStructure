// LAB6 - bstree.cpp

/* ���α׷� ����

�ϳ� �̻��� ���� �̷���� Ʈ���� �̷�� �����̸�, �� ���� �ִ� 2���� ���� Ʈ���� ���� �� �ִ�.
Ʈ���� ������ root�� current�� �Ǿ� �ְ�, Ʈ���� ���� left, data, right�� �̷���� �ִ�.

Ư��, lab05�� ������ �� �� ���� �� ������ ������ �Ǵ� KEY ���� ���´ٴ� ���� �������̴�.
�ڽ��� ���� ����Ʈ���� ������ �ڽ��� key�� ���� ���� key ������, �������� ū key ������ ���´�.

+ setData �Լ�(current�� ���ϴ� ������ �����ϴ� �Լ�) ���°��� lab05���� �ٸ� Ư¡�̴�.
+ lab06������ �����Լ��� �߰��Ǿ���. (insert, remove, find, count)

����Ʈ���� ��ȸ�ϸ� ���� �����ϴ� �Լ��� ���� ���ǵǾ� �ִ�.
��ȸ�� �� ������ ���� ����(DLR), ����(LDR), ����(LRD) �� ������ ����ȴ�.

*/

// 2019111309
// Ȳ����
// �ڷᱸ��
// 2020/10/13




// bstreeNode ������
bstreeNode::bstreeNode()
{}

bstreeNode::bstreeNode(bstreeData newData, bnodePtr lptr, bnodePtr rptr)
{
	data = newData;
	left = lptr;
	right = rptr;
}

// bstree ������
bstree::bstree()
{
	setRoot(0);
	setCurrent(0);
}

// bstree �Ҹ���
bstree::~bstree()
{
	clear();
}


// insert = �߰��Լ�
// bstree newData.key�� �����ϸ� update
// bstree newData.key�� �������� �ʴ´ٸ� key���� ���� ��� Ʈ���� �߰� & current

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

// find = ã���Լ�
// bstree key�� �����ϸ� found�� true�� ��ȯ & current����, �ƴϸ� false���� ��ȯ
bool bstree::find(bstreeKey searchKey)
{
	return findSub(root, searchKey);
}

bool bstree::findSub(bnodePtr p, bstreeKey searchKey)
{
	bool found;

	if (p == 0) //p���� ���ٸ� false ��ȯ
		found = 0;

		// level �ϳ��� ������. (�ִ� �ܸ������� �������� ã��)
	else if (searchKey < p->data.key)
		found = findSub(p->left, searchKey);
	else if (searchKey > p->data.key)
		found = findSub(p->right, searchKey);

	else // �����Ѵٸ� found true�� ��ȯ, current ���� ����
	{
		found = 1;
		setCurrent(p);
	}

	return found;

}

// remove = ���� �Լ�
// bstree key�� �����ϸ� key�� ���� ��� ���� + root ��� current ��� / �ƴ϶�� �������� ����X
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

	if (p == 0) //�������� ������ �ǹ�
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
	else if (p->right == 0) //���� ����Ʈ���ۿ� ����
	{
		q = p;
		p = p->left;
		delete q;
	}
	else if (p->left == 0) //������ ����Ʈ���ۿ� ����
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

// bstree ���� key���� ���� �������� ���
// Ʈ���� ����ִٸ� 'empty tree' ���
void bstree::writeAscending()
{
	ascendingSub(root); //root ��� �Ű������� ����
	cout << endl;
}

//������ ��� (LDR)
void bstree::ascendingSub(bnodePtr p)
{

	if (p)
	{
		ascendingSub(p->left); //L
		cout << p->data.key << " "; //���������
		ascendingSub(p->right); //R
	}
	else //Ʈ���� ����ִٸ� empty tree ���
	{
		cout << "empty tree";
	}
}

// bstree ��� ��� ����
void bstree::clear()
{
	clearSub(root);
	setRoot(NULL);
}

// ������ ���� (LRD)
void bstree::clearSub(bnodePtr p)

{
	if (p != 0) //p�� ������� �ʴٸ�
	{
		clearSub(p->left);	//L	
		clearSub(p->right);	//R
		delete p;			//��� ����	
	}
}

// goto~ : current ��带 ~���� �����ϴ� �Լ�

// current�� root���� ����
void bstree::gotoRoot()
{
	current = root;
}

// current�� current�� ���� �ڽ� ���� ����
void bstree::gotoLeft()
{
	current = current->left;
}

// current�� current�� ������ �ڽ� ���� ����
void bstree::gotoRight()
{
	current = current->right;
}

// current�� current�� �θ� ���� ����
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

// is~ : ���� ~�� �����ϴ��� ���� �Լ�

// current�� ���� �ڽ� ��尡 ����ִ°�?
bool bstree::isLeftEmpty()
{
	return (!current->left);
}

// current�� ������ �ڽ� ��尡 ����ִ°�?
bool bstree::isRightEmpty()
{
	return (!current->right);
}

// current�� root����ΰ�?
bool bstree::isRoot()
{
	return (current == root);
}

// tree�� ����ִ°�? (= root�� ���°�?)
bool bstree::isEmpty()

{
	return (root == 0);
}

// �ܸ�����ΰ�? (= ���ʰ� �����ʿ� �ڽ� ��尡 ���°�?)
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
	return leafSub(root); //root������ ����
}

// �ܸ��� ��带 Ȯ���ϴ� �Լ�
int bstree::leafSub(bnodePtr p)
{
	int leaves; //�ܸ���� �� �����ϴ� ����

	if (p == 0) // p�� ���ٸ� (�ڽĳ�� ����)
		leaves = 0;
	else
	{
		if (isLeaf(p))
			leaves = 1;
		else
		{
			leaves = leafSub(p->left) + leafSub(p->right);
			//leafSub(p->left) + leafSub(p->right) + 0; //p �ڽ� �� ��. p������
		}
		return leaves;
	}
}

int bstree::nonleafCount()
{
	return nonleafSub(root);
}

// ��ܸ� ��� Ȯ���ϴ� �Լ�
int bstree::nonleafSub(bnodePtr p)
{
	int nonleaves;  //��ܸ� ��� �� �����ϴ� ����

	if (p == 0) // p�� ���ٸ� (�ڽĳ�� ����)
		nonleaves = 0;
	else
	{
		if (isLeaf(p))
			nonleaves = 0;
		else
			nonleaves = nonleafSub(p->left) + nonleafSub(p->right) + 1; //�ڽ��� �ֱ� ������ p�� ��ܸ�. p ���Ե�
	}
	return nonleaves;



}

// bstree�� ��� ��� ���� ��ȯ�ϴ� �Լ�

int bstree::totalCount()
{
	return totalSub(root); //root ������ Ž�� ����
}

int bstree::totalSub(bnodePtr p)
{
	int total; // ��� ���� �����ϴ� ����

	if (p == 0) // ��尡 �������� �ʴ´ٸ� 0��ȯ
		total = 0;
	else
	{
		if (isLeaf(p)) //�ܸ������ 1��ȯ
			total = 1;
		else
			total = totalSub(p->left) + totalSub(p->right) + 1; // (�ܸ���尡 �ƴ϶��) ���� ��� �� + ������ ��� �� + ����
	}
	return total;
}

// Ʈ���� height �� ��ȯ�ϴ� �Լ�
int bstree::height()
{
	return heightSub(root); // root ������ Ž��
}

int bstree::heightSub(bnodePtr p)
{
	int l, r, height;

	if (p == NULL)
		height = 0;
	else
	{
		l = heightSub(p->left);		// ���� ����� height
		r = heightSub(p->right);		// ������ ����� height
		if (l > r)
			height = l + 1;				// ���� ��尡 �� ������ ���ʳ�� + ���� = height
		else
			height = r + 1;				// ������ ��尡 �� ������ �����ʳ�� + ���� = height
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
// ��ȸ����: Reverse InOrder (RDL)
// Recursive partner of the showStringsubucture() function. 
// ������ p�� �����ϴ� ���� �����ϴ� ����Ʈ���� ����Ѵ�.
// ���� level�� �����˻�Ʈ�������� ������ �ǹ��Ѵ�.

void bstree::printSub(bnodePtr p, int level)
{
	int j, oldTextColor;

	if (p != 0)
	{
		printSub(p->right, level + 1);				// R : Output right subtree

		for (j = 0; j < level; j++)					// level ���� tab ���
			cout << '\t';
		oldTextColor = getColor(0);
		if (p == current)
			setColor(12);							// ������
		cout << p->data.key;						// D
		setColor(oldTextColor);						// ���� ���ڻ�����!
													// ������ ���		
		if ((p->left != 0) && (p->right != 0))		// ���� �ڽ�?      < ���
			cout << '<';
		else if (p->right != 0)						// ���� �ڽĸ�?    / ���  
			cout << '/';
		else if (p->left != 0)						// ������ �ڽĸ�?  \ ���  
			cout << '\\';
		cout << endl;

		printSub(p->left, level + 1);				// L : Output left subtree
	}
}

void bstree::writeMoreThan(bstreeKey searchKey)
{
	writeMoreThanSub(root, searchKey); // root ������ Ž��, searchKey(����key) �Ű������� �Բ� ����
}

// �����Լ�
// bstree���� searchKey���� ū key���� ���� ������ ������������ ����ϴ� �Լ�
// �������� �����̱� ������ ���� LDR ���
// searchKey�� p data ���� �� ũ��?! ���ʿ��� ���ܴ� �̾߱�. �����ʸ� ���Ƶ� �ȴ�.

void bstree::writeMoreThanSub(bnodePtr p, bstreeKey searchKey)
{

	if (p)
	{
		
		if (p->data.key > searchKey) //���� searchKey���� key���� ũ�ٸ�?
		{
			writeMoreThanSub(p->left, searchKey); //L
			cout << p->data.key << " "; //���������

		}
		writeMoreThanSub(p->right, searchKey); //R
	}
}