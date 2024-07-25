#include <stdio.h>
int main(){
	printf("lutfen matrisin boyutunu girin\n");
	scanf("%d",&N);
	
	int A[N][N];
	
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			scanf("%d",&A[i][j]);
		}
	}
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			A[i][j]=0;
			A[j][i]=0;
		}
		k=0;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(A[i][j]!=0){
				B[k]=A[i][j];
					k++;
					}
				}
			}
			for(i=0;i<N;i++){
				for(j=0;j<N;j++){
					
				}
			}
	}
	
		}
	}
}
