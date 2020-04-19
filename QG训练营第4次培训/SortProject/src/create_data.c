# include <stdio.h>
# include <stdlib.h>
# include <time.h>


int main()
{
	freopen("data.txt","w",stdout);
	int n;
	scanf("%d",&n);
    srand((unsigned int)time(NULL));
    long i;
    for (i = 0; i < n; i++){
        printf("%d\n", rand());
    }
    
  return 0;
  
}


