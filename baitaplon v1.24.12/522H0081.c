#include <stdio.h>
#include <math.h>
#define PI 3.1415926535

// Weather Wind
void wind  (double n, double nbc, double nbg, double ld, int dc, int dg, int bc, int bg, double nd){
	FILE *outfile = fopen("output.out", "w");

	int banh; // so banh tong cong
	int thua; // so banh thua
	bc = n / nbc;
	bg = (n - bc*nbc) / nbg;
	// do dai canh >= duong kinh
	if (dc >= dg){   
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
//	printf("\nnd = %lf\n",nd);
//	printf("%d %d %.3lf", bc, bg, nd);
	fprintf(outfile, "%d %d %.3lf", bc, bg, nd);
	fclose(outfile);
		
}// ket thuc Weather Wind

// Weather Rain
void rain  (double n, double nbc, double nbg, double ld, int dc, int dg, int bc, int bg, double nd){
	FILE *outfile = fopen("output.out", "w");
	int sobanh; 	// so luong banh cho ca hai loai
	sobanh = n / (nbc+nbg);
	bc = sobanh;
	if  ( dc == 0) bc = 0;
	bg = sobanh;
	if  ( dg == 0) bg = 0;
	nd = n - bc*nbc - bg*nbg;
	
	// do dai canh > duong kinh
	if ( dc > dg){
		// banh chung truoc, banh giay sau
		while (nd > nbc){	// nep du > so nep lam banh chung
			if ( dc == 0) {
				bc = 0;
				break;
			}
		
			bc = bc + 1;
			nd = n - bc*nbc - bg*nbg; // thay doi banh giay
		}
		while (nd > nbg){	// nep du > so nep lam banh giay
			if ( dg == 0) {
				bg = 0;
				break;
			}
			bg = bg + 1;
			nd = n - bc*nbc - bg*nbg; // thay doi banh giay
		}
	}
	
	// do dai canh < duong kinh
	else if (dc < dg){
		
		// banh giay truoc, banh chung sau
				while (nd > nbg){	// nep du > so nep lam banh giay
			if ( dg == 0) {
				bg = 0;
				break;
			}
			bg = bg + 1;
			nd = n - bc*nbc - bg*nbg; // thay doi banh giay
		}
		while (nd > nbc){	// nep du > so nep lam banh chung
			if ( dc == 0) {
				bc = 0;
				break;
			}
		
			bc = bc + 1;
			nd = n - bc*nbc - bg*nbg; // thay doi banh giay
		}
	}
	
	while (ld < ( bc+bg)){
		if  ( bc > 0) bc --;  // banh chung lon hon 0 
		if(ld == (bc+bg)) break;
		
		if ( bg > 0) bg --;	 // banh giay lon hon 0 
		if(ld == (bc+bg)) break;
	}	
	nd = n - bc*nbc - bg*nbg;
		
	// xuat file
//	printf("%d %d %.3lf", bc, bg, nd);
	fprintf(outfile, "%d %d %.3lf", bc, bg, nd);
	fclose(outfile);
	
} // ket thuc Weather Rain

// Weather Cloud
void cloud (double n, double nbc, double nbg, double ld, int dc, int dg, int bc, int bg, double nd){
	FILE *outfile = fopen("output.out", "w");		
	
	// so nep va la dong la so ban be
	if ( (n == 220 && ld == 284) || (n == 284 && ld == 220) ){
		bc = 0; 
		bg = 0;
		nd = n;
	}
		
	// lam nhieu banh giay
	else{
		int banh; // so banh tong cong
		int thua; // so banh thua
		bg = n / nbg;
		bc = (n - bg*nbg) / nbc;
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
		// do dai canh <= duong kinh	
		else if (dc <= dg){	
			bg = n / nbg;
			if (ld <= bg){		// la dong <= banh giay
				thua = bg - ld;
				bg = bg - thua;  // thay doi banh chung
				bc = 0;
				nd = n - bg*nbg;  
		
				// case 200 5 6 5 Wind dung	
			}	
			
			// (...)
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
	}
	// xuat file
//	printf("%d %d %.3lf", bc, bg, nd);
	fprintf(outfile, "%d %d %.3lf", bc, bg, nd);
	fclose(outfile);
} // ket thuc Weather Cloud

// Weather Sun
void sun   (double n, double nbc, double nbg, double ld, int dc, int dg, int bc, int bg, double nd){
	FILE *outfile = fopen("output.out", "w");
	int G; 		// phan du do dai canh (dc) banh chung
	int H;		// phan du la dong (ld) 
	int x;		//  phan tram tang them nep va giam la dong 
	int hieu;  // goi hieu = G - H
		
	G = dc % 6;
	H = (int)ld % 5;
	hieu = G - H; 
		
	if 		(hieu == 0)					x = 5;			
	else if (hieu == 1) 				x = 7;	
	else if (hieu == 2 || hieu == -4)	x = 10;		
	else if (hieu == 3 || hieu == -3)	x = 12;		
	else if (hieu == 4 || hieu == -2)	x = 15;		
	else if (hieu == 5 || hieu == -1)	x = 20;
			
	// thay doi nep, la dong
	n = n + (n * x/100) ;
	ld = ld - (ld * x/100);
	
//	printf("n = %lf", n);
//	printf("\nld = %lf \n", ld);
		
	// thay doi thoi tiet
	int weather;
	weather = (dc+dg)%3;
		
	//Rain
	if (weather == 0)
		rain (n, nbc, nbg, ld, dc, dg, bc, bg, nd);
			
	// Wind
	else if (weather == 1)
		wind (n, nbc, nbg, ld, dc, dg, bc, bg, nd);
		
	// Cloud
	else if (weather == 2)
		cloud(n, nbc, nbg, ld, dc, dg, bc, bg, nd);

//	printf("\nx = %d", x);
//	printf("\nweather = %d", weather);
	} // ket thuc Weather Sun

// Weather Fog
void fog   (double n, double nbc, double nbg, double ld, int dc, int dg, int bc, int bg, double nd){	
	FILE *outfile = fopen("output.out", "w");
	bc = dc; 	// banh chung = do dai canh
	bg = dg; 	// banh giay = duong kinh
	nd = n;

	// xuat file
//	printf("%d %d %.3lf", bc, bg, nd);
	fprintf(outfile, "%d %d %.3lf", bc, bg, nd);
	fclose(outfile);
}

// Main
int main() {
	FILE *infile, *outfile; // bien nhap - xuat file
	
	// nep, do dai canh, duong kinh, la dong, thoi tiet
	int dc, dg;
	double n, ld;
	char w[10];
	
	// ten input - output
	infile = fopen("input.inp", "r");
	outfile = fopen("output.out", "w");
	
	// nhap file
	fscanf(infile, "%lf %d %d %lf %s", &n, &dc, &dg, &ld, &w);
	fclose(infile);
	
	// sai du lieu
	if (infile == NULL || n >=1000 || n < 0 || ld > 300 || ld < 1){
		fprintf(outfile, "-1 -1 %d", n);
		return 0;
	}
	
	// banh chung, banh giay, nep du
	int bc, bg;
	double nd;
	
	// so banh can dung de xai la dong, so nep xai banh chung, banh giay
	int banh;
	double nbc, nbg;
	
	// chinh sua dc, dg khi nhap so am
	if(dc < 0) dc = 0;
	if(dg < 0) dg = 0;
	
	// cong thuc tinh so nep can dung cua banh chung, banh giay
	nbc = pow(dc, 2);
	nbg = (pow(dg, 2)*PI) / 4;
	
	// Weather Wind
	if (strcmp(w,"Wind") == 0)
		wind (n, nbc, nbg, ld, dc, dg, bc, bg, nd); // theo thu tu nep, nep banh chung, nep banh giay, la dong
	
	// Weather Rain
	else if (strcmp(w,"Rain") == 0)		
		rain (n, nbc, nbg, ld, dc, dg, bc, bg, nd);
		
	// Weather Sun
	else if (strcmp(w,"Sun") == 0)
		sun (n, nbc, nbg, ld, dc, dg, bc, bg, nd);	
	
	// Weather Fog
	else if (strcmp(w,"Fog") == 0)
		fog (n, nbc, nbg, ld, dc, dg, bc, bg, nd);	
		
	// Weather Cloud
	else if (strcmp(w,"Cloud") == 0)
		cloud (n, nbc, nbg, ld, dc, dg, bc, bg, nd);	

	// Sai thoi tiet
	else {
		fprintf(outfile, "-1 -1 %d", n);
		return 0;
	}
	
}// ket thuc main
