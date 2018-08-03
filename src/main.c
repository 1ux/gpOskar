#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef NDEBUG
    #define DEBUG
#endif

/*This program constructs the adequate gnuplot program call
//when you give it the csv raw data from OpenHantek
//You need gnuplot version >=5.0
//The basic gnuplot config file is in /src
*/

struct measur_frame
{
    bool cha1;          //was channel 1 active?
    bool cha2;          //was channel 2 active?
    int lines_cha1;     //Number of measurements on channel 1
    int lines_cha2;     //Number of measurements on channel 2
    double interval_cha1;     //Sampling interval on cha1
    double interval_cha2;     //Sampling interval on cha2
};

int main(int argc, char *argv[])
{
    struct measur_frame mf = {false,false,0,0,0.0,0.0};
    char input_cache[32];       //cache for reading the input file
    char *time_res;             //ref. to the time resolution in input_cache 
    char gnuplot_call[128];     //parameterline buffer for gnuplot
    double frq=0.0;
    FILE *fp;


    if(argc<2)
    {
        fprintf(stderr,"%s","no input file!\n"
        "press gpOpenHantek -h for help\n");
        return 1;
    }
    if(argc >2)
    {
        fprintf(stderr,"%s","too many arguments\n");
        return 1;
    }
    if(strcmp(argv[1],"-h")==0)
    {
        printf("\n\tgpOpenHantek - utility for simple output of gnuplot-graphs\n"
                "\trecorded by openhantek. You need gnuplot version >=5.0\n\n");
        printf("\tuse: gpOpenHantek SOURCE.txt\n\tSOURCE is a csv file from " 
                "openhantek with voltage values\n\n");
        return 0;
    }

    if(NULL==(fp=fopen(argv[1],"r")))
    {
        fprintf(stderr,"%s","opening input stream failed!\n");
        return 1;
    }
    while(1)
    {
        fgets(input_cache,sizeof(input_cache),fp);          //read raw data
        if(feof(fp)) break;
        if(!strncmp("#CH1",input_cache,4))                  //search for characteristic measuring string
        {
            if(!mf.cha1)    mf.cha1=true;                   //set channel1 active
            else                                            //do not accept multiple assignments per channel
            {
                fprintf(stderr,"%s","input file corrupted,multiple cha1!\n");
                return 1;
            }
            if((time_res=strpbrk(input_cache,","))==NULL)   //extract time resolution
            {
                fprintf(stderr,"%s","input file corrupted,incorrect measuring string found for CHA1.\n");
                return 1;
            }
            if((mf.interval_cha1=atof(time_res+1))==0)      //convert resolution string into double
            {
                fprintf(stderr,"%s","input file corrupted,incorrect measuring interval on CHA1.\n");
                return 1;
            }
        #ifdef DEBUG
            printf("possible time resolution CHA1:\t%s",time_res+1);
            printf("double interpretation of CHA1:\t%0.12f\n",mf.interval_cha1);
        #endif
        }
        else if(!strncmp("#CH2",input_cache,4))             //search for characteristic measuring string
        {
            if(!mf.cha2)    mf.cha2=true;                   //set channel2 active
            else                                            //do not accept multiple assignments per channel
            {
                fprintf(stderr,"%s","input file corrupted,multiple cha2!\n");
                return 1;
            }
            if((time_res=strpbrk(input_cache,","))==NULL)   //extract time resolution
            {
                fprintf(stderr,"%s","input file corrupted,incorrect measuring string found for CHA2.\n");
                return 1;
            }
            if((mf.interval_cha2=atof(time_res+1))==0)      //convert resolution string into double
            {
                fprintf(stderr,"%s","input file corrupted,incorrect measuring interval on CHA2.\n");
                return 1;
            }
        #ifdef DEBUG
            printf("possible time resolution CHA2:\t%s",time_res+1);
            printf("double interpretation of CHA2:\t%0.12f\n",mf.interval_cha2);
        #endif
        }
        if(atof(input_cache)!=0)                            //count the measured values per channel
        {                                                   //currently only one timebase is accepted
            if((mf.cha1==true) && (mf.cha2==false)) mf.lines_cha1++;
            else if((mf.cha1==true) && (mf.cha2==true) && (mf.lines_cha2 > mf.lines_cha1)) mf.lines_cha1++;
            else if((mf.cha2==true) && (mf.cha1==false)) mf.lines_cha2++;
            else if((mf.cha2==true) && (mf.cha1==true) && (mf.lines_cha1 > mf.lines_cha2)) mf.lines_cha2++;
        }
    }
    //Samples [S]/Samplerate [S/s] = frequenzy
    if(EOF==fclose(fp))
    {
        fprintf(stderr,"funktion \"fclose()\" reports error !\n");
        return 1;
    }
    //Build input-stream for GNUplot
    if(mf.cha1) 
    {
        frq=mf.lines_cha1/(1/mf.interval_cha1); //frq ist ein unpassender Bezeichner
        if(sizeof(gnuplot_call) < snprintf(gnuplot_call,sizeof(gnuplot_call),"gnuplot -c "
                "./src/config.gnuplot %s %0.16f %0.16f",argv[1],frq,1/mf.interval_cha1))
        {
            fprintf(stderr,"data path too long!\n\n");
            return 1;
        }
    }
    else if(mf.cha2)
    {
        frq=mf.lines_cha2/(1/mf.interval_cha2);
        if(sizeof(gnuplot_call) < snprintf(gnuplot_call,sizeof(gnuplot_call),"gnuplot -c "
                "./src/config.gnuplot %s %0.16f %0.16f",argv[1],frq,1/mf.interval_cha2))
        {
            fprintf(stderr,"data path too long!\n\n");
            return 1;
        }
    }
/*    if(sizeof(gnuplot_call) < snprintf(gnuplot_call,sizeof(gnuplot_call),"gnuplot -c "
                "./src/config.gnuplot %s %0.16f %0.16f",argv[1],frq,1/mf.interval_cha1))
    {
        fprintf(stderr,"data path too long!\n\n");
        return 1;
    }
*/    
    #ifdef DEBUG
        printf("status channel 1:\t%s",mf.cha1?"active\n":"inactive\n");
        printf("status channel 2:\t%s",mf.cha2?"active\n":"inactive\n");
        printf( "lines CHA1: %d\n"
                "lines CHA2: %d\n",mf.lines_cha1,mf.lines_cha2);
        printf("frequenzy:\t%0.8f\n",frq);

        printf("\ngnuplot program-call:\n%s\n\n",gnuplot_call); 
    #endif

    system(gnuplot_call);

    return 0;
}
