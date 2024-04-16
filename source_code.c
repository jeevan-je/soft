#include<stdio.h>

// Function to calculate factorial recursively
int fact(int n) {
    if (n == 1 || n == 0) { // Base case: if n is 0 or 1, return 1
        return 1;
    }
    int prod = 1; // Initialize a variable to store the product
    while (n > 0) { // Loop to calculate factorial iteratively
        prod = prod * n; // Multiply current product by n
        n--; // Decrement n
    }
    return prod; // Return the final product
}

int main() {
    int k = fact(7); // Call the fact function to calculate factorial of 7
    printf("%d", k); // Print the result
    return 0; // Return 0 to indicate successful completion
}
