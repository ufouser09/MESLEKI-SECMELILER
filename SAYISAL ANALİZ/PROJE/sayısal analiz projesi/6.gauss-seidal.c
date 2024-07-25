#include <stdio.h>
#include <math.h>

#define SIZE 100
//asagida kullanýcagýmýz fonksiyonlarý tanýmlarýz
float matris_alma();
float determinant(float[SIZE][SIZE], float);

//Yöntemler




float gauss_seidal();
//kullanýcagýmýz degiskenleri tanýmlarýz
int cevap;
float N, matris[SIZE][SIZE];
float degisken[SIZE], deger[SIZE];

//degisken[x] = x1, x2 ...
//deger[x] = c1, c2 ...

int main(){
	
		gauss_seidal();

	
	return 0;
}

//Fonksiyonlar
float matris_alma(){
	
	int i, j;
	
	//Matrisin geniþliðini alma
	printf("\n\nDenklem ve degisken sayisi: ");//kullanýcýdan matrisin genisliðini aliriz
	scanf("%f", &N);
	while(N <= 0){//eger matrisin genisligi 0 dan kucukse tekrar bir deger girmesi istenir
		printf("\n\n(!) Degisken sayisi pozitif bir tamsayi olmalidir.");
		printf("\nLutfen geçerli bir deger giriniz: ");
		scanf("%f", &N);
	}
	
	//Matrisi alma
	printf("\nDenklem katsayilarini giriniz.\n");
	for(i=0 ; i<N ; i++){//kullanýcýdan matris alýnýr
		printf("---\n");
		for(j=0 ; j<N ; j++){
			printf("%d. denklemin, %d. degiskeninin katsayisi: ", i+1, j+1);
			scanf("%f", &matris[i][j]);
		}
		printf("%d. denklemin esit oldugu deger: ", i+1);
		scanf("%f", &deger[i]);
	}
	
	//Matrisi yazdýrma
	printf("\nDenklem Matrisiniz:");
	for(i=0 ; i<N ; i++){
		printf("\n");
		for(j=0 ; j<N ; j++){
			printf("%.2f(x%d)\t", matris[i][j], j+1);
		}
		printf("=  %.2f", deger[i]);
	}
}

float determinant(float a[SIZE][SIZE], float n){
	int i, j, k, p, r;
	float det = 0;
	float minor[SIZE][SIZE];
	
	//1x1
	if(n == 1){
		return a[0][0];
		
	//2x2
	}else if(n == 2){
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



float gauss_seidal(){
	
	int i, j, flag = 0, kontrol = 1;
	float temp[SIZE], sum, epsilon;
	
	printf("\n\nGAUSS-SEIDAL YONTEMI");
	printf("\n\n-----");
	
	matris_alma();
	printf("\n\n-----");
	
	//Kontrol
	while(kontrol == 1){
		for(i=0 ; i<N ; i++){	
			sum = 0;
			for(j=0 ; j<N ; j++){
				if(j != i){
					sum = sum + fabs(matris[i][j]);
				}
			}
			if(fabs(matris[i][i]) < sum){
				kontrol = 0;
				printf("\n\n(!) Yakinsama kontrolu saglanmamistir.");
				printf("\nYine de isleme devam etmek istiyor musunuz?");
				printf("\n1) Evet\t2) Iptal Et\n");
				scanf("%d", &cevap);
			}
		}
		if(kontrol == 1){
			printf("\n\n(!) Yakinsama kontrolu saglanmistir.");
			kontrol = 0;
			cevap = 1;
		}
	}
	
	if(cevap == 1){
		//Deðer girme
		printf("\n\nDegiskenlerin baslangic degerlerini giriniz.\n");
		for(i=0 ; i<N ; i++){
			printf("x%d: ", i+1);
			scanf("%f", &degisken[i]);
		}
		printf("\nEpsilon degerini giriniz: ");
		scanf("%f", &epsilon);
		printf("\n");
		
		//Tablo yazdýrma
		for(i=0 ; i<N ; i++){
			printf("x%d\t\td(x%d)\t\t", i+1, i+1);
		}
		printf("\n");
		for(i=0 ; i<N ; i++){
			printf("------\t\t------\t\t");
		}
		printf("\n");
		for(i=0 ; i<N ; i++){
			printf("%f\t-\t\t", degisken[i]);
		}
		
		//Yeni x deðiþkenlerini hesaplama
		while(flag == 0){
			for(i=0 ; i<N ; i++){
				sum = 0;
				for(j=0 ; j<N ; j++){
					if(j != i){
						sum = sum + (matris[i][j] * degisken[j]);
					}
				}
				degisken[i] = (deger[i] - sum) / matris[i][i];
			}
			
			//Epsilon kontrolü
			kontrol = 1;
			while(kontrol == 1){
				for(i=0 ; i<N ; i++){
					if(fabs(degisken[i]-temp[i]) > epsilon){
						kontrol = 0;
					}
				}
				if(kontrol == 1){
					flag = 1;
					kontrol = 0;
				}
			}
			
			//Yazdýrma
			if(flag != 1){
				printf("\n");
				for(i=0 ; i<N ; i++){
					printf("%f\t%f\t", degisken[i], fabs(degisken[i]-temp[i]));
					temp[i] = degisken[i];
				}
			}else{
				printf("\n");
				for(i=0 ; i<N ; i++){
					printf("------\t\t------\t\t");
				}
				printf("\n");
				for(i=0 ; i<N ; i++){
					printf("%f\t%f < e\t", degisken[i], fabs(degisken[i]-temp[i]));
				}
				printf("\n\nDegiskenler:");
				for(i=0 ; i<N ; i++){
					printf("\nx%d = %f", i+1, degisken[i]);
				}
			}
			
		} //while sonu
	} //if sonu
}















