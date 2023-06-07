#include <stdio.h>
#include <math.h>
#define PI 3.1415926535

// Weather Wind
void wind  (int n, double nbc, double nbg, int ld, int dc, int dg, int bc, int bg, double nd){
	FILE *outfile = fopen("output.out", "w");

	if (dc <=0)
		bc == 0;
	else bc = n / (dc*dc);
	
	if (dg<=0)
		bg == 0;
	else bg = n-(bc*dc*dc) / (dg*dg*PI/4);
	
	if (ld<=bc){
		bg = 0;
		bc=ld;
	}
	else{
		if(ld < (bc + bg))
			bg = ld - bc;
	}
	
	nd = n - bc*nbc - bg*nbg;
	// xuat file
	printf("%d %d %.3lf", bc, bg, nd);
	fprintf(outfile, "%d %d %.3lf", bc, bg, nd);
	fclose(outfile);
		
}// ket thuc Weather Wind

int main() {
	FILE *infile, *outfile; // bien nhap - xuat file
	
	// nep, do dai canh, duong kinh, la dong, thoi tiet
	int n, dc, dg, ld;
	char w[10];
	
	// ten input - output
	infile = fopen("input.inp", "r");
	outfile = fopen("output.out", "w");
	
	// nhap file
	fscanf(infile, "%d %d %d %d %s", &n, &dc, &dg, &ld, &w);
	fclose(infile);
	
	// sai du lieu
	if (infile == NULL || n >=1000 || n < 0 || dc < 0 || dg < 0 || ld > 300 || ld < 1){
		fprintf(outfile, "-1 -1 %d", n);
		return 0;
	}
	
	// banh chung, banh giay, nep du
	int bc, bg;
	double nd;
	
	// so banh can dung de xai la dong, so nep xai banh chung, banh giay
	int banh;
	double nbc, nbg;
	
	// cong thuc tinh so nep can dung cua banh chung, banh giay
	nbc = pow(dc, 2);
	nbg = (pow(dg, 2)*PI) / 4;
	
	// so luong banh chung, banh giay du kien
	bc = n / nbc;
	bg = (n - bc*nbc) / nbg;
	nd = n - bc*nbc - bg*nbg;
	
	// Weather Wind
	if (strcmp(w,"Wind") == 0)
		wind (n, nbc, nbg, ld, dc, dg, bc, bg, nd); // theo thu tu nep, nep banh chung, nep banh giay, la dong
		

	// Sai thoi tiet
	else {
		fprintf(outfile, "-1 -1 %d", n);
		return 0;
	}
	

	
}// ket thuc main
