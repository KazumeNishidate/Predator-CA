#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rw.h"
#include "prototypes.h"
#define MAT(MM,II,JJ) MM[(ctl.mat_size+4)*(II)+(JJ)]

void hunt()
{
  int i, j;
  int x, n, e, s, w;

  for (i = 2; i < ctl.mat_size+2; i++){
    for (j = 2; j < ctl.mat_size+2; j++){
      x  = sys.mat0[ctl.shift*i+j];
      n  = MAT(sys.spec_mat0,(i-1),     j);
      e  = MAT(sys.spec_mat0,    i, (j+1));
      s  = MAT(sys.spec_mat0,(i+1),     j);
      w  = MAT(sys.spec_mat0,    i, (j-1));

      if(x==1 && (n==2||e==2||s==2||w==2 ) ) {
	sys.vitl_mat1[ctl.shift*i+j]+=ctl.increased_vitl;
      }
      if(x==2 && (n==1||e==1||s==1||w==1 ) ) {
	sys.mat1[ctl.shift*i+j]=0;
	sys.spec_mat1[ctl.shift*i+j]=0;
	sys.vitl_mat1[ctl.shift*i+j]=0;
      }

    }
      
  }



}

void breeding()
{
  int i, j;
  int x, n, e, s, w;

  for (i = 2; i < ctl.mat_size+2; i++){
    for (j = 2; j < ctl.mat_size+2; j++){
      x  = sys.mat0[ctl.shift*i+j];
      n  = MAT(sys.spec_mat0,(i-1),     j);
      e  = MAT(sys.spec_mat0,    i, (j+1));
      s  = MAT(sys.spec_mat0,(i+1),     j);
      w  = MAT(sys.spec_mat0,    i, (j-1));
      if(x==0 && (n==2||e==2||s==2||w==2 ) ) { /* prey will be born */
	if(ran1()<ctl.prey_reborn) {
	  sys.mat0[ctl.shift*i+j]=(int)(4*ran1()+1);
	  sys.spec_mat0[ctl.shift*i+j]=2;  
	  sys.vitl_mat0[ctl.shift*i+j]=ctl.prey_energy;
	}
      }

      if(x==0 && (n==1||e==1||s==1||w==1 ) ) { /* predator will be born */
	if(ran1()<ctl.predator_reborn) { 
	  sys.mat0[ctl.shift*i+j]=(int)(4*ran1()+1);
	  sys.spec_mat0[ctl.shift*i+j]=1;
	  sys.vitl_mat0[ctl.shift*i+j]=ctl.predator_energy;
	}
      }
      
    }
  }

}


void energy_consumption()
{
  int i, j;
  int *x, *y, *z;

  for (i = 2; i < ctl.mat_size+2; i++){
    for (j = 2; j < ctl.mat_size+2; j++){
      x = &MAT(sys.mat0,i,j);
      if(x>0) {
	y = &MAT(sys.spec_mat0,i,j);
	z = &MAT(sys.vitl_mat0,i,j);
	if(*z<=0) {/* starve to death */
	  *x = 0; 
	  *y = 0;
	  *z = 0;
	}
	if(*z>0) --*z;
      }
    }
  }

}

void count_walkers()
{
  int *x, i, j, cnt1=0, cnt2=0, cnt3=0;
  int n_predators, n_prey;
  static int n_time = 0;
  
  for (i = 2; i < ctl.mat_size+2; i++){
    for (j = 2; j < ctl.mat_size+2; j++){
      x = &MAT(sys.spec_mat0,i,j);
      if(*x==1) cnt1++;
      else if(*x==2) cnt2++;      
    }
  }
  cnt3 = cnt1 + cnt2;

  if(n_time==0)  fprintf(fpout,"# time_step  predator prey  total \n");
  fprintf(fpout,"%d  %d  %d  %d\n",n_time,cnt1, cnt2, cnt3);
  n_time++;
}

