#include <stdio.h>
#include <string.h>
/* Exercise 2.5: Selection sort */
/* Parameters:
 * start: start of an array
 * size: length of an array
 */

void sort(int *start, int size)
{
  int i;
  int temp = 0;

  while(size > 0)
  {
    for(i = 1; i < size + 1; i++)
    {
      if(*start > *(start + i))
      {
	temp = *start;
	*start = *(start + i);
	*(start+i) = temp;
      }
    }
         
    start++;
    size--;
  }
}

int main()
{
    /* Testing 2.5 Selection Sort. Implement a function to print
     * the resulting array to see that it really works */ 
    int arr[] = {3, 4, 7, 2, 8};
    int i;
    
    sort(arr, 5);
    
    for(i = 0; i < 5; i++)
    {
      printf("%d ", arr[i]);
    }
    
    printf("\n");
 
    
    return 0;
}