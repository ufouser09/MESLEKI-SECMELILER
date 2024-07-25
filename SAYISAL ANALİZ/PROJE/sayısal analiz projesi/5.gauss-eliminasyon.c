#include <stdio.h>
#include <math.h>

#define SIZE 100

float matris_alma();//kullanýcagýmýz fonksiyonlarý ilk basta tanýmladýk
float determinant(float[SIZE][SIZE], float);

//Yöntemler
float yoketme_gauss();


int cevap;//degiskenleri tanýmladýk
float N, matris[SIZE][SIZE];
float degisken[SIZE], deger[SIZE];

//degisken[x] = x1, x2 ...
//deger[x] = c1, c2 ...

int main(){
    yoketme_gauss();
		
	
	
	return 0;
}

//Fonksiyonlar
float matris_alma(){
	
	int i, j;//degiskenleri tanýmla
	
	//Matrisin geniþliðini alma
	printf("\n\nDenklem ve degisken sayisi: ");//kullanýcýdan matrisin boyutunu alýnýz
	scanf("%f", &N);
	while(N <= 0){//matrisin boyutu 0 dan kucuk girilirse kullanýcýdan tekrar bir deger alýn
		printf("\n\n(!) Degisken sayisi pozitif bir tamsayi olmalidir.");
		printf("\nLutfen geçerli bir deger giriniz: ");
		scanf("%f", &N);
	}
	
	//Matrisi alma
	printf("\nDenklem katsayilarini giriniz.\n");//denklemin katsayilarini giriniz mesela 3,6x+2,4y+-1,8z=6,3 bu denklemin eþittire olan kýsmýndaki katsayilari matrise aktarýrýz
	for(i=0 ; i<N ; i++){
		printf("---\n");
		for(j=0 ; j<N ; j++){
			printf("%d. denklemin, %d. degiskeninin katsayisi: ", i+1, j+1);//kullanýcýdan matrisimizi aldýk
			scanf("%f", &matris[i][j]);
		}
		printf("%d. denklemin esit oldugu deger: ", i+1);//bu kýsýmda denklemlerin eþit oldugu degerleri kullanýcýdan alýrýz
		scanf("%f", &deger[i]);
	}
	
	//Matrisi yazdýrma
	printf("\nDenklem Matrisiniz:");//kullanýcýdan aldýgýmýz degerleri yazdiririz
	for(i=0 ; i<N ; i++){
		printf("\n");
		for(j=0 ; j<N ; j++){
			printf("%.2f(x%d)\t", matris[i][j], j+1);
		}
		printf("=  %.2f", deger[i]);//denklemin esit oldugu degeri yazdirir
	}
}

float determinant(float a[SIZE][SIZE], float n){
	int i, j, k, p, r; // burada degiskenleri tanýmlarýz
	float det = 0;
	float minor[SIZE][SIZE];
	
	//1x1
	if(n == 1){//eger matrisimiz 1x1 matris ise determinant hesaplamamýza gerek yoktur matristeki tek degeri yazdýrsak yeter 
		return a[0][0];
		
	//2x2
	}else if(n == 2){//eger matrisimiz 2x2 matris ise determinant hesaplamýmýza gerek direk tek islemde halledebiliriz
		det=( a[0][0] * a[1][1] - a[0][1] * a[1][0] );
		return det;
		
	//3x3, 4x4, ...
	}else{
		for(k=0 ; k<n ; k++){
			p = 0;
			r = 0;
			for(i=1 ; i<n ; i++){
				for(j=0 ; j<n ; j++){
					if(j != k){
						minor[p][r] = a[i][j];
						r++;
						if(r == n-1){
							p++;
							r = 0;
						}
					}
				}
			}
			det = det + a[0][k] * pow(-1, k) * determinant(minor, n-1);
		}
    return det;
	}
}

//Yöntemler

float yoketme_gauss(){
	
	int i, j, k;
	float temp1, temp2, sum;
	
	printf("\n\nGAUSS ELIMINASYONU");
	printf("\n\n-----");
	
	matris_alma();
	
	printf("\n\n-----");
	
	//Üst üçgen matris oluþturma
	for(i=0 ; i<N-1 ; i++){
		temp1 = matris[i][i];
		for(j=i+1 ; j<N ; j++){
			temp2 = matris[j][i];
			for(k=i ; k<N ; k++){
				matris[j][k] = matris[j][k] - ( ( matris[i][k] / temp1 ) * temp2 );
			}
			deger[j] = deger[j] - ( ( deger[i] / temp1 ) * temp2 );
		}
	}
	
	//Üst üçgen matrisi yazdýrma
	printf("\n\nUst Ucgen Matrisiniz:");
	for(i=0 ; i<N ; i++){
		printf("\n");
		for(j=0 ; j<N ; j++){
			printf("%.2f(x%d)\t", matris[i][j], j+1);
		}
		printf("=  %.2f", deger[i]);
	}
	
	printf("\n\n-----");
	
	//Hesaplama
	for(i=(N-1) ; i>=0 ; i--){
		sum = 0;
		for(j=(N-1) ; j>=i ; j--){
			sum = sum + ( degisken[j] * matris[i][j] );
		}
		degisken[i] = (deger[i] - sum) / matris[i][i];
	}
	
	//Deðiþkenleri yazdýrma
	printf("\n\nDegiskenler:");
	for(i=0 ; i<N ; i++){
		printf("\nx%d = %f", i+1, degisken[i]);
	}
}
//bi sorun var




