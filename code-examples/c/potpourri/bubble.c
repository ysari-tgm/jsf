#include <stdlib.h>
#include <stdio.h>

#define SORTMAX 10

int sort[SORTMAX];

void bubble_sort(void);

int main()
{
  int i,j;
  for(j=0,i=SORTMAX; i>0;i--,j++)
    sort[j]=i;
  for(i=0; i<SORTMAX; i++)
    printf("%d.Stelle: %d\n",i,sort[i]);
  bubble_sort();
  for(i=0; i<SORTMAX; i++)
    printf("%d.Stelle: %d\n",i,sort[i]);
  return 0;
}

void bubble_sort(void)
{
  int i,zw,ok;
  
  do
  {
    ok=0;
    for(i=0;i<SORTMAX-1;i++)
    {
      if(sort[i]>sort[i+1])
      {
	zw=sort[i];
	sort[i]=sort[i+1];
	sort[i+1]=zw;
	ok=1;
      }
    }
  } while(ok);
}
