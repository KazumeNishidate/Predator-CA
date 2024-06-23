
This code simulates predator-prey ecosystem Cellular Automata, a
complex system based on the RWCA model [1,2,3].

- Predators and prey walk around the 2D lattice following the RWCA
  rules.  As they move, predators and prey undergo a realistic,
  gradual reduction in their energy points, accurately reflecting the
  energy expenditure in a natural ecosystem.

- A predator will consume prey at the nearest neighbor sites with a
  certain probability—where the nearest neighbors refer to N, E, S,
  and W sites—and eliminate the prey.

- A predator will probably have a baby predator when it meets another
  predator in the nearest neighboring sites.

- A prey will also have a baby prey with some probability when it
  meets another prey in neighboring sites.


[1] K. Nishidate, M. Baba, and R.J. Gaylord. Cellular automaton model
  for random walkers. Phys. Rev. Lett., 77:1675–1678,
  1996. https://journals. aps.org/prl/abstract/10.1103/PhysRevLett.77.1675.

[2] K. Nishidate, M. Baba, and R.J. Gaylord. Cellular automaton model
  for bias ed diffusive traffic flow. J. Phys. Soc. Jpn.,
  65:3415–3418,
  1996. https://journals.jps.jp/doi/abs/10.1143/JPSJ.65.3415.

[3] K. Nishidate, M. Baba, H. Chiba, T. Ito, K. Kodama, and
  K. Nishikawa. Cellular automaton model for biased diffusive traffic
  flow. J. Phys. Soc. Jpn., 69:1352–1355,
  2000. https://journals.jps.jp/doi/abs/10.1143/ JPSJ.69.1352.

kazume.nishidate@gmail.com
