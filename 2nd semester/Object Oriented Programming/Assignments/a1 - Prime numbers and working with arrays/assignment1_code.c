#include <stdio.h>
#include <stdbool.h>

int input()
/// function that reads the value for n and returns it 
/// returns the read value 
{
	
	int n; 
	scanf("%d", &n); //reads the value for n 
	return n;
}

void generate_vector(int vector[], int nr_elements)
/// function that reads the elements of a vector with n elements 
/// vector[] = the vector where the elements are stored 
/// nr_elements = the number of elements inside the vector 
{ 
	for (int i = 0; i < nr_elements; i++)
	{
		printf("\n Give element: ");
		scanf("%d", &vector[i]);
	}
	for (int i = 0; i < nr_elements; i++)
	{
		printf("%d ", vector[i]);
	}
}

bool is_prime(int n)
/// a function that checks if n is prime 
/// return true or false 
{
	if (n < 2)  return false; 
	if (n == 2) return true;
	if (n % 2 == 0) return false; 

	for (int d = 3; d < n; d += 2)
	{
		if (n % d == 0) return false; 
	}
	return true; 
}

void first_n_primes(int n)
/// a function that returns the firts n natural prime numbers 
{
	int i = 1; 
	int start = 2; 
	while (i <= n)
	{
		if (is_prime(start))
		{
			printf("%d ", start); 
			i++; 
		}
		start++; 
	}
}

bool relatively_prime(int nr1, int nr2)
/// a function that check wheter 2 numbers nr1 and nr2 are relatively prime
/// returns true or false 
{
	int res; 
	if (nr1 < nr2) res = nr1;
	else res = nr2; 

	while (res != 0)
	{
		if (nr1 % res == 0 && nr2 % res == 0) break;
		res--;
	}
	if (res == 1) return true;
	return false;
}

void longest_subs(int v[], int n, int* subseq_len, int* subseq_start)
/// a function that returns the start and the len of the max contiguous subsequence of elements that are consecutively relatively prime 
/// using the pointers *subseq_len and *subseq_start it puts at  he memory addr. the value of the start and max_len
{
	int i = 0;
	int max_len = 0, start_pos = 0;

	while (i < n - 1)
	{
		int j = i;
		// while loop to go thru all elements that are consecutively relatively prime 
		while (j + 1 < n && relatively_prime(v[j], v[j + 1]))
			j++;

		int current_len = j - i + 1; //the len of the current subset
		if (current_len > max_len)
		{
			max_len = current_len;
			start_pos = i;
		}
		i = j + 1;  //start the next search from the end of the current longest subset 
	}
	*subseq_start = start_pos;
	*subseq_len = max_len;
}


int main()
{
	printf("Assignment 1. Problem 2");
	printf("\n 1. Read a vector of numbers");
	printf("\n 2. Generate the first n prime numbers");
	printf("\n 3. In the given vector find the longest contiguos subsequence such that any 2 consecutive numbers are relatively prime");
	printf("\n 0. Exit");

	printf("\n");
	int nr_elements;
	int vector[1001];
	int choice; 

	do
	{
		printf("Choose the task: ");
		choice = input();
		printf("\n");


		switch (choice)
		{
		case 0:
		{
			printf("Exiting");
			break;
		}

		case 1:
		{
			printf("Task 1");
			printf("\nHow many elements do you want in the vector?");
			nr_elements = input();
			generate_vector(vector, nr_elements);
			printf("\n");
			break;
		}

		case 2:
		{
			printf("Task 2");
			printf("\nEnter n: ");
			int first_n = input();
			first_n_primes(first_n);
			printf("\n");
			break;
		}

		case 3:
		{
			printf("Task 3");
			printf("\n The vector: ");
			for (int i = 0; i < nr_elements; i++)
			{
				printf("%d ", vector[i]);
			}
			printf("\n");

			int start, len;
			longest_subs(vector, nr_elements, &len, &start);
			printf("Longest contiguous subsequence: ");
			for (int i = start; i < start + len; i++)
			{
				printf("%d ", vector[i]);
			}
			printf("\nof length: ");
			printf("%d", len);

			printf("\n");
			break;
		}

		default:
			printf("Invalid command");

		}
	} while (choice != 0);

	return 0; 
}