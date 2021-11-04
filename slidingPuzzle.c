#include <stdio.h>
#include <termio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int getch(void){

	int ch;
	struct termios buf;
	struct termios save;
	tcgetattr(0,&save);
	buf=save;
	buf.c_lflag &= ~(ICANON|ECHO);
	buf.c_cc[VMIN]=1;
	buf.c_cc[VTIME]=0;
	tcsetattr(0,TCSAFLUSH,&buf);
	ch=getchar();
	tcsetattr(0,TCSAFLUSH,&save);
	return ch;
}

int main(int argc, char *argv[]){


	int num;
	num = atoi(argv[1]);

	int b=1;
	int arr[4][4];
	int check[4][4];
	for(int i=0; i<4; i++){//배열 순서대로 정렬 되어있는지 비교하기 위한 배열
		for(int j=0; j<4; j++){

			check[i][j]=b;
			b++;
		}
	}

	int row, column;
	if(num==1){

		system("clear");//화면 클리어
		int a=1;
		for(int i=0; i<4; i++){//배열에 숫자 순서대로 저장
			for(int j=0; j<4; j++){

				arr[i][j] = a;
				a++;
			}

		}

	}
	else if(num==2){

		system("clear");

		srand((unsigned int)time(NULL));

		int i,j,z,n;
		int num[16];
		int array[4][4];
		for(i=0; i<16; i++){//중복 없이 랜덤하게 숫자 저장

			num[i] = rand()%16+1;
			for(j=0;j<i;j++){
				if(num[i] == num[j]){
					i--;
				}
			}
		}

		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){

				arr[i][j] = num[4*i+j];
			}
		}


	}else{
		printf("1, 2가 아닌 다른 입력!\n");
		exit(1);
	}


	printf("\n\n\n\n");
	for(int i=0; i<4; i++){//저장된 숫자 순서대로 출력
		printf("                              ");
		for(int j=0; j<4; j++){


			if(arr[i][j]==16)
				printf("    ");
			else
				printf("%3d ",arr[i][j]);
		}
		printf("\n\n");

	}
	printf("\n\n");


	for(int i=0; i<4; i++){//빈칸의 위치 찾기
		for(int j=0; j<4; j++){

			if(arr[i][j] ==16){
				row = i;
				column = j;
			}
		}
	}
	int move;
	while(move!=113){//q일때 까지

		move=getch();
		

		if(move==105&&row!=3){//위, i입력, 마지막 행일땐 위 버튼 안먹히게

			int tmp;
			tmp = arr[row][column];
			arr[row][column]=arr[row+1][column];
			arr[row+1][column] = tmp;
			row=row+1;

		}else if(move==106&&column!=3){//왼쪽, j입력, 마지막 열일땐 왼쪽 버튼 안먹히게

			int tmp;
			tmp = arr[row][column];
			arr[row][column] = arr[row][column+1];
			arr[row][column+1]=tmp;
			column=column+1;


		}else if(move==107&&row!=0){//아래, k입력, 첫번째 행일땐 아래 버튼 안먹히게

			int tmp;
			tmp=arr[row][column];
			arr[row][column]=arr[row-1][column];
			arr[row-1][column]=tmp;
			row=row-1;


		}else if(move==108&&column!=0){//오른쪽, l입력, 첫번째 열일땐 오른쪽 버튼 안먹히게

			int tmp;
			tmp=arr[row][column];
			arr[row][column]=arr[row][column-1];
			arr[row][column-1]=tmp;
			column=column-1;

		}

		system("clear");
		int count=0;
		

		printf("\n\n\n\n");
		for(int i=0; i<4; i++){//배열 순서대로 출력하고 퍼즐이 풀렸는지 검사
			printf("                              ");
			for(int j=0; j<4; j++){

				if(arr[i][j]==16)
					printf("    ");
				else
					printf("%3d ",arr[i][j]);
				if(arr[i][j]==check[i][j])
					count++;
			}
			printf("\n\n");

		}
		printf("\n\n");

		if(move!=113 && count==16){//모든 숫자가 순서대로 정렬되어 있을 때

			printf("                                 ");
			printf("축하합니다.\n\n\n");
			sleep(3);
			break;
		}
	}




}
