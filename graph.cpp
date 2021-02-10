
//���α׷� ����
/*
[ weighted graph ]
- ���� ��ķ� ǥ���� ����ġ �׷���
- ������ ������ ��Ŀ� ����

[ graph Ŭ������ ���� ��������� ]
1. size
- int������ ������ ������ �����صδ� �����̴�.

2. vertex[]
- 1���� �迭��, ������ �̸��� �迭�� �����ϴ� �����̴�.
- vertex[]�迭�� ũ��� size ������ �����ϰ�, �ʿ信 ���� ������ų �� �ִ�.

3. edgeData[][]
- ��� �����鿡 ���� ������ ���� ������ �����ϴ� 2���� �迭�̴�.
- exist, weight, second�� �̷���� �ִ�.
	exist : bool ���·�, ������ �����Ѵٸ� T, �ƴϸ� F�� �����Ѵ�.
	weight : int ���·�, �� ������ ����ġ�� �����Ѵ�.
	second : int ���·�, �ִ� ��ο����� ���� ������ ������ �����Ѵ�. (��� ��� �� �ʿ�)
*/

// 2019111309
// �����й̵���а�
// Ȳ����
// �ڷᱸ�� (02�й�)
// 2020.12.08


// graph ������
//---------------------------------------------------------------
graph:: graph() 
{
	size = 0; //���� �ʱ�ȭ (�迭������ 0)
	for (int j = 0; j < Max; j++)
		for (int k = 0; k < Max; k++) 
			edge[j][k].exist = false; //���� �ʱ�ȭ
}

// graph �Ҹ���
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
bool graph:: vertexExists (char2 SrchKey, int &vnum) //������ �̸��� �Ű������� ����
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
// �׷����� ���� newVertex�� �߰��Ѵ�.    				       //	
// 0: �߰����� ����											   //		
// 1: �߰���												   //
// 2: ������												   //
//-------------------------------------------------------------//
int graph::insertVertex(vertexData newVertex)
{
	int j;
	// ������ �����ϸ� ������Ʈ
	if (vertexExists(newVertex.vname, j))
	{
		vertex[j] = newVertex;
		return(2);
	}
	// ������ �������� �ʰ� �׷����� ��ȭ�� �ƴϸ� �߰�
	else if (!isFull())
	{
		vertex[size++] = newVertex;
		return(1);
	}
	// �ƴϸ� �߰����� �ʴ´�
	else
		return(0);
}

//---------------------------------------------------------------
// ���� �߰�
// ���ex. E A B 10 : A�� B ���̿� ����ġ 10�� ���� �߰�
bool graph::insertEdge (char2 from, char2 to, int wt) 
{
	int j, k;

	//�����ϴ� �����ΰ�?
	if (vertexExists(from, j) && vertexExists(to, k))//�� ������ index�� j�� k�� ����
	{
		//�������̱� ������ �������� ���� �߰�
		edge[j][k].exist = true; // ���� �߰�
		edge[j][k].weight = wt; // ����ġ ����
		edge[k][j].exist = true; // ���� �߰�
		edge[k][j].weight = wt; // ����ġ ����
		return true;
	}
	else
		return false;
}

//---------------------------------------------------------------
// ���� �����ϴ°�?
// ���ex. X A B : A�� B������ ������ �����ϸ� ����ġ�� �Բ� ���
bool graph:: edgeExists (char2 from, char2 to, int &wt) 
{
	int j, k;

	//���� ������ �����ϰ�(�� ������ index�� j�� k�� ����), ���� ���� �Ѵٸ�
	if (vertexExists(from, j) && vertexExists(to, k) && edge[j][k].exist)
	{
		wt = edge[j][k].weight; // ����ġ wt�� ����
		return true;
	}
	else
		return false;
}

//---------------------------------------------------------------
// ��� �����ϴ°�?
// ���ex. P A B : A�� B������ ��ΰ� �����ϸ� ����ġ�� �հ� �Բ� ���
bool graph:: pathExists (char2 from, char2 to, int &wt) 
{
	int j, k;

	//���� ������ �����ϰ�(�� ������ index�� j�� k�� ����), ��� ���� �Ѵٸ�
	if (vertexExists(from, j) && vertexExists(to, k) && path[j][k].exist)
	{
		wt = path[j][k].weight; // ����ġ wt�� ����
		return true;
	}
	else
		return false;
}

// �����Լ�
// ��ȸ�ϴ� ��� ���
// path�� second�� Ȱ���Ͽ� ��� looping�� ����.
void graph:: displayPath (char2 from, char2 to) 
{
	int j, k;
	vertexExists(from, j); // �Է¹��� ó�� ������ ��ġ�� j�� �޾ƿ�
	vertexExists(to, k); // �Է¹��� ó�� ������ ��ġ�� k�� �޾ƿ�

	cout << vertex[j].vname << " <-> " << vertex[k].vname<<"�� �ִܰ�� : ";

	while (j != k) // ������ ���� ���� ������ �ݺ�
	{
		cout << vertex[j].vname << " -> ";
		j = path[j][k].second; // �������� ��ġ(second ��ġ)�� ������Ʈ
	}

	cout << vertex[k].vname; // ������ ���� ���
}

//---------------------------------------------------------------
void graph:: computePaths () 
{
	int j, k, m;

	// 1. ���� ��ķ� �ʱ�ȭ
	for (j=0; j<size; j++)
		for (k = 0; k < size; k++)
		{
			path[j][k].exist = edge[j][k].exist;
			path[j][k].weight = edge[j][k].weight;
			path[j][k].second = k;
		}

	// 2. �밢�� ���� �ʱ�ȭ (�ڽ��Ƿ��� ��� ��)
	for (j = 0; j < size; j++)
	{
		path[j][j].exist = true;
		path[j][j].weight = 0;
		path[j][k].second = j;
	}

	// 3. ��� �����ֿ� ���� �ִܰ�� ��� (3�� looping)
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
					path[j][k].second = path[j][m].second; //*�߿�
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
					cout << "V " << v.vname << " : �����Ϳ� ������ �ֽ��ϴ�." << endl;
				else if (ch == 'E')
					cout << "E " << source << " " << dest << " : �����Ϳ� ������ �ֽ��ϴ�." << endl;
				getchar(); getchar();
			}
		}
	}
}

//---------------------------------------------------------------
// �׷��� ���: �������� second �� ����
//
void graph:: showStructure () 
{
	int j;
	//system("cls"); cout << endl;
	cout << endl;
	if (isEmpty()) 
		cout << "�׷����� ����ֽ��ϴ�" << endl;
	else 
	{
		cout << "�׷���" << endl << endl;
		cout << "����:" << endl;
		for (j = 0; j < size; j++)
			cout << setw(2) << "     " << j << " : " << vertex[j].vname << endl;
		cout  << endl << "���� ���:" << endl;
		printMatrix(size, edge);
//		cout << endl  << "��� ���:" << endl;
//		printMatrix(size, path);
		cout << endl;
	}
}

//---------------------------------------------------------------
// �׷��� ���: �������� second ���� ���
//
void graph:: showSecond() 
{
	if (isEmpty()) 
		cout << "�׷����� ����ֽ��ϴ�" << endl;
	else 
	{
		cout << "��� ���(second):" << endl;
		printMatrix(size, path, 1);
		cout << endl;
	}
}

//---------------------------------------------------------------
// ����� weight ���� ���
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
// ����� second ���� ���
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