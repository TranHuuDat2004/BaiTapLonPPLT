#include <stdio.h>
#include <string.h>
#include <stdbool.h>
const double PI = 3.1415926535;
typedef struct INPUT
{
	int n, ld;
	bool dc,dg;
	char w[20];
}Input;

typedef struct OUTPUT
{
	int bc,bg;
	double nd;
}Output;

Input docDuLieuDauVao()
{
	Input ip;
	FILE* f=fopen("input.inp","r");
	fscanf(f,"%d%d%d%d%s",&ip.n,&ip.dc,&ip.dg,&ip.ld,&ip.w);
	fclose(f);
	return ip;
}

Output taoKetQua()
{
	Output op;
	op.bc=0;
	op.bg=0;
	op.nd=0;
	return op;
}

int kiemTraDuLieuDauVao(Input ip)
{
	if(ip.n>=1000||ip.n<0||ip.ld>300||ip.ld<1)
		return 0;
	if( ip.dc>0 || ip.dg>0 )
		return 1;
	if(strcmp(ip.w,"Rain")!=0&&strcmp(ip.w,"Sun")!=0&&strcmp(ip.w,"Cloud")!=0&&strcmp(ip.w,"Fog")!=0&&strcmp(ip.w,"Wind")!=0)
		return 0;	
	return 1;
}

double tinhSoNepLam1BanhChung(Input ip)
{
	return ip.dc*ip.dc;
}

double tinhSoNepLam1BanhGiay(Input ip)
{
	return ((double)(ip.dg*ip.dg)*PI)/4;
}

Output Rain(Input ip,Output op,double soNepLam1BanhChung,double soNepLam1BanhGiay)
{
	op.bc=(int)(op.nd/(soNepLam1BanhChung+soNepLam1BanhGiay));
	if(op.bc>ip.ld/2)
		op.bc=ip.ld/2;
	ip.ld-=op.bc*2;
	op.bg=op.bc;
	op.nd-=op.bc*(soNepLam1BanhChung+soNepLam1BanhGiay);
	
	if(soNepLam1BanhChung>soNepLam1BanhGiay)
	{
		int soBanhChungThem=(int)(op.nd/soNepLam1BanhChung);
		if(soBanhChungThem>ip.ld)
			soBanhChungThem=ip.ld;
		ip.ld-=soBanhChungThem;
		op.nd-=soBanhChungThem*soNepLam1BanhChung;
		op.bc+=soBanhChungThem;
	
		int soBanhGiayThem=(int)(op.nd/soNepLam1BanhGiay);
		if(soBanhGiayThem>ip.ld)
			soBanhGiayThem=ip.ld;
		ip.ld-=soBanhGiayThem;
		op.nd-=soBanhGiayThem*soNepLam1BanhGiay;
		op.bg+=soBanhGiayThem;
	}
	else 
	{
		int soBanhGiayThem=(int)(op.nd/soNepLam1BanhGiay);
		if(soBanhGiayThem>ip.ld)
			soBanhGiayThem=ip.ld;
		ip.ld-=soBanhGiayThem;
		op.nd-=soBanhGiayThem*soNepLam1BanhGiay;
		op.bg+=soBanhGiayThem;	

		int soBanhChungThem=(int)(op.nd/soNepLam1BanhChung);
		if(soBanhChungThem>ip.ld)
			soBanhChungThem=ip.ld;
		ip.ld-=soBanhChungThem;
		op.nd-=soBanhChungThem*soNepLam1BanhChung;
		op.bc+=soBanhChungThem;
	}
	return op;
}

Output Wind(Input ip,Output op,double soNepLam1BanhChung,double soNepLam1BanhGiay)
{
	op.bc=(int)(op.nd/soNepLam1BanhChung);
	if(op.bc>ip.ld)
		op.bc=ip.ld;
	ip.ld-=op.bc;
	op.nd-=op.bc*soNepLam1BanhChung;
	
	op.bg=(int)(op.nd/soNepLam1BanhGiay);
	if(op.bg>ip.ld)
		op.bg=ip.ld;
	ip.ld-=op.bg;
	op.nd-=op.bg*soNepLam1BanhGiay;
	
	return op;
}

