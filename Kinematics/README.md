# Kinematics - 1D
To create an accurate kinematics physics simulation, the relationships between position, velocity, and acceleration can be used.

$$v(t)=\dfrac{dx}{dt}$$
$$a(t)=\dfrac{dv}{dt}$$

Where $a(t)$ is acceleration, $v(t)$ is velocity, and $x(t)$ is position. If we start from a known acceleration and initial position, which this program will, then to find the current velocity and position, these two differential equations can be solved. However, since the explicit velocity and accelerations functions are unknown (as they are inputted by the user), a closed form solution is not available and numerical integration must be used.

One of the simplest numerical integration methods, Euler's method, comes from the definition of the derivative.

$$v(t)=\dfrac{dx}{dt}=\lim_{\Delta t \to 0} \frac{x(t+\Delta t)-x(t)}{\Delta t}$$

By using sufficiently small values of $\Delta t$, the following approximation is good enough for cases such as our simulation.

$$v(t)\approx \frac{x(t+\Delta t) - x(t)}{\Delta t}$$

Now, the equation can be rearranged for $x(\Delta t + t)$:

$$x(t+\Delta t) \approx x(t) + v(t)\Delta t$$

We now have an expression that will give us the next position from the current position and velocity. However, since only the acceleration in our simulation is known, a similar process must be done to find the velocity.

$$v(t + \Delta t) \approx v(t) + a(t)\Delta t$$

In this simulation, the velocity at the current timestep will be calculated from the previous time step. The current velocity will then be used to find $x(t + \Delta t)$, i.e., the position that the ball will move to.

In code, this looks like choosing a set value of $\Delta t$, in this case, `0.01`, and calculating velocity and position for each timestep.

```c++
double v = 0.0; // Velocity
double a = 0.0; // Acceleration
double x = 0.0; // Position
double dt = 0.01;

while (window.isOpen())
{
    a = getAcceleration(); // User input
    v = v + a * dt;
    x = x + v * dt;
    ball.setPosition(x);
}
```

Note that in the actual program, the `a * dt` and `v * dt` terms are calculated separately so they can be displayed in the text, but the overall process is the same.

For more information on this subject, Gaffer on Games provides helpful articles on [numerical integration](https://gafferongames.com/post/integration_basics/) and [timesteps](https://gafferongames.com/post/fix_your_timestep/).
