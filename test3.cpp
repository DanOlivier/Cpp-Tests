#include <stdio.h>
#include <iostream>

int f(int, int);
int main()
{
	fprintf(stderr, "Hello World: %d\n", 3);
	int i = 0;
	i = ++i + 2;       // 1. undefined behavior until C++11
	i = i++ + 2;       // 2. undefined behavior until C++17
	f(i = -2, i = -2); // 3. undefined behavior until C++17
	f(++i, ++i);       // 4. undefined behavior until C++17, unspecified after C++17
	i = ++i + i++;     // 5. undefined behavior


	int a[10];
	std::cout << i << i++; // 6. undefined behavior until C++17
	a[i] = i++;            // 7. undefined behavior until C++17
	int n = ++i + i;       // 8. undefined behavior

	i = ++i + i++;  // 1. undefined behavior
	i = i++ + 1;    // 2. undefined behavior
	i = ++i + 1;    // 3. undefined behavior (well-defined in C++11)
	++ ++i;         // 4. undefined behavior (well-defined in C++11)
	f(++i, ++i);    // 5. undefined behavior
	f(i = -1, i = -1); // 6. undefined behavior	
	return 0;
}
