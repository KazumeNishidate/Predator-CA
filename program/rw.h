/*------------------ global definitions ----------------------------------*/

/* input and output files */
FILE *fpin, *fpout, *fpout_msd, *fpout_move;

/*------------------ global variables -------------------------------------*/
typedef	struct {

  int max_time_step;    /* max time step */
  int mat_size;         /* system size   */
  int mat_size2;        /* mat_size/2: will be used at "msd_calc()"  */
  int shift;            /* column shift = mat_size + 4               */
  double concentration; /* initial concentration probability         */

  double p_of_predator; /* percentage of the predators */
  int predator_energy;  /* initial energy of predator */
  int prey_energy;      /* initial energy of prey */

  double predator_reborn; /* reborn probability of predator */
  double prey_reborn;     /* reborn probability of prey */
  double increased_vitl;  /*  vital is increased by eating prey */
  
  int do_moved_ants_calc;     /* calculation of number of moved walkers  */
  int average_iteration_num;  /* number of runs for averaged calculation */
} calc_control;

typedef	struct {

  long tdumy;   /* dummy variable for time() function     */ 
  long seed;    /* seed for random number genelater       */

  int time_step;    /* current number of time step */
  int average_step; /* current average step        */

  int *mat0; 
  int *mat1; 

  int *spec_mat0;
  int *spec_mat1;
  int *vitl_mat0;
  int *vitl_mat1;
  int *clck_mat0;
  int *clck_mat1;  
  
  double *accumulation;
  double *distinct_sites;
  int number_of_walkers;

  long *random_seed;
  float random;

} system_property;

/*------------------- declaration for the structures ----------------------*/

calc_control ctl;
system_property sys;


