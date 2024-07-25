#include <stdio.h>
#include <conio.h>
int main(){
	int N,i,j,x;//degiskenler tan�mla
	
	printf("lutfen kare matrisin boyutunu giriniz\n");//kare matrisin boyutunu al�r�z
	scanf("%d",&N);
	
	float A[N][N];//matrisleri tan�mlar�z
	float B[N][N],C[N][N];
	
	for(i=0;i<N;i++){//kullan�c�dan matrisleri al�r�z
		for(j=0;j<N;j++){
			printf("A[%d][%d]=",i,j);
			scanf("%f",&A[i][j]);
		}
	}
	printf("kullanicidan aldigimiz matris\n");//kullan�c�dan ald�g�m�z matrisi ekrana yazd�r�r�z
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%f   ",A[i][j]);
		}
		printf("\n");
	}
	for(i=0;i<N;i++){//birim matris olustururuz bu da B matrisimiz olur
		for(j=0;j<N;j++){
			if(i==j)
			B[i][j]=1;
			else
			B[i][j]=0;
		}
	}
	float d,k;
	for(i=0;i<N;i++){
		d=A[i][i];
		for(j=0;j<N;j++){
			A[i][j]=A[i][j]/d;
			B[i][j]=B[i][j]/d;
		}
		for(x=0;x<N;x++){
			if(x!=i){
				k=A[x][i];
				for(j=0;j<N;j++){
					A[x][j]=A[x][j]-(A[i][j]*k);
					B[x][j]=B[x][j]-(B[i][j]*k);
				}
			}
		}
	}
	printf("\nmatrisin tersi:\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%f   ",B[i][j]);
			
		}
		printf("\n");
	}
	return 0;
}
//kod cal�s�yor
