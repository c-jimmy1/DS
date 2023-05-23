#include <iostream>

using namespace std;

void compute_squares(unsigned *a, unsigned *b, int n) {
	for (int x = 0; x < n; x++)
		*(b+x) = *(a+x) * *(a+x); 
}

void print_array(unsigned *a, int n) {
	for (int x = 0; x < n; x++) {
		unsigned i = *(a + x); 
		cout << i << ' ';
	} 
	cout << endl; 
}

int main() {
	const int a_size = 5; 
	unsigned a[a_size] = { 1, 2, 3, 4, 5 }; 
	unsigned b[a_size]; 


	compute_squares(a, b, a_size); 

	print_array(a, a_size);
	print_array(b, a_size);


	return 0; 
}