void move_walkers()
{
/*****************************************************************/
/* move_walkers                                                  */
/*                                                               */
/* All walkers will move according to the RWCA-2D dynamics.      */
/* sys.mat0  => MOVE => sys.mat1                                 */
/*                                                               */
/*****************************************************************/
  int i, j, x, y;
  int n, e, s, w;
  int ne, se, sw, nw;
  int nn, ee, ss, ww;
  int move_cnt = 0;

  for (i = 2; i < ctl.mat_size+2; i++){
    for (j = 2; j < ctl.mat_size+2; j++){

      x  = sys.mat0[ctl.shift*i+j];

      n  = sys.mat0[ctl.shift*(i-1)+j];
      e  = sys.mat0[ctl.shift*i+j+1];
      s  = sys.mat0[ctl.shift*(i+1)+j];
      w  = sys.mat0[ctl.shift*i+j-1];

      ne  = sys.mat0[ctl.shift*(i-1)+j+1];
      se  = sys.mat0[ctl.shift*(i+1)+j+1];
      sw  = sys.mat0[ctl.shift*(i+1)+j-1];
      nw  = sys.mat0[ctl.shift*(i-1)+j-1];

      nn  = sys.mat0[ctl.shift*(i-2)+j];
      ee  = sys.mat0[ctl.shift*i+j+2];
      ss  = sys.mat0[ctl.shift*(i+2)+j];
      ww  = sys.mat0[ctl.shift*i+j-2];

      if( x==1 && n==0 ){                     /*   rule set 1   */
        if( ne==4 )
          y = (int)(4*ran1()+1);
        else if( nw==2 )
          y = (int)(4*ran1()+1);
        else if( nn==3 )
          y = (int)(4*ran1()+1);
        else{
          y = 0;
	  if( ctl.do_moved_ants_calc!=0 ) move_cnt++;
        }
      }

      else if( x==2 && e==0 ){                /*   rule set 2   */
        if( ne==3 )
          y = (int)(4*ran1()+1);
        else if( se==1 )
          y = (int)(4*ran1()+1);
        else if( ee==4 )
          y = (int)(4*ran1()+1);
        else{
          y = 0;
          if( ctl.do_moved_ants_calc!=0 ) move_cnt++;
        }
      }

      else if( x==3 && s==0 ){                /*   rule set 3   */
        if( se==4 )
          y = (int)(4*ran1()+1);
        else if( sw==2 )
          y = (int)(4*ran1()+1);
        else if( ss==1 )
          y = (int)(4*ran1()+1);
        else{
          y = 0;
          if( ctl.do_moved_ants_calc!=0 ) move_cnt++;
        }
      }

      else if( x==4 && w==0 ){                /*   rule set 4   */
        if( sw==1 )
          y = (int)(4*ran1()+1);
        else if( nw==3 )
          y = (int)(4*ran1()+1);
        else if( ww==2 )
          y = (int)(4*ran1()+1);
        else{
          y = 0;
          if( ctl.do_moved_ants_calc!=0 ) move_cnt++;
        }
      }

      else if( x==1||x==2||x==3||x==4)         /*   rule set 5   */
          y = (int)(4*ran1()+1);

      if( x==0 && n==3 && e==4 )               /*   rule set 6   */
          y = 0;
      else if( x==0 && n==3 && s==1 )
          y = 0;
      else if( x==0 && n==3 && w==2 )
          y = 0;
      else if( x==0 && e==4 && s==1 )
          y = 0;
      else if( x==0 && e==4 && w==2 )
          y = 0;
      else if( x==0 && s==1 && w==2 )
          y = 0;

      else if( x==0 && n==3){                  /*   rule set 7   */
          y = (int)(4*ran1()+1);
	  MAT(sys.spec_mat1,i,j) = MAT(sys.spec_mat0,i-1,j);
	  MAT(sys.vitl_mat1,i,j) = MAT(sys.vitl_mat0,i-1,j); 
        }
      else if( x==0 && e==4){
          y = (int)(4*ran1()+1);
	  MAT(sys.spec_mat1,i,j) = MAT(sys.spec_mat0,i,j+1);
	  MAT(sys.vitl_mat1,i,j) = MAT(sys.vitl_mat0,i,j+1); 
        }
      else if( x==0 && s==1){
          y = (int)(4*ran1()+1);
	  MAT(sys.spec_mat1,i,j) = MAT(sys.spec_mat0,i+1,j);
	  MAT(sys.vitl_mat1,i,j) = MAT(sys.vitl_mat0,i+1,j);
        }
      else if( x==0 && w==2){
          y = (int)(4*ran1()+1);
	  MAT(sys.spec_mat1,i,j) = MAT(sys.spec_mat0,i,j-1);
	  MAT(sys.vitl_mat1,i,j) = MAT(sys.vitl_mat0,i,j-1); 
        }

      else if( x==0 )                          /*   rule set 8   */
          y = 0;

      *(sys.mat1+ctl.shift*i+j) = y;
      if(y==0) {
	MAT(sys.spec_mat1,i,j) = 0;
	MAT(sys.vitl_mat1,i,j) = 0;
      }

    }
  }
  set_bc(sys.mat1);
  set_bc(sys.spec_mat1);
  set_bc(sys.vitl_mat1);

/* fix */
/*
    show_matrix(sys.mat0);
    show_matrix(sys.mat1);
    printf("mvcnt = %d averaged_velocity = %f\n",
	   move_cnt, sys.averaged_velocity[sys.time_step]); 
    getchar();
*/
}

