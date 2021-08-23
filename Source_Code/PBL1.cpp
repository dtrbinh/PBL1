#include<stdio.h>
#include<conio.h>

//Thu vien ho tro trinh bay
#include<windows.h>
#include<stdlib.h>
#include<math.h>

//-------------Phan khai bao dslk-------------
struct dslk{
	
char tenfile[100];
float dayA[100], dayB[100];
int n, k; //n la so phan tu lay di, k la tong so phan tu cua day
};
dslk data;
//------------Phan khai bao ham con-----------
void kiemtratenfile();            // | Day la |
void docdayso();                  // | buoc 1 |

void xoapt();                     // | Day la buoc 2|

void dathuc();                    // | "Day la ham con cho   |
void khoangnghiem();              // | qua trinh tinh buoc 3 |

int main();
void menu();
int chonchucnang();
void trunggian();
bool check(char s[]);

//-------------Than chuong trinh-------------

//Buoc 1
void kiemtratenfile(){
printf("\nNhap ten file: ");	
scanf("%s", &data.tenfile);
FILE *fp;
    fp = fopen(data.tenfile, "r");
    if (fp!=NULL){
		docdayso();
	    trunggian(); 
				}
    else
    {
		printf("\nKhong co file nay, hay nhap lai. ");
		Sleep(1000);
		system("cls");
		menu();
		kiemtratenfile();
	}
}

void docdayso(){
   
   FILE *fp;
   int i; //k là so pt cua day, n la so pt can lay
   data.k=0;
   float temp; //bien dem trung gian
    
    // doc so phan tu cua day
    fp = fopen(data.tenfile, "r");
    while (fscanf(fp, "%f", &temp) > 0) data.k++;
    fclose(fp);
    printf("\nSo phan tu cua day: %d", data.k);

    // doc noi dung day
    fp = fopen(data.tenfile, "r");
    printf("\n\nSo phan tu can lay (n>=7): ");
    scanf("%d",&data.n);
    if (data.n>data.k) printf("Vi n>k chi co the lay duoc %d phan tu.", data.k);
    if (data.n>=7)
            {
                                 	
            // doc noi dung day
            for (i = 0; i<data.n ; i++) 
			    {
                fscanf(fp,"%f\n", &data.dayA[i]);
                data.dayB[i] = data.dayA[i];
                }
    
            printf("\nTa co day so: ");
                                 
            for (i = 0; i < data.n; i++){
                printf("%.1f ", data.dayA[i]);
                }
            }
    else {
    	printf("\nSo phan tu phai lon hon hoac bang 7. Hay nhap lai.");
    	Sleep(1000);
    	getch();
    	menu();
    	docdayso();
        }
        fclose(fp);

}
//Ket thuc buoc 1



//Buoc 2
void xoapt(){  //Thuc hien xoa phan tu vi tri n/2 va ghi ra file RESULT1.OUT//
	int i,x;
	x=data.n/2;
	printf("\n\nThuc hien xoa phan tu thu %d cua day so.",x);
	printf("\n\nTa duoc day so moi: ");
	for( i=0; i<data.n-1; i++)
	     {
    if (i>=x-1){
       data.dayB[i] = data.dayB[i+1];
       printf("%.1f ", data.dayB[i]);
               }
                else printf("%.1f ", data.dayB[i]);
         };
         
         //delete dayB[n];
printf("\n\nKet qua da luu vao file RESULT1.OUT.\n");

//bat dau ghi kq
FILE *fp;
fp = fopen("RESULT1.OUT", "w");
for (i=0; i<data.n-1;i++){
	fprintf(fp,"%.2f ",data.dayB[i]);
}                        
fclose(fp); 
//ghi vao file xong
  
}
//Ket thuc buoc 2



//Buoc 3
void dathuc(){
	int j;
	printf("\n\nTa co da thuc: ");
	for(j=0;j<data.n-1;j++){
		if (j!=data.n-2) {
		printf("%.1fx^%d + ",data.dayB[j],j);
	} else printf("%.1fx^%d ",data.dayB[j],j);
		         }         
		         
	khoangnghiem();
	}
	
