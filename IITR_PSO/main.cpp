//
//  main.cpp
//  IITR_PSO
//
//  Created by rishabh on 23/06/16.
//  Copyright © 2016 rishabh. All rights reserved.
//

#include <iostream>
#include<math.h>
using namespace std;

int main() {
// insert code here...
    unsigned int address[20],
            signalquality[20][20],
            energy[20],
            path[30][20],
            gbestParticle=0;
    
    float x[30][20],
        v[30][20],
        pbest[30],
    pbestPath[30][20],
    gbestPath[20],
        gbest = 9999,
    energyConsumedInPath[30],
    meanEnergy = 0;
    
    int debugCount =0 ;
    
    srand (time(NULL));

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//                                     INITIALISATION
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    

    
//assigning random addresses to address[]
    for(int i=0;i<20;i++)
    {
        int temp = rand()%255;
        bool flag = true;
        for(int j=0;j<i;j++)
            if(address[j] == temp)
                flag = false;
        if(flag == true)
            address[i] = temp;
    }
    

//assigning random values to signalquality[]

    for(int i=0;i<20;i++)
        for(int j=0;j<=i;j++)
        {
            signalquality[i][j] = rand()%35 + 20;
            signalquality[j][i] = signalquality[i][j];
        }
    for(int i=0;i<20;i++)
        signalquality[i][i] = 999;
//assigning random values energy levels of nodes and paths

    for(int i=0;i<20;i++)
    {energy[i] = rand()%5 + 5;
        meanEnergy += energy[i];}
    meanEnergy/=20;
    for(int i=0;i<20;i++)
        for(int j=0;j<20;j++)
            path[i][j] = 0;
ABC:
    for(int shiftingPt = 0;shiftingPt<20-1;shiftingPt++)
    {
    //assigning random values to x[] and v[]
    for(int i=0;i<30;i++)
        for(int j=0;j<20;j++)
        {
            x[i][j] =  rand()%100 ;
            x[i][j] /= 100;
            v[i][j] =  rand()%100;
            v[i][j] /= 100;
            
        }
        
        //initializing variables
        for(int i=0;i<20;i++)
            address[i] = 0;
        for(int i=0;i<30;i++)
        {
            pbest[i] = 9999;
            gbestPath[i] =0;
            for(int j=0;j<20;j++)
            {
                pbestPath[i][j] =0;
                //v[i][j]=0;
            }
        }
        gbest=9999;
    
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//                                    IMPLEMENTATION
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

//starting point taken :- 1
    
        int origin = shiftingPt,
        destination = 19;

for(int iterationCount = 0;iterationCount<20;iterationCount++)
{
    for(int i=0;i<30;i++)
    {

//storing array x[][20] in priority[] as the contents will change during path creation
        float prioity[20];
        for(int j=0;j<20;j++)
            prioity[j] = x[i][j];

//|||||||||||||||||||||||||||||||||||||BUILDING PATH||||||||||||||||||||||||||||||||||||||||||
//-- choosing max priority particle for path creation
        int k=0;
        for(int j=0;j<20;j++)
            path[i][j] = 0;
        path[i][0] = origin;
        prioity[origin] = 1;
        bool validpath = false;
        for(int q=0;q<20;q++)
        {
            float min = 1;//prioity[origin+1];
            int newparticle = 99;//origin+1;
            for(int j=0;j<20;j++)
                if(min>prioity[j])// && energy[j]>= 9)//meanEnergy - 1)
                {
                    min = prioity[j];
                    newparticle = j;
                }
            prioity[newparticle] = 0.9990;
            path[i][++k] = newparticle;
            if(newparticle == destination)
            {
                validpath = true;
                break;
            }
        }
        if(validpath == true && k<=5)
        {
            
            
//|||||||||||||||||||||||||||||||||||||FITNESS EVALAUATION||||||||||||||||||||||||||||||||||||||||||
            
            
            int j = 0, fitnessvalue = 0;
            bool penalty = false;
            //energyConsumedInPath[i] = path[i][j];
            if(path[i][0
                       ] != destination)
                while(path[i][j] != destination)
                {
                    fitnessvalue += signalquality[path[i][j]][path[i][j+1]];
                    energyConsumedInPath[i] += energy[path[i][j+1]];
                    //if(energy[path[i][j+1]]<meanEnergy)
                     //   penalty = true;
                    j++;
                    //if(i == 0)
                    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
                        //cout<<path[i][j]<<" ";-----displaying path convergence|||||||||||||||||||
                    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
                }
            //if(i==0)
            //cout<<endl;
            fitnessvalue = fitnessvalue / j; //- j / 2;
           // if(penalty==true)
             //   fitnessvalue = 999;
            //energyConsumedInPath[i] /= j;
            
            
//|||||||||||||||||||||||||||||||||||||UPDATING PBEST||||||||||||||||||||||||||||||||||||||||||

            if(pbest[i] > fitnessvalue)// && energyConsumedInPath[i] >= 6)
            {
                pbest[i] = fitnessvalue;
                    //cout<<"debug:pbest changed"<<++debugCount;
                /*int w = 0;
                 while(path[i][w-1] != 19 || w==0)
                {
                    pbestPath[i][w] = path[i][w];
                    w++;
                }*/
                for(int w=0;w<20;w++)
                    pbestPath[i][w] = x[i][w];
            }
        }
       // else
         //   pbest[i] = 0;
        
//|||||||||||||||||||||||||||||||||||||UPDATING GBEST||||||||||||||||||||||||||||||||||||||||||
        if(pbest[i]<gbest)
        {
            gbest = pbest[i];
            gbestParticle = i;
        }
        if(i == 30 -1)
        {
            /*int w = 0;
            while(pbestPath[gbestParticle][w-1] != 19 || w==0)
            {
                gbestPath[w] = pbestPath[gbestParticle][w];
                w++;
            }*/
            for(int w=0;w<20;w++)
                gbestPath[w] = pbestPath[gbestParticle][w];
        }
//|||||||||||||||||||||||||||||||||||||UPDATING X AND V||||||||||||||||||||||||||||||||||||||||||

        if(iterationCount>0)
        {
            float weight = 0.4438,
                personalLearningFactor = /*1.3950,//*/0.2699,
                globalLEarningFactor = 3.3950,
                constrictionFactor = personalLearningFactor + globalLEarningFactor;
            float denominator = (fabs(2 - constrictionFactor - sqrt(-constrictionFactor*constrictionFactor + 4* constrictionFactor)));
            constrictionFactor = 2/denominator;
            for(int j=0;j<20;j++)
            {
                float r1 = (rand()%100),r2 = (rand()%100);
                r1/=100;
                r2/=100;
                
                v[i][j] = weight*v[i][j] + r1*personalLearningFactor*(pbestPath[i][j] - x[i][j]) + r2*globalLEarningFactor*(gbestPath[j] - x[i][j]);
                
                v[i][j] *= constrictionFactor;
                /*if(v[i][j]>=0.9990)
                    v[i][j] = 1;
                if(v[i][j]<=-0.9990)
                    v[i][j] = 0;*/
            
                
                x[i][j]+= v[i][j];
                //if(i == 0 && j==0)
                  //  cout<<v[i][j]<<endl;
                
                
                if(x[i][j]<0.0001)
                    x[i][j] = 0;
                if(x[i][j]>0.9990)
                    x[i][j] = 0.9990;
                    //debug purpose
                //if(i == 0 && j==0)
                    //cout<<v[0][0]<<"    "<<i<<"  "<<iterationCount<<" \n";
                //x[i][j]/=iterationCount;
                //v[i][j]/=iterationCount;
            }
        }
    }//END OF i
}//END OF iterationCost
    
  //  if(gbest == 9999)
    //    goto ABC;
////|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//                                      displaying path
////|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

        cout<<shiftingPt<<" ";
        float prioity[20];
        for(int j=0;j<20;j++)
            prioity[j] = gbestPath[j];
        prioity[origin] = 1;
        for(int q=0;q<20;q++)
        {
            float min = 1;//prioity[origin+1];
            int newparticle = 99;//origin+1;
            for(int j=0;j<20;j++)
                if(min>prioity[j])// && energy[j]>= meanEnergy + 1)
                {
                    min = prioity[j];
                    newparticle = j;
                }
            prioity[newparticle] = 0.9990;
            cout << newparticle <<" ";
            if(newparticle == destination)
            {
                break;
            }
            
        }

        
      /*
    cout<<shiftingPt<<" ";
    for(int q=0;q<20;q++)
    {
        float min = 99;//gbestPath[1];
        int newparticle = 99;
        for(int j=0;j<20;j++)
            if(min>gbestPath[j])
            {
                min = gbestPath[j];
                newparticle = j;
            }
        gbestPath[newparticle] = 0.9990;
        cout<<newparticle<<" ";
        if(newparticle == destination)
        {
            break;
        }
    }*/
        cout<<endl;
}//END OF CHOICE OF ORIGIN
    for(int i=0;i<9;i++)
        cout<<"*";
    
    
    
    
    return 0;
}