void set_bc(int *ants)
{
  int i;

/* corner adjustment 1 */
  *ants     = *(ants+( ctl.shift*(ctl.mat_size+1) - 4));
  *(ants+1) = *(ants+( ctl.shift*(ctl.mat_size+1) - 3));
  *(ants+ctl.shift) = *(ants+( ctl.shift*(ctl.mat_size+2) - 4));
  *(ants+(ctl.mat_size+5)) = *(ants+( ctl.shift*(ctl.mat_size+2) - 3));

/* corner adjustment 2 */
  *(ants+(ctl.mat_size+2))   = *(ants+(ctl.shift*ctl.mat_size + 2));
  *(ants+(ctl.mat_size+3))   = *(ants+(ctl.shift*ctl.mat_size + 3));
  *(ants+2*(ctl.mat_size+3)) = *(ants+(ctl.shift*(ctl.mat_size+1)+2));
  *(ants+2*(ctl.mat_size+3)+1) = *(ants+(ctl.shift*(ctl.mat_size+1)+3));

/* corner adjustment 3 */
  *(ants+(ctl.mat_size+3)*(ctl.mat_size+3)-1) = *(ants+3*ctl.shift-4);
  *(ants+(ctl.mat_size+3)*(ctl.mat_size+3)) = *(ants+3*ctl.shift-3);
  *(ants+(ctl.mat_size+3)*ctl.shift) = *(ants+4*ctl.shift-4);
  *(ants+(ctl.mat_size+3)*ctl.shift+1) = *(ants+4*ctl.shift-3);

/* corner adjustment 4 */
  *(ants+ctl.shift*(ctl.mat_size+3)-2) = *(ants+2*ctl.shift+2);
  *(ants+ctl.shift*(ctl.mat_size+3)-1) = *(ants+2*ctl.shift+3);
  *(ants+ctl.shift*ctl.shift-2) = *(ants+3*ctl.shift+2);
  *(ants+ctl.shift*ctl.shift-1) = *(ants+3*ctl.shift+3);

/* border adjustment   */

  for (i = 2; i < ctl.mat_size+2; i++){
      *(ants+i) = *(ants+ctl.shift*ctl.mat_size+i);
      *(ants+ctl.mat_size+4+i) = *(ants+ctl.shift*(ctl.mat_size+1)+i); 
      *(ants+ctl.shift*(ctl.mat_size+2)+i)=*(ants+2*ctl.shift+i);
      *(ants+ctl.shift*(ctl.mat_size+3)+i) = *(ants+3*ctl.shift+i); 

      *(ants+i*ctl.shift)   = *(ants+(i+1)*ctl.shift-4);
      *(ants+i*ctl.shift+1) = *(ants+(i+1)*ctl.shift-3);

      *(ants+(i+1)*ctl.shift-2)   = *(ants+i*ctl.shift+2);
      *(ants+(i+1)*ctl.shift-1)   = *(ants+i*ctl.shift+3);
    }

}

void mk_copy(int *original, int *copy)
{
  int i, j;

  for(i=0; i<ctl.mat_size+4; i++){
    for(j=0; j<ctl.mat_size+4; j++){
      *(copy+ctl.shift*i+j)  = *(original+ctl.shift*i+j);
    }
  }
}

