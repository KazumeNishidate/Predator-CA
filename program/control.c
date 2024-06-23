#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rw.h"
#include "prototypes.h"

#define ON  (1)
#define OFF (0)

void get_control_param(void){ 
  long time_dumy;

  /* set up the system control parameters */
  ctl.max_time_step = 100000;   /* max time step */
  ctl.mat_size = 100;         /* system size = n X n squared lattice */

  ctl.concentration = 0.1;  /* initial concentration probability */
  ctl.p_of_predator = 0.05;   /* percentage of the predators */

  ctl.predator_energy = 20;  /* initial energy of predator */
  ctl.prey_energy = 6;      /* initial energy of prey */

  ctl.predator_reborn = 0.02; /* reborn probability of predator */
  ctl.prey_reborn = 0.07;     /* reborn probability of prey */
  ctl.increased_vitl = 0.4;     /* vital is increased by eating prey */
  
  /* "ctl.mat_size2" will be used at "msd_calc()" to consider the */
  /* effect of cyclic boundaly condition in MSD calculation.      */
  ctl.mat_size2 = ctl.mat_size/2; 
  ctl.shift = ctl.mat_size+4;

  /* set a "seed" for random number generator */
  sys.random_seed = (long *)calloc(1, sizeof(long)); 
  *sys.random_seed=-time(&time_dumy); /* set seed for random numbers */

}
