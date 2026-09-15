#include <stdio.h>
#include <math.h>

#define MAX 10
#define EPS 0.00001

// Function to display matrix
void displayMatrix(float a[MAX][MAX + 1], int n)
{
    int i, j;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j <= n; j++)
        {
            printf("%8.2f", a[i][j]);
        }
        printf("\n");
    }
}

// Gaussian Elimination with Partial Pivoting
int gaussian(float a[MAX][MAX + 1], int n)
{
    int i, j, k, p;
    float factor, temp;

    for(i = 0; i < n; i++)
    {
        // Find largest pivot
        p = i;

        for(k = i + 1; k < n; k++)
        {
            if(fabs(a[k][i]) > fabs(a[p][i]))
            {
                p = k;
            }
        }

        // Check for zero pivot
        if(fabs(a[p][i]) < EPS)
        {
            continue;
        }

        // Swap rows
        if(p != i)
        {
            for(j = 0; j <= n; j++)
            {
                temp = a[i][j];
                a[i][j] = a[p][j];
                a[p][j] = temp;
            }
        }

        // Eliminate elements below pivot
        for(k = i + 1; k < n; k++)
        {
            factor = a[k][i] / a[i][i];

            for(j = i; j <= n; j++)
            {
                a[k][j] = a[k][j] - factor * a[i][j];
            }
        }
    }

    return 1;
}

// Back Substitution
int backSubstitution(float a[MAX][MAX + 1], float x[MAX], int n)
{
    int i, j;
    float sum;

    for(i = n - 1; i >= 0; i--)
    {
        if(fabs(a[i][i]) < EPS)
        {
            return 0;
        }

        sum = a[i][n];

        for(j = i + 1; j < n; j++)
        {
            sum = sum - a[i][j] * x[j];
        }

        x[i] = sum / a[i][i];
    }

    return 1;
}

// Verify solution
void verify(float a[MAX][MAX], float b[MAX],
            float x[MAX], int n)
{
    int i, j;
    float sum;

    printf("\nVerification:\n");

    for(i = 0; i < n; i++)
    {
        sum = 0;

        for(j = 0; j < n; j++)
        {
            sum = sum + a[i][j] * x[j];
        }

        printf("Equation %d: %.2f = %.2f",
               i + 1, sum, b[i]);

        if(fabs(sum - b[i]) < EPS)
            printf("  -> Verified\n");
        else
            printf("  -> Not Verified\n");
    }
}

// Main function
int main()
{
    int n, i, j;
    float a[MAX][MAX];
    float b[MAX];
    float aug[MAX][MAX + 1];
    float x[MAX];

    printf("Enter the order of matrix: ");
    scanf("%d", &n);


    // Input coefficient matrix
    printf("\nEnter coefficient matrix:\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%f", &a[i][j]);
        }
    }

    // Input RHS vector
    printf("\nEnter RHS vector:\n");

    for(i = 0; i < n; i++)
    {
        scanf("%f", &b[i]);
    }

    // Create augmented matrix
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            aug[i][j] = a[i][j];
        }

        aug[i][n] = b[i];
    }

    // Display coefficient matrix
    printf("\nInput Coefficient Matrix:\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("%8.2f", a[i][j]);
        }
        printf("\n");
    }

    // Display RHS
    printf("\nRHS Vector:\n");

    for(i = 0; i < n; i++)
    {
        printf("%8.2f\n", b[i]);
    }

    // Display augmented matrix
    printf("\nAugmented Matrix:\n");
    displayMatrix(aug, n);

    // Gaussian elimination
    gaussian(aug, n);

    // Display upper triangular matrix
    printf("\nMatrix after Forward Elimination:\n");
    displayMatrix(aug, n);

    // Back substitution
    if(backSubstitution(aug, x, n) == 0)
    {
      printf("\nError: System has no unique solution.\n");
    return 0;
    } 

    // Display solution
    printf("\nSolution after Back Substitution:\n");

    for(i = 0; i < n; i++)
    {
      printf("x%d = %.2f\n", i + 1, x[i]);
    }
    // Verification
    verify(a, b, x, n);

    return 0;
}