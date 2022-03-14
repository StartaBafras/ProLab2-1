#include <stdio.h>
int main(){
	int i;
    int j;
	int sum = 0;
	int n=10;
	int arr[n][n];
	for (i=0;i<10;i++){
		for (j=0;j<10;j++){
		    arr[i][j]=i*j;
			sum = sum + arr[i][j];
		}
	}
	for (int i=0;i<10;i++)
	{

	}
        printf("%d", sum);	
        return 0;
        
}
 //zaman karmaşıklığı=O(n2)
 //yer karmaşıklığı=(4n2+16 O(n2))