//
//프로그램 설명
/*
Directed Graph (diGraph)
리스트와 배열을 합하여 응용한 구조

** 간선 리스트의 헤더포인터를 정점 배열에 합치는 원리이다.
graph는 size와 vertex()로 이루어져 있다.
size : 정점의 정보를 저장
vertex() : vertexNode 타입의 1차원 배열
  -> vertextNode : vdata, edgeHead로 구성 (edgeHead에는 간선 리스트의 헤더 포인트를 저장)
+ edgeNode :  vnum과 next로 구성

*/
//
// 2019111309
// 디지털미디어학과
// 황혜림
// 자료구조 (02분반)
// 2020.12.01
//

// edgeNode 생성자
//-------------------------------------------------------------
edgeNode:: edgeNode ()
{
}

edgeNode::edgeNode (edgeData newData, edgeNode *newNext)
{
	vnum = newData;
	next = newNext;
}

// graph 생성자: 
//-------------------------------------------------------------
graph:: graph () 
{
	size = 0; //리스트
	for (int j=0; j<Num; j++) //배열
		vertex[j].edgeHead = NULL;
}

// graph 소멸자
//-------------------------------------------------------------
graph:: ~graph () 
{
	for (int j=0; j<size; j++) //배열초기화
	{
		clear(vertex[j].edgeHead);
		vertex[j].edgeHead = NULL;
	}
	size = 0; //리스트초기화
}

//----------------< clear() >-------------------
// head로 시작하는 간선 리스트의 모든 노드를 삭제한다

void graph:: clear(enodePtr head)
{
	enodePtr     p,       // 삭제 할 노드
	         nextp;		  // 삭제 할 노드의 다음 노드
	p = head;
	while (p) 			  // 노드가 존재 하는 동안
	{
		nextp = p->next;
		delete p;
		p = nextp;
	}
}

// 정점명 SrchKey의 번호를 찾아 반환한다.   				   	
//-------------------------------------------------------------
bool graph:: vertexExists(char10 SrchKey, int &vnum) 
{
	bool found = false;
	vnum = 0;
	while ((vnum < size) && (!found)) 
	{
		if (strcmp(vertex[vnum].vdata.vname, SrchKey) == 0)
			found = true;
		else
			vnum++;
	}
	return(found);
}

//-------------------------------------------------------------
bool graph:: edgeExists (char10 from, char10 to, enodePtr &eptr) 
{
	int j, k;
	bool found;

	// from 값은 j에, to 값은 k에 저장
	if (vertexExists(from, j) && vertexExists(to, k))
	{
		eptr = vertex[j].edgeHead;
		found = false;

		//eptr이 null이 아닌 동안 (즉, 끝까지 갈때까지) + 필요한 것을 만나기 전까지 반복
		while (eptr && !found) 
		{
			if (eptr->vnum == k)
				found = true;
			else
				eptr = eptr->next;
		}
		return found;
	}
	else
		return 0; //false
}

//-------------------------------------------------------------
// 정점을 추가하는 함수
// 정점추가의 경우 오류면 0. 수정의 경우 2,추가의 경우 1을 반환
int graph:: insertVertex (vertexData newVertex) 
{
	int j;

	// 추가하려는 정점이 이미 존재한다면? 업데이트(수정)
	if (vertexExists(newVertex.vname, j)) //존재하는지 알아보고, 존재한다면 j에 반환
	{
		vertex[j].vdata = newVertex;
		return 2;
	}

	// 추가하려는 정점이 이미 없으며 포화가 아니라면? 추가
	else if (!isFull())
	{
		vertex[size].vdata = newVertex;
		size++;
		return 1;
	}

	// 포화상태라면? 추가하지 않음
	return 0;
	
}

//-------------------------------------------------------------
// 간선을 추가하는 함수
// 오류의 경우 0, 추가하는 경우 1, 수정하는 경우 2 반환
int graph:: insertEdge (char10 from, char10 to) 
{
	int j, k;
	enodePtr eptr;
	
	if (vertexExists(from, j) && vertexExists(to, k))
	{
		//  case1 : 수정하는 경우
		if (edgeExists(from, to, eptr)) //정점이 존재 (그 위치를 eptr에 반환)
		{
			eptr->vnum = k;
			return 2;
		}
		else
		{
			eptr = vertex[j].edgeHead;
			// case 3 : 간선이 아직 없는 경우 (head에 바로 연결)
			if (eptr == 0)
				vertex[j].edgeHead = new edgeNode(k, 0);

			// case 2 : 추가하는 경우 (마지막에 추가)
			else
			{
				// eptr을 마지막으로 이동
				while (eptr->next)
					eptr = eptr->next;
				eptr->next = new edgeNode(k, 0);

			}
			return 1;
		}
	}
	else //정점이 존재하지 않는다면
		return 0;

}

//-------------------------------------------------------------
void graph:: DFSPrint (char10 from) 
{
	int j;
	// 방문확인변수 visited를 모두 false로 설정
	for (j = 0; j < size; j++)
		visited[j] = false;
	if (vertexExists(from, j)) //인덱스를 j로 저장
		DFSPrintSub(j); // 서브 함수에서 진행
}