long tinhTongUocThat(int x)
{
	long tong=0;
	int i=0;
	for(i=1;i<x;i++)
		if(x%i==0)
			tong+=i;
	return tong; 
}

int kiemTraSoBanBe(int x,int y)
{
	if(tinhTongUocThat(x)==y&&tinhTongUocThat(y)==x)
		return 1;
	return 0;
}

Output Cloud(Input ip,Output op,double soNepLam1BanhChung,double soNepLam1BanhGiay)
{
	if(kiemTraSoBanBe(ip.n,ip.ld)==1)
	{
		return op;
	}
	
	op.bg=(int)(op.nd/soNepLam1BanhGiay);
	if(op.bg>ip.ld)
		op.bg=ip.ld;
	ip.ld-=op.bg;
	op.nd-=op.bg*soNepLam1BanhGiay;	

	op.bc=(int)(op.nd/soNepLam1BanhChung);
	if(op.bc>ip.ld)
		op.bc=ip.ld;
	ip.ld-=op.bc;
	op.nd-=op.bc*soNepLam1BanhChung;
	
	return op;
}

Input CapnhatSun(Input ip)
{
	int H=ip.ld%5,G=ip.dc%6;
	int mangGiaTriX[6]={5,7,10,12,15,20};
	int viTri=G;
	int i;
	for(i=1;i<=H;i++)
	{
		viTri--;
		if(viTri==-1)
			viTri=5;
	}
	int giaTriX=mangGiaTriX[viTri];
	ip.ld-=giaTriX;
	ip.n=(ip.n*(giaTriX+100))/100;
	return ip;
}

Output Sun(Input ip,Output op,double soNepLam1BanhChung,double soNepLam1BanhGiay)
{
	ip=CapnhatSun(ip);
	op.nd=ip.n;
	int truonghop=(ip.dc+ip.dg)%3;
	if(truonghop==0)
	{	
		strcpy(ip.w,"Rain");
		return Rain(ip,op,soNepLam1BanhChung,soNepLam1BanhGiay);
	}
	if(truonghop==1)
	{	
		strcpy(ip.w,"Wind");
		return Wind(ip,op,soNepLam1BanhChung,soNepLam1BanhGiay);
	}
	if(truonghop==2)
	{
	strcpy(ip.w,"Cloud");
	return Cloud(ip,op,soNepLam1BanhChung,soNepLam1BanhGiay);
	}
}

Output Fog(Input ip,Output op,double soNepLam1BanhChung,double soNepLam1BanhGiay)
{
	op.bc=ip.dc;
	op.bg=ip.dg;
	return op;
}

Output xuLyDuLieu(Input ip)
{
	Output op=taoKetQua();

	if(kiemTraDuLieuDauVao(ip)==0)
	{
		op.bc=op.bg=-1;
		op.nd=ip.n;
		return op;
	}

	op.nd=ip.n;
	double soNepLam1BanhChung=tinhSoNepLam1BanhChung(ip);
	double soNepLam1BanhGiay=tinhSoNepLam1BanhGiay(ip);
	if(strcmp(ip.w,"Wind")==0)
		return Wind(ip,op,soNepLam1BanhChung,soNepLam1BanhGiay);
	if(strcmp(ip.w,"Rain")==0)
		return Rain(ip,op,soNepLam1BanhChung,soNepLam1BanhGiay);
	if(strcmp(ip.w,"Sun")==0)
		return Sun(ip,op,soNepLam1BanhChung,soNepLam1BanhGiay);
	if(strcmp(ip.w,"Fog")==0)
		return Fog(ip,op,soNepLam1BanhChung,soNepLam1BanhGiay);
	return Cloud(ip,op,soNepLam1BanhChung,soNepLam1BanhGiay);
}

void xuatKetQuaDauRa(Output op)
{
	FILE* f=fopen("output.out","w");
	fprintf(f,"%d %d %0.3lf",op.bc,op.bg,op.nd);
	fclose(f);
}

int main()
{
	
	Input ip=docDuLieuDauVao();
	Output op=xuLyDuLieu(ip);
	xuatKetQuaDauRa(op);
	return 0;
}
