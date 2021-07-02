---
title: Kinematics - 2D
date: "2021-06-25T22:40:32.169Z"
description: Two-dimensional kinematics simulation program
---
### Kinematics - 2D

The key to generalizing kinematic relationships to higher dimensions is to break each dimension of a problem into multiple one-dimensional problems. Since each dimension can be thought of as having independent position, velocity, and acceleration, complex kinematics problems can be greatly simplified.

In the two-dimensional case, position, velocity, and acceleration can all be split up into horizontal and vertical components. Here, the vector $\vec{u}$ is shown with its corresponding $x$ and $y$ components.

![Diagram showing velocity components](Fig1.png)
*Fig. 1*

In our program, $\vec{u}$ will be the velocity vector of the ball. The angle $a$ is the initial direction of the ball's trajectory. Each component of $\vec{a}$ is controlled by the user's mouse position. Since each component of the velocity is known, they can each be solved as one-dimensional problems, and the ball's position can be updated according to each one. However, since we want to display the direction and magnitude of the initial velocity as an arrow on screen, these two values must be found.

The trigonometric ratios between sides of the right triangle formed by the velocity components can be used to solve for the angle $a$. The Pythagorean theorem can be used to solve for the hypotenuse of this triangle, also known as the magnitude and denoted by $\|u\|$.

$$
\tan{a} = \frac{u.y}{u.x}
\\
a = \arctan{\frac{u.y}{u.x}}
$$


$$
(u.x)^2 + (u.y)^2 = \|u\|^2
\\
\|u\| = \sqrt{(u.x)^2 + (u.y)^2}
$$

In C++ there is a helpful function that will perform the last calculation for us, taking in the two sides as parameters and returning the length of the hypotenuse.
```cpp
trajectoryMagnitude = std::hypot(vComponents.x, vComponents.y);
```

From this information, we can set the sizes, positions, and rotations of the rectangles that will display the ball's velocity and its components.