void khoangnghiem(){
	float a=0,b=0,c=0,fa=0,fb=0,fc=0;
	float e = 0.00001;
	
	char x[100],y[100]; //mang chua du lieu cho a, b chua kiem tra
	
	printf("\n\nNhap a sao cho f(a)<0 : ");
	scanf("%s",&x);
	printf("\nNhap b sao cho f(b)>0 : ");
	scanf("%s",&y);
	
	//kiemtra du lieu a vs b
	if (check(x)==true && check(y)==true) {
		
		a = atoi(x);
		b = atoi(y);
		
		for(int m = 0; m<data.n-1;m++)
		    {
			fa = fa + data.dayB[m]*pow(a,m);
			fb = fb + data.dayB[m]*pow(b,m);	
		    }
		printf("\nf(a) = %.2f", fa);
		printf("\nf(b) = %.2f", fb);
		
		if ((fa<0 && fb>0) || (fa>0 && fb<0)) {
		printf("\n\n	|       	a      	|       	b      	|		f(c)		|");	
		c=(a+b)/2;
	    for(int m = 0; m<data.n-1;m++) fc = fc + data.dayB[m]*pow(c,m);          
		while ((fabs(a-b)>e) && fc!=0)
		{
			c=(a+b)/2;
			fc=0;
			for(int m = 0; m<data.n-1;m++) fc = fc + data.dayB[m]*pow(c,m);
			if (fc>0) b=c; else a=c;
			
			//Hien các buoc tinh toan
			
			printf("\n	|	");
			printf("%f",a);
			printf("	|	");
			printf("%f",b);
			printf("	|	");
			printf("%f",fc);
			printf("		|");
		}
			
		//bat dau ghi kq
	    FILE *fp;
	    fp = fopen("RESULT2.txt", "a");
		fprintf(fp,"\nPhuong trinh co nghiem: %f.",c);                       
	    fclose(fp); 
	    
	    //ghi vao file xong	
			
		printf("\n\nPhuong trinh co nghiem: %f",c);
		printf("\n\nKet qua da ghi vao file RESULT2.OUT.");
		
		printf("\n\n1. Quay lai menu.");
		printf("\n2. Nhap khoang nghiem khac.");
		
		//Menu hoac tinh tiep
		char z;
		printf("\nLua chon: ");
		scanf("%s",&z);
		
		switch (z) {
			case '1': { 
				system("cls");
				main();
				break;
        	 		}
			case '2':{
				system("cls");
				dathuc();
				break;
					}
			default: {
			    system("cls");
				main();
				break;
					}
				};
		
		}
		else {
			printf("\na va b khong thoa man dieu kien. Moi nhap lai.");
			getch();
			system("cls");
			dathuc();
		}	
		
	}
	else {
	printf ("\nChu y: a va b phai la so. Hay nhap lai");
	getch();
	system("cls");
	dathuc();
}
	
}
//Ket thuc buoc 3


//Cac ham con ho tro
int main(){
    data.k=0;
    data.n=0;
	system("color f0");
	printf("\n____________________DO AN LAP TRINH TINH TOAN___________________");
	printf("\n|                                                              |");
	printf("\n|         Nhom sinh vien: DO TRAN BINH - PHAM SI CHIEN.        |");
	printf("\n|         Lop:            20T1.                                |");
	printf("\n|         GVHD:           DO THI TUYET HOA.                    |");
	printf("\n|                                                              |");
    printf("\n|         Truong Dai hoc Bach Khoa - Dai hoc Da Nang.          |");
	printf("\n|______________________________________________________________|");
	printf("\n\nNhan nut bat ki de bat dau.");
	getch();
	menu();
	chonchucnang();
	
}

void menu(){

    
	system("cls");
	
	printf("\n_____________________________________MENU___________________________________");
	printf("\n|                                                                           |");
	printf("\n|           1. Bai tap do an.                                               |");
	printf("\n|              a/Doc N phan tu so tu file DAYSO.IN.                         |");
	printf("\n|              b/Xoa phan tu vi tri N/2, luu ket qua vao file RESULT1.OUT.  |");
	printf("\n|              c/Tim nghiem phuong trinh bang phuong phap chia doi.         |");
	printf("\n|           2. Ket thuc tinh toan.                                          |");
	printf("\n|___________________________________________________________________________|");
	printf("\n");
}
	
int chonchucnang(){
    char q;
	printf("\nChon chuc nang: ");
	scanf("%s",&q);
	printf("\n---------------");
	
	switch (q) {
	case '1': { printf("\nBuoc 1: Nhap vao ten file can lay du lieu. ");
	          kiemtratenfile();
		      break;
        	 }
	
	case '2':{
		printf("\nXin cam on.");
		getch();
		return 0;
		break;
	}
	default: {
	    printf("\nKhong co chuc nang nay. Hay chon lai.");
	    Sleep(1000);
	    system("cls");
	    menu();
	    chonchucnang();
		break;
	}
	};
	
}

void trunggian(){
	printf("\n\nNhan de tiep tuc.");
	getch();
	system("cls");
	printf("\n\nBuoc 2: ");
	xoapt();
	printf("\n\nNhan de tiep tuc.");
	getch();
	system("cls");
	printf("\nBuoc 3: ");
	dathuc();
	printf("\n\nNhan de tiep tuc.");
	getch();
	system("cls");
	main();
}

bool check(char s[])
{
	for (int i = 0; i < strlen(s); i++)
	{
		if ((s[i] >= '0' && s[i] <= '9' ) || (s[i]='-'))
			return true;
		else return false;
	}
}
