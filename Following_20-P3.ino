int trigPin=9;     // change pin
int echoPin=10;   // change pin

int a[9][9];
int marg[10],l=0,m=0,stearing[10];
int sensor[5]={0,0,0,0,0},kp,p,d,kd,error;
int last_error=0;
int facing=1,proxy=0;
int current[2]={-1,-1},endc[2];

int obstacle()
{
  long duration;
  int distance;
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration=pulseIn(echoPin,HIGH);
  distance=duration*0.034/2;

  if (distance<30)
  {
    int i,j,k,p,n;
    u_turn();
    delay(50);
    for(i=0;i<10;i++)
     marg[i]=0;
    j= current[1];
    i= current[0];
    for (k=l;k<(l-m+1);k--)
     {
      if (stearing[k]== 1)
       j=j-2;
      else if(stearing[k]== 2)
       i=i+2;
      else if (stearing[k]== 3)
       j= j+2;
      else if(stearing[k]== 4)
       i=i-2;
     }
    p= i;
    n=j;
    if(stearing[l-m]==1)
    {
      facing= 3;
      j=j-1;
    }
    else if(stearing[l-m]==2)
    {
      facing= 4;
      i=i+1;
    }
    else if(stearing[l-m]==3)
    {
      facing= 1;
      j=j+1;
    }
    else if(stearing[l-m]==4)
    {
      facing= 2;
      i=i-1;
    }
    m=0;
    facing=path(n,p,endc[1],endc[0],facing);
    k= 10*i+j;
    return k;
  }
  return 0;
}

void initialize()
{
 int i,j;
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
  for (i=0;i<10;i++)
   marg[i]=0;
   
}

