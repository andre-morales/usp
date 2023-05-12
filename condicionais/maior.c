#include <stdio.h>

int main() {
	int x,y,z;

	printf("Entre com três inteiros:");

	scanf("%d %d %d",&x,&y,&z);

	int m;
	// O maior entre o X e Y
	m = (x > y) ? x : y;
	
	// O maior entre o outro maior e Z
	m = (m > z) ? m : z;
	
	printf ("O maior número é: %d\n", m);
}
