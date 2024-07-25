#include <stdio.h>
#include <math.h>

#define SIZE 100
#define E 2.7182818

//asasgidaki kullancag�m�z fonksiyonlar� tan�mlad�k
float matris_alma();//kullan�cag�m�z fonksiyonlar� ilk basta tan�mlad�k
float determinant(float[SIZE][SIZE], float);
double denklem_alma();
double denklem_hesap(double x);
double turev_alma();
double turev_hesap(double);


//y�ntem fonksiyonlar�
double regula_f();
double aralik_y();
double newton_r();
float yoketme_gauss();
float gauss_seidal();
float trapez_y();
float simpson_y();
//kullan�cag�m�z degiskenleri tan�mlad�k
int derece, cevap,i,j;
double temp;

int cevap;//degiskenleri tan�mlad�k
float N, matris[SIZE][SIZE];
float degisken[SIZE], deger[SIZE];
//degisken[x] = x1, x2 ...
//deger[x] = c1, c2 ...

float denklem_katsayi[SIZE];
double denklem_katsayi[2][SIZE], trigo_katsayi[4], trigo_ic_katsayi[4],trigo_katsayi[2][4];
double ln_katsayi, ln_ic_katsayi, e_katsayi, e_uskatsayi;

//basit iterasyon i�in gerekli de�i�kenler
int derece_2, turev_derece_2;
double denklem_katsayi_2, turev_katsayi_2;

//denklem_katsayi[0][x] = denklem de�i�kenlerinin katsay�s�
//denklem_katsayi[1][x] = t�rev denkleminin de�i�kenlerinin katsay�s�

//turev_katsayi[0][x] = trigonometrik de�i�kenlerinin katsay�s�
//turev_katsayi[1][x] = trigonometrik de�i�kenlerinin t�revlerinin katsay�s�

//denklem_katsayi[0][x] = denklem de�i�kenlerinin katsay�s�

//trigo_katsayi[x]: trigonometrik de�i�kenlerin katsay�lar�
//[  0  ,  1  ,  2  ,  3  ]
//[ sin , cos , tan , cot ]
	
//trigo_katsayi[1][x]: trigonometrik de�i�kenlerin katsay�lar�
//[  0  ,  1   ,  2          ,  3           ]
//[ cos , -sin , 1/(cos*cos) , -1/(sin*sin) ]


