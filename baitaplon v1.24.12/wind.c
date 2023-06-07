#include <stdio.h>
#include <math.h>
#define PI 3.1415926535

// Weather Wind
void wind  (int n, double nbc, double nbg, int ld, int dc, int dg, int bc, int bg, double nd){
	FILE *outfile = fopen("output.out", "w");

	int banh; // so banh tong cong
	int thua; // so banh thua
	bc = n / nbc;
	bg = (n - bc*nbc) / nbg;
	// do dai canh > duong kinh
	if (dc > dg){   
		bc = n / nbc;
		if (ld <= bc){		// la dong <= banh chung
			thua = bc - ld;
			bc = bc - thua;  // thay doi banh chung
			bg = 0;
			nd = n - bc*nbc; 

			// case 200 5 6 5 Wind dung		
			// case 337 6 4 9 Wind dung	
		}
		else if (ld > bc) {	// la dong > banh chung
			thua = ld - bc;
			bg = (n - bc*nbc) / nbg;
			if(thua < bc)
				bg = bg - thua;
			nd = n - bc*nbc - bg*nbg;
			
			// case 485 9 5 7 Wind dung	
		}		
		else {
			bg = (n - bc*nbc) / nbg;
			nd = n - bc*nbc - bg*nbg;
			
		}
	}
	// do dai canh < duong kinh	
	else if (dc < dg){	
		bg = n / nbg;
		if (ld <= bg){		// la dong <= banh giay
			thua = bg - ld;
			bg = bg - thua;  // thay doi banh chung
			bc = 0;
			nd = n - bg*nbg;  
		
			// case 200 5 6 5 Wind dung	
		}
		else if ( (n - (bc-1)*nbc ) < nbg){  // uu tien nep du toi thieu
			bg = (n - bc*nbc) / nbg;
			nd = n - bc*nbc - bg*nbg; 

			// case 152 5 6 20 Wind dung	
			}
		else if ((n - (bc+1)*nbc) < nbg){
			bc = bc - 1;
			bg = (n - bc*nbc) / nbg;
			nd = n - bc*nbc - bg*nbg;
			
			// case 155 5 6 20 Wind dung	
		}
	
		else {
			bc = (n - bg*nbg) / nbc;
			nd = n - bc*nbc - bg*nbg;
			
		}
		
	}
	
	// xuat file
//	printf("%lf\n",nd);
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
