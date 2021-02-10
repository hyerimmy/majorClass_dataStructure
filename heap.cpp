//
// ���α׷� ����
/*

������ ����Ʈ���� pointer�� ���� ǥ���Ͽ��ٸ�, �̹����� �迭�� Ȱ���� ǥ���Ѵ�.
���� ���� Ʈ�� ���·� ǥ���Ͽ�, ����Ǵ� ������ ������ �Ѵ�.

�ִ�Ʈ�� : �� ��� Ű ���� �� �ڽ��� Ű ������ ���� ���� Ʈ��
�ִ����� : �ִ� Ʈ���̸鼭 ���� ���� Ʈ��

��� ���� : heap�� �� ���� �񱳿����� ������ �Ǵ� <key> ���� ���´�.
heap�� ���� : node��� �̸��� �迭�� Ȱ���ϸ�, ����� ũ�� ���� �����ϴ� ���� size�� �ִ�.

enqueue�� dequeue�� ����� ���ο� �����͸� �ִ� �Լ� insert�� ����Ʈ�� �����ϴ� �Լ� removeMac�� ����Ѵ�.

*/
//
// 2019111309
// �����й̵���а� Ȳ����
// 02�й�
// 2020.11.17 (ȭ) ���� ����
//


#define SWAP(x, y, t) (t=x, x=y, y=t)

// ������
heap::heap()
{
    size = 0;
}

// �Ҹ���
heap:: ~heap()
{
    size = 0;
}

//enqueue
void heap::insert(heapData newData)
{
    int parent, child;
    heapData temp;

    size++; // ����� size�� �� ĭ �ø���.
    node[size] = newData; //size��° ���(���������)�� ���� �Ű������� ���� �����͸� �����Ѵ�.

    child = size;
    parent = size / 2;

    // log n �� �ݺ�
    while (node[parent].key < node[child].key && parent>0) // child > 1
    {
        SWAP(node[child], node[parent], temp);
        child = parent;
        parent = parent / 2;
    }

}

void heap::read(ifstream& input_file)
{
    heapData inputData;

    while (input_file >> inputData.key)
        insert(inputData);
}

// dequeue
// ���� ū ��带 �����ϴ� �Լ�
// ���� ������ ���� ù ��° ��带 �ٲ� ��, ���������� �̵��� ��带 �����ϴ� ����
heapData heap::removeMax()
{
    int parent, child;
    heapData maxData, temp;

    maxData = node[1];
    SWAP(node[1], node[size], temp); // ù ��° ���� ������ ��带 �ٲ۴�.
    size--;

    parent = 1;
    do
    {
        child = largerChild(parent); // 5, 8
        if (parent == child)
            break;
        SWAP(node[parent], node[child], temp); //6
        parent = child; //7
    } while (parent <= child);

    return maxData;

}

// ��� ��ü ����
// size ���� 0���� ���������ν� ����
void heap::clear()
{
    size = 0;
}

// ����ִ°�?
bool heap::isEmpty()
{
    return size == 0;
}

// ���� �� �ִ°�?
bool heap::isFull()
{
    return size == Max;
}

// sort �Լ�
void heap::sort()
{
    heap temp;
    int i, oldSize = size;
    heapData data;


    while (!isEmpty())
    {
        data = removeMax();
        showSort(oldSize); getchar(); //�߰���� �� �� ����.
    }


    cout << endl;
    for (i = 1; i <= oldSize; i++)
        cout << node[i].key << endl;
}

// ���� ����ϴ� �Լ�
int heap::height()
{
	return (int)ceil(log((double)(size + 1)) / log(2.0)); //log2 (size+1) ����

}

// heap�� �ܸ� ����� ������ ��ȯ
int  heap::leafCount()
{
    return (int)(ceil(size / 2.0));
}

// heap�� �� �ܸ� ����� ������ ��ȯ
int  heap::nonLeafCount()
{
    return (int)(floor(size / 2.0));
}

