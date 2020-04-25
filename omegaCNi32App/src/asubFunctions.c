#include <stdlib.h>
#include <stdio.h>
#include <registryFunction.h>
#include <aSubRecord.h>
#include <epicsExport.h>

#define N 5
#define FILTERING_ON 0

static int compare (const void * a, const void * b)
{
	if (*(double*)a > *(double*)b) return 1;
	else if (*(double*)a < *(double*)b) return -1;
	else return 0;  
}

double median(double* in){
	int i = 0;
	double* in_copy;
	double ret;
	in_copy = (double*) malloc(N*sizeof(double));
	for(i=0; i<N; ++i){
		in_copy[i] = in[i];
	}
	qsort(in_copy,N,sizeof(double), compare);
	ret = in_copy[(int)(N/2)];
	free(in_copy);
	return ret;
}

int isOutlier(double* data, double val){
	if(val > median(data)+10) return 1;
	if(val < median(data)-10) return 1;
	return 0;
}

static long filter(aSubRecord *prec)
{
	static double lastN[N] = { 0 };
	static int count=0;
	double raw = *((double*)prec->a);
	if(!FILTERING_ON){
		*((double*)prec->vala) = raw;
	}
	else if(!isOutlier(lastN,raw)){
		*((double*)prec->vala) = raw;
	}
	if(raw==0.0)
		return;
	lastN[count] = raw;
	count++;
	count = count % N;
    return 0;
}

char* keys[256];
int vals[256];

static long rollCall(aSubRecord *prec)
{
	printf("STAT: %s %s\n", ((char*)prec->inpa->name),((char*)prec->a));
	return 0;
}


epicsRegisterFunction(filter);
epicsRegisterFunction(rollCall);
