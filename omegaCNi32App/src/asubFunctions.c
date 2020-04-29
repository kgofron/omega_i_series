#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <registryFunction.h>
#include <aSubRecord.h>
#include <epicsExport.h>
#include <epicsTime.h>

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

#define N_KEYS 256
char* keys[N_KEYS]={0};
int vals[N_KEYS]={0};

int find_or_add_key(char* pv_name){
	int i=0;
	for(i=0; i<N_KEYS; ++i){
		if(keys[i]==0){
			keys[i] = pv_name;
			return i;
		}
		else if(!strcmp(keys[i], pv_name)){
			return i;
		}
	}
}

int isAlarm(char* alarm_text){
	if(!strcmp(alarm_text, "NO_ALARM")){
		return 0;
	}
	return 1;
}

static long rollCall(aSubRecord *prec)
{
	char* pv_name = ((char*)prec->b);
	char* alarm_text = ((char*)prec->a);
	int index;
	//printf("STAT: %s %s\n", ((char*)prec->b),((char*)prec->a));
	index = find_or_add_key(pv_name);
	vals[index] = isAlarm(alarm_text);
	return 0;
}

static long timeElapsed(aSubRecord *prec)
{
	epicsTimeStamp t;
	epicsTimeGetCurrent(&t);
	long t_diff = t.secPastEpoch - *((double*)prec->a);
	//printf("here\n");
	//printf("%d\n", t.secPastEpoch);
	*((double*)prec->vala) = t_diff;
	prec->stat = "COMM1";
	prec->nsta = "COMM1";
	return 0;
}

static long alarmSum(aSubRecord *prec){
	int i=0;
	while(keys[i]!=0){
		if(vals[i]){
			//prec->vala="ALARM";
			//printf("ALARM\n");
			*((double*)prec->vala)=1.0;
			return 0;
		}
		++i;
	}
	//rec->vala="NO_ALARM";
	*((double*)prec->vala)=0.0;
	
	return 0;
}


epicsRegisterFunction(filter);
epicsRegisterFunction(rollCall);
epicsRegisterFunction(alarmSum);
epicsRegisterFunction(timeElapsed);
