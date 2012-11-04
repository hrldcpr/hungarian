//adapted from Dominic Battre's implementation of the Hungarian algorithm by hbc@mit.edu

#include "asp.h"

void asp(int size, cost **Array, long *col_mate, long *row_mate)
{
// IMPORTANT! The values of Array[][] don't exist after calling asp() any more
int i;
/*for (i=0;i<size;++i)
{
  int j;
  for (j=0;j<size;++j)
   Result[i][j]=false;
}*/
long m=size,n=size;
long k;
long l;
long j;
cost s;
//long*col_mate;
//long*row_mate;
long*parent_row;
long*unchosen_row;
long t;
long q;
cost*row_dec;
cost*col_inc;
cost*slack;
long*slack_row;
long unmatched;

for (i=0;i<n;++i) col_mate[i]=0;
for (i=0;i<n;++i) row_mate[i]=0;
parent_row= new long[n];for (i=0;i<n;++i) parent_row[i]=0;
unchosen_row= new long[m]; for (i=0;i<m;++i) unchosen_row[i]=0;
//col_mate= new long[m];
for (i=0;i<m;++i) col_mate[i]=0;
//row_mate= new long[n];
for (i=0;i<n;++i) row_mate[i]=0;
row_dec= new cost[m]; for (i=0;i<m;++i) row_dec[i]=0;
col_inc= new cost[n]; for (i=0;i<n;++i) col_inc[i]=0;
slack= new cost[n];  for (i=0;i<n;++i) slack[i]=0;
slack_row= new long[n]; for (i=0;i<n;++i) slack_row[i]=0;

// Do heuristic
for(l= 0;l<n;l++){
  s= Array[0][l];
  for(k= 1;k<n;k++)
   if(Array[k][l]<s)s= Array[k][l];
  if(s!=0)
   for(k= 0;k<n;k++)
    Array[k][l]-= s;
}

t= 0;
for(l= 0;l<n;l++){
  row_mate[l]= -1;
  parent_row[l]= -1;
  col_inc[l]= 0;
  slack[l]= INF;
}
for(k= 0;k<m;k++){
  s= Array[k][0];
  for(l= 1;l<n;l++)
   if(Array[k][l]<s) s=Array[k][l];
  row_dec[k]= s;
  for(l= 0;l<n;l++)
   if((s==Array[k][l])&&(row_mate[l]<0)){
    col_mate[k]= l;
    row_mate[l]= k;
    goto row_done;
   }
   col_mate[k]= -1;
   unchosen_row[t++]= k;
row_done:;
}

if(t==0)goto done;
unmatched= t;
while(1){
  q= 0;
  while(1){
   while(q<t){
    {
     k= unchosen_row[q];
     s= row_dec[k];
     for(l= 0;l<n;l++)
      if(slack[l]){
       cost del;
       del= Array[k][l]-s+col_inc[l];
       if(del<slack[l]){
        if(del==0){
         if(row_mate[l]<0)goto breakthru;
         slack[l]= 0;
         parent_row[l]= k;
         unchosen_row[t++]= row_mate[l];
        }else{
         slack[l]= del;
         slack_row[l]= k;
        }
       }
      }
    }
    q++;
   }
   
   s= INF;
   for(l= 0;l<n;l++)
    if(slack[l]&&slack[l]<s)
     s= slack[l];
   for(q= 0;q<t;q++)
    row_dec[unchosen_row[q]]+= s;
   for(l= 0;l<n;l++)
    if(slack[l]){
     slack[l]-= s;
     if(slack[l]==0)
     {
      k= slack_row[l];
      if(row_mate[l]<0){
       for(j= l+1;j<n;j++)
        if(slack[j]==0)col_inc[j]+= s;
        goto breakthru;
      }else{
       parent_row[l]= k;
       unchosen_row[t++]= row_mate[l];
      }
     }
    }else col_inc[l]+= s;
  }
breakthru:  
  while(1){
   j= col_mate[k];
   col_mate[k]= l;
   row_mate[l]= k;
   if(j<0)break;
   k= parent_row[j];
   l= j;
  }
  if(--unmatched==0)goto done;
  t= 0;
  for(l= 0;l<n;l++){
   parent_row[l]= -1;
   slack[l]= INF;
  }
  for(k= 0;k<m;k++)
   if(col_mate[k]<0){
    unchosen_row[t++]= k;
   }
}
done: // Just test whether everything went right

/* for(k= 0;k<m;k++)
  for(l= 0;l<n;l++)
   if(Array[k][l]<row_dec[k]-col_inc[l]){
    ASSERT(NULL);
   }
for(k= 0;k<m;k++){
  l= col_mate[k];
  if(l<0||Array[k][l]!=row_dec[k]-col_inc[l]){
   ASSERT(NULL);
  }
}
k= 0;
for(l= 0;l<n;l++)
  if(col_inc[l])k++;
if(k>m){
  ASSERT(NULL);
}
*/
/*for (i=0;i<size;++i)
{
  Result[i][col_mate[i]]=true;
}*/
for (k=0;k<m;++k)
{
  for (l=0;l<n;++l)
  {
   /*TRACE("%d ",Array[k][l]-row_dec[k]+col_inc[l]);*/
   Array[k][l]=Array[k][l]-row_dec[k]+col_inc[l];
  }
  /*TRACE("\n");*/
}
//delete[] col_mate;
//delete[] row_mate;
delete[] parent_row;
delete[] unchosen_row;
delete[] row_dec;
delete[] col_inc;
delete[] slack;
delete[] slack_row;
}
