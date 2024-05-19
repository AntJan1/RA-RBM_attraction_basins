#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Define the parameters for the Pareto distribution
double alpha = 0.73;   // Shape parameter
double scale = 0.87;   // Scale parameter
double location = 0.0; // Location parameter

// Generate a random number following the Pareto distribution
double generateRandomNumber() {
    // Generate a random number between 0 and 1
    double random = (double)rand() / RAND_MAX;

    // Apply the inverse transform method
    double number = scale / pow(1 - random, 1 / alpha) - (scale-location);

    return number;
}

int main(int argc, char *argv[]) {
    // Seed the random number generator
    srand(time(NULL));
    FILE *amps;
    amps=fopen("amplitudes","w");
    int n=atoi(argv[1]);
    int powr=(int)pow(2,n);
	double *tab=malloc(powr*sizeof(double));
    // Generate and print 10 random numbers following the Pareto distribution
    for (int i = 0; i < powr/2; i++) {
        *(tab+i) = generateRandomNumber();
        }
    for(int i=0;i<powr/2;i++)
	    *(tab+powr-1-i)=*(tab+i);
    for(int i=0;i<powr;i++)
	    fprintf(amps,"%f\n",*(tab+i));

    fclose(amps);
    return 0;
}

