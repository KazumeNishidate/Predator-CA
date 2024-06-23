#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rw.h"
#include "prototypes.h"

#define MAT(MM,II,JJ) MM[(ctl.mat_size+4)*(II)+(JJ)]

/****
 set the initial configuration of the system
****/
void set_init_conf()
{
  int i, j, cnt=0;

  while(cnt==0){  /*=== to avoid a vacant system ===*/
    cnt = 0; 

    for (i = 2; i < ctl.mat_size+2; i++){
      for (j = 2; j < ctl.mat_size+2; j++){
	if(ran1()<ctl.concentration)
	  MAT(sys.mat0,i,j) = (int)(4*ran1()+1);

	if(MAT(sys.mat0,i,j)>0) {
	  if(ran1() < ctl.p_of_predator ) {
	    MAT(sys.spec_mat0,i,j) = 1; /* predator */
	    MAT(sys.vitl_mat0,i,j) =
	      (int)(ctl.predator_energy*ran1()+1);
	  } else {
	    MAT(sys.spec_mat0,i,j) = 2; /* prey */
	    MAT(sys.vitl_mat0,i,j) =
	      (int)(ctl.prey_energy*ran1()+1);
	  }
	    cnt++;
	}

      }
    }
  } 
  sys.number_of_walkers = cnt;
/*
  printf("num = %d\n",cnt);
  printf("prob. = %f\n",(double)cnt/(double)ctl.mat_size);
  getchar();
*/
  set_bc(sys.mat0);
  set_bc(sys.spec_mat0);
}

void open_files(void)
{
  if((fpout = fopen("../files/out","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }
  if((fpout_move = fopen("../files/move","w"))==NULL){
    printf("cannot open out. Abort\n");
    exit(EXIT_FAILURE);
  }
}

void init_mem(void){
  int n;
  
  n = ctl.mat_size+4;
  sys.mat0 = (int *)calloc(n*n, sizeof(int)); 
  sys.mat1 = (int *)calloc(n*n, sizeof(int)); 
  sys.spec_mat0 = (int *)calloc(n*n, sizeof(int));
  sys.spec_mat1 = (int *)calloc(n*n, sizeof(int)); 
  sys.vitl_mat0 = (int *)calloc(n*n, sizeof(int));
  sys.vitl_mat1 = (int *)calloc(n*n, sizeof(int));
  sys.clck_mat0 = (int *)calloc(n*n, sizeof(int));
  sys.clck_mat1 = (int *)calloc(n*n, sizeof(int)); 
}

void show_matrix(int *field){
  int i, j;
/*
  for(i=0; i<ctl.mat_size+4; i++){
    for(j=0; j<ctl.mat_size+4; j++){
      printf(" %2d",field[(ctl.mat_size+4)*i+j]);
    }
    printf("\n");
  }
  printf("\n");
*/

  for(i=2; i<ctl.mat_size+2; i++){
    for(j=2; j<ctl.mat_size+2; j++){
      printf(" %2d",field[(ctl.mat_size+4)*i+j]);
    }
    printf("\n");
  }
  printf("\n");

}

void print_matrix(int *field){
  int i, j;
/*
  for(i=0; i<ctl.mat_size+4; i++){
    for(j=0; j<ctl.mat_size+4; j++){
      fprintf(fpout," %d",field[(ctl.mat_size+4)*i+j]);
    }
    fprintf(fpout,"\n");
  }
  fprintf(fpout,"\n");
*/

  for(i=2; i<ctl.mat_size+2; i++){
    for(j=2; j<ctl.mat_size+2; j++){
      fprintf(fpout," %d",field[(ctl.mat_size+4)*i+j]);
    }
    fprintf(fpout,"\n");
  }
  fprintf(fpout,"\n");

}

