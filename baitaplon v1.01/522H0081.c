/*************************************************************
 chú thích
*************************************************************/
/*
    n: số nếp
    dc: độ dài cạnh bánh giầy
    dg: đường kính bánh chưng
    ld: số lá dong
    bc: bánh chưng
    bg: bánh giầy
    nd: nếp dư 
*/
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#define PI 3.1415926535

int n = 0, dc = 0, dg = 0, ld = 0, bc = 0, bg = 0;
float nd = 0;
char w[100];
int thoiTiet(char [],int,int,int,int);
float tinhSoNepBG(int);
int tinhSoNepBC(int);
int timBanBe(int,int);

/************************************************************
 * Ham:doc_File
 * Sinh vien can hoan chinh ham doc_File de thuc hien viec doc gia tri file input.inp
*************************************************************/
int doc_File(int *n, int *dc, int *dg, int *ld, char w[]){
    
    FILE *doc;

    doc = fopen("input.inp","r");
    fscanf(doc,"%d %d %d %d %s", n, dc, dg, ld, w);
    fclose(doc);

    if(*n>1000) return 0;
    if(*ld <1 || *ld >300)  return 0; 
    return 1;  
}
//sinh vien viet code de thuc hien viec doc cac gia tri tu file output.out tai thu muc lam viec
void ghi_File(int bc, int bg, float nd){

    FILE *doc;

    doc = fopen("output.out","w");
    fprintf(doc,"%d %d %.3f", bc, bg, nd);
    fclose(doc);
}
int doc_n(int *n)
{
	FILE *doc;
	doc = fopen("input.inp", "r");
	fscanf(doc, "%d", n);
	fclose(doc);

	return *n;
}

