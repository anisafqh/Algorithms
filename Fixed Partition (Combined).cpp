// This program reads data from a file into an array.
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<bits/stdc++.h>
using namespace std;

// Function Prototypes
void readData_1(int[], int[], int[], int[], int&); //read Joblist.txt
void readData_2(int[], int&); //read MemoryList.txt
void firstFit(int[], int[], int[], int&, int&, int[]); //Job allocation using 10 blocks
void firstFit_2(int[],int[],int[],int&,int[]); //Determine number of blocks of job allocation
void bestFit (int[], int[], int[], int&, int&, int[]); 
void bestFit_2(int[], int[], int[], int&, int[]);
void menu();

int main()
{
	// Define variables
	int size=40;
	int SIZE=10;
	int jobNum[size]; 
	int	arvTime[size];
	int	proTime[size];
	int	jobSize[size];
	int memorySize[SIZE];
	int memoryBlock[SIZE];
	int intfrag[size];
	int choice, fchoice, pick;		// To hold a menu choice

	// readData_1
	readData_1(jobNum, arvTime, proTime, jobSize, size);
	
	// readData_2
	readData_2(memorySize, SIZE);
	
	// Constants for the menu choices
	const int first_CHOICE = 1 ,
			  sec_CHOICE = 2 ,
			  QUIT_CHOICE = 3;
			  
	cout << fixed << showpoint << setprecision(1); 		// set to 1 decimal place
	
	do{
		// display menu
		menu();
		
		cout << "\n\n\t\tEnter Option: ";
		
		cin >> choice;  		// user enter their choice
		cout << endl << endl;
		
		switch(choice)
		{
			case 1: {
				cout << endl << endl;
				cout << " [1] |\tAll memory blocks (10 blocks)\n"; 
				cout << " [2] |\tMemory blocks entered\n";
				cout << " [3] |\tQuit\n";
				cout << " \n\n Select Option: ";
				cin >> fchoice;
				
				// validate the menu selection
				while (fchoice < first_CHOICE || fchoice > QUIT_CHOICE)
				{
					cout << " Please enter a valid menu choice: ";
					cin >> fchoice;
				}
				
				// if the user does not want to quit, proceed
				if (fchoice != QUIT_CHOICE)
				{
					// if user choose 1
					if (fchoice == 1)	
					{
						// first-fit algorithm
						firstFit(memorySize, jobNum, jobSize, SIZE, size, intfrag);
					}
					
					// if user choose 2
					else if( fchoice == 2)
					{
						firstFit_2(memorySize,jobNum, jobSize, size, intfrag);
					}
				}
				break;
			}
			
			case 2:{
				cout << endl << endl;
				cout << " [1] |\tAll memory blocks (10 blocks)\n"; 
				cout << " [2] |\tMemory blocks entered\n";
				cout << " [3] |\tQuit\n";
				cout << " \n\n Select Option: ";
				cin >> fchoice;
				
				// validate the menu selection
				while (fchoice < first_CHOICE || fchoice > QUIT_CHOICE)
				{
					cout << " Please enter a valid menu choice: ";
					cin >> fchoice;
				}
				
				// if the user does not want to quit, proceed
				if (fchoice != QUIT_CHOICE)
				{
					// if user choose 1
					if (fchoice == 1)	
					{
						// first-fit algorithm
						bestFit(memorySize, jobNum, jobSize, SIZE, size, intfrag);
					}
					
					// if user choose 2
					else if( fchoice == 2)
					{
						bestFit_2(memorySize,jobNum, jobSize, size, intfrag);
					}
				}
				break;
			}
			
		}
		
	}while (choice != QUIT_CHOICE);
	
	
	return 0;
}

// Function readData_1 to read data from joblist.txt
void readData_1(int JOBNUM[], int ARVTIME[], int PROTIME[], int JOBSIZE[], int &size){
	
	// Open file
	ifstream jobFile;
	jobFile.open("Joblist.txt");
	
	int totalJobs;
	
	// Read textfile
	jobFile>>totalJobs;
	for(int i=0; i<size; i++){
		jobFile>>JOBNUM[i]>>ARVTIME[i]>>PROTIME[i]>>JOBSIZE[i];
	}
	
	// Display 
	cout << " Joblist.txt file has been read " << endl;
	
	// Close file
	jobFile.close();
	
	// Display Data
	/*cout << totalJobs << endl;
	for(int i=0; i<size; i++){
		cout << JOBNUM[i] << " " << ARVTIME[i] << " " << PROTIME[i] << " " << JOBSIZE[i] << " " << endl;
		
	}*/
}

