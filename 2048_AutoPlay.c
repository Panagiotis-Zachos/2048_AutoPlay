#include <stdio.h>
#include <stdlib.h>

inline void fast_srand( int seed );

inline int fastrand();

void printmatrix(int matrix[4][4]);

int fillbox(int matrix[4][4]);

void movematrix(int matrix[4][4],int m,int* score);

int ismovepossible(int matrix[4][4], int m);

int losscheck(int matrix[4][4]);

int moveselect(int matrix[4][4]);

static unsigned int g_seed;

int main(int argc, char *argv[]) {
	int matrix[4][4];
	int i,j,n,move;
	int score = 0;
	
	
	//Matrix Initialization
	for(i=0;i<4;i++){ 
		for(j=0;j<4;j++){
			matrix[i][j] = 0;
		}
	}	
	fast_srand(time(NULL));
	fillbox(matrix);
	fillbox(matrix);
	//End of initialization	
	printf("Your score is: %d\n",score);
	printmatrix(matrix);
	
	while(losscheck(matrix) == 0){
		move = moveselect(matrix);
		movematrix(matrix,move,&score);
		fillbox(matrix);
		printf("Your score is: %d\n",score);
		printmatrix(matrix);
	}
	return 0;
}

int moveselect(int matrix[4][4]){
	int i,j,move,k,n;
	int score_sum,max_score = 0;
	int best_move;
	int temp[4][4];
	
	for(i=2;i<=8;i+=2){
		if(ismovepossible(matrix,i)){
			score_sum = 0;			
			for(j=0;j<1000;j++){
				for(k=0;k<4;k++){
					for(n=0;n<4;n++){
						temp[k][n] = matrix[k][n];
					}
				}
				movematrix(temp,i,&score_sum);
				while(losscheck(temp) == 0){
					move = 2 * (fastrand()%4 + 1);
					while(ismovepossible(temp,move) == 0){
						move = 2 * (fastrand()%4 + 1);
					}
					movematrix(temp,move,&score_sum);
					fillbox(temp);
				}
			}
			if(score_sum > max_score){
				max_score = score_sum;
				best_move = i;
			}
		}
	}
	return best_move;
}

inline void fast_srand( int seed )   {
        g_seed = seed;
}

inline int fastrand(){

g_seed = (214013*g_seed+2531011);

  return (g_seed>>16)&0x7FFF;

}

void printmatrix(int matrix[4][4]){
	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(j == 0)printf("| %d   ",matrix[i][j]);
			else if(j == 3)printf("%d |\n\n\n",matrix[i][j]);
			else printf("%d   ",matrix[i][j]);
		}
	}
}

int fillbox(int matrix[4][4]){
	int i,j,n=0;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(matrix[i][j] == 0)n++;
		}
	}
	if(n == 0)return 1;
	do{
		i = fastrand()%4;
		j = fastrand()%4;
	}while(matrix[i][j] != 0);
	n = fastrand()%10;
	matrix[i][j] = 2;
	if(n == 9
	)matrix[i][j] = 4;
	return 0;
}

void movematrix(int matrix[4][4],int m,int* score){
	int i,j,k,stop=5;
	if(m==4){
		for(i=0;i<4;i++){
			for(j=1;j<4;j++){
				if(matrix[i][j] != 0){
					k = j;
					while(k > 0){
						if(!matrix[i][k-1]){
							matrix[i][k-1] = matrix[i][k];
							matrix[i][k] = 0;
							k--; 
						}
						else if(matrix[i][k-1] == matrix[i][k]){
							matrix[i][k-1] *= 2;
							*score += matrix[i][k-1];
							matrix[i][k] = 0;							
							k--;
							break;
						}
						else break;
					} 
				}
				
			}
		}
	}
	else if(m == 6){
		for(i=0;i<4;i++){
			for(j=2;j>=0;j--){
				if(matrix[i][j] != 0){
					k = j;
					while(k < 3){
						if(matrix[i][k+1] == 0){
							matrix[i][k+1] = matrix[i][k];
							matrix[i][k] = 0;
							k++; 
						}
						else if(matrix[i][k+1] == matrix[i][k]){
							matrix[i][k+1] *= 2;
							*score += matrix[i][k+1];
							matrix[i][k] = 0;
							k++;
							break;
						}
						else break;
					} 
				}
				
			}
		}
	}
	else if(m == 8){
		for(j=0;j<4;j++){
			for(i=1;i<4;i++){
				if(matrix[i][j] != 0){
					k = i;
					while(k > 0){
						if(matrix[k-1][j] == 0){
							matrix[k-1][j] = matrix[k][j];
							matrix[k][j] = 0;
							k--; 
						}
						else if(matrix[k-1][j] == matrix[k][j]){
							matrix[k-1][j] *= 2;
							*score += matrix[k-1][j];
							matrix[k][j] = 0;
							k--;
							break;
						}
						else break;
					} 
				}
				
			}
		}
	}
	else if(m == 2){
		for(j=0;j<4;j++){
			for(i=2;i>=0;i--){
				if(matrix[i][j] != 0){
					k = i;
					while(k < 3){
						if(matrix[k+1][j] == 0){
							matrix[k+1][j] = matrix[k][j];
							matrix[k][j] = 0;
							k++; 
						}
						else if(matrix[k+1][j] == matrix[k][j]){
							matrix[k+1][j] *= 2;
							*score += matrix[k+1][j];
							matrix[k][j] = 0;
							k++;
							break;
						}
						else break;
					} 
				}
				
			}
		}
	}
}

int ismovepossible(int matrix[4][4], int m){
	int temp_matrix[4][4];
	int i,j;
	
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			temp_matrix[i][j] = matrix[i][j];
		}
	}
	movematrix(temp_matrix,m,&i);
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(temp_matrix[i][j] != matrix[i][j])return 1;
		}
	}
	return 0;
}


int losscheck(int matrix[4][4]){
	int i;
	
	for(i=0;i<=8;i+=2){
		if(ismovepossible(matrix,i)){
			return 0;
		}
	}
	return 1;
}
