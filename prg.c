#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int scalar(int alpha,int beta,int n){
	int sum=0;
	for(int i=0;i<n;i++){
		if(alpha%2==beta%2)
			sum+=1;
		else
			sum-=1;
		alpha=(alpha-alpha%2)/2;
		beta=(beta-beta%2)/2;
	}
	if(sum>0)
		return 1;
	else
		return -1;

}

int main(int argc, char *argv[]){
	FILE *amps;
	FILE *out;
	FILE *ev;
	int n=atoi(argv[1]);
	ev=fopen("evollist","w");
	out=fopen("output","w");
	amps = fopen("amplitudes", "r");
	if (amps){
		printf("found amps\n");
	}
	else{//xd zrób to 
		printf("generating amps\n");

		return 0;
		// int return_value = system("example.exe");
// 
    		// if (return_value == -1) {
        	// perror("System call failed");
    		// } else {
        	// printf("Program exited with status %d\n", return_value);
    		// }
	}
	// Initialisation of variables and memory allocation
	int powr=(int)pow(2,n);
	float sum;
	int res;
	float gamma=1;
	int v;
	int state;
	float *amp = malloc(powr*sizeof(float));
	int *scal = malloc(powr*sizeof(int));
	int *evol=malloc(powr*sizeof(int));
	
	// Loading amplitudes from the 'amplitudes' file
	for(int i=0;i<powr;i++)
		fscanf(amps,"%f",(amp+i));
	
	// Loop over all possible configurations \beta 
	for(int beta=0;beta<powr;beta++){
		res=0;
		// Creating table of signs of scalar products of beta with each configuration (alpha)
		for(int alpha=0;i<powr;i++)
			*(scal+alpha)=scalar(alpha,beta,n);

		for(int i=0;i<n;i++){
			sum=0;
			for(int alpha=0;alpha<powr;alpha++){
				v=alpha;
				for(int j=0;j<i;j++)
					v=(v-v%2)/2;
				v%=2;
				sum+=gamma**(scal+alpha)**(amp+alpha)*pow(-1,v);
	//			printf("%f, %f, %f\n",sum, v, pow(-1,v));
			}
			if(sum<0)
				res+=(int)pow(2,i);
		}
		printf("%d %d\n",beta,res);
		fprintf(ev,"%d\n",res);
		*(evol+beta)=res;
	}
	int j;
	int step;
	printf("\n");
	for(int i=0;i<powr;i++){
		j=i;
		step=0;
		while(j!=*(evol+j)){
			j=*(evol+j);
			step++;
		fprintf(out,"%d\t",j);
		fprintf(out,"%d\n",step);
		// printf("%d\n",j);
	}
	free(evol);
	free(amp);
	free(scal);
   	fclose(ev);
	fclose(amps);
	fclose(out);
	return 0;
}