// Function readData_2 to read data from memoryList.txt
void readData_2(int MEMORYSIZE[], int &SIZE){
	
	// Open file
	ifstream memoryFile;
	memoryFile.open("MemoryList.txt");
	
	int totalBlocks;
	
	// Read textfile
	memoryFile>>totalBlocks;
	for(int j=0; j<SIZE; j++){
		memoryFile>>MEMORYSIZE[j];
	}
	
	// Display 
	cout << " MemoryList.txt file has been read " << endl;
	
	// Close file
	memoryFile.close();
	
	// Display Data
	/*cout << totalBlocks << endl;
	for(int j=0; j<SIZE; j++){
		cout << MEMORYSIZE[j] << endl;
	}*/
}

// Function to display menu
void menu(){
	
	cout << "\n\t\t____________________________________________________________\t\t\n";
	cout << "\t\t************************************************************\n";
	cout << "\t\t************************************************************";
	cout << endl;
	cout << "\t\tEvent-Driven Simulation: Fixed Partition\t\t\t" << endl;
	cout << "\t\t\t1|First-Fit algorithm" << endl;
	cout << "\t\t\t2|Best-Fit algorithm" << endl;
	cout << "\t\t____________________________________________________________\t\t\n";
	cout << "\t\t************************************************************\n";
	cout << "\t\t************************************************************";
	
}

// Function to allocate memory to blocks as per First fit alogorithm	
void firstFit(int MEMORYSIZE[],int JOBNUM[],int JOBSIZE[],int &SIZE,int &size,int INTFRAG[]){
	
	system("CLS");
	
	int allocation[size]; 	
	int frag;
	int sum,
		avrFrag;
	int memorySize[size];
	
	
		for(int x=0; x<size; x++)
		{
			allocation[x]=-1;
			memorySize[x]=MEMORYSIZE[x];
		}
		
		SIZE=10;
		
	    // pick job and find suitable memory block according to its size and assign to it 
	    for (int i=0; i<size; i++) 
	    { 
	        for (int j=0; j<10; j++) 
	        { 
	            if (memorySize[j] >= JOBSIZE[i]) 
	            { 
	                // allocate job j to p[i] memory 
	                allocation[i] = j; 
	                
	                //internal fragmentation
	                frag = JOBSIZE[i] - memorySize[j];
	                if(frag < 0)
	                {
	                	frag*=-1;
	                    INTFRAG[i]=frag;
	                    sum+=INTFRAG[i];
					}
	                // Reduce available memory in this memory 
	                memorySize[j] -= memorySize[j];
	                break; 
	            }
				 avrFrag = sum/40; 
	        } 
	    } 
	  
	    cout << "\nJob No\t\tJob Size\tMemory Block\tStatus\t\tFragmentation\n"; 
	    for (int i = 0; i<size; i++) 
	    { 
	        cout << " " << i+1 << "\t\t" << JOBSIZE[i] << "\t\t"; 
	        if (allocation[i] != -1){
	        	
	        	cout << allocation[i] + 1 << "\t\tAllocated\t" << INTFRAG[i] << "\t\t";
	        	system("pause");
			} 
	    
	        else{
		        cout << "\t\tWait..."; 
		        cout << endl; 
			}
	            
	    }

}

// Function to allocate memory to blocks as per First fit alogorithm	
void firstFit_2(int MEMORYSIZE[],int JOBNUM[],int JOBSIZE[],int &size,int INTFRAG[]){
	
	system("CLS");
	
	int SIZE;
	int allocation[size]; 	
	int frag;
	int sum,
		avrFrag;
	int memorySize[size];
	
		for(int x=0; x<size; x++)
		{
			allocation[x]=-1;
			memorySize[x]=MEMORYSIZE[x];
		}
		
		cout << "Enter number of blocks : " ;
		cin >> SIZE; 
		
	    // pick job and find suitable memory block according to its size and assign to it 
	    for (int i=0; i<size; i++)  //job
	    { 
	        for (int j=0; j<SIZE; j++) //memory
	        { 
	        	//cout << "Memory=" << MEMORYSIZE[j] << "  Job=" << JOBSIZE[i] << endl;
	            if (memorySize[j] >= JOBSIZE[i]) 
	            { 
	                // allocate job j to p[i] memory 
	                allocation[i] = j; 
	                
	                //internal fragmentation
	                frag = JOBSIZE[i] - memorySize[j];
	                if(frag < 0)
	                {
	                	frag*=-1;
	                    INTFRAG[i]=frag;
	                    sum+=INTFRAG[i];
					}
	                // Reduce available memory in this memory 
	                memorySize[j] -= memorySize[j];
	                break; 
	            }
				 avrFrag = sum/40; 
	        } 
	    } 
	  
	    cout << "\nJob No\t\tJob Size\tMemory Block\tStatus\t\tFragmentation\n"; 
	    for (int i = 0; i<size; i++) 
	    { 
	        cout << " " << i+1 << "\t\t" << JOBSIZE[i] << "\t\t"; 
	        if (allocation[i] != -1){
	        	
	        	cout << allocation[i] + 1 << "\t\tAllocated\t" << INTFRAG[i] << "\t\t";
	        	system("pause");
			} 
	    
	        else{
		        cout << "\t\tWait..."; 
		        cout << endl; 
			}
	            
	    }

}