int path(int sx, int sy, int ex, int ey, int facing)         // the frame is according to IP 
{
  int grid[9][9],c=0;                             // local grid to work upon
  int drxn[5][5],i,j,t;
  int queue[25],front=0,rear=0;
  l=0;
  for (i=0;i<9;i++)
   for(j=0;j<9;j++)
    grid[i][j]= a[i][j];
   grid[proxy%10][proxy/10]=0;                    // Main difference in Phase 2 nd Phase 3.
  //printf("till grid done.\n");
  for (i=0;i<5;i++)
  {for (j=0;j<5;j++)
   drxn[i][j]=0;
  }
  queue[rear]=10*sx+sy;
  while(c!=1)
  {
    t= queue[front];
    front= (front+1)%25; 
    i= t/10;
    j= t%10;
    
    if (j>=2 && grid[j-1][i]==1)           // North block
    {
      rear=(rear+1)%25;                 //queue.append(10*i+j-2)
      queue[rear]= 10*i+j-2;
      grid[j-1][i]=0; 
      drxn[j/2-1][i/2]=1;
      if ((j-2)==ey && ex==i)
     c=1;
    }
  if(j<7 && grid[j+1][i]==1)         // South block
  {
    rear=(rear+1)%25;            // queue.append(10*i+j+2)
    queue[rear]= 10*i+j+2;
    grid[j+1][i]=0; 
    drxn[j/2+1][i/2]=3;
    if ((j+2)==ey && ex==i)
     c=1;
  }
  if(i>=2 && grid[j][i-1]==1)        // West block
  {
    rear=(rear+1)%25;             // queue.append(10*(i-2)+j)
    queue[rear]= 10*(i-2)+j;
    grid[j][i-1]=0;
    drxn[j/2][i/2-1]=4;
    if (j==ey && ex==(i-2))
     c=1;
  }
  if(i<7 && grid[j][i+1]==1)       // East block
  {
    rear=(rear+1)%25;           // queue.append(10*(i+2)+j)
    queue[rear]= 10*(i+2)+j;
    grid[j][i+1]=0; 
    drxn[j/2][i/2+1]=2;
    if (j==ey && ex==(i+2))
     c=1;
  }
  }
  //printf("Loop 1 is over\n");
  /*for(i=0;i<5;i++)
   {
    for(j=0;j<5;j++)
     printf("%d\t",drxn[i][j]);
    printf("\n");
   }*/
  i=ex/2;
  j=ey/2;
  
  int v,b=0;
  for (v=0;v<10;v++){
   stearing[v]=0;
   marg[v]=0;}
  while(b!=1)
  {
    v= drxn[j][i];
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
  //for (i=0;i<=l;i++)
   //printf("%d",marg[i]);
  return stearing[0];
}

void forward()
{
   digitalWrite(6,1);
   digitalWrite(8,0);
   digitalWrite(10,1);
   digitalWrite(12,0);
  analogWrite(9,120); //120
  
  analogWrite(11,120);
}

void right()
{
   digitalWrite(6,1);
   digitalWrite(8,0);
   digitalWrite(10,0);
   digitalWrite(12,0);
  analogWrite(9,100); //120
  
  analogWrite(11,0);
}

void left()
{
   digitalWrite(6,0);
   digitalWrite(8,0);
   digitalWrite(10,1);
   digitalWrite(12,0);
  analogWrite(9,0); //120
  
  analogWrite(11,100);
}

void u_turn()
{
   digitalWrite(6,1);
   digitalWrite(8,0);
   digitalWrite(10,0);
   digitalWrite(12,1);
  analogWrite(9,100); //120
  
  analogWrite(11,100);
}

void setup() {
 pinMode(trigPin,OUTPUT);
 pinMode(echoPin,INPUT);
 pinMode(6,OUTPUT);
 pinMode(8,OUTPUT);
 pinMode(9,OUTPUT);
 pinMode(10,OUTPUT);
 pinMode(11,OUTPUT);
 pinMode(12,OUTPUT);
 pinMode(2,INPUT);
 pinMode(3,INPUT);
 pinMode(4,INPUT);
 pinMode(5,INPUT);
 pinMode(7,INPUT);
 Serial.begin(9600);
 initialize();
}


void loop() {
  
 sensor[0]=digitalRead(2);
 sensor[1]=digitalRead(3);
 sensor[2]=digitalRead(4);
 sensor[3]=digitalRead(5);
 sensor[4]=digitalRead(7);

 if(sensor[0]==1&&sensor[1]==1&&sensor[2]==0&&sensor[3]==1&&sensor[4]==1)
   error=0;

 else if(sensor[0]==1&&sensor[1]==1&&sensor[2]==1&&sensor[3]==1&&sensor[4]==0)
    error=4;
 
 else if(sensor[0]==1&&sensor[1]==1&&sensor[2]==1&&sensor[3]==0&&sensor[4]==0)
    error=3;
 
 else if(sensor[0]==1&&sensor[1]==1&&sensor[2]==1&&sensor[3]==0&&sensor[4]==1)
    error=2;
 
 else if(sensor[0]==1&&sensor[1]==1&&sensor[2]==0&&sensor[3]==0&&sensor[4]==1)
    error=1;
 
 else if(sensor[0]==1&&sensor[1]==0&&sensor[2]==0&&sensor[3]==1&&sensor[4]==1)
    error=-1;
 
 else if(sensor[0]==1&&sensor[1]==0&&sensor[2]==1&&sensor[3]==1&&sensor[4]==1)
    error=-2;
 
 else if(sensor[0]==0&&sensor[1]==0&&sensor[2]==1&&sensor[3]==1&&sensor[4]==1)
    error=-3;
 
 else if(sensor[0]==0&&sensor[1]==1&&sensor[2]==1&&sensor[3]==1&&sensor[4]==1)
    error=-4;

     kp=20; //18,22
    kd=35; //5,7,25,28,32,<40
  
  p=kp*error;
  d=kd*(error-last_error);
  last_error=error;
  if(!(sensor[0]==0&&sensor[1]==0&&sensor[2]==0&&sensor[3]==1&&sensor[4]==1)&&!(sensor[0]==1&&sensor[1]==1&&sensor[2]==0&&sensor[3]==0&&sensor[4]==0))
 { 
   proxy= obstacle();
   if(proxy==0){
   digitalWrite(6,1);
   digitalWrite(8,0);
   digitalWrite(10,1);
   digitalWrite(12,0);
  analogWrite(9,100-p-d); //120
  
  analogWrite(11,100+p+d);}
 }
  
 if(sensor[0]==1&&sensor[1]==1&&sensor[2]==1&&sensor[3]==1&&sensor[4]==1)
  {digitalWrite(6,1);
   digitalWrite(8,0);
   digitalWrite(10,1);
   digitalWrite(12,0);
   analogWrite(9,100-(20*last_error));
   
   analogWrite(11,100+(20*last_error));
  // delay(2);
  }

   else if(sensor[0]==0&&sensor[1]==0&&sensor[2]==0&&sensor[3]==0&&sensor[4]==0)
    {
      if(marg[m]==0)
       {if (m>l && l>0)
         {delay(1000);
          m=0;
          current[1]= endc[1];
          current[0]= endc[0];
         }
      int value,i,j;
      Serial.println("\nEnter end coordinates....");
      while(! Serial.available())
      {
        
      }
      value=Serial.readStringUntil("\n").toInt();
      i= value/10;
      j= value%10;
      endc[0]= 8-(2*j);
      endc[1]= 2*i;
      facing=path(current[1],current[0],endc[1],endc[0],facing);
      
         //printf("\nFacing:-%d",facing);
       }
      else
        {
          if(marg[m]==1)
          {
           forward();
           delay(50);
          }
          else if(marg[m]==2)
           {
            right();
            delay(50);
            forward();
            delay(50);
           }
          else if(marg[m]==3)
           {
            u_turn();
            delay(50);
            forward();
            delay(50);
           }
          else if(marg[m]==4)
          {
            left();
            delay(50);
            forward();
            delay(50);
          }
          m+=1;
       }
    }
}
