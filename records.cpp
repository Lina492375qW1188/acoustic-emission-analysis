/* --------------------------------------------------------------------------------------------------------------
Author: Sun-Ting Tsai
This program was originally developed by the previous graduate assistant Hsiu-Wei Yang at Sep 2013 – Jun 2014. 
The program was then stabilized by the author in 2015 and used to measure the acoustic emission of crumpled 
paper, acoustic emission from breaking bamboo chopstics and spagetti, acoustic emission from twisting paper roll.
-------------------------------------------------------------------------------------------------------------- */

# include<stdio.h>
# include<stdlib.h>
# include<math.h>
# define Length 30000000  // User-defined length which determines the memories which will be used in the future.
# define Duration 200     // The time used to difine two seperate sounds: Experimentally our recorder cannot 
                          // distinguish two sounds within 0.00453 sec.
# define Clicks 10000     // The number of total sound pulses. Users can specify their own number. It's safer to
                          // set the number much greater than the acutual number of sound pulses.

void ReadData(const char*);
void threshold();
void SubtractNoise(double* );
void Output(const char*);
void IntensityCount(double *, double *);

double Background=0.005;  // This background threshold was set in order to remove the noise from the environment. 
                          // For other experimental setup, this number might be different.
double Threshold;
int peaknum=7;
int times=6;

double *Input;  // The amplitude read out from the MATLAB-generated text file.
double *Data;   // Input*Input, which is the square of the amplitude.
double *Click;  // This will be used to record the magnitude of sound pulses.

double SoundPosition[10000][3];

int main(int argc, char* argv[])
{
    int i;
    double sum=0;
    
    // borrow memory from CPU with memory equals "8 bits(double)*Legth", and let Data points to the memory site.
    Data=(double*)malloc(sizeof(double)*Length);   
    Input=(double*)malloc(sizeof(double)*Length);
    Click=(double*)malloc(sizeof(double)*Length); 
    
    ReadData(argv[1]);
    
    Threshold=0.000009*Duration;  // This means that we expect the amplitude of noise is 0.003.

    IntensityCount(Data, Click);  // Calculate and count the intensity of sound.
  
    Output(argv[2]);
    
    // Release the memory space borrowed from CPU.
    free(Data);
    free(Input);
    free(Click);

}

void ReadData(const char* filename_in)
{
    FILE *fp;
     
    char ch, string[20]; // The ch is used to store each number. Up to 20 number can be stored in the string.
    int  i=0, k=0;       // Variables for the while loop: i checks number ch, k checks string.
     
    int d;
    for(d=0;d<Length;d++) Data[i]=0;
     
    fp=fopen(filename_in, "r");

    if(fp==NULL) printf("File doesn't exist.'.\n");
    else printf("File is open. \n\n");
     
    while((ch=fgetc(fp)) != EOF)
    {
        if(ch==' ')
        {
            Input[k]=atof(string);  
            i=0; // reset i for the next string to overwrite the original string.
            k=k+1;
        }
        // The char of "\n" is "0x0a". By doing this, it could read "line feed" as a char.
        else if(ch==0x0a)
        { 
            ;   // Do nothing.  
        }
        string[i]=ch;
        i=i+1;
    }

     fclose(fp);

     for(i=0;i<Length;i++) Data[i]=Input[i]*Input[i];

}

void IntensityCount( double Data[], double Click[] )
{
    double sum=0;
    double interval=0;
    
    double forward=0;
    double behind=0;

    int index=0;    
    int lastnum=0;

    int i=0,j=0,k=0,l=0,m=0;
    int start=0,over=0;               // start=statrpoint of the sound pulse, over=end point of the sound pulse.

    for(i=0;i<Clicks;i++) Click[i]=0; // Let Click[i] all values=0.

    for(i=0;i<2000;i++)           // Let SoundPosition[i][j] all values=0.
    {             
        SoundPosition[i][0]=0;
        SoundPosition[i][1]=0;
        SoundPosition[i][2]=0;
    }

    for(i=0;i<Length;i++)
    {
        if(index<Duration)  // accumulate untill duration
        {
            interval=interval+Data[i];
            sum=sum+Data[i];

            if(index==0) start=i;

            index=index+1; 
        }
        else
        {
            interval=interval+Data[i]-Data[i-Duration];
            sum=sum+Data[i];
            if(interval<=Threshold)
            {
                Click[k]=sum;
                if(sum>=Threshold)
                {
                    k=k+1;
                    over=i;

                    SoundPosition[m][0]=Click[k];
                    SoundPosition[m][1]=start;
                    SoundPosition[m][2]=over;

                    m=m+1;
                }

                index=0;
                interval=0;
                sum=0;
                lastnum=i;

            }
            else
            {
                forward=0;
                behind=0;

                if(Data[i]>Data[i-1] && Data[i]> Data[i+1])   // If it's peak, start recording.
                {
                    forward=Data[i];

                    j=1;
                    l=1;
                    while(j<peaknum)                         // This while loop will run 6 times.
                    {
                        if(i+l+1>Length) break;
                        // If the amplitude of i+l is another peak. Since i=1 is definitely not, there are 
                        // actually five peaks.
                        if(Data[i+l]>Data[i+l-1] && Data[i+l]> Data[i+l+1])  
                        {
                            forward=forward+Data[i+l];
                            j=j+1;
                        }

                        l=l+1;
                    }


                    j=0;
						        l=1;
                    while(j<peaknum)  // Find out the last 5 peaks.
                    {
                        if(i-l-1<lastnum) break;
                        if(Data[(i-l)]>Data[((i-l)-1)] && Data[(i-l)]> Data[((i-l)+1)])
                        {
                            behind=behind+Data[i-l];
                            j=j+1;
                        }

                        l=l+1;

                    }

                    if( forward >= times*behind && behind!=0)    // If forward > behind
                    {
                        Click[k]=sum;
                        k=k+1;
                        over=i;

                        SoundPosition[m][0]=Click[k];
                        SoundPosition[m][1]=start;
                        SoundPosition[m][2]=over;

                        m=m+1;

                        index=0;
                        interval=0;
                        sum=0;

                        lastnum=i;
                    }
                }
            }
        }
    }
}

void Output(const char* filename_out)
{
    FILE *pt;
    int i,j,k;

    pt= fopen(filename_out, "a");
/*
// PART A   Calculate Sound.

    for(j=0;j<Clicks;j++)
    {
        if(Click[j]==0) break;
        fprintf(pt,"%f\n", Click[j]);
    }
        
       fclose(pt);
*/
//PART B    Calculate Time Sequence.

    for(j=0;j< Clicks ;j++)
    {
       	if(Click[j]==0) break;
        fprintf(pt,"%f   %f   %f\n", Click[j], SoundPosition[j][1]/44100, SoundPosition[j][2]/44100);
		}       

    fclose(pt);

}