void bestFit(int MEMORYSIZE[],int JOBNUM[],int JOBSIZE[],int &SIZE,int &size,int INTFRAG[]){
	
	system("CLS");
	
	int flags[size],allocation[size];
	int i,j,smallest,sum=0,avgFrag;
	for(i=0; i < 10; i++)
	{
		flags[i]=0;
		allocation[i]=-1;
	}
		
	//allocation as per best fit
	for(i=0;i < size;i++)
	{
		smallest=-1;
		for(j=0; j < SIZE; j++)
			if(flags[j]==0 && MEMORYSIZE[j] >= JOBSIZE[i])
			{
				smallest=j;
				break;
			}
		for(j=0; j < SIZE; j++)
			if(flags[j]==0 && MEMORYSIZE[j] >= JOBSIZE[i] && MEMORYSIZE[j] < MEMORYSIZE[smallest])
				smallest=j;
		if(smallest!=-1)
		{
			allocation[smallest]=i;
			flags[smallest]=1;
		}
	}
	
	//display allocation details
	cout<<"\n Block\tBlock Size\tJob No.\tJob Size\tFragmentation";
	cout << "\n______________________________________________________________\n";
	for(i=0;i < SIZE;i++)
	{
		INTFRAG[i] = MEMORYSIZE[i] - JOBSIZE[allocation[i]];
		sum = sum + INTFRAG[i];
		
		cout<<"\n  "<<i+1<<"      "<<MEMORYSIZE[i]<<"\t\t";
		if(flags[i]==1)
			cout<<allocation[i]<<"\t"<<JOBSIZE[allocation[i]]<<"\t\t"<<INTFRAG[i];
		else
			cout<<"Wait";		
	}
	avgFrag = sum/40;
	cout << "\n\nAverage Internal Fragmentation = " << avgFrag << endl;
}

void bestFit_2(int MEMORYSIZE[],int JOBNUM[],int JOBSIZE[],int &size,int INTFRAG[]){
	
	system("CLS");
	
	int flags[size],allocation[size];
	int i,j,smallest,sum=0,avgFrag, SIZE;
	
	cout << "Enter number of blocks : " ;
		cin >> SIZE; 
		
	for(i=0; i < 10; i++)
	{
		flags[i]=0;
		allocation[i]=-1;
	}
		
	//allocation as per best fit
	for(i=0;i < size;i++)
	{
		smallest=-1;
		for(j=0; j < SIZE; j++)
			if(flags[j]==0 && MEMORYSIZE[j] >= JOBSIZE[i])
			{
				smallest=j;
				break;
			}
		for(j=0; j < SIZE; j++)
			if(flags[j]==0 && MEMORYSIZE[j] >= JOBSIZE[i] && MEMORYSIZE[j] < MEMORYSIZE[smallest])
				smallest=j;
		if(smallest!=-1)
		{
			allocation[smallest]=i;
			flags[smallest]=1;
		}
	}
	
	//display allocation details
	cout<<"\n Block\tBlock Size\tJob No.\tJob Size\tFragmentation";
	cout << "\n______________________________________________________________\n";
	for(i=0;i < SIZE;i++)
	{
		INTFRAG[i] = MEMORYSIZE[i] - JOBSIZE[allocation[i]];
		sum = sum + INTFRAG[i];
		
		cout<<"\n  "<<i+1<<"      "<<MEMORYSIZE[i]<<"\t\t";
		if(flags[i]==1)
			cout<<allocation[i]<<"\t"<<JOBSIZE[allocation[i]]<<"\t\t"<<INTFRAG[i];
		else
			cout<<"Wait";		
	}
	avgFrag = sum/40;
	cout << "\n\nAverage Internal Fragmentation = " << avgFrag << endl;
}
