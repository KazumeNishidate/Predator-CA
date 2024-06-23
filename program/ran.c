#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rw.h"
#include "prototypes.h"
#include <gsl/gsl_rng.h>
#include <sys/time.h>

double ran1(){
  static const gsl_rng_type *T;
  static gsl_rng *r;
  static int cnt=0;

  if(cnt==0){
    gsl_rng_env_setup ();
    T = gsl_rng_default;
    r = gsl_rng_alloc (T);
    gsl_rng_set(r,time(NULL));
    cnt =1;
  }
  return gsl_rng_uniform(r);
}
