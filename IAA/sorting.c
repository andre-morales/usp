#include <stdio.h>

void swap(int[], int, int);
void printArr(int[], int);

void bubble_sort(int vec[], int n) {
	for (int m = n - 1; m >= 1; m--) {
		for (int i = 0; i < m; i++) {
			if (vec[i] > vec[i + 1]) {
				swap(vec, i, i+1);
			}
		}
	}
}

void insertion_sort(int vec[], int n) {
	for (int p = 1; p < n; p++) {
		for (int b = p; b > 0; b--) {
			if (vec[b - 1] <= vec[b]) break;

			swap(vec, b, b-1);
		}
	}
}

void merge(int vec[], int s, int m, int e) {
	printf("Merging %i : %i : %i\n", s, m, e);

	int A[m-s+2];
	for (int i = 0; i < m-s+2; i++) {
		A[i] = vec[s+i];
	}
	A[m-s+1] = 99999;

	int B[e-m+1];
	for (int i = 0; i < e-m+1; i++) {
		B[i] = vec[m+i];
	}
	B[e-m] = 999999;

	int aI = 0;
	int bI = 0;
	for (int i = s; i <= e; i++) {
		if (vec[aI] <= vec[bI]) {
			vec[i] = vec[aI];
			aI++;
		} else {
			vec[i] = vec[bI];
			bI++;
		}
	}
}

void rec_merge_sort(int vec[], int s, int e, int d) {
	if (e <= s) return;

	for (int i = 0; i < d; i++) {
		printf("\t");	
	}
	printf("Sorting from %i to %i\n", s, e);

	int hs = (e - s + 1) / 2;
	int m = s + hs - 1;

	rec_merge_sort(vec, s, m, d + 1);
	rec_merge_sort(vec, m + 1, e, d + 1);
	merge(vec, s, m, e);
}


void merge_sort(int vec[], int n) {
	rec_merge_sort(vec, 0, n - 1, 0);
}


void selection_sort(int vec[], int n) {
	for (int d = 0; d < n - 1; d++) {
		int min = d;
		for (int i = d + 1; i < n; i++) {
			if (vec[i] < vec[min]) min = i;
		}

		swap(vec, d, min);
	}
}

int main() {
	int vector[] = {4, 1, 2, 9, 3, 0, 8, 23, 5, 92, 7, 6, 10};
	int size = sizeof(vector) / 4;

	printf("Antes: ");
	printArr(vector, size);

	merge_sort(vector, size);

	printf("Depois: ");
	printArr(vector, size);
}

void printArr(int arr[], int n) {
	printf("[");
	for (int i = 0; i < n - 1; i++) {
		printf("%i, ", arr[i]);
	}
	printf("%i]\n", arr[n-1]);
}

void swap(int v[], int p, int q) {
	int x = v[p];
	v[p] = v[q];
	v[q] = x;
}