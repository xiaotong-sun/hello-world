// Fibonacci_Search.c

#include <stdio.h>

#define MAX_SIZE 20
#define MAX 100

// ----����쳲���������-----
void Fibonacci(int *F) {
    F[0] = 0;
    F[1] = 1;
    for (int i = 2; i < MAX_SIZE; ++i) {
        F[i] = F[i - 1] + F[i - 2];
    }
}

//----쳲����������㷨------
int Fibonacci_Search(int *a, int n, int key) {     //aΪ��Ҫ���ҵ����飬nΪa�ĳ��ȣ�keyΪҪ���ҵ���
    int F[MAX_SIZE];
    Fibonacci(F);
    int u = 0;
    while (n > F[u]) {						//����nλ��쳲��������е�λ��
        u ++;
    }
    for (int i = n; i < F[u] - 1; ++i) {	//���n < F[u] - 1,�����������һ������λ��ֱ��n = F[u] -1
        a[i + 1] = a[i];
    }
    int low = 1;
    int high = n;
    while (low <= high) {
        int mid = low + F[u - 1] - 1;
        if (mid > n && a[n] == key) {		//��mid>=n��˵������չ����ֵ,����n
            return n;
        } else if (mid > n){
            return -2;						//���ҵ����ݲ�����
        }
        if (key == a[mid]) {
            return mid;
        } else if (key > a[mid]) {
            low = mid + 1;
            u -= 2;
        } else if (key < a[mid]) {
            high = mid - 1;
            u--;
        }
    }
    return -2; 								//���ҵ����ݲ�����
}

int main() {
    int F[MAX_SIZE];
    Fibonacci(F);
    int a[MAX];
    int n;
    printf("���������ݵĸ�����");
    scanf("%d", &n);
    printf("���������ݣ�\n");
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    int key;
    printf("������Ҫ���ҵ����ݣ�");
    scanf("%d", &key);
    int answer = Fibonacci_Search(a, n, key);
    printf("����λ�ڵ�%d��\n", answer);
    return 0;
}