#include <stdio.h>
#include <math.h>

#define SIZE 100
#define E 2.7182818

//asagida kullan�cag�m�z fonksiyonlar� tan�mlad�k
double denklem_alma();
double denklem_hesap(double);




//y�ntem fonksiyonlar�

double regula_f();


int derece, cevap;//degiskenleri tan�mlad�k
double denklem_katsayi[2][SIZE], trigo_katsayi[4], trigo_ic_katsayi[4];
double ln_katsayi, ln_ic_katsayi, e_katsayi, e_uskatsayi;



//denklem_katsayi[0][x] = denklem de�i�kenlerinin katsay�s�


//trigo_katsayi[x]: trigonometrik de�i�kenlerin katsay�lar�
//[  0  ,  1  ,  2  ,  3  ]
//[ sin , cos , tan , cot ]
	

int main(){
		
	
		regula_f();
	
	
	return 0;
}

//Fonksiyonlar buradan sonra.

double denklem_alma(){
	
	int i;
	
	//�sl� ifadeler
	printf("\n\nDenkleminizin derecesini giriniz: ");//kullan�c�dan denklemin derecesini al�r�z
	scanf("%d", &derece);
	while(derece < 0){//eger derecem�z 0 dan kucukse kullan�c�dan bi kere daha deger isteriz
		printf("\n(!) Denkleminizin derecesi negatif olamaz.");
		printf("\nLutfen gecerli bir tamsayi degeri giriniz: ");
		scanf("%d", &derece);
	}
	for(i=0 ; i<=derece ; i++){          //denklem_katsayisi[0][i] matrisinde degiskenlerin katsayisini tut
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
		printf("\n\n(A)sin(Bx)");           //trigonometrik degiskenlerden sin in baskatsayisini al
		printf("\nA katsayisini giriniz: ");
		scanf("%lf", &trigo_katsayi[0]);
		if(trigo_katsayi[0] != 0){             //eger kullan�c� baskatsayisini 0 vermemisse bi de i� katsayisini sor
			printf("B katsayisini giriniz: ");  
			scanf("%lf", &trigo_ic_katsayi[0]);
		}
		printf("-----");
		//cos
		printf("\n(A)cos(Bx)");     //cos un baskatsayisini trigo_katsayi[1] de i� katsayisini trigo_ic_katsayi[1] de tut
		printf("\nA katsayisini giriniz: ");  //trigonometrik degiskenlerden cos un baskatsayisini al
		scanf("%lf", &trigo_katsayi[1]);
		if(trigo_katsayi[1] != 0){   //eger kullanici baskatsayisini 0 girmemisse bir de i� katsayisini al
			printf("B katsayisini giriniz: ");
			scanf("%lf", &trigo_ic_katsayi[1]);
		}
		printf("-----");
		//tan
		printf("\n(A)tan(Bx)");  //tan �n baskatsayisini trigo_katsayi[2] de i� katsayisini trigo_ic_katsayi[2] de tut
		printf("\nA katsayisini giriniz: ");//trigonometrik degiskenlerden tan �n baskatsayisini al
		scanf("%lf", &trigo_katsayi[2]);
		if(trigo_katsayi[2] != 0){   //eger kullanici baskatsayisini 0 vermemisse kullaniciya bi de i�katsayisini sor
			printf("B katsayisini giriniz: ");
			scanf("%lf", &trigo_ic_katsayi[2]);
		}
		printf("-----");
		//cot
		printf("\n(A)cot(Bx)");  //cotun baskatsayisini trigo_katsayi[3] de i� katsayisini trigo_ic_katsayi[3] de tut
		printf("\nA katsayisini giriniz: ");//trigonometrik degiskenlerden cot un baskatsaysini al
		scanf("%lf", &trigo_katsayi[3]);
		if(trigo_katsayi[3] != 0){      //eger kullanici baskatsayisini 0 vermemisse kullaniciya bi de ic katsayisini sor
			printf("B katsayisini giriniz: ");
			scanf("%lf", &trigo_ic_katsayi[3]);
		}
	}else{     // bu else en bastaki eger trigonometrik ifade varsa 1 e bas�n�z kosulunu sunan if in else dal�
		for(i=0 ; i<4 ; i++){  //yani eger if kosulu saglanmazsa yani ifademizde hi� trigonometrik ifademiz yoksa t�m trigonometrik ifadelerin katsayisini 0 yap
			trigo_katsayi[i]=0;
		}
	}
	
	//logaritmik ifade
	printf("\nlnx degiskeni var mi?");//kullan�c�ya lnx olup olmad�g�n� sor 
	printf("\n1) Var.   2) Yok.\n");
	scanf("%d", &cevap);
	
	if(cevap==1){          //eger cevab�m�z olumlu ise bu kosula gir
		printf("\n(A)ln(Bx)");   //kullanc�dan lnx in baskatsayisini al
		printf("\nA katsayisini giriniz: ");//lnx in baskatsayini ln_katsayi degiskenine ata
		scanf("%lf", &ln_katsayi);
		printf("B katsayisini giriniz: ");//kullanicidan lnx in bi de ic katsayisini al
		scanf("%lf", &ln_ic_katsayi);    //lnx in ic katsayisini ln_ic_katsayi degiskenine ata
	}else{ //eger cevabimiz olumsuz ise yani cumlede lnx li bir ifademiz yoksa lnx in baskatsayisini 0 yap
		ln_katsayi=0;
		ln_ic_katsayi=1;
	}
	
	//�stel ifade
	printf("\ne^x degiskeni var mi?");//cumlede e li bir ifade olup olmad�g�n� sor
	printf("\n1) Var.   2) Yok.\n");
	scanf("%d", &cevap);
	
	if(cevap==1){   // eger cevabimiz olumlu ise lnx in baskatsayisini al
		printf("\n(A)e^((B)x)");//baskatsayi degerini e_katsayiya ata
		printf("\nA katsayisini giriniz: ");
		scanf("%lf", &e_katsayi);
		printf("B katsayisini giriniz: ");// baskatsayidan ust katsayi olup olmad�g�n� sor
		scanf("%lf", &e_uskatsayi);      //e nin ust katsayisini e_ustkatsayi ya ata
	}else{
		e_katsayi=0;
	}
	
	//denklemi yazd�rma
	printf("\nDenkleminiz:\n");
	
	if(denklem_katsayi[0][derece]!=0){//denklemin derecesi olan terimi yazd�r�r�z ekrana
		printf("(%.2fx^%d)", denklem_katsayi[0][derece], derece);
	}
	for(i=derece-1 ; i>=0 ; i--){//denklemde derecesi haricindeki terimleri yazd�r�r�z ekrana
		if(denklem_katsayi[0][i]!=0){
			printf("+(%.2fx^%d)", denklem_katsayi[0][i], i);
		}
	}
	if(trigo_katsayi[0]!=0){  //sin un baskatsayisi 0 degilse sin�s � ekrana yazd�r
		printf("+(%.2fsin(%.2fx))", trigo_katsayi[0], trigo_ic_katsayi[0]);
	}
	if(trigo_katsayi[1]!=0){  //cosun  baskatsayisi 0 degilse cosu ekrana yazdir
		printf("+(%.2fcos(%.2fx))", trigo_katsayi[1], trigo_ic_katsayi[1]);
	}
	if(trigo_katsayi[2]!=0){ //tan�n baskatsayisi 0 degilse tanjant� ekrana yazdir
		printf("+(%.2ftan(%.2fx))", trigo_katsayi[2], trigo_ic_katsayi[2]);
	}
	if(trigo_katsayi[3]!=0){ //cotun baskatsayisi 0 degilse cotu ekrana yazd�r
		printf("+(%.2fcot(%.2fx))", trigo_katsayi[3], trigo_ic_katsayi[3]);
	}
	if(ln_katsayi!=0){   //lnx in katsayisi 0 degils lnx i ekrana yazdir
		printf("+(%.2fln(%.2fx))", ln_katsayi, ln_ic_katsayi);
	}
	if(e_katsayi!=0){   //e nin katsayisi 0 degilse e yi ekrana yazdir
		printf("+(%.2fe^(%.2fx))", e_katsayi, e_uskatsayi);
	}
}




