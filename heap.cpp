//
// 프로그램 설명
/*

기존에 이진트리를 pointer를 통해 표현하였다면, 이번에는 배열을 활용해 표현한다.
완전 이진 트리 형태로 표현하여, 낭비되는 공간이 없도록 한다.

최대트리 : 각 노드 키 값이 그 자식의 키 값보다 작지 않은 트리
최대히프 : 최대 트리이면서 완전 이진 트리

노드 구조 : heap의 각 노드는 비교연산의 기준이 되는 <key> 값을 갖는다.
heap의 구조 : node라는 이름의 배열을 활용하며, 노드의 크기 값을 저장하는 변수 size가 있다.

enqueue와 dequeue의 기능은 새로운 데이터를 넣는 함수 insert와 데이트를 제거하는 함수 removeMac를 사용한다.

*/
//
// 2019111309
// 디지털미디어학과 황혜림
// 02분반
// 2020.11.17 (화) 수업 관련
//


#define SWAP(x, y, t) (t=x, x=y, y=t)

// 생성자
heap::heap()
{
    size = 0;
}

// 소멸자
heap:: ~heap()
{
    size = 0;
}

//enqueue
void heap::insert(heapData newData)
{
    int parent, child;
    heapData temp;

    size++; // 노드의 size를 한 칸 늘린다.
    node[size] = newData; //size번째 노드(마지막노드)에 새로 매개변수로 받은 데이터를 저장한다.

    child = size;
    parent = size / 2;

    // log n 번 반복
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
// 가장 큰 노드를 삭제하는 함수
// 가장 마지막 노드와 첫 번째 노드를 바꾼 후, 마지막으로 이동한 노드를 삭제하는 원리
heapData heap::removeMax()
{
    int parent, child;
    heapData maxData, temp;

    maxData = node[1];
    SWAP(node[1], node[size], temp); // 첫 번째 노드와 마지막 노드를 바꾼다.
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

// 노드 전체 삭제
// size 값을 0으로 설정함으로써 구현
void heap::clear()
{
    size = 0;
}

// 비어있는가?
bool heap::isEmpty()
{
    return size == 0;
}

// 가득 차 있는가?
bool heap::isFull()
{
    return size == Max;
}

// sort 함수
void heap::sort()
{
    heap temp;
    int i, oldSize = size;
    heapData data;


    while (!isEmpty())
    {
        data = removeMax();
        showSort(oldSize); getchar(); //중간결과 볼 수 있음.
    }


    cout << endl;
    for (i = 1; i <= oldSize; i++)
        cout << node[i].key << endl;
}

// 높이 출력하는 함수
int heap::height()
{
	return (int)ceil(log((double)(size + 1)) / log(2.0)); //log2 (size+1) 형태

}

// heap의 단말 노드의 개수를 반환
int  heap::leafCount()
{
    return (int)(ceil(size / 2.0));
}

// heap의 비 단말 노드의 개수를 반환
int  heap::nonLeafCount()
{
    return (int)(floor(size / 2.0));
}

// heap의 모든 노드 개수 반환
int  heap::totalCount()
{
    return size;
}

// heap의 노드 중 한 개의 자식만을 갖는 노드의 개수 반환
int  heap::singleCount()
{
    if (size % 2 == 0)
        return 1;
    else
        return 0;
}

// 과제함수
// 배열의 원소를 줄바꿈을 통해 구분해 출력
void heap::levelOrder()
{
    int newLine,   // 현재 레벨의 마지막 원소 번호 (언제 줄바꿀 것인가)
        j;         // loop counter

    system("cls");
    cout << endl << endl;

    j = 1;
    newLine = 1;
    for (int i = 1; i <= size; i++)
    {
        cout << node[i].key << "    ";
        if (i == newLine) // 현재 레벨의 마지막 원소인 경우
        {
            cout << endl; // 줄바꿈
            j = j * 2; 
            newLine = newLine + j; // 다음 레벨의 마지막 원소 재 설정
        }
    }



}

//---------------   < largerChild(int index) >----------------------------------
// index의 자식이 index 보다 큰 경우 큰 자식의 위치를 반환하며
// 그러한 자식이 존재하지 않은 경우 index 자체를 반환한다
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
// 자신 보다 큰 키값를 갖는 자식과 교환한다.
void heap::siftDown(int bottom, int top)
{
    int i;
    heapData temp;

    for (i = top; i >= bottom; i--)
    {
        if (node[i].key < node[i * 2].key)            // 자신이 왼쪽자식보다 작으면 
            if (node[i * 2].key > node[i * 2 + 1].key)   // 왼쪽자식이 오른쪽 자식보다 크면 
                SWAP(node[i], node[i * 2], temp);      // 자신 <-> 왼쪽자식 
            else
                SWAP(node[i], node[i * 2 + 1], temp);   // 자신 <-> 오른쪽자식 
        else if (node[i].key < node[i * 2 + 1].key)      // 자신이 오른쪽자식보다 작으면 
            SWAP(node[i], node[i * 2 + 1], temp);      // 자신 <-> 오른쪽자식 
    }
}

//------------------<  convert() >--------------------------
// complete banary tree => heap 변환
void heap::convert()
{
    int top = (int)(size / 2);      // top <- 자식을 가지는 마지막 노드 
    int bottom;

    for (bottom = 1; bottom <= top; bottom++)
    {
        system("cls");
        // cout << "bottom = " << bottom << endl << endl;
        siftDown(bottom, top);
        showConvert(bottom);      // 1에서 bottom까지 빨간색으로 출력
        getchar();
    }
}

//
/****************************************************/
/*                                       */
/*       heap 을 출력하기 위한 여러가지 함수        */
/*                                       */
/****************************************************/
//

//--------------------------------------------------------------------
// heap을 반시계방향으로 90도 돌린 트리형식으로 보인다. 

void heap::showStructure()
{
    int j;   // loop counter

    cout << endl << endl;
    if (isEmpty())
        cout << "Empty heap" << endl;
    else
    {
        cout << endl << "size = " << size << endl;  // 배열 형식으로 출력
        cout.setf(ios::right);
        for (j = 1; j <= size; j++)
        {
            cout.width(5);
            cout << j << " : " << node[j].key << endl;
        }
        cout.unsetf(ios::right);
        cout << endl;
        showSubtree(1, 0);                        // 트리 형식으로 출력
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
        if (2 * index + 1 <= size)         // 연결자 출력
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
            SetColor(12);                     // 빨간색
        cout << node[index].key;                  // D
        SetColor(oldTextColor);                     // 원래색으로! 
        if (2 * index + 1 <= sortSize)
            cout << '<';                           // branch 출력
        else if (2 * index <= sortSize)
            cout << '\\';                        // branch 출력
        cout << endl;
        showSortSubtree(2 * index, level + 1, sortSize);   // L
    }
}

//------------------< heapSortTree >--------------------------
// heap sort 과정을 반시계방향으로 90도 돌린 트리형식으로 보인다. 
//
void heap::showSort(int size)
{
    if (isEmpty())
        cout << "Empty heap" << endl;
    else
    {
        clrScr();                         //system("cls");   
        cout << "size = " << size << endl;       // 배열 형식으로 출력
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
            SetColor(12);                        // 빨간색
        cout << node[index].key;                  // D
        SetColor(oldTextColor);                     // 원래색으로! 
        if (2 * index + 1 <= sortSize)
            cout << '<';                        // branch 출력
        else if (2 * index <= sortSize)
            cout << '\\';                        // branch 출력
        cout << endl;
        showConvertSubtree(2 * index, level + 1, sortSize, bottom);   // L
    }
}

//------------------< showConvert >--------------------------
// 변환 과정을 반시계방향으로 90도 돌린 트리형식으로 보인다. 
//
void heap::showConvert(int bottom)
{
    cout << endl;
    if (isEmpty())
        cout << "Empty heap" << endl;
    else
    {
        clrScr();                        //system("cls");   
        cout << "size = " << size << endl;      // 배열 형식으로 출력
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