// heap�� ��� ��� ���� ��ȯ
int  heap::totalCount()
{
    return size;
}

// heap�� ��� �� �� ���� �ڽĸ��� ���� ����� ���� ��ȯ
int  heap::singleCount()
{
    if (size % 2 == 0)
        return 1;
    else
        return 0;
}

// �����Լ�
// �迭�� ���Ҹ� �ٹٲ��� ���� ������ ���
void heap::levelOrder()
{
    int newLine,   // ���� ������ ������ ���� ��ȣ (���� �ٹٲ� ���ΰ�)
        j;         // loop counter

    system("cls");
    cout << endl << endl;

    j = 1;
    newLine = 1;
    for (int i = 1; i <= size; i++)
    {
        cout << node[i].key << "    ";
        if (i == newLine) // ���� ������ ������ ������ ���
        {
            cout << endl; // �ٹٲ�
            j = j * 2; 
            newLine = newLine + j; // ���� ������ ������ ���� �� ����
        }
    }



}

//---------------   < largerChild(int index) >----------------------------------
// index�� �ڽ��� index ���� ū ��� ū �ڽ��� ��ġ�� ��ȯ�ϸ�
// �׷��� �ڽ��� �������� ���� ��� index ��ü�� ��ȯ�Ѵ�
//
int heap::largerChild(int index)
{
    int left = 2 * index;
    int right = 2 * index + 1;

    if (left > size)                           // index has no children
        return index;
    else
        if (left == size)                        // index has left child only
            if (node[index].key < node[left].key)      // index < left child
                return left;
            else                              // index >= left child
                return index;
        else
            if (node[left].key < node[right].key)      // index has two children 
                if (node[index].key < node[right].key)    // index < right child                        
                    return right;
                else                           // index >= right child
                    return index;
            else                              // left child >= right child
                if (node[index].key < node[left].key)   // index < left child
                    return left;
                else                           // index >= left child
                    return index;
}

//------------------<  SiftDown() >--------------------------
// �ڽ� ���� ū Ű���� ���� �ڽİ� ��ȯ�Ѵ�.
void heap::siftDown(int bottom, int top)
{
    int i;
    heapData temp;

    for (i = top; i >= bottom; i--)
    {
        if (node[i].key < node[i * 2].key)            // �ڽ��� �����ڽĺ��� ������ 
            if (node[i * 2].key > node[i * 2 + 1].key)   // �����ڽ��� ������ �ڽĺ��� ũ�� 
                SWAP(node[i], node[i * 2], temp);      // �ڽ� <-> �����ڽ� 
            else
                SWAP(node[i], node[i * 2 + 1], temp);   // �ڽ� <-> �������ڽ� 
        else if (node[i].key < node[i * 2 + 1].key)      // �ڽ��� �������ڽĺ��� ������ 
            SWAP(node[i], node[i * 2 + 1], temp);      // �ڽ� <-> �������ڽ� 
    }
}

//------------------<  convert() >--------------------------
// complete banary tree => heap ��ȯ
void heap::convert()
{
    int top = (int)(size / 2);      // top <- �ڽ��� ������ ������ ��� 
    int bottom;

    for (bottom = 1; bottom <= top; bottom++)
    {
        system("cls");
        // cout << "bottom = " << bottom << endl << endl;
        siftDown(bottom, top);
        showConvert(bottom);      // 1���� bottom���� ���������� ���
        getchar();
    }
}

//
/****************************************************/
/*                                       */
/*       heap �� ����ϱ� ���� �������� �Լ�        */
/*                                       */
/****************************************************/
//

//--------------------------------------------------------------------
// heap�� �ݽð�������� 90�� ���� Ʈ���������� ���δ�. 