// Recursive partner of DFSPrint
//-------------------------------------------------------------
void graph:: DFSPrintSub (int j) 
{
	enodePtr eptr;

	// 방문하면 2가지 실행 (이름출력, visited를 true로)
	cout << vertex[j].vdata.vname; // j번째 정점 출력
	visited[j] = true;

	eptr = vertex[j].edgeHead; //edgeHead에서 시작

	while (eptr) //eptr이 null이 아닌 동안 (모든 정점 다 돌아야 종료)
	{
		if (visited[eptr->vnum] == false) //방문하지 않았다면 재귀호출
		{
			// 간선출력(과제)
			cout << "   <" << j << "," << eptr->vnum << ">" << endl;

			DFSPrintSub(eptr->vnum);
		}
		eptr = eptr->next;
	}

}

//-------------------------------------------------------------
// 과제코드
// 세트로 enqueue하고 세트로 dequeue해서 필요한것만 분리해서 사용함.
void graph:: BFSPrint (char10 from) 
{
	int j;
	enodePtr eptr;
	queueData qdata;	// 간선까지 출력 시 필요(과제)
	
	for (j = 0; j < size; j++)
		visited[j] = false;
	if (vertexExists(from, j))
		cout << vertex[j].vdata.vname;
	visited[j] = true;
	eptr = vertex[j].edgeHead; 
	if (eptr) 
		do 
		{
			while (eptr) 
			{
				if (!visited[eptr->vnum]) 
				{
					qdata.from = j;// qdata의 from에 j를 넣음
					qdata.to = eptr;// qdata의 to에 eptr를 넣음
					Q.enqueue(qdata); // 최종적으로 qdata를 한번에 넣음.
				}
				eptr = eptr->next;
			}

			qdata = Q.dequeue();
			eptr = qdata.to;//eptr의 to 부분만 빼서 저장
			
			if (!visited[eptr->vnum]) 
			{
				// 간선출력 (qdata의 from이 있기 때문에 가능함)
				cout << "   <" << qdata.from << "," << eptr->vnum << ">" << endl;
				cout << vertex[eptr->vnum].vdata.vname;
				visited[eptr->vnum] = true;
			}
			j = eptr->vnum;
			eptr = vertex[eptr->vnum].edgeHead; 
		} while (!Q.empty());
}

//-------------------------------------------------------------
bool graph:: pathExists (char10 from, char10 to) 
{
	int j, k;

	for (j = 0; j < size; j++)
		visited[j] = false;
	if (vertexExists(from, j) && vertexExists(to, k))
		return DFSpath(j ,k);
	else
		return (false);
}

// Recursive partner of pathExists								
//-------------------------------------------------------------
// DFS와 다른 점 2가지
// void -> bool
// 출발점 뿐만 아니라 목적지(k) index 까지 매개변수로 가짐
bool graph:: DFSpath (int j, int k) 
{
	bool found = false;
	enodePtr eptr;

	cout << vertex[j].vdata.vname;
	visited[j] = true;
	eptr = vertex[j].edgeHead;

	while (eptr && !found)
	{
		// 목적지? => 종료
		if (eptr->vnum == k)
		{
			// 간선출력 (과제)
			cout << "   <" << j << "," << eptr->vnum << ">" << endl;
			// 마지막 정점 출력
			cout << vertex[k].vdata.vname << endl;

			found = true;
		}
		else if (visited[eptr->vnum] == false)
		{
			// 간선출력 (과제)
			cout << "   <" << j << "," << eptr->vnum << ">" << endl;

			found = DFSpath(eptr->vnum, k); 
		}
		eptr = eptr->next;
	}
	return found;

}

//-------------------------------------------------------------
void graph:: readLabel (ifstream &input_file, char10 vname) 
{
	char ch;
	int len=0;

	input_file.get(ch);
	while ( ch != '\n' && ch != ' ' && len < Num)
	{
		vname[len++] = ch;
		input_file.get(ch);
	}
	vname[len] = '\0';

}

//-------------------------------------------------------------
void graph:: readGraph (ifstream &input_file) 
{
	vertexData v;
	char10 from, to;
	char ch, sp;
	int inserted;

	while (input_file) 
	{
		ch=' ';
		input_file.get(ch); input_file.get(sp);
		if (ch == 'V') 
		{
		      readLabel(input_file, v.vname);
		      inserted = insertVertex(v);
		}
		else if (ch == 'E') 
		{
		      readLabel(input_file, from);
		      readLabel(input_file, to);
		      inserted = insertEdge(from, to);
		}
		if (!inserted) 
		{
			cout << "Error in graph data file" << endl;
			exit(1);
		}
	}
}


//-------------------------------------------------------------
bool graph:: isEmpty()
{
	return (size == 0);
}

//-------------------------------------------------------------
bool graph:: isFull()
{
	return (size == Num);
}

//-------------------------------------------------------------
void graph:: showGraph() 
{
	int len;
	enodePtr p;

	cout  << endl << "graph:  " << endl;
	for (int j = 0; j < size; j++) 
	{
		len = (int)strlen(vertex[j].vdata.vname);
		cout.width(3);
		cout << j << " : " << vertex[j].vdata.vname;
		for (int k = 0; k < (10-len); k++) cout << " ";
		p = vertex[j].edgeHead;
		while (p) 
		{
		       cout.width(3);
			   cout << " -> " << p->vnum;
		       p = p->next;
		}
		cout << endl;
	}
}
