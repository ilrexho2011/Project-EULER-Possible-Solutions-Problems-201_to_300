#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h> 
#include <gmp.h>

void PeterProbaScore(int *tab){
	int i0, i1, i2, i3, i4, i5, i6, i7, i8;
	int Score[40];
	int i;
	for (i = 0; i < 40; i++){
			Score[i] = 0;
	}
	
	for ( i0 = 1; i0 < 5; i0++){
		for ( i1 = 1; i1 < 5; i1++){
			for ( i2 = 1; i2 < 5; i2++){
				for ( i3 = 1; i3 < 5; i3++){
					for ( i4 = 1; i4 < 5; i4++){
						for ( i5 = 1; i5 < 5; i5++){
							for ( i6 = 1; i6 < 5; i6++){
								for ( i7 = 1; i7 < 5; i7++){
									for ( i8 = 1; i8 < 5; i8++){
										Score[i0+i1+i2+i3+i4+i5+i6+i7+i8] += 1;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	for (i = 0; i < 40; i++){
		tab[i] =Score[i];
	}
}

void ColinProbaScore( int *tab ){
	int i0, i1, i2, i3, i4, i5;
	int Score[40];
	int i;
	
	for (i = 0; i < 40; i++){
		Score[i] = 0;
	}
	
	for ( i0 = 1; i0 < 7; i0++){
		for ( i1 = 1; i1 < 7; i1++){
			for ( i2 = 1; i2 < 7; i2++){
				for ( i3 = 1; i3 < 7; i3++){
					for ( i4 = 1; i4 < 7; i4++){
						for ( i5 = 1; i5 < 7; i5++){
							Score[i0+i1+i2+i3+i4+i5] += 1;
						}
					}
				}
			}
		}
	}
	
	for (i = 0; i < 40; i++){
		tab[i] = Score[i];
	}
}


int main(){
	
	//tableaux contenant la probabilité du score de sortie
	
	int ProbColin[40];
	int ProbPeter[40];
	int i,j;
	
	mpq_t prob;
	mpq_t tmp1;
	mpq_t tmp2;
	
	mpq_init(prob);
	mpq_init(tmp1);
	mpq_init(tmp2);
	
	
	for (i = 0; i < 40; i++){
		ProbColin[i] = 0;
		ProbPeter[i] = 0;
	}
	
	//calcul des probas de sortie d un score
	long OccurPeter = (long) pow(4,9);
	long OccurColin = (long) pow(6,6);
	
	PeterProbaScore(ProbPeter);
	ColinProbaScore(ProbColin);

	for (i = 9; i < 37; i++){
		for (j = 6; j < i; j++){
			mpq_set_ui(tmp1, ProbPeter[i],OccurPeter);
			mpq_set_ui(tmp2,ProbColin[j],OccurColin);
			mpq_mul(tmp1,tmp1,tmp2);
			mpq_add(prob,prob,tmp1);
		}
	}
	
	mpf_t last;
	mpf_init(last);
	mpf_set_q(last,prob);
	
	mpf_out_str (stdout,10,7, last);
	
	return 0;
	
}