void heap::showStructure()
{
    int j;   // loop counter

    cout << endl << endl;
    if (isEmpty())
        cout << "Empty heap" << endl;
    else
    {
        cout << endl << "size = " << size << endl;  // �迭 �������� ���
        cout.setf(ios::right);
        for (j = 1; j <= size; j++)
        {
            cout.width(5);
            cout << j << " : " << node[j].key << endl;
        }
        cout.unsetf(ios::right);
        cout << endl;
        showSubtree(1, 0);                        // Ʈ�� �������� ���
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Recursive partner of the showStructure()

void heap::showSubtree(int index, int level)
{
    int j;   // Loop counter

    if (index <= size)
    {
        showSubtree(2 * index + 1, level + 1);      // R
        for (j = 1; j <= level; j++)   // tab 
            cout << "\t";
        cout << " " << node[index].key;      // D
        if (2 * index + 1 <= size)         // ������ ���
            cout << "<";
        else if (2 * index <= size)
            cout << "\\";
        cout << endl;
        showSubtree(2 * index, level + 1);      // L
    }
}

//------------------< showSortSubtree >--------------------------
// Recursive partner of the showSort() function. 
//
void heap::showSortSubtree(int index, int level, int sortSize)
{
    int j, oldTextColor;
    if (index <= sortSize)
    {
        showSortSubtree(2 * index + 1, level + 1, sortSize);   // R
        for (j = 1; j <= level; j++)
            cout << '\t';
        oldTextColor = GetColor(0);
        if (index > size)
            SetColor(12);                     // ������
        cout << node[index].key;                  // D
        SetColor(oldTextColor);                     // ����������! 
        if (2 * index + 1 <= sortSize)
            cout << '<';                           // branch ���
        else if (2 * index <= sortSize)
            cout << '\\';                        // branch ���
        cout << endl;
        showSortSubtree(2 * index, level + 1, sortSize);   // L
    }
}

//------------------< heapSortTree >--------------------------
// heap sort ������ �ݽð�������� 90�� ���� Ʈ���������� ���δ�. 
//
void heap::showSort(int size)
{
    if (isEmpty())
        cout << "Empty heap" << endl;
    else
    {
        clrScr();                         //system("cls");   
        cout << "size = " << size << endl;       // �迭 �������� ���
        cout.setf(ios::right);
        for (int j = 1; j <= size; j++)
        {
            cout.width(5);
            cout << j << " : " << node[j].key << endl;
        }
        cout.unsetf(ios::right);
        cout << endl;
        showSortSubtree(1, 0, size);
    }
}

//------------------< showSortSubtree >--------------------------
// Recursive partner of the showSort() function. 
//
void heap::showConvertSubtree(int index, int level, int sortSize, int bottom)
{
    int j, oldTextColor; ;
    if (index <= sortSize)
    {
        showConvertSubtree(2 * index + 1, level + 1, sortSize, bottom);   // R
        for (j = 1; j <= level; j++)
            cout << '\t';
        oldTextColor = GetColor(0);
        if (index <= bottom)
            SetColor(12);                        // ������
        cout << node[index].key;                  // D
        SetColor(oldTextColor);                     // ����������! 
        if (2 * index + 1 <= sortSize)
            cout << '<';                        // branch ���
        else if (2 * index <= sortSize)
            cout << '\\';                        // branch ���
        cout << endl;
        showConvertSubtree(2 * index, level + 1, sortSize, bottom);   // L
    }
}

//------------------< showConvert >--------------------------
// ��ȯ ������ �ݽð�������� 90�� ���� Ʈ���������� ���δ�. 
//
void heap::showConvert(int bottom)
{
    cout << endl;
    if (isEmpty())
        cout << "Empty heap" << endl;
    else
    {
        clrScr();                        //system("cls");   
        cout << "size = " << size << endl;      // �迭 �������� ���
        cout.setf(ios::right);
        for (int j = 1; j <= size; j++)
        {
            cout.width(5);
            cout << j << " : " << node[j].key << endl;
        }
        cout.unsetf(ios::right);
        cout << endl;
        showConvertSubtree(1, 0, size, bottom);
    }
}