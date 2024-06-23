#include <eggx.h>
#include <stdio.h>
#include  <stdlib.h>
#include  <math.h>
#include  <string.h>
#include  <X11/Xlib.h>
#include  <X11/Xutil.h>
#include "rw.h"
#include "prototypes.h"

#define X_MAX 500
#define Y_MAX 500

void egg_disp(void){
  static int cnt=0, win;
  int i, j, ii, jj;

  if(cnt==0){
    win=gopen(X_MAX,Y_MAX);
    layer(win, 0, 1);
  }

  newcolor(win, "DarkSeaGreen");
  gclr(win) ;

  for (i = 2; i < ctl.mat_size+2; i++){
    for (j = 2; j < ctl.mat_size+2; j++){
      ii = i-2; jj = j-2;

      if(sys.spec_mat1[ctl.shift*i+j]==1){
	newcolor(win, "DeepPink");
	fillrect(win, ii*5, jj*5, 4, 4);
      } else if(sys.spec_mat1[ctl.shift*i+j]==2){
	newcolor(win, "LawnGreen");
	fillrect(win, ii*5, jj*5, 4, 4);
      }
    }
  }

  copylayer(win, 1, 0);

  cnt++;  


}
