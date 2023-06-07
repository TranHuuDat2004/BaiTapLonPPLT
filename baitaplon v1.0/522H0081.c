#include <stdio.h>
#include <math.h>
#define PI 3.1415926535

int main() {
	FILE *infile, *outfile;
	
	// nep, do dai canh, duong kinh, la dong, thoi tiet
	int n, dc, dg, ld;
	char w[10];
	
	// ten input - output
	infile = fopen("input.inp", "r");
	outfile = fopen("output.out", "w");
	
	// nhap file
	fscanf(infile, "%d %d %d %d %s", &n, &dc, &dg, &ld, &w);
	fclose(infile);
	
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
	
	nbc = pow(dc, 2);
	nbg = (pow(dg, 2)*PI) / 4;
	
	// Weather Wind
	if (strcmp(w,"Wind") == 0){	
		bc = n / nbc;
		if (ld < bc){
			int thua; // so banh thua
			thua = bc - ld;
			bc = bc - thua;
			bg = 0;
			nd = n - bc*nbc;
		}
		
		else{
			bg = (n - bc*nbc) / nbg;
			banh = bc + bg; 
			nd = n - bc*nbc - bg*nbg;
		}
		
	}// ket thuc Weather Wind
	
	// Weather Rain
	else if (strcmp(w,"Rain") == 0){
		int sobanh; 	// so luong banh cho ca hai loai
		sobanh = n / (nbc+nbg);
		bc = sobanh;
		bg = sobanh;
		nd = n - bc*nbc - bg*nbg;
	} // ket thuc Weather Rain
	
	// Weather Sun
	else if (strcmp(w,"Sun") == 0){
		int G; 		// phan du do dai canh (dc) banh chung
		int H;		// phan du la dong (ld) 
		int x;		//  phan tram tang them nep va giam la dong 
		int hieu;  // goi hieu = G - H
		
		G = dc % 6;
		H = ld % 5;
		hieu = G - H; 
		
		if (hieu == 0){
			x = 5;
		}
		
		else if (hieu == 1){
			x = 7;
		}
		
		else if (hieu == 2 || hieu == -4){
			x = 10;
		}
		
		else if (hieu == 3 || hieu == -3){
			x = 12;
		}
		
		else if (hieu == 4 || hieu == -2){
			x = 15;
		}
		
		else if (hieu == 5 || hieu == -1){
			x = 20;
		}
		
		// thay doi nep, la dong
		n = n + (n * x/100) ;
		ld = ld - (ld * x/100);
		
		// thay doi thoi tiet
		int weather;
		weather = (dc+dg)%3;
		
		//Rain
		if (weather == 0){
			int sobanh; 	// so luong banh cho ca hai loai
			sobanh = n / (nbc+nbg);
			bc = sobanh;
			bg = sobanh;
			nd = n - bc*nbc - bg*nbg;
		}// ket thuc Rain phu
		
		// Wind
		else if (weather == 1){	
			bc = n / nbc;
			if (ld < bc){
				int thua; // so banh thua
				thua = bc - ld;
				bc = bc - thua;
				bg = 0;
				nd = n - bc*nbc;
			}
			
			else{
				bg = (n - bc*nbc) / nbg;
				banh = bc + bg; 
				
			}
			nd = n - bc*nbc - bg*nbg;
		}// ket thuc Wind phu
		
		// Cloud
		else if (weather == 2){
			
			// so nep va la dong la so ban be
			if ( (n == 220 && ld == 284) || (n == 284 && ld == 220) ){
				bc = 0; 
				bg = 0;
				nd = n;
				}
		
			// lam nhieu banh giay
			else{
				bg = n / nbg;
				if (ld < bg){
					int thua; // so banh thua
					thua = bg - ld;
					bg = bg - thua;
					bc = 0;
					nd = n - bg*nbg;
				}
				else{
					bc = (n - bg*nbg) / nbc;
					banh = bc + bg; 
					nd = n - bc*nbc - bg*nbg;	
				}			
			}	
		}// ket thuc Cloud phu
		
	} // ket thuc Weather Sun
	
	// Weather Fog
	else if (strcmp(w,"Fog") == 0){
		bc = dc; 	// banh chung = do dai canh
		bg = dg; 	// banh giay = duong kinh
		nd = n;
	}
		
	// Weather Cloud
	else if (strcmp(w,"Cloud") == 0){
		
		// so nep va la dong la so ban be
		if ( (n == 220 && ld == 284) || (n == 284 && ld == 220) ){
			bc = 0; 
			bg = 0;
			nd = n;
			}
		
		// lam nhieu banh giay
		else{
			bg = n / nbg;
			if (ld < bg){
				int thua; // so banh thua
				thua = bg - ld;
				bg = bg - thua;
				bc = 0;
				nd = n - bg*nbg;
			}
			else{
			bc = (n - bg*nbg) / nbc;
			banh = bc + bg; 
			nd = n - bc*nbc - bg*nbg;	
			}			
		}
	} // ket thuc Weather Cloud

	// Sai thoi tiet
	else {
		fprintf(outfile, "-1 -1 %d", n);
		return 0;
	}


	// xuat file
	fprintf(outfile, "%d %d %.3lf", bc, bg, nd);
	fclose(outfile);
	
	return 0;

}
