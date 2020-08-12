#include<stdio.h>
#include<math.h>
#include<conio.h>
#include<stdlib.h>
int a[9][9];
int marg[20];

void initialize()
{int i,j;
 for (i=0;i<9;i++)
	{
	  for(j=0;j<9;j++)
	  {
	  	if (i%2==0)
	  	{
	  	  a[i][j]=1;
		  }
		else
		 if (j%2==0)
		  a[i][j]=1;
		else
		 a[i][j]=0;
	  }
	}
  for (i=0;i<20;i++)
   marg[i]=0;
}

int path(int sx, int sy, int ex, int ey, int facing)         // the frame is according to IP 
{
  int grid[9][9],c=0;                             // local grid to work upon
  int direction[5][5],i,j,t;
  int queue[50],front=0,rear=0;
  for (i=0;i<9;i++)
   for(j=0;j<9;j++)
    grid[i][j]= a[i][j];
  //printf("till grid done.\n");
  for (i=0;i<5;i++)
  {for (j=0;j<5;j++)
   direction[i][j]=0;
  }
  queue[rear]=10*sx+sy;
  while(c!=1)
  {
  	t= queue[front];
  	front= (front+1)%50; 
  	i= t/10;
  	j= t%10;
  	
  	if (j>=2 && grid[j-1][i]==1)           // North block
  	{
  		rear=(rear+1)%50;                 //queue.append(10*i+j-2)
  		queue[rear]= 10*i+j-2;
  		grid[j-1][i]=0; 
  		direction[j/2-1][i/2]=1;
  		if ((j-2)==ey && ex==i)
		 c=1;
	  }
	if(j<7 && grid[j+1][i]==1)         // South block
	{
		rear=(rear+1)%50;            // queue.append(10*i+j+2)
		queue[rear]= 10*i+j+2;
		grid[j+1][i]=0; 
		direction[j/2+1][i/2]=3;
		if ((j+2)==ey && ex==i)
		 c=1;
	}
	if(i>=2 && grid[j][i-1]==1)        // West block
	{
		rear=(rear+1)%50;             // queue.append(10*(i-2)+j)
		queue[rear]= 10*(i-2)+j;
		grid[j][i-1]=0;
		direction[j/2][i/2-1]=4;
		if (j==ey && ex==(i-2))
		 c=1;
	}
	if(i<7 && grid[j][i+1]==1)       // East block
	{
		rear=(rear+1)%50;           // queue.append(10*(i+2)+j)
		queue[rear]= 10*(i+2)+j;
		grid[j][i+1]=0; 
		direction[j/2][i/2+1]=2;
		if (j==ey && ex==(i+2))
		 c=1;
	}
  }
  //printf("Loop 1 is over\n");
  /*for(i=0;i<5;i++)
   {
   	for(j=0;j<5;j++)
   	 printf("%d\t",direction[i][j]);
   	printf("\n");
   }*/
  i=ex/2;
  j=ey/2;
  int stearing[20];                            // declare stearing as queue.
  int v,l=0,b=0;
  for (v=0;v<20;v++)
   stearing[v]=0;
  while(b!=1)
  {
  	v= direction[j][i];
	if (v==1)
	{
		j=j+1;
		stearing[l]=1;                     // stearing.append(1)
	 } 
	else if(v==2)
	{
		i=i-1;
		stearing[l]=2;                   //stearing.append(2)
	}
	else if(v==3)
	{
		j=j-1;
		stearing[l]=3;                 // stearing.append(3)
	}
	else if(v==4)
	{
		i=i+1;
		stearing[l]=4;               // stearing.append(4)
	}
	if ((2*j)==sy && (2*i)==sx)
	 b=1;
	l+=1;
  }
  //printf("Loop 2 is done");
  l=l-1;
  if(facing==1)
   marg[0]= stearing[l];
  else if(facing==stearing[l])
   	marg[0]=1;
  else if(facing==2)
    {
      if(stearing[l]==4)
       marg[0]=3;
      else
       marg[0]= 5-stearing[l];
	}
  else if(facing==3)
   {
   	if (stearing[l]==1)
   	 marg[0]=3;
   	else
   	 marg[0]= 8/stearing[l];
   }
  else if(facing==4)
   {
   	if(stearing[l]==2)
   	 marg[0]=3;
   	else
   	 marg[0]=1+ stearing[l];
   }
  
  for (i=l-1;i>=0;i--)
  {
  	if (stearing[i+1]==1)           // North block traversed previously
  	 marg[l-i]= stearing[i];
  	else if(stearing[i+1]==stearing[i])
  	 marg[l-i]=1;
  	 
  	else if( stearing[i+1]==3)           // South block traversed previously
  	{
  		marg[l-i]= 8/stearing[i];
	}
	else if( stearing[i+1]==2)          // East block traversed previously
	{
	   marg[l-i]= 5- stearing[i];	
	}
	else if(stearing[i+1]==4)          // West block traversed previously
	{
		marg[l-i]= stearing[i]+1;
	}
  }
  //printf("\nDONE\n");
  for (i=0;i<=l;i++)
   printf("%d",marg[i]);
  return stearing[0];
}

main()
{
	int i,j,k;
	int facing=1;
	int current[2]={-1,-1},endc[2];
	
	initialize();
	for(k=0;k<3;k++)
  {
	if (current[0]<0 && current[1]<0)
	{
	  printf("Enter the starting coordinate...");
	  scanf("%d %d",&i,&j);
	  current[1]=2*i;
	  current[0]= 8-(2*j);
    }
	printf("\nEnter end coordinates....");
	scanf("%d %d",&i,&j);
	endc[0]= 8-(2*j);
	endc[1]= 2*i;
	
	facing=path(current[1],current[0],endc[1],endc[0],facing);
	current[1]= endc[1];
	current[0]= endc[0];
	printf("\nFacing:-%d",facing);
  }
}
