#include <stdio.h>
#include <math.h>

#define SIZE 100

double denklem_alma();
double turev_alma();
double denklem_hesap(double);
double turev_hesap(double);




//yöntem fonksiyonlarý

double newton_r();

//degiskenleri tanýmlarýz
int i, j, cevap;
double temp;

int derece;
double denklem_katsayi[2][SIZE], trigo_katsayi[2][4], trigo_ic_katsayi[4], ln_katsayi, ln_ic_katsayi;

//basit iterasyon için gerekli deðiþkenler
int derece_2, turev_derece_2;
double denklem_katsayi_2, turev_katsayi_2;

//denklem_katsayi[0][x] = denklem deðiþkenlerinin katsayýsý
//denklem_katsayi[1][x] = türev denkleminin deðiþkenlerinin katsayýsý

//turev_katsayi[0][x] = trigonometrik deðiþkenlerinin katsayýsý
//turev_katsayi[1][x] = trigonometrik deðiþkenlerinin türevlerinin katsayýsý

//trigo_katsayi[0][x]: trigonometrik deðiþkenlerin katsayýlarý
//[  0  ,  1  ,  2  ,  3  ]
//[ sin , cos , tan , cot ]
	
//trigo_katsayi[1][x]: trigonometrik deðiþkenlerin katsayýlarý
//[  0  ,  1   ,  2          ,  3           ]
//[ cos , -sin , 1/(cos*cos) , -1/(sin*sin) ]

int main(){
		
	
		newton_r();

	return 0;
}

//Fonksiyonlar buradan sonra.

