
//프로그램 설명
/*
[ weighted graph ]
- 인접 행렬로 표현된 가중치 그래프
- 간선의 정보를 행렬에 저장

[ graph 클래스가 가진 멤버변수들 ]
1. size
- int형으로 정점의 개수를 저장해두는 변수이다.

2. vertex[]
- 1차원 배열로, 정점의 이름을 배열에 저장하는 형태이다.
- vertex[]배열의 크기는 size 변수에 저장하고, 필요에 따라 증가시킬 수 있다.

3. edgeData[][]
- 모든 정점들에 대한 간선에 대한 정보를 저장하는 2차원 배열이다.
- exist, weight, second로 이루어져 있다.
	exist : bool 형태로, 간선이 존재한다면 T, 아니면 F를 저장한다.
	weight : int 형태로, 각 간선의 가중치를 저장한다.
	second : int 형태로, 최단 경로에서의 다음 정점의 정보를 저장한다. (경로 출력 시 필요)
*/

// 2019111309
// 디지털미디어학과
// 황혜림
// 자료구조 (02분반)
// 2020.12.08


// graph 생성자
//---------------------------------------------------------------
graph:: graph() 
{
	size = 0; //정점 초기화 (배열사이즈 0)
	for (int j = 0; j < Max; j++)
		for (int k = 0; k < Max; k++) 
			edge[j][k].exist = false; //간선 초기화
}

// graph 소멸자
//---------------------------------------------------------------
graph:: ~graph() 
{
	size = 0; //clear();
}

// graph clear
//---------------------------------------------------------------
void graph::clear()
{
	size = 0;
	for (int j = 0; j < Max; j++)
		for (int k = 0; k < Max; k++)
			edge[j][k].exist = false;
}

//---------------------------------------------------------------
// utility
//---------------------------------------------------------------
bool graph:: vertexExists (char2 SrchKey, int &vnum) //정점의 이름을 매개변수로 전달
{
	bool found = 0;
	vnum = 0;
	
	while ( (vnum < size ) && (!found) )
		if ( strcmp(vertex[vnum].vname,SrchKey) == 0 )    
			found = true;
		else
			vnum++;
	return(found);
}

//---------------------------------------------------------------
bool graph:: isEmpty() 
{
	return ( size == 0 );
}

//---------------------------------------------------------------
bool graph:: isFull () 
{
	return ( size == Max );
}

//-------------------------------------------------------------//
// 그래프에 정점 newVertex를 추가한다.    				       //	
// 0: 추가되지 않음											   //		
// 1: 추가됨												   //
// 2: 수정됨												   //
//-------------------------------------------------------------//
int graph::insertVertex(vertexData newVertex)
{
	int j;
	// 정점이 존재하면 업데이트
	if (vertexExists(newVertex.vname, j))
	{
		vertex[j] = newVertex;
		return(2);
	}
	// 정점이 존재하지 않고 그래프가 포화가 아니면 추가
	else if (!isFull())
	{
		vertex[size++] = newVertex;
		return(1);
	}
	// 아니면 추가하지 않는다
	else
		return(0);
}

//---------------------------------------------------------------
// 간선 추가
// 명령ex. E A B 10 : A와 B 사이에 가중치 10인 간선 추가
bool graph::insertEdge (char2 from, char2 to, int wt) 
{
	int j, k;

	//존재하는 정점인가?
	if (vertexExists(from, j) && vertexExists(to, k))//각 정점의 index를 j와 k에 저장
	{
		//무방향이기 때문에 양쪽으로 간선 추가
		edge[j][k].exist = true; // 간선 추가
		edge[j][k].weight = wt; // 가중치 저장
		edge[k][j].exist = true; // 간선 추가
		edge[k][j].weight = wt; // 가중치 저장
		return true;
	}
	else
		return false;
}

//---------------------------------------------------------------
// 간선 존재하는가?
// 명령ex. X A B : A와 B사이의 간선이 존재하면 가중치와 함께 출력
bool graph:: edgeExists (char2 from, char2 to, int &wt) 
{
	int j, k;

	//만약 정점이 존재하고(각 정점의 index를 j와 k에 저장), 간선 존재 한다면
	if (vertexExists(from, j) && vertexExists(to, k) && edge[j][k].exist)
	{
		wt = edge[j][k].weight; // 가중치 wt에 저장
		return true;
	}
	else
		return false;
}

//---------------------------------------------------------------
// 경로 존재하는가?
// 명령ex. P A B : A와 B사이의 경로가 존재하면 가중치의 합과 함께 출력
bool graph:: pathExists (char2 from, char2 to, int &wt) 
{
	int j, k;

	//만약 정점이 존재하고(각 정점의 index를 j와 k에 저장), 경로 존재 한다면
	if (vertexExists(from, j) && vertexExists(to, k) && path[j][k].exist)
	{
		wt = path[j][k].weight; // 가중치 wt에 저장
		return true;
	}
	else
		return false;
}