int main()
{
    timBanBe(n,ld);
    doc_n(&n);

    if  (doc_File(&n,&dc,&dg,&ld,w) == 0 )
    {
        bc = -1;
        bg = -1;
        nd = n;
    }       
    else    
        thoiTiet(w,n,ld,dc,dg);
        
    ghi_File(bc,bg,nd);
    return 0;
}
// nếp tính mỗi bánh chưng
int tinhSoNepBC(int dc)
{
    return pow(dc,2); 
}
//nếp tính mỗi bánh giầy
float tinhSoNepBG(int dg){
    return (pow(dg,2)*PI)/4;
}
//xét hàm theo thời tiết
int thoiTiet(char w[],int n,int ld,int dc,int dg){

    int sum,avg;

    if(strcmp(w,"Sun") == 0)
    {
        int G,H,X;

        G=dc%6;
        H=ld%5;

        switch(G)
        {   case 0:
                if(H==0)    X=5;
                if(H==1)    X=20;
                if(H==2)    X=15;
                if(H==3)    X=12;
                if(H==4)    X=10;
                break;
            case 1:
                if(H==0)    X=7;
                if(H==1)    X=5;
                if(H==2)    X=20;
                if(H==3)    X=15;
                if(H==4)    X=12;
                break;
            case 2:
                if(H==0)    X=10;
                if(H==1)    X=7;
                if(H==2)    X=5;
                if(H==3)    X=20;
                if(H==4)    X=15;
                break;
            case 3:
                if(H==0)    X=12;
                if(H==1)    X=10;
                if(H==2)    X=7;
                if(H==3)    X=5;
                if(H==4)    X=20;
                break;
            case 4:
                if(H==0)    X=15;
                if(H==1)    X=12;
                if(H==2)    X=10;
                if(H==3)    X=7;
                if(H==4)    X=5;
                break;
            case 5:
                if(H==0)    X=20;
                if(H==1)    X=15;
                if(H==2)    X=12;
                if(H==3)    X=10;
                if(H==4)    X=7;
                break;
        }
        n += ((X*n)/100);
        ld -= X;
        int c;
        c= (dc+dg) %3;
        switch(c)
        {
            case 0:
                strcpy(w,"Rain");
                break;
            case 1:
                strcpy(w,"Wind");
                break;
            case 2:
                strcpy(w,"Cloud");
                break;
        }
    }
    if(strcmp(w,"Wind") == 0)
    {
        if ( ld < 0 || ld > 300 || n > 1000)
        {
            bc = -1;
            bg = -1;
            nd = n;
        }
        else{
            if ( dc > 0 && dg < 0)
            {
                if ( n >= tinhSoNepBC(dc))
                {
                bc = n/tinhSoNepBC(dc);
                if ( bc > ld)   bc = ld;
                nd = n - bc*tinhSoNepBC(dc);
                bg = 0;
                }
                else
                {
                    bc = 0;
                    bg = 0;
                    nd = n;
                }
            }
            if ( dc > 0 && dg > 0)
            {
                if ( n >= tinhSoNepBC(dc))
                {
                    if( n < tinhSoNepBC(dc) )
            {
                bc=0;
                bg=0;
                nd=n;
            }
            else
            {
                if(tinhSoNepBC(dc) > tinhSoNepBG(dg))
                {
                    bc = n / tinhSoNepBC(dc);
                    nd = n - bc*tinhSoNepBC(dc);
                    bg = nd / tinhSoNepBG(dg);
                    avg = tinhSoNepBC(dc) / tinhSoNepBG(dg);
                    float ndt;
                    if (avg == 0)   avg = 1;
                    if (bc > ld)    bc = ld;
                    nd = n - bc*tinhSoNepBC(dc) - bg*tinhSoNepBG(dg);
                    ndt = nd + tinhSoNepBC(dc) - tinhSoNepBG(dg);
                    if (nd > ndt){
                        while (bg == 0)
                        {
                            bc -= avg;
                            nd = n - bc*tinhSoNepBC(dc);
                            bg = n / tinhSoNepBG(dg);
                        }
                    }
                    ld -= bc;
                    if ( bg > ld )  bg = ld;
                    nd = n - bc*tinhSoNepBC(dc) - bg*tinhSoNepBG(dg);
                }
                if (tinhSoNepBC(dc) < tinhSoNepBG(dg))
                {
                    bg = n / tinhSoNepBG(dg);
                    nd = n - bg*tinhSoNepBG(dg);
                    bc = nd / tinhSoNepBG(dc);
                    avg = tinhSoNepBG(dg) / tinhSoNepBC(dc);
                    
                    if (avg == 0)   avg = 1;
                    if ( bg+bc > ld)  
                    {
                        bg = ld;
                        bc = 0;
                    }
                    while (bc <= bg && nd > 0)
                    {
                        bg -= avg;
                        bc += avg;
                        nd = n - bc*tinhSoNepBC(dc) - bg*tinhSoNepBG(dg);
                    }
                    float ndt;
                    nd = n - bc*tinhSoNepBC(dc) - bg*tinhSoNepBG(dg);
                    ndt = nd + tinhSoNepBC(dc) - tinhSoNepBG(dg);
                    if (nd > ndt && bg + bc < ld)
                    {
                        do 
                        {
                            bc++;
                            nd = n - bc*tinhSoNepBC(dc);
                            bg = nd / tinhSoNepBG(dg);
                            nd = n - bc*tinhSoNepBC(dc) - bg*tinhSoNepBG(dg);
                        } while ( nd > tinhSoNepBC(dc));
                    }
                    if ( bc > ld){
                        while ( bc > ld)
                        {
                            bc--;
                            bg++;
                        }
                    }
                    nd = n - bc*tinhSoNepBC(dc) - bg*tinhSoNepBG(dg);
                    ndt = nd + tinhSoNepBC(dc) - tinhSoNepBG(dg);
                    if ( bc + bg < ld && ndt > 0){
                        if ( nd > ndt && nd > 0)
                        {
                            do{
                            bc++;
                            nd = n - bc*tinhSoNepBC(dc);
                            bg = nd / tinhSoNepBG(dg);
                            nd = n - bc*tinhSoNepBC(dc) - bg*tinhSoNepBG(dg);
                            ndt = nd + tinhSoNepBC(dc) - tinhSoNepBG(dg);
                            }while( nd > tinhSoNepBC(dc) || (nd > ndt && ndt > 0) );
                        }
                    }
                    nd = n - bc*tinhSoNepBC(dc) - bg*tinhSoNepBG(dg);   
                }
            }   
                }
                if ( n < tinhSoNepBC(dc) && n >= tinhSoNepBG(dg))
                {
                    bc = 0;
                    bg = n / tinhSoNepBG(dg);
                    if ( bg > ld)   bg = ld;
                    nd = n - bg*tinhSoNepBG(dg);
                }
                if ( n < tinhSoNepBC(dc) && n < tinhSoNepBG(dg) )
                {
                    bg = 0;
                    bc = 0;
                    nd = n;
                }
            }
            if ( dc < 0 && dg < 0)
            {
                bc = 0;
                bg = 0;
                nd = n;
            }
            if ( dc < 0 && dg > 0)
            {
                if ( n >= tinhSoNepBG(dg))
                {
                    bg = n / tinhSoNepBG(dg);
                    if ( bg > ld )  bg = ld;
                    nd = n - bg*tinhSoNepBG(dg);
                    bc = 0;
                }
                else
                {
                    bc = 0;
                    bg = 0;
                    nd = n;
                }
            }
        }
    }       
    if(strcmp(w,"Rain")==0){
        if ( ld < 0 || ld > 300 || n > 1000)
        {
            bc = -1;
            bg = -1;
            nd = n;
        }
        else{
            if ( dc > 0 && dg > 0)
            {
                if ( n >= tinhSoNepBC(dc))
                {
                    if(tinhSoNepBC(dc) > tinhSoNepBG(dg))
                    {
                        bc = n / tinhSoNepBC(dc);
                        nd = n - bc*tinhSoNepBC(dc);
                        bg = nd / tinhSoNepBG(dg);
                        nd = n - (bc*tinhSoNepBC(dc) + bg*tinhSoNepBG(dg));
                        sum = bc + bg;
                        avg = tinhSoNepBC(dc) / tinhSoNepBG(dg);
                        if ( avg == 0 ) avg = 1;
                        if(ld <= sum)
                        {
                            bc=ld;
                            bg=0;
                        }
                        if ( avg < bc )
                        {
                            while (( bc > bg ) && nd >= 0)
                            {
                                bc -= avg;
                                nd = n - bc*tinhSoNepBC(dc);
                                bg = nd / tinhSoNepBG(dg);
                                nd = n - (bc*tinhSoNepBC(dc) + bg*tinhSoNepBG(dg));
                            }
                        }
                        if ( (bc - bg) >= 2 )
                        {
                            while (bc > bg && nd >= 0)
                            {
                                bc--;
                                nd = n - bc*tinhSoNepBC(dc);
                                bg = nd / tinhSoNepBG(dg);
                                nd = n - (bc*tinhSoNepBC(dc) + bg*tinhSoNepBG(dg));
                            }
                        }
                        if ( (bg - bc) >= 2 )
                        {
                            while (bg > bc && nd >= 0)
                            {
                                bg--;
                                nd = n - bg*tinhSoNepBG(dg);
                                bc = nd / tinhSoNepBC(dc);
                                nd = n - (bc*tinhSoNepBC(dc) + bg*tinhSoNepBG(dg));
                            }
                            ld -= bc;
                            if (ld < bg)    bg = ld;
                            nd = n - (bc*tinhSoNepBC(dc) + bg*tinhSoNepBG(dg));
                        }
                    }
                    if (tinhSoNepBC(dc) < tinhSoNepBG(dg))
                    {
                        bg = n/tinhSoNepBG(dg);
                        nd = n - bg*tinhSoNepBG(dg);
                        bc = nd / tinhSoNepBC(dc);
                        nd = n - (bc*tinhSoNepBC(dc) + bg*tinhSoNepBG(dg));
                        sum = bg + bc;
                        avg = tinhSoNepBG(dg) / tinhSoNepBC(dc); 
                        if ( avg == 0 ) avg = 1;
                        if ( ld <= sum )
                        {
                            bg = ld;
                            bc = 0;
                        }
                        if ( avg < bg )
                        {
                            while (( bg > bc ) && nd >= 0)
                            {
                                bg -= avg;
                                nd = n - bg*tinhSoNepBG(dg);
                                bc = nd / tinhSoNepBC(dc);
                                nd = n - (bc*tinhSoNepBC(dc) + bg*tinhSoNepBG(dg));
                            }
                        }
                        if ((bg - bc) >= 2)
                        {
                            while ( bg > bc && nd >= 0)
                            {
                                bg--;
                                nd = n - bg*tinhSoNepBG(dg);
                                bc = nd / tinhSoNepBC(dc);
                                nd = n - (bc*tinhSoNepBC(dc) + bg*tinhSoNepBG(dg));
                            }
                        }
                        if ( (bc - bg) >= 2 )
                        {
                            while (bc > bg && nd >= 0 )
                            {
                                bc--;
                                nd = n - bc*tinhSoNepBC(dc);
                                bg = nd / tinhSoNepBG(dg);
                                nd = n - (bc*tinhSoNepBC(dc) + bg*tinhSoNepBG(dg));
                            }
                        }
                        nd = n - (bc*tinhSoNepBC(dc) + bg*tinhSoNepBG(dg));
                        float ndt;
                        ndt = nd - tinhSoNepBG(dg) + tinhSoNepBC(dc);
                        if ( ndt > 0 && ( bg > bc || bg < bc ))
                        {
                            if (nd < ndt && nd > 0)
                            {
                                bg++;
                                nd = n - bc*tinhSoNepBC(dc);
                                bg = nd / tinhSoNepBG(dg);
                                nd = n - (bc*tinhSoNepBC(dc) + bg*tinhSoNepBG(dg));
                            }
                        }
                        if ( bc + bg > ld){
                            bg = ld/2;
                            bc = ld - bg;
                        }
                            ld -= bg;
                            if (bc > ld)    bc = ld;
                            nd = n - (bc*tinhSoNepBC(dc) + bg*tinhSoNepBG(dg));  
                    }   
                }
            }
            if ( dc < 0 && dg < 0)
            {
                bc = 0;
                bg = 0;
                nd = n;
            }
        }
    }
    if(strcmp(w,"Fog")==0){
        if ( ld < 0 || ld > 300 || n > 1000)
        {
            bc = -1;
            bg = -1;
            nd = n;
        }
        else
        {
            bc=dc;
            bg=dg;
            nd=n;
        }
    }
    if(strcmp(w,"Cloud")==0){
        if ( ld < 0 || ld > 300 || n > 1000)
        {
            bc = -1;
            bg = -1;
            nd = n;
        }
        else
        {
            if(timBanBe(n,ld) == 1)
            {
                bc = 0;
                bg = 0;
                nd = n;
            }
            else
            {
                if ( dg > 0 && dc < 0)
                {
                    if ( n >= tinhSoNepBG(dg))
                    {
                    bg = n/tinhSoNepBG(dg);
                    if ( bg > ld)   bg = ld;
                    nd = n - bg*tinhSoNepBG(dg);
                    bc = 0;
                    }
                    else
                    {
                        bc = 0;
                        bg = 0;
                        nd = n;
                    }
                }
                if ( dc > 0 && dg > 0)
                {
                    if ( n >= tinhSoNepBG(dg))
                    {
                        if( n < tinhSoNepBG(dg) )
                        {
                            bc = 0;
                            bg = 0;
                            nd = n;
                        }
                        else
                        {
                            if(tinhSoNepBG(dg) > tinhSoNepBC(dc))
                            {
                                bg = n / tinhSoNepBG(dg);
                                nd = n - bg*tinhSoNepBG(dg);
                                bc = nd / tinhSoNepBC(dc);
                                avg = tinhSoNepBG(dg) / tinhSoNepBG(dc);
                                float ndt;
                                if (avg == 0)   avg = 1;
                                if (bg > ld)    bg = ld;
                                nd = n - bc*tinhSoNepBC(dc) - bg*tinhSoNepBG(dg);
                                ndt = nd + tinhSoNepBG(dg) - tinhSoNepBC(dc);
                                if ( nd > ndt && ndt > 0){
                                    while (bc == 0)
                                    {
                                    bg -= avg;
                                    nd = n - bg*tinhSoNepBG(dg);
                                    bc = n / tinhSoNepBC(dc);
                                    }
                                }
                                ld -= bg;
                                if ( bc > ld )  bc = ld;
                                nd = n - bc*tinhSoNepBC(dc) - bg*tinhSoNepBG(dg);
                            }
                            if (tinhSoNepBG(dg) < tinhSoNepBC(dc))
                            {
                                bc = n / tinhSoNepBC(dc);
                                nd = n - bc*tinhSoNepBC(dc);
                                bg = nd / tinhSoNepBG(dg);
                                avg = tinhSoNepBC(dc) / tinhSoNepBG(dg);
                                if (avg == 0)   avg = 1;
                                if ( bg+bc > ld)  
                                {
                                    bc = ld;
                                    bc = 0;
                                }
                                while (bg <= bc && nd > 0)
                                {
                                    bc -= avg;
                                    bg += avg;
                                nd = n - bc*tinhSoNepBC(dc) - bg*tinhSoNepBG(dg);
                                }
                                float ndt;
                                nd = n - bc*tinhSoNepBC(dc) - bg*tinhSoNepBG(dg);
                                ndt = nd - tinhSoNepBC(dc) + tinhSoNepBG(dg);
                                if (nd > ndt && bg + bc < ld)
                                {
                                    do 
                                    {
                                        bg++;
                                        nd = n - bg*tinhSoNepBG(dg);
                                        bc = nd / tinhSoNepBC(dc);
                                        nd = n - bc*tinhSoNepBC(dc) - bg*tinhSoNepBG(dg);
                                    } while ( nd > tinhSoNepBG(dg));
                                }
                                if ( bg > ld){
                                    while ( bg + bc > ld && nd > 0)
                                    {
                                        if ( bg < bc)   bg++;
                                        bg--;
                                        nd = n - bg*tinhSoNepBG(dg);
                                        bc = nd / tinhSoNepBC(dc);
                                        nd = n - bc*tinhSoNepBC(dc) - bg*tinhSoNepBG(dg);
                                    }
                                }
                                nd = n - bc*tinhSoNepBC(dc) - bg*tinhSoNepBG(dg);
                                ndt = nd + tinhSoNepBC(dc) - tinhSoNepBG(dg);
                                if ( bc + bg < ld && ndt > 0){
                                    if ( nd > ndt )
                                    {
                                        bg++;
                                        bc--;
                                        nd = n - bc*tinhSoNepBC(dc) - bg*tinhSoNepBG(dg);
                                        while( nd > tinhSoNepBG(dg)){
                                            bg++;
                                            nd = n - bg*tinhSoNepBG(dg);
                                            bc = nd / tinhSoNepBC(dc);
                                            nd = n - bc*tinhSoNepBC(dc) - bg*tinhSoNepBG(dg);  
                                        }
                                    }
                                }
                                nd = n - bc*tinhSoNepBC(dc) - bg*tinhSoNepBG(dg);   
                            }
                        }   
                    }
                    if ( n < tinhSoNepBG(dg) && n >= tinhSoNepBC(dc))
                    {
                        bg = 0;
                        bc = n / tinhSoNepBC(dc);
                        if ( bc > ld)   bc = ld;
                        nd = n - bc*tinhSoNepBC(dc);
                    }
                    if ( n < tinhSoNepBG(dg) && n < tinhSoNepBC(dc) )
                    {
                        bg = 0;
                        bc = 0;
                        nd = n;
                    }
                }
                if ( dc < 0 && dg < 0)
                {
                    bc = 0;
                    bg = 0;
                    nd = n;
                }
                if ( dc < 0 && dg > 0)
                {
                    if ( n >= tinhSoNepBC(dc))
                    {
                        bc = n / tinhSoNepBC(dc);
                        if ( bc > ld )  bc = ld;
                        nd = n - bc*tinhSoNepBC(dc);
                        bg = 0;
                    }
                    else
                    {
                        bc = 0;
                        bg = 0;
                        nd = n;
                    }
                }
            }
        }
    }
 }
int timBanBe(int n, int ld){
    int i,j,UC,UC1;
    UC=0;
    UC1=0;
    // tìm ước của nếp
    for(i=1;i<n;i++){
       if(n%i==0)    UC+=i;
    }
    // tìm ước của lá dong
    for(j=1;j<ld;j++){
        if(ld%j==0)    UC1+=j;
    }
    // tìm cặp số bạn bè
    if(UC==ld || UC1==n) return 1;
    else return 0;
}