double denklem_hesap(double x){
	
	int i;//degiskenleri tan�mlar�z
	double sum=0, x_sum=1;
	double sinx, cosx, tanx, cotx, lnx, ex;
	
	//trigonometrik de�erler
	sinx = trigo_katsayi[0]*sin(trigo_ic_katsayi[0]*x);  //sin�s degerini hesapla
	cosx = trigo_katsayi[1]*cos(trigo_ic_katsayi[1]*x);  //cosin�s degerini hesapla
	if(trigo_katsayi[2] == 0){//tanjant�n baskatsayisi 0 m� kontrol et
		tanx = 0; //baskatsayimiz 0 ise degerini 0 yap
	}else{
		tanx = trigo_katsayi[2]*tan(trigo_ic_katsayi[2]*x);//tanjant�n baskatsayisi 0 degilse tanjanti hesapla
	}
	if(trigo_katsayi[3] == 0){ //cotun baskatsayisi 0 mi kontrol et
		cotx = 0; //baskatsayi 0 ise degerini 0 yap
	}else{
		cotx = trigo_katsayi[3]/(tan(trigo_ic_katsayi[3]*x)); //eger cotun baskatsayisi 0 degilse  cotanjant�n degerini hesapla
	}
	
	//logaritmik de�er
	if(ln_katsayi == 0){//lnx in baskatsayisi 0 mi kontrol et
		lnx = 0;//eger baskatsayisi 0 ise lnx in degerini 0 yap
	}else{
		lnx = ln_katsayi*log(ln_ic_katsayi*x);//eger baskatsayisi 0 degilse lnx i hesapla
	}
	
	//�stel de�er
	if(e_katsayi == 0){//e nin baskatsayisinin 0 olup olmadigini kontrol et
		ex = 0;//eger baskatsayisi 0 ise degerini 0 yap otomatik olarak
	}else{
		ex = e_katsayi*pow(E, e_uskatsayi*x);//eger baskatsayimiz 0 degilse e nin degerini hesapla
	}
	
	//di�er de�i�kenler
	for(i=0 ; i<=derece ; i++){//polinom fonksiyonunu buluruz
		sum = sum + (denklem_katsayi[0][i]*x_sum);
		x_sum = x_sum * x;
	}
	
	//toplam
	sum = sum + sinx + cosx + tanx + cotx + lnx + ex;//denklemin son hali b�yledir
	return sum;
}




//Y�NTEMLER



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







