//
//프로그램 설명
/*

다양한 내부정렬을 구현하고, 각 정렬이 완료되는데까지 걸리는 시간을 출력하여 비교/분석한다.
시간 측정은 Timer 함수의 멤버함수를 호출해 구현한다.

*/
//
// 2019111309
// 디지털미디어학과
// 황혜림
// 자료구조 (02분반)
// 2020.11.24
//

#define SWAP(x, y, t) (t=x, x=y, y=t)
#define radix 10

//---------------------------------------------------------------//
// 버블정렬을 이용한 오름차순 정렬                               //
//---------------------------------------------------------------//

//버블정렬
void bubbleSort(Array L) 
{
	int temp;
	for (int i = 1; i <= Max; i++)
		for (int j = i + 1; j <= Max; j++)
			if (L[i] > L[j])
				SWAP(L[i], L[j], temp);

}

// 선택정렬 
// 버블 정렬에 비해서 불필요한 swap 수를 줄임
// position에 작은 값을 갱신한 후, 최종적으로 position번째 값과 swap
void selectionSort (Array L) 
{
	int position, temp;
	for (int i = 1; i <= Max; i++)
	{
		position = i;
		for (int j = i + 1; j <= Max; j++)
			if (L[position] > L[j])
				position = j; // 제일 작은 j를 position에 저장
		SWAP(L[position], L[i], temp);
	}
}

// 삽입정렬
// i번째 원소 정렬시 (1 ... i-1) 까지는 이미 정렬
// 부분적으로 정렬되어 있을 때 효과적 !!!
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
// 삽입정렬 활용해 조금 더 개선한 정렬
void shellSort( Array L ) 
{
	int j, h=1, next;

	// 간격 초기화
	while (3 * h < Max)
		h = 3 * h + 1;

	while (h > 0)
	{
		// 간격을 h로 하는 삽입정렬
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

		// 간격 감소 (마지막 간격은 항상 1 !!!)
		h = h / 3;
	} // while

}

// 퀵정렬
// 전체를 크고 작게 (더이상 나누어지지 않을 때 까지) 나누는 방식
void quickSort(Array L, int left, int right) 
{
	int i, j, pivot, temp;

	if (left < right) // 종료조건
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
// 합병정렬
// 작은게 앞에 오도록 점점 합병해 정렬
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
	// n: 전체 원소의 개수, length: 합병할 subfile의 길이
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
// 합병정렬을 이용한 오름차순 정렬                               //
//---------------------------------------------------------------//
void mergeSort(Array L1, int n)
{
	int i, length = 1;   // 합병할 서브파일의 길이
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
// 힙으로 변환                                                   //
//---------------------------------------------------------------//
void adjust(Array L, int root, int n)
{
	int child, rootkey, temp;
	temp = L[root];
	rootkey = L[root];
	child = 2 * root;		   //왼쪽자식
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
// 힙정렬을 이용한 오름차순 정렬                                 //
//---------------------------------------------------------------//
void heapSort(Array L, int n)
{
	int i, temp;

	// heap으로 만든다
	for (i = n / 2; i>0; i--)
		adjust(L, i, n);

	// 제일큰수(1번째 원소)를 마지막(n번째)으로 옮기고 나머지를 다시 heap으로 만든다.
	for (i = n - 1; i>0; i--)
	{
		SWAP(L[1], L[i + 1], temp);
		adjust(L, 1, i);
	}
}

//---------------------------------------------------------------//
// 기수정렬을 이용한 오름차순 정렬                               //
//---------------------------------------------------------------//

// p : 최대자리수 (RAND_MAX의 경우 최대값은 32767이므로 5자리, 따라서 5)
void radixSort(Array L, int p)
{
	Array temp;        // 중간 결과를 저장
	int counts[radix]; // 각 자리수 당 카운트
	int index, power, i, j, n;
	int k;

	for (n = 0; n < p; n++)
	{
		for (i = 0; i<radix; i++)
			counts[i] = 0; // 초기화

		power = (int)pow((double)radix, (double)n);  // power = 10^n

													 // 현재 자리수(=n) 기준으로 각 숫자의 발생횟수를 센다.
		for (j = 1; j <= Max; j++)
		{
			index = (int)(L[j] / power) % radix;
			counts[index]++;
		}

		// 누적 카운트
		for (i = 1; i<radix; i++)
			counts[i] = counts[i] + counts[i - 1];

		// 누적 카운트를 사용해 각 항목의 위치를 결정
		for (j = Max; j >= 1; j--) // 뒤에서 부터 시작
		{
			index = (int)(L[j] / power) % radix;
			temp[counts[index]] = L[j];
			counts[index]--;
		}

		for (k = 1; k <= Max; k++)	// 중간 결과에서 다시 시작하기 위해 복사
			L[k] = temp[k];
	}
}
