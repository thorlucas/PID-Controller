# Proportional-Integral-Derivative Controller

This is a simple implementation of a PID controller.

The model is a simple "hotplate" simulation. I've tuned the PID to work well for that particular simulation, but note: it must be manually tuned (for now) for any other application. The model seems to work best at P: 35.5 I: 0.03 D: 110.

The model can be ran with:
```
./main -p 35.5 -i 0.03 -d 110 > out.dat
gnuplot plot.gnu
```