int main(){
	
		
	aralik_y();
	
	return 0;
}
float determinant(float a[SIZE][SIZE], float n){
	int i, j, k, p, r; // burada degiskenleri tan�mlar�z
	float det = 0;
	float minor[SIZE][SIZE];
	
	//1x1
	if(n == 1){//eger matrisimiz 1x1 matris ise determinant hesaplamam�za gerek yoktur matristeki tek degeri yazd�rsak yeter 
		return a[0][0];
		
	//2x2
	}else if(n == 2){//eger matrisimiz 2x2 matris ise determinant hesaplam�m�za gerek direk tek islemde halledebiliriz
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



float matris_alma(){
	
	int i, j;//degiskenleri tan�mla
	
	//Matrisin geni�li�ini alma
	printf("\n\nDenklem ve degisken sayisi: ");//kullan�c�dan matrisin boyutunu al�n�z
	scanf("%f", &N);
	while(N <= 0){//matrisin boyutu 0 dan kucuk girilirse kullan�c�dan tekrar bir deger al�n
		printf("\n\n(!) Degisken sayisi pozitif bir tamsayi olmalidir.");
		printf("\nLutfen ge�erli bir deger giriniz: ");
		scanf("%f", &N);
	}
	
	//Matrisi alma
	printf("\nDenklem katsayilarini giriniz.\n");//denklemin katsayilarini giriniz mesela 3,6x+2,4y+-1,8z=6,3 bu denklemin e�ittire olan k�sm�ndaki katsayilari matrise aktar�r�z
	for(i=0 ; i<N ; i++){
		printf("---\n");
		for(j=0 ; j<N ; j++){
			printf("%d. denklemin, %d. degiskeninin katsayisi: ", i+1, j+1);//kullan�c�dan matrisimizi ald�k
			scanf("%f", &matris[i][j]);
		}
		printf("%d. denklemin esit oldugu deger: ", i+1);//bu k�s�mda denklemlerin e�it oldugu degerleri kullan�c�dan al�r�z
		scanf("%f", &deger[i]);
	}
	
	//Matrisi yazd�rma
	printf("\nDenklem Matrisiniz:");//kullan�c�dan ald�g�m�z degerleri yazdiririz
	for(i=0 ; i<N ; i++){
		printf("\n");
		for(j=0 ; j<N ; j++){
			printf("%.2f(x%d)\t", matris[i][j], j+1);
		}
		printf("=  %.2f", deger[i]);//denklemin esit oldugu degeri yazdirir
	}
}



//Fonksiyonlar buradan sonra.
double denklem_alma(){
	
	int i;
	
	//�sl� ifadeler,kullan�c�dan denklemin derecesini al�r�z(yani polinomdaki en buyuk uslu ifadenin �ss�n� sorar�z.
	printf("\n\n DENKLEM�N DERECES�N� G�R�N�Z: ");//
	scanf("%d", &derece);
	
	
	
	//eger denklemin derecesi 0 dan kucukse kullan�c�dan denklemin derecesini tekrar girmesini isteriz
	while(derece < 0){
		printf("\n(!) Denkleminizin derecesi negatif olamaz.");
		printf("\nLutfen gecerli bir tamsayi degeri giriniz: ");
		scanf("%d", &derece);
	}
	
	
	
	//denklem_katsayisi[0][i] matrisinde degiskenlerin katsayisini tut
	for(i=0 ; i<=derece ; i++){          
		printf("x^%d degiskeninin katsayisi: ", i);
		scanf("%lf", &denklem_katsayi[0][i]);
	}
	
	
	
	//trigonometrik ifadeler
	printf("\nTrigonometrik degisken var mi?");//trigonometrik degisken olup olmad�g�na bak bunu kullaniciya sor
	printf("\n1) Var.   2) Yok.\n");
	scanf("%d", &cevap);
	
	
	
	if(cevap==1){
		
		printf("\nTrigonometrik degiskenlerin katsayilarini giriniz.");   //sin in bas katsayisini trigo_katsayi[0]da i� katsayisini trigo_ic_katsayi[0] da tut 
		
		//sin
		//trigonometrik degiskenlerden sin in baskatsayisini al
		printf("\n\n(A)sin(Bx)");           
		printf("\nA katsayisini giriniz: ");
		scanf("%lf", &trigo_katsayi[0]);
		
		
		
		//eger kullan�c� baskatsayisini 0 vermemisse bi de i� katsayisini sor
		if(trigo_katsayi[0] != 0){             
			printf("B katsayisini giriniz: ");  
			scanf("%lf", &trigo_ic_katsayi[0]);
		}
		
		
		
		printf("-----");
		
		
		
		//cos
		//cos un baskatsayisini trigo_katsayi[1] de i� katsayisini trigo_ic_katsayi[1] de tut
		//trigonometrik degiskenlerden cos un baskatsayisini al
		printf("\n(A)cos(Bx)");     
		printf("\nA katsayisini giriniz: ");  
		scanf("%lf", &trigo_katsayi[1]);
		
		
		
		 //eger kullanici baskatsayisini 0 girmemisse bir de i� katsayisini al
		if(trigo_katsayi[1] != 0){  
			printf("B katsayisini giriniz: ");
			scanf("%lf", &trigo_ic_katsayi[1]);
		}
		
		
		
		printf("-----");
		
		
		
		//tan
		//tan �n baskatsayisini trigo_katsayi[2] de i� katsayisini trigo_ic_katsayi[2] de tut
		//trigonometrik degiskenlerden tan �n baskatsayisini al
		printf("\n(A)tan(Bx)");  
		printf("\nA katsayisini giriniz: ");
		scanf("%lf", &trigo_katsayi[2]);
		
		
		//eger kullanici baskatsayisini 0 vermemisse kullaniciya bi de i�katsayisini sor
		if(trigo_katsayi[2] != 0){   
			printf("B katsayisini giriniz: ");
			scanf("%lf", &trigo_ic_katsayi[2]);
		}
		
		
		
		printf("-----");
		
		
		
		//cot
		//cotun baskatsayisini trigo_katsayi[3] de i� katsayisini trigo_ic_katsayi[3] de tut
		//trigonometrik degiskenlerden cot un baskatsaysini al
		printf("\n(A)cot(Bx)");  
		printf("\nA katsayisini giriniz: ");
		scanf("%lf", &trigo_katsayi[3]);
		
		
		
		 //eger kullanici baskatsayisini 0 vermemisse kullaniciya bi de ic katsayisini sor
		if(trigo_katsayi[3] != 0){     
			printf("B katsayisini giriniz: ");
			scanf("%lf", &trigo_ic_katsayi[3]);
		}
		
		
		
		
		// bu else en bastaki eger trigonometrik ifade varsa 1 e bas�n�z kosulunu sunan if in else dal�
		//yani eger if kosulu saglanmazsa yani ifademizde hi� trigonometrik ifademiz yoksa t�m trigonometrik ifadelerin katsayisini 0 yap
	}else{     
		for(i=0 ; i<4 ; i++){  
			trigo_katsayi[i]=0;
		}
	}
	
	
	
	
	//logaritmik ifade
	//kullan�c�ya lnx olup olmad�g�n� sor 
	printf("\nlnx degiskeni var mi?");
	printf("\n1) Var.   2) Yok.\n");
	scanf("%d", &cevap);
	
	
	
	 //eger cevab�m�z olumlu ise bu kosula gir
	//kullanc�dan lnx in baskatsayisini al
	//lnx in baskatsayini ln_katsayi degiskenine ata
	//kullanicidan lnx in bi de ic katsayisini al
	//lnx in ic katsayisini ln_ic_katsayi degiskenine ata
	if(cevap==1){         
		printf("\n(A)ln(Bx)");   
		printf("\nA katsayisini giriniz: ");
		scanf("%lf", &ln_katsayi);
		printf("B katsayisini giriniz: ");
		scanf("%lf", &ln_ic_katsayi);    
	
	
	
	//eger cevabimiz olumsuz ise yani cumlede lnx li bir ifademiz yoksa lnx in baskatsayisini 0 yap
	}else{ 
		ln_katsayi=0;
		ln_ic_katsayi=1;
	}
	
	//�stel ifade
	//cumlede e li bir ifade olup olmad�g�n� sor
	printf("\ne^x degiskeni var mi?");
	printf("\n1) Var.   2) Yok.\n");
	scanf("%d", &cevap);
	
	
	// eger cevabimiz olumlu ise lnx in baskatsayisini al
	//baskatsayi degerini e_katsayiya ata
	// baskatsayidan ust katsayi olup olmad�g�n� sor
	//e nin ust katsayisini e_ustkatsayi ya ata
	if(cevap==1){   
		printf("\n(A)e^((B)x)");
		printf("\nA katsayisini giriniz: ");
		scanf("%lf", &e_katsayi);
		printf("B katsayisini giriniz: ");
		scanf("%lf", &e_uskatsayi);      
		
		
		//eger e li bir ifademiz yok ise e nin baskatsayisini 0 yap
	}else{
		e_katsayi=0;
	}
	
	
	
	
	//denklemi yazd�rma
	printf("\nDenkleminiz:\n");
	
	
	
	
	//denklemin derecesi olan terimi ekrana yazd�r�rz
	if(denklem_katsayi[0][derece]!=0){
		printf("(%.2fx^%d)", denklem_katsayi[0][derece], derece);
	}
	
	
	
	//denklemin derecesi olan terim harici olan polinom terimlerini ekrana yazdiririz
	for(i=derece-1 ; i>=0 ; i--){
		if(denklem_katsayi[0][i]!=0){
			printf("+(%.2fx^%d)", denklem_katsayi[0][i], i);
		}
	}
	
	
	
	//sin un baskatsayisi 0 degilse sin�s � ekrana yazd�r
	if(trigo_katsayi[0]!=0){  
		printf("+(%.2fsin(%.2fx))", trigo_katsayi[0], trigo_ic_katsayi[0]);
	}
	
	
	
	//cosun  baskatsayisi 0 degilse cosu ekrana yazdir
	if(trigo_katsayi[1]!=0){  
		printf("+(%.2fcos(%.2fx))", trigo_katsayi[1], trigo_ic_katsayi[1]);
	}
	
	
	
	//tan�n baskatsayisi 0 degilse tanjant� ekrana yazdir
	if(trigo_katsayi[2]!=0){ 
		printf("+(%.2ftan(%.2fx))", trigo_katsayi[2], trigo_ic_katsayi[2]);
	}
	
	
	
	//cotun baskatsayisi 0 degilse cotu ekrana yazd�r
	if(trigo_katsayi[3]!=0){ 
		printf("+(%.2fcot(%.2fx))", trigo_katsayi[3], trigo_ic_katsayi[3]);
	}
	
	
	
	//lnx in katsayisi 0 degils lnx i ekrana yazdir
	if(ln_katsayi!=0){   
		printf("+(%.2fln(%.2fx))", ln_katsayi, ln_ic_katsayi);
	}
	
	
	
	//e nin katsayisi 0 degilse e yi ekrana yazdir
	if(e_katsayi!=0){   
		printf("+(%.2fe^(%.2fx))", e_katsayi, e_uskatsayi);
	}
}



double denklem_hesap(double x){
	
	//degiskenleri tan�mlar�z
	int i;
	double sum=0, x_sum=1;
	double sinx, cosx, tanx, cotx, lnx, ex;
	
	
	
	
	//trigonometrik de�erler
	//sin�s degerini hesapla
	sinx = trigo_katsayi[0]*sin(trigo_ic_katsayi[0]*x);  
	
	
	 //cosin�s degerini hesapla
	cosx = trigo_katsayi[1]*cos(trigo_ic_katsayi[1]*x); 
	
	
	//tanjant�n baskatsayisi 0 m� kontrol et
	//baskatsayimiz 0 ise degerini 0 yap
	if(trigo_katsayi[2] == 0){
		tanx = 0; 
	
	
		
	//tanjant�n baskatsayisi 0 degilse tanjanti hesapla
	}else{
		tanx = trigo_katsayi[2]*tan(trigo_ic_katsayi[2]*x);
	}
	
	
	//cotun baskatsayisi 0 mi kontrol et
	//baskatsayi 0 ise degerini 0 yap
	if(trigo_katsayi[3] == 0){ 
		cotx = 0; 
		
	
		
	//eger cotun baskatsayisi 0 degilse  cotanjant�n degerini hesapla
	}else{
		cotx = trigo_katsayi[3]/(tan(trigo_ic_katsayi[3]*x)); 
	}
	
	//logaritmik de�er
	//lnx in baskatsayisi 0 mi kontrol et
	//eger baskatsayisi 0 ise lnx in degerini 0 yap
	if(ln_katsayi == 0){
		lnx = 0;
		
		
	//eger baskatsayisi 0 degilse lnx i hesapla
	}else{
		lnx = ln_katsayi*log(ln_ic_katsayi*x);
	}
	
	//�stel de�er
	//e nin baskatsayisinin 0 olup olmadigini kontrol et
	//eger baskatsayisi 0 ise degerini 0 yap otomatik olarak
	if(e_katsayi == 0){
		ex = 0;
		
		
	//eger baskatsayimiz 0 degilse e nin degerini hesapla
	}else{
		ex = e_katsayi*pow(E, e_uskatsayi*x);
	}
	
	
	
	//di�er de�i�kenler
	//x_sum burda ilk 1 di yani x^0 l� ifademizin katsayisini 0 a att�k sonra x_sum x oldu x^1 li ifademizin katsayisi ile x i carpip bunu sum'a ekledik b�ylece polinomumuzu bulduk
	for(i=0 ; i<=derece ; i++){
		sum = sum + (denklem_katsayi[0][i]*x_sum);
		x_sum = x_sum * x;
	}
	
	
	
	
	//toplam
	//denklemin son hali b�yledir
	sum = sum + sinx + cosx + tanx + cotx + lnx + ex;
	return sum;
}





//Y�NTEMLER



double aralik_y(){
	
	double alt, ust, orta, e;
	
	printf("\n\nARALIK YARILAMA YONTEMI");
	printf("\n\n-----");
	
	//burda denklemimizi ald�k
	denklem_alma(); 
	
	printf("\n\n-----");
	
	
	
	//kullan�c�dan alt degeri al
	printf("\n\nAlt deger: ");
	scanf("%lf", &alt);
	
	
	
	//kullanicidan ust degeri al
	printf("Ust deger: ");
	scanf("%lf", &ust);
	
	
	//f(alt)*f(ust)<0 ise bu aral�kta kok vardir
	if(denklem_hesap(alt)*denklem_hesap(ust) > 0){  
	
	
		//eger kosul saglanmazsa y�ntem uygulanamaz
		printf("\n(!) Verilen aralik, gereken kosulu saglamamaktadir.");
		printf("\n(!) f(alt) x f(ust) < 0 olmalidir.");
		
		
		
	}else{
		
		
		// eger ustteki sart saglan�yorsa bu sefer epsilon degeri al
		printf("Epsilon degeri: ");
		scanf("%lf", &e);
		
		printf("\nalt\t\tf(alt)\t\tust\t\tf(ust)\t\torta\t\tf(orta)");
		printf("\n---\t\t------\t\t---\t\t------\t\t----\t\t-------");
		
		
		//alt ve ust degerin ortas�n� bulmak i�in 2 ye b�l ve bunu orta degiskenine ata
		orta = (alt + ust)/2; 
		
		
		
		//burda ilk yukar�da buldugumuz ilk alt ust ve orta degerleri ekrana yazd�r�r�z
		while(fabs(denklem_hesap(orta)) >= e){
			
			printf("\n%f\t%f", alt, denklem_hesap(alt));
			printf("\t%f\t%f", ust, denklem_hesap(ust));
			printf("\t%f\t%f", orta, denklem_hesap(orta));
			
			
			
			//alt ve orta degerlerinin carp�m� pozitifse yani grafikte alt ve orta degerler ayn� b�lgede ise orta degerini alt degere ata
			if(denklem_hesap(orta)*denklem_hesap(alt) > 0){
				alt = orta;
				
				
			//ust ve orta degerlerin carpimi pozitifse yani grafikte ust ve orta degerler ayn� bolgede ise orta degeri ust degere ata
			}else if(denklem_hesap(orta)*denklem_hesap(ust) > 0){ 
				ust = orta;
			}
			
			
		//yeni buldugumuz degerlerle yeni bir orta deger olustur
		orta = (alt + ust)/2; 
		}
		
		//while dan c�kt�g� zaman yani istenilen hata pay�na ulas�ld�g� zaman asagidekileri yazd�r�r
		printf("\n---\t\t------\t\t---\t\t------\t\t----\t\t-------");
		printf("\n%f\t%f", alt, denklem_hesap(alt));  //buldugun son sonuclar� ekrana yazdir
		printf("\t%f\t%f", ust, denklem_hesap(ust));
		printf("\t%f\t%f < e", orta, denklem_hesap(orta));
		
		printf("\n\nx = %f degerinde saglanir.", orta);
	}
}

double regula_f(){
	
	double alt, ust, orta, e;
	
	printf("\n\nREGULA FALSI YONTEMI");
	printf("\n\n-----");
	
	denklem_alma();
	
	printf("\n\n-----");
	
	printf("\n\nAlt deger: ");//kullan�c�dan alt degeri al
	scanf("%lf", &alt);
	
	printf("Ust deger: ");//kullanicidan ust degeri al
	scanf("%lf", &ust);
	
	if(denklem_hesap(alt)*denklem_hesap(ust) > 0){
		printf("\n(!) Verilen aralik, gereken kosulu saglamamaktadir.");
		printf("\n(!) f(alt) x f(�st) < 0 olmalidir.");
	}else{
		printf("Epsilon degeri: ");//eger ustteki kosul saglan�rsa kullan�c�dan epsilon degerini al
		scanf("%lf", &e);
		
		printf("\nalt\t\tf(alt)\t\tust\t\tf(ust)\t\torta\t\tf(orta)");
		printf("\n---\t\t------\t\t---\t\t------\t\t----\t\t-------");
		
		orta = (ust*(denklem_hesap(alt)) - alt*(denklem_hesap(ust))) / ((denklem_hesap(alt)-denklem_hesap(ust)));//bu denklemnden orta deger hesaplan�r
		
		while(fabs(denklem_hesap(orta)) >= e){
			
			printf("\n%f\t%f", alt, denklem_hesap(alt)); //kullan�c�n�n girdigi degerler yazd�r�l�r
			printf("\t%f\t%f", ust, denklem_hesap(ust));
			printf("\t%f\t%f", orta, denklem_hesap(orta));
			
			if(denklem_hesap(orta) < 0){
				alt = orta;
			}else if(denklem_hesap(orta) > 0){
				ust = orta;
			}
			orta = (ust*(denklem_hesap(alt)) - alt*(denklem_hesap(ust))) / ((denklem_hesap(alt)-denklem_hesap(ust)));
		}
		printf("\n---\t\t------\t\t---\t\t------\t\t----\t\t-------");
		printf("\n%f\t%f", alt, denklem_hesap(alt));
		printf("\t%f\t%f", ust, denklem_hesap(ust));
		printf("\t%f\t%f < e", orta, denklem_hesap(orta));
		
		printf("\n\nx = %f degerinde saglanir.", orta);
	}
}


double turev_alma(){
	
	for(i=0 ; i<=derece-1 ; i++){
		denklem_katsayi[1][i] = (i+1)*denklem_katsayi[0][i+1];
	}
	
	for(i=0 ; i<4 ; i++){
		trigo_katsayi[1][i] = trigo_katsayi[0][i];
	}
	
	printf("\nTurevi:\n");
	
	for(i=derece-1 ; i>0 ; i--){
		if(denklem_katsayi[1][i]!=0){
			printf("(%.2fx^%d)+", denklem_katsayi[1][i], i);
		}
	}
	if(denklem_katsayi[1][0]!=0){
		printf("(%.2f)", denklem_katsayi[1][0]);
	}
	
	if(trigo_katsayi[0][0]!=0){
		printf("+(%.2fcos(%.2fx))", trigo_katsayi[1][0]*trigo_ic_katsayi[0], trigo_ic_katsayi[0]);
	}
	if(trigo_katsayi[0][1]!=0){
		printf("+(-%.2fsin(%.2fx))", trigo_katsayi[1][1]*trigo_ic_katsayi[1], trigo_ic_katsayi[1]);
	}
	if(trigo_katsayi[0][2]!=0){
		printf("+(%.2f/(cos(%.2fx))^2)", trigo_katsayi[1][2]*trigo_ic_katsayi[2], trigo_ic_katsayi[2]);
	}
	if(trigo_katsayi[0][3]!=0){
		printf("+(%.2f/(sin(%.2fx))^2)", (-1)*trigo_katsayi[1][3]*trigo_ic_katsayi[3], trigo_ic_katsayi[3]);
	}
	
	if(ln_katsayi!=0){
		printf("+(%.2f/x))", ln_katsayi*ln_ic_katsayi);
	}
	//ln_katsayi*ln_ic_katsayi ayn� zamanda t�revdeki 1/x ifadesinin katsay�s�
}


double turev_hesap(double x){
	
	double sum=0, x_sum=1;
	double sinx_t, cosx_t, tanx_t, cotx_t, lnx_t;
	
	//trigonometrik de�erler
	sinx_t = trigo_ic_katsayi[0]*trigo_katsayi[1][0]*cos(trigo_ic_katsayi[0]*x);
	cosx_t = (-1)*trigo_ic_katsayi[1]*trigo_katsayi[1][1]*sin(trigo_ic_katsayi[1]*x);
	if(trigo_katsayi[1][2] == 0){
		tanx_t = 0;
	}else{
		tanx_t = trigo_ic_katsayi[2]*trigo_katsayi[1][2]/(cos(trigo_ic_katsayi[2]*x)*cos(trigo_ic_katsayi[2]*x));
	}
	if(trigo_katsayi[1][2] == 0){
		cotx_t = 0;
	}else{
		cotx_t = (-1)*trigo_ic_katsayi[3]*trigo_katsayi[1][3]/(sin(trigo_ic_katsayi[3]*x)*sin(trigo_ic_katsayi[3]*x));
	}
	
	//logaritmik de�erler
	if(ln_katsayi == 0){
		lnx_t = 0;
	}else{
		lnx_t = (ln_katsayi*ln_ic_katsayi)/x;
	}
	
	//di�er de�i�kenler
	for(i=0 ; i<=derece-1 ; i++){
		sum = sum + (denklem_katsayi[1][i]*x_sum);
		x_sum = x_sum * x;
	}
	
	//toplam
	sum = sum + sinx_t + cosx_t + tanx_t + cotx_t + lnx_t;
	return sum;
}


double newton_r(){
	
	double x0, x1, e;
	
	printf("\n\nNEWTON - RAPHSON YONTEMI");
	printf("\n\n-----");
	
	denklem_alma();
	turev_alma();
	
	printf("\n\n-----");
	
	printf("\n\nx'in baslangic degeri: ");
	scanf("%lf", &x0);
	
	printf("Epsilon degeri: ");
	scanf("%lf", &e);
	
	printf("\nx(k)\t\tx(k+1)\t\t|x(k)-x(k+1)|");
	printf("\n----\t\t------\t\t-------------");
	
	x1 = x0 - (denklem_hesap(x0)/turev_hesap(x0));
	
	while(fabs(x1-x0) >= e){
		printf("\n%f\t%f\t%f", x0, x1, fabs(x1-x0));
		x0 = x1;
		x1 = x0 - (denklem_hesap(x0)/turev_hesap(x0));
	}
	
	printf("\n----\t\t------\t\t-------------");
	printf("\n%f\t%f\t%f < e", x0, x1, fabs(x1-x0));
	printf("\n\nx = %f degerinde saglanir.", x1);
	
}


float yoketme_gauss(){
	
	int i, j, k;
	float temp1, temp2, sum;
	
	printf("\n\nGAUSS ELIMINASYONU");
	printf("\n\n-----");
	
	matris_alma();
	
	printf("\n\n-----");
	
	//�st ��gen matris olu�turma
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
	
	//�st ��gen matrisi yazd�rma
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
	
	//De�i�kenleri yazd�rma
	printf("\n\nDegiskenler:");
	for(i=0 ; i<N ; i++){
		printf("\nx%d = %f", i+1, degisken[i]);
	}
}
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
		//De�er girme
		printf("\n\nDegiskenlerin baslangic degerlerini giriniz.\n");
		for(i=0 ; i<N ; i++){
			printf("x%d: ", i+1);
			scanf("%f", &degisken[i]);
		}
		printf("\nEpsilon degerini giriniz: ");
		scanf("%f", &epsilon);
		printf("\n");
		
		//Tablo yazd�rma
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
		
		//Yeni x de�i�kenlerini hesaplama
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
			
			//Epsilon kontrol�
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
			
			//Yazd�rma
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

float trapez_y(){
	
	int i;
	float alt, ust, n;
	float x0, x1, y0, y1;
	float sum = 0, h;
	
	printf("\n\nTRAPEZ YONTEMI");
	printf("\n\n-----");
	
	denklem_alma();
	printf("\n\n-----");
	
	printf("\n\nIntegralin hesaplanacagi aralik icin...");
	printf("\nAlt deger: ");
	scanf("%f", &alt);
	printf("Ust deger: ");
	scanf("%f", &ust);
	
	printf("\nAralik sayisi: ");
	scanf("%f", &n);
	
	while(n <= 0){
		printf("\n(!) Aralik sayisi pozitif bir sayi olmalidir.");
		printf("\nLutfen uygun bir aralik sayisi giriniz: ");
		scanf("%f", &n);
	}
	
	h = (ust - alt) / n;
	x1 = alt;
	
	for(i=0 ; i<n ; i++){
		x0 = x1;
		x1 = x1 + h;
		y0 = denklem_hesap(x0);
		y1 = denklem_hesap(x1);
		sum = sum + (y0 + y1);
	}
	sum = (sum * h) / 2;
	
	printf("\nIntegral degeri: %f", sum);
}

float simpson_y(){
	int i;
	float alt, ust, n, h;
	float x, y0, yn;
	float sum_cift = 0, sum_tek = 0, sum;
	
	printf("\n\nSIMPSON YONTEMI");
	printf("\n\n-----");
	
	denklem_alma();
	printf("\n\n-----");
	
	printf("\n\nIntegralin hesaplanacagi aralik icin...");
	printf("\nAlt deger: ");
	scanf("%f", &alt);
	printf("Ust deger: ");
	scanf("%f", &ust);
	
	printf("\nAralik sayisi: ");
	scanf("%f", &n);
	i = n;
	
	while(i%2 == 1 || i <= 0){
		printf("\n(!) Aralik sayisi bu yontemde pozitif ve cift sayi olmalidir.");
		printf("\nLutfen uygun bir aralik sayisi giriniz: ");
		scanf("%f", &n);
		i = n;
	}
	
	h = (ust - alt) / n;
	y0 = denklem_hesap(alt);
	yn = denklem_hesap(ust);
	x = alt;
	
	for(i=1 ; i<n ; i++){
		x = x + h;
		if(i%2 == 1){
			sum_tek = sum_tek + denklem_hesap(x);
		}else{
			sum_cift = sum_cift + denklem_hesap(x);
		}
	}
	
	sum = ( (y0 + yn + (4 * sum_tek) + (2 * sum_cift)) * h ) / 3;
	
	printf("\nIntegral degeri: %f", sum);
}