double denklem_alma(){
	
	//üslü ifadeler
	printf("\n\nDenkleminizin derecesini giriniz: ");//polinomun en buyuk derecesini giriniz.
	scanf("%d", &derece);
	while(derece < 0){     //denklemimizin derecesi negatif olamaz eger kullanýcý negatif sayi girerse kullanýcýdan bi daha bir sayi istenir 
		printf("\n(!) Denkleminizin derecesi negatif olamaz.");
		printf("\nLutfen gecerli bir tamsayi degeri giriniz: ");
		scanf("%d", &derece);
	}
	for(i=0 ; i<=derece ; i++){    //denklemdeki xli ifadelerin sýrasýyla baskatsayisini kullanýcýdan alýrýz ve bunlarý bir matris de tutariz
		printf("x^%d degiskeninin katsayisi: ", i);
		scanf("%lf", &denklem_katsayi[0][i]);
	}
	
	//trigonometrik ifadeler
	printf("\nTrigonometrik degisken var mi?");//trigonometrik ifade olup olmadýgýný kullanýcýdan alýrýz
	printf("\n1) Var.   2) Yok.\n");
	scanf("%d", &cevap);
	
	if(cevap==1){//eger cevabimiz olumlu ise kullanýcýdan trigonometrik ifadelerin katsayilarini aliriz
		printf("\nTrigonometrik degiskenlerin katsayilarini giriniz.");
		//sin
		printf("\n\nAsin(Bx)");
		printf("\nA katsayisini giriniz: ");
		scanf("%lf", &trigo_katsayi[0][0]);//kullancýdan sinüslü ifadenin baskatsayisini aliriz ve bunu trigo_katsayi[0][0] da tutariz
		if(trigo_katsayi[0][0] != 0){ //kullanýcý eger baskatsayiyi 0 girmemisse bu sefer iç katsayiyi alýrýz
			printf("B katsayisini giriniz: ");
			scanf("%lf", &trigo_ic_katsayi[0]);
		}
		printf("-----");
		//cos
		printf("\nAcos(Bx)");//kullanýcýdan coslu ifadenin baskatsayisini aliriz ve bunu trigo_katsayi[0][1] de tutariz
		printf("\nA katsayisini giriniz: ");
		scanf("%lf", &trigo_katsayi[0][1]);
		if(trigo_katsayi[0][1] != 0){  //eger baskatsayisi 0 dan farklýysa cosinüsün iç katsayisini giriniz
			printf("B katsayisini giriniz: ");
			scanf("%lf", &trigo_ic_katsayi[1]);
		}
		printf("-----");
		//tan
		printf("\nAtan(Bx)");//kullanýcýdan tanjantlý ifadenin baskatsayisini alýrýz ve bunu trigo_katsayi[0][2] de tutariz
		printf("\nA katsayisini giriniz: ");
		scanf("%lf", &trigo_katsayi[0][2]);
		if(trigo_katsayi[0][2] != 0){//eger baskatsayimiz 0 dan farklýysa bu sefer iç katsayisini giriniz
			printf("B katsayisini giriniz: ");
			scanf("%lf", &trigo_ic_katsayi[2]);
		}
		printf("-----");
		//cot
		printf("\nAcot(Bx)");//kullanýcýdan cot lu ifaden baskatsayisini alýrýz ve bunu trigo_katsayi[0][3]de tutariz
		printf("\nA katsayisini giriniz: ");
		scanf("%lf", &trigo_katsayi[0][3]);
		if(trigo_katsayi[0][3] != 0){//eger baskatsayi sýfýrdan farklýysa iç katsayisini giriniz
			printf("B katsayisini giriniz: ");
			scanf("%lf", &trigo_ic_katsayi[3]);
		}
	}else{//eger trigonometrik ifade yoksa butun trigonometrik ifadelerin baskatsayisini 0 a ceviricez
		for(i=0 ; i<4 ; i++){
			trigo_katsayi[0][i]=0;
			trigo_katsayi[1][i]=0;
		}
	}
	
	//logaritmik ifadeler
	printf("\nlnx degiskeni var mi?");//kullanýcýya lnx degiskeni olup olmadýgýný sor
	printf("\n1) Var.   2) Yok.\n");
	scanf("%d", &cevap);
	
	if(cevap==1){
		printf("\n(A)ln(Bx)");//eger ln li bir ifade varsa kullanýcýdan baskatsayisini al
		printf("\nA katsayisini giriniz: ");
		scanf("%lf", &ln_katsayi);//baskatsayisini aldýktan sonra ic katsayisini al
		printf("B katsayisini giriniz: ");
		scanf("%lf", &ln_ic_katsayi);
	}else{
		ln_katsayi=0;//eger ln li ifademiz yoksa katsayilari 0 lýyoruz
		ln_ic_katsayi=1;
	}
	
	//denklemi yazdýrma
	printf("\nDenkleminiz:\n");
	
	for(i=derece ; i>0 ; i--){
		if(denklem_katsayi[0][i]!=0){
			printf("(%.2fx^%d)+", denklem_katsayi[0][i], i);
		}
	}
	if(denklem_katsayi[0][0]!=0){
		printf("(%.2f)", denklem_katsayi[0][0]);
	}
	if(trigo_katsayi[0][0]!=0){//eger sin li ifademize katsayi atanmýssa bunu yazdýr
		printf("+(%.2fsin(%.2fx))", trigo_katsayi[0][0], trigo_ic_katsayi[0]);
	}
	if(trigo_katsayi[0][1]!=0){//eger coslu ifademize katsayi atanmýssa bunu yazdir
		printf("+(%.2fcos(%.2fx))", trigo_katsayi[0][1], trigo_ic_katsayi[1]);
	}
	if(trigo_katsayi[0][2]!=0){//eger tanlý ifadeye katsayi atanmýssa bunu yazdir
		printf("+(%.2ftan(%.2fx))", trigo_katsayi[0][2], trigo_ic_katsayi[2]);
	}
	if(trigo_katsayi[0][3]!=0){//eger cot lu ifadeye katsayi atanmýssa bunu yazdir
		printf("+(%.2fcot(%.2fx))", trigo_katsayi[0][3], trigo_ic_katsayi[3]);
	}
	if(ln_katsayi!=0){//eger lnx imizin katsayisi 0 dan farklýysa bunu yazdýr
		printf("+(%.2fln(%.2fx))", ln_katsayi, ln_ic_katsayi);
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
	//ln_katsayi*ln_ic_katsayi ayný zamanda türevdeki 1/x ifadesinin katsayýsý
}

double denklem_hesap(double x){
	//degiskenleri tanýmladýk
	double sum=0, x_sum=1;
	double sinx, cosx, tanx, cotx, lnx;
	
	//trigonometrik deðerler
	sinx = trigo_katsayi[0][0]*sin(trigo_ic_katsayi[0]*x);//sin li ifadeyi yazdýrdýk
	cosx = trigo_katsayi[0][1]*cos(trigo_ic_katsayi[1]*x);//cos lu ifadeyi yazdýrdýk
	if(trigo_katsayi[0][2] == 0){//tan lý ifademizin baskatsayisi 0 esit olup olmadýgýna bak eger 0 esitse tanjantý 0 a esitle
		tanx = 0;
	}else{
		tanx = trigo_katsayi[0][2]*tan(trigo_ic_katsayi[2]*x);//eger 0 a esit degilse tanlý ifadeyi yazdýr
	}
	if(trigo_katsayi[0][3] == 0){//cot lu ifademizin baskatsayisinin 0 olup olmadýgýný kontrol et eger 0 a esitse cot u 0'a esitle
		cotx = 0;
	}else{
		cotx = trigo_katsayi[0][3]*1/(tan(trigo_ic_katsayi[3]*x));//eger 0 a esit degilse cotlu ifademizi yazdir
	}
	
	//logaritmik deðerler
	if(ln_katsayi == 0){//lnx li ifademizin baskatsayisinin 0 olup olmadýgýný kontrol et eger 0 a esitse lnx i 0'a esitle
		lnx = 0;
	}else{
		lnx = ln_katsayi*log(ln_ic_katsayi*x);//eger 0 a esit degilse lnx li ifademizi yazdir
	}
	
	//diðer deðiþkenler
	for(i=0 ; i<=derece ; i++){//polinom fonksiyonunu buluruz
		sum = sum + (denklem_katsayi[0][i]*x_sum);
		x_sum = x_sum * x;
	}
	
	//toplam
	sum = sum + sinx + cosx + tanx + cotx + lnx;//buldugumuz degerleri yazdir
	printf("\nsum = %f\n",sum);
	return sum;
}

double turev_hesap(double x){
	
	double sum=0, x_sum=1;
	double sinx_t, cosx_t, tanx_t, cotx_t, lnx_t;
	
	//trigonometrik deðerler
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
	
	//logaritmik deðerler
	if(ln_katsayi == 0){
		lnx_t = 0;
	}else{
		lnx_t = (ln_katsayi*ln_ic_katsayi)/x;
	}
	
	//diðer deðiþkenler
	for(i=0 ; i<=derece-1 ; i++){
		sum = sum + (denklem_katsayi[1][i]*x_sum);
		x_sum = x_sum * x;
	}
	
	//toplam
	sum = sum + sinx_t + cosx_t + tanx_t + cotx_t + lnx_t;
	return sum;
}




//YÖNTEMLER





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


//kod calýsýyor
































