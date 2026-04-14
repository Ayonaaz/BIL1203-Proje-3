#include <stdio.h>
void boslukbul(int tahta[3][3],int *satir,int *sutun){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(tahta[i][j]==0){
				*satir=i;
				*sutun=j;
				return;
			}
		}
	}
	
}
int main(){
	int tahta[3][3]={
	{1,2,3},
	{4,5,0},
	{6,7,8}
	};
	int bossatir,bosutun;
	boslukbul(tahta,&bossatir,&bosutun);
	printf("Bosluk=%d.satir %d.sutun",bossatir+1,bosutun+1);
	return 0;
}