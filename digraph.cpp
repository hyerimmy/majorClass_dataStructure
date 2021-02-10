//
//���α׷� ����
/*
Directed Graph (diGraph)
����Ʈ�� �迭�� ���Ͽ� ������ ����

** ���� ����Ʈ�� ��������͸� ���� �迭�� ��ġ�� �����̴�.
graph�� size�� vertex()�� �̷���� �ִ�.
size : ������ ������ ����
vertex() : vertexNode Ÿ���� 1���� �迭
  -> vertextNode : vdata, edgeHead�� ���� (edgeHead���� ���� ����Ʈ�� ��� ����Ʈ�� ����)
+ edgeNode :  vnum�� next�� ����

*/
//
// 2019111309
// �����й̵���а�
// Ȳ����
// �ڷᱸ�� (02�й�)
// 2020.12.01
//

// edgeNode ������
//-------------------------------------------------------------
edgeNode:: edgeNode ()
{
}

edgeNode::edgeNode (edgeData newData, edgeNode *newNext)
{
	vnum = newData;
	next = newNext;
}

// graph ������: 
//-------------------------------------------------------------
graph:: graph () 
{
	size = 0; //����Ʈ
	for (int j=0; j<Num; j++) //�迭
		vertex[j].edgeHead = NULL;
}

// graph �Ҹ���
//-------------------------------------------------------------
graph:: ~graph () 
{
	for (int j=0; j<size; j++) //�迭�ʱ�ȭ
	{
		clear(vertex[j].edgeHead);
		vertex[j].edgeHead = NULL;
	}
	size = 0; //����Ʈ�ʱ�ȭ
}

//----------------< clear() >-------------------
// head�� �����ϴ� ���� ����Ʈ�� ��� ��带 �����Ѵ�

void graph:: clear(enodePtr head)
{
	enodePtr     p,       // ���� �� ���
	         nextp;		  // ���� �� ����� ���� ���
	p = head;
	while (p) 			  // ��尡 ���� �ϴ� ����
	{
		nextp = p->next;
		delete p;
		p = nextp;
	}
}

// ������ SrchKey�� ��ȣ�� ã�� ��ȯ�Ѵ�.   				   	
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

	// from ���� j��, to ���� k�� ����
	if (vertexExists(from, j) && vertexExists(to, k))
	{
		eptr = vertex[j].edgeHead;
		found = false;

		//eptr�� null�� �ƴ� ���� (��, ������ ��������) + �ʿ��� ���� ������ ������ �ݺ�
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
// ������ �߰��ϴ� �Լ�
// �����߰��� ��� ������ 0. ������ ��� 2,�߰��� ��� 1�� ��ȯ
int graph:: insertVertex (vertexData newVertex) 
{
	int j;

	// �߰��Ϸ��� ������ �̹� �����Ѵٸ�? ������Ʈ(����)
	if (vertexExists(newVertex.vname, j)) //�����ϴ��� �˾ƺ���, �����Ѵٸ� j�� ��ȯ
	{
		vertex[j].vdata = newVertex;
		return 2;
	}

	// �߰��Ϸ��� ������ �̹� ������ ��ȭ�� �ƴ϶��? �߰�
	else if (!isFull())
	{
		vertex[size].vdata = newVertex;
		size++;
		return 1;
	}

	// ��ȭ���¶��? �߰����� ����
	return 0;
	
}

//-------------------------------------------------------------
// ������ �߰��ϴ� �Լ�
// ������ ��� 0, �߰��ϴ� ��� 1, �����ϴ� ��� 2 ��ȯ
int graph:: insertEdge (char10 from, char10 to) 
{
	int j, k;
	enodePtr eptr;
	
	if (vertexExists(from, j) && vertexExists(to, k))
	{
		//  case1 : �����ϴ� ���
		if (edgeExists(from, to, eptr)) //������ ���� (�� ��ġ�� eptr�� ��ȯ)
		{
			eptr->vnum = k;
			return 2;
		}
		else
		{
			eptr = vertex[j].edgeHead;
			// case 3 : ������ ���� ���� ��� (head�� �ٷ� ����)
			if (eptr == 0)
				vertex[j].edgeHead = new edgeNode(k, 0);

			// case 2 : �߰��ϴ� ��� (�������� �߰�)
			else
			{
				// eptr�� ���������� �̵�
				while (eptr->next)
					eptr = eptr->next;
				eptr->next = new edgeNode(k, 0);

			}
			return 1;
		}
	}
	else //������ �������� �ʴ´ٸ�
		return 0;

}

//-------------------------------------------------------------
void graph:: DFSPrint (char10 from) 
{
	int j;
	// �湮Ȯ�κ��� visited�� ��� false�� ����
	for (j = 0; j < size; j++)
		visited[j] = false;
	if (vertexExists(from, j)) //�ε����� j�� ����
		DFSPrintSub(j); // ���� �Լ����� ����
}


// Recursive partner of DFSPrint
//-------------------------------------------------------------
void graph:: DFSPrintSub (int j) 
{
	enodePtr eptr;

	// �湮�ϸ� 2���� ���� (�̸����, visited�� true��)
	cout << vertex[j].vdata.vname; // j��° ���� ���
	visited[j] = true;

	eptr = vertex[j].edgeHead; //edgeHead���� ����

	while (eptr) //eptr�� null�� �ƴ� ���� (��� ���� �� ���ƾ� ����)
	{
		if (visited[eptr->vnum] == false) //�湮���� �ʾҴٸ� ���ȣ��
		{
			// �������(����)
			cout << "   <" << j << "," << eptr->vnum << ">" << endl;

			DFSPrintSub(eptr->vnum);
		}
		eptr = eptr->next;
	}

}

//-------------------------------------------------------------
// �����ڵ�
// ��Ʈ�� enqueue�ϰ� ��Ʈ�� dequeue�ؼ� �ʿ��Ѱ͸� �и��ؼ� �����.
void graph:: BFSPrint (char10 from) 
{
	int j;
	enodePtr eptr;
	queueData qdata;	// �������� ��� �� �ʿ�(����)
	
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
					qdata.from = j;// qdata�� from�� j�� ����
					qdata.to = eptr;// qdata�� to�� eptr�� ����
					Q.enqueue(qdata); // ���������� qdata�� �ѹ��� ����.
				}
				eptr = eptr->next;
			}

			qdata = Q.dequeue();
			eptr = qdata.to;//eptr�� to �κи� ���� ����
			
			if (!visited[eptr->vnum]) 
			{
				// ������� (qdata�� from�� �ֱ� ������ ������)
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
// DFS�� �ٸ� �� 2����
// void -> bool
// ����� �Ӹ� �ƴ϶� ������(k) index ���� �Ű������� ����
bool graph:: DFSpath (int j, int k) 
{
	bool found = false;
	enodePtr eptr;

	cout << vertex[j].vdata.vname;
	visited[j] = true;
	eptr = vertex[j].edgeHead;

	while (eptr && !found)
	{
		// ������? => ����
		if (eptr->vnum == k)
		{
			// ������� (����)
			cout << "   <" << j << "," << eptr->vnum << ">" << endl;
			// ������ ���� ���
			cout << vertex[k].vdata.vname << endl;

			found = true;
		}
		else if (visited[eptr->vnum] == false)
		{
			// ������� (����)
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