// 과제함수
// 우회하는 경로 출력
// path의 second를 활용하여 출력 looping을 돈다.
void graph:: displayPath (char2 from, char2 to) 
{
	int j, k;
	vertexExists(from, j); // 입력받은 처음 정점의 위치를 j로 받아옴
	vertexExists(to, k); // 입력받은 처음 정점의 위치를 k로 받아옴

	cout << vertex[j].vname << " <-> " << vertex[k].vname<<"의 최단경로 : ";

	while (j != k) // 최종값 까지 가기 전까지 반복
	{
		cout << vertex[j].vname << " -> ";
		j = path[j][k].second; // 다음값의 위치(second 위치)로 업데이트
	}

	cout << vertex[k].vname; // 마지막 정점 출력
}

//---------------------------------------------------------------
void graph:: computePaths () 
{
	int j, k, m;

	// 1. 간선 행렬로 초기화
	for (j=0; j<size; j++)
		for (k = 0; k < size; k++)
		{
			path[j][k].exist = edge[j][k].exist;
			path[j][k].weight = edge[j][k].weight;
			path[j][k].second = k;
		}

	// 2. 대각선 원소 초기화 (자신의로의 경로 유)
	for (j = 0; j < size; j++)
	{
		path[j][j].exist = true;
		path[j][j].weight = 0;
		path[j][k].second = j;
	}

	// 3. 모든 정점쌍에 대한 최단경로 계산 (3중 looping)
	for (m = 0; m < size; m++)
		for (k = 0; k < size; k++)
			for (j = 0; j < size; j++)
			{
				//if ((1 && 2) && (3 || 4))
				if ((path[j][m].exist && path[m][k].exist) 
					&& (!path[j][k].exist || 
						path[j][m].weight + path[m][k].weight < path[j][k].weight))
				{
					path[j][k].exist = true;
					path[j][k].weight = path[j][m].weight + path[m][k].weight;
					path[j][k].second = path[j][m].second; //*중요
				}
			}

}

//-------------------------------------------------------------
void graph:: readLabel (ifstream &input_file, char2 vname) 
{
	char ch;
	int len=0;

	input_file.get(ch);
	while ( ch != '\n' && ch != ' ' && len < Max)
	{
		vname[len++] = ch;
		input_file.get(ch);
	}
	vname[len] = '\0';
}

//-------------------------------------------------------------
void graph::read (ifstream &input_file) 
{
	vertexData v;
	char2 source, dest;
	char ch, sp;
	int wt, inserted;

	while (input_file) 
	{
		ch=' '; 
		input_file.get(ch); input_file.get(sp);
		if (ch == 'V') 
		{
			readLabel(input_file, v.vname);
			insertVertex(v);
		}
		else if (ch == 'E') 
		{
			{
				readLabel(input_file, source);
				readLabel(input_file, dest);
				input_file >> wt; input_file.get(sp);
				inserted = insertEdge(source, dest, wt);
			}
			if (!inserted)
			{
				if (ch == 'V')
					cout << "V " << v.vname << " : 데이터에 오류가 있습니다." << endl;
				else if (ch == 'E')
					cout << "E " << source << " " << dest << " : 데이터에 오류가 있습니다." << endl;
				getchar(); getchar();
			}
		}
	}
}

//---------------------------------------------------------------
// 그래프 출력: 경로행렬의 second 값 제외
//
void graph:: showStructure () 
{
	int j;
	//system("cls"); cout << endl;
	cout << endl;
	if (isEmpty()) 
		cout << "그래프가 비어있습니다" << endl;
	else 
	{
		cout << "그래프" << endl << endl;
		cout << "정점:" << endl;
		for (j = 0; j < size; j++)
			cout << setw(2) << "     " << j << " : " << vertex[j].vname << endl;
		cout  << endl << "간선 행렬:" << endl;
		printMatrix(size, edge);
//		cout << endl  << "경로 행렬:" << endl;
//		printMatrix(size, path);
		cout << endl;
	}
}

//---------------------------------------------------------------
// 그래프 출력: 경로행렬의 second 값만 출력
//
void graph:: showSecond() 
{
	if (isEmpty()) 
		cout << "그래프가 비어있습니다" << endl;
	else 
	{
		cout << "경로 행렬(second):" << endl;
		printMatrix(size, path, 1);
		cout << endl;
	}
}

//---------------------------------------------------------------
// 행렬의 weight 값을 출력
//
void graph:: printMatrix (int size, edgeMatrix Matrix) 
{
	int j, k;
	cout << "     ";
	for (j = 0; j < size; j++)
		cout << setw(5) << j ;
	cout << endl;
	for (j = 0; j < size; j++) 
	{
		cout << setw(6) << j;
		for (k = 0; k < size; k++)
			if (Matrix[j][k].exist) 
				cout << setw(4) << Matrix[j][k].weight << " ";
			else
				cout << "   - ";
		cout << endl;
	}
}

//---------------------------------------------------------------
// 행렬의 second 값을 출력
//
void graph:: printMatrix (int size, edgeMatrix Matrix, int second) 
{
	int j, k;
	cout << "     ";
	for (j = 0; j < size; j++)
		cout << setw(5) << j ;
	cout << endl;
	for (j = 0; j < size; j++) 
	{
		cout << setw(6) << j;
		for (k = 0; k < size; k++)
			if (Matrix[j][k].exist) 
				cout << setw(4) << Matrix[j][k].second << " ";
			else
				cout << "   - ";
		cout << endl;
	}
}