//
//���α׷� ����
/*

�پ��� ���������� �����ϰ�, �� ������ �Ϸ�Ǵµ����� �ɸ��� �ð��� ����Ͽ� ��/�м��Ѵ�.
�ð� ������ Timer �Լ��� ����Լ��� ȣ���� �����Ѵ�.

*/
//
// 2019111309
// �����й̵���а�
// Ȳ����
// �ڷᱸ�� (02�й�)
// 2020.11.24
//

#define SWAP(x, y, t) (t=x, x=y, y=t)
#define radix 10

//---------------------------------------------------------------//
// ���������� �̿��� �������� ����                               //
//---------------------------------------------------------------//

//��������
void bubbleSort(Array L) 
{
	int temp;
	for (int i = 1; i <= Max; i++)
		for (int j = i + 1; j <= Max; j++)
			if (L[i] > L[j])
				SWAP(L[i], L[j], temp);

}

// �������� 
// ���� ���Ŀ� ���ؼ� ���ʿ��� swap ���� ����
// position�� ���� ���� ������ ��, ���������� position��° ���� swap
void selectionSort (Array L) 
{
	int position, temp;
	for (int i = 1; i <= Max; i++)
	{
		position = i;
		for (int j = i + 1; j <= Max; j++)
			if (L[position] > L[j])
				position = j; // ���� ���� j�� position�� ����
		SWAP(L[position], L[i], temp);
	}
}

// ��������
// i��° ���� ���Ľ� (1 ... i-1) ������ �̹� ����
// �κ������� ���ĵǾ� ���� �� ȿ���� !!!
void insertionSort (Array L) 
{
	int j, next;

	for (int i = 1; i <= Max; i++)
	{
		next = L[i];
		j = i - 1;
		while (L[j] > next && j>0)
		{
			L[j+1] = L[j];
			j--;
		}
		L[j + 1] = next;
	}

}

// 1 4 13 40 121 364 1093  3280 9841 ...
// 3h + 1
// �������� Ȱ���� ���� �� ������ ����
void shellSort( Array L ) 
{
	int j, h=1, next;

	// ���� �ʱ�ȭ
	while (3 * h < Max)
		h = 3 * h + 1;

	while (h > 0)
	{
		// ������ h�� �ϴ� ��������
		for (int i = 1; i <= Max; i++)
		{
			next = L[i];
			j = i - h;
			while (L[j] > next && j > 0)
			{
				L[j + h] = L[j];
				j = j - h;
			}
			L[j + h] = next;
		}

		// ���� ���� (������ ������ �׻� 1 !!!)
		h = h / 3;
	} // while

}

// ������
// ��ü�� ũ�� �۰� (���̻� ���������� ���� �� ����) ������ ���
void quickSort(Array L, int left, int right) 
{
	int i, j, pivot, temp;

	if (left < right) // ��������
	{
		i = left;
		j = right + 1;
		pivot = L[left];
		do
		{
			do i++; while (L[i] < pivot);
			do j--; while (L[j] > pivot);
			if (i < j)
				SWAP(L[i], L[j], temp);
		} while (i < j);
		SWAP(L[left], L[j], temp);
		quickSort(L, left, j - 1);
		quickSort(L, j + 1, right);
	}
}


//---------------------------------------------------------------//
// merge : L1[l..m]+L1[(m+1)..n] => L2[l..m]                     //
//---------------------------------------------------------------//
// �պ�����
// ������ �տ� ������ ���� �պ��� ����
void merge(Array L1, Array L2, int l, int m, int n)
{
	int i, j, k, t;

	i = l;
	k = l;
	j = m + 1;

	while ((i <= m) && (j <= n))
	{
		if (L1[i] <= L1[j])
			L2[k++] = L1[i++];
		else
			L2[k++] = L1[j++];
	}

	if (i > m)
		for (t = j; t <= n; t++)
			L2[k++] = L1[t];
	else
		for (t = i; t <= m; t++)
			L2[k++] = L1[t];
}

//--------------------------------------------------------------
void Mpass(Array L1, Array L2, int n, int length)
{
	// n: ��ü ������ ����, length: �պ��� subfile�� ����
	int i, t;

	i = 1;
	while (i <= (n - 2 * length + 1))
	{
		merge(L1, L2, i, i + length - 1, i + 2 * length - 1);
		i += 2 * length;
	}

	if (i + length < n)
		merge(L1, L2, i, i + length - 1, n);
	else
		for (t = i; t < n; t++)
			L2[t] = L1[t];
}

//---------------------------------------------------------------//
// �պ������� �̿��� �������� ����                               //
//---------------------------------------------------------------//
void mergeSort(Array L1, int n)
{
	int i, length = 1;   // �պ��� ���������� ����
	Array L2;

	while (length < n) {
		Mpass(L1, L2, n, length);
		length *= 2;
		for (i = 1; i < Max + 1; i++)
			L1[i] = L2[i];
		//Mpass(L2, L1, n, length);
		//length *= 2;
	}
}

//---------------------------------------------------------------//
// ������ ��ȯ                                                   //
//---------------------------------------------------------------//
void adjust(Array L, int root, int n)
{
	int child, rootkey, temp;
	temp = L[root];
	rootkey = L[root];
	child = 2 * root;		   //�����ڽ�
	while (child <= n)
	{
		if ((child<n) && (L[child]<L[child + 1]))
			child++;
		if (rootkey > L[child])
			break;
		else
		{
			L[child / 2] = L[child];
			child *= 2;
		}
	}
	L[child / 2] = temp;
}

//---------------------------------------------------------------//
// �������� �̿��� �������� ����                                 //
//---------------------------------------------------------------//
void heapSort(Array L, int n)
{
	int i, temp;

	// heap���� �����
	for (i = n / 2; i>0; i--)
		adjust(L, i, n);

	// ����ū��(1��° ����)�� ������(n��°)���� �ű�� �������� �ٽ� heap���� �����.
	for (i = n - 1; i>0; i--)
	{
		SWAP(L[1], L[i + 1], temp);
		adjust(L, 1, i);
	}
}

//---------------------------------------------------------------//
// ��������� �̿��� �������� ����                               //
//---------------------------------------------------------------//

// p : �ִ��ڸ��� (RAND_MAX�� ��� �ִ밪�� 32767�̹Ƿ� 5�ڸ�, ���� 5)
void radixSort(Array L, int p)
{
	Array temp;        // �߰� ����� ����
	int counts[radix]; // �� �ڸ��� �� ī��Ʈ
	int index, power, i, j, n;
	int k;

	for (n = 0; n < p; n++)
	{
		for (i = 0; i<radix; i++)
			counts[i] = 0; // �ʱ�ȭ

		power = (int)pow((double)radix, (double)n);  // power = 10^n

													 // ���� �ڸ���(=n) �������� �� ������ �߻�Ƚ���� ����.
		for (j = 1; j <= Max; j++)
		{
			index = (int)(L[j] / power) % radix;
			counts[index]++;
		}

		// ���� ī��Ʈ
		for (i = 1; i<radix; i++)
			counts[i] = counts[i] + counts[i - 1];

		// ���� ī��Ʈ�� ����� �� �׸��� ��ġ�� ����
		for (j = Max; j >= 1; j--) // �ڿ��� ���� ����
		{
			index = (int)(L[j] / power) % radix;
			temp[counts[index]] = L[j];
			counts[index]--;
		}

		for (k = 1; k <= Max; k++)	// �߰� ������� �ٽ� �����ϱ� ���� ����
			L[k] = temp[k];
	}
}
