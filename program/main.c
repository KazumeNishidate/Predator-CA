#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include "rw.h"
#include "prototypes.h"

/* RWCA-2d uder cyclic boundary condition */

int main(void){

  open_files();
  get_control_param();
  init_mem();

  set_init_conf();
  mk_copy(sys.mat0, sys.mat1);
  mk_copy(sys.spec_mat0, sys.spec_mat1);
  mk_copy(sys.vitl_mat0, sys.vitl_mat1);
    
  /*----------- RWCA moving step -----------*/
  for(sys.time_step=0;sys.time_step<ctl.max_time_step;sys.time_step++){
    count_walkers();
    breeding();
    energy_consumption();
    hunt();

    set_bc(sys.mat0);
    set_bc(sys.spec_mat0);
    set_bc(sys.vitl_mat0);
    
    mk_copy(sys.mat0, sys.mat1);
    mk_copy(sys.spec_mat0, sys.spec_mat1);
    mk_copy(sys.vitl_mat0, sys.vitl_mat1);

    egg_disp();
    
    move_walkers();       /* sys.mat0 => RWCA  => sys.mat1 */


    mk_copy(sys.mat1, sys.mat0);
    mk_copy(sys.spec_mat1, sys.spec_mat0);
    mk_copy(sys.vitl_mat1, sys.vitl_mat0);

  }

  return 0;
}

