---
title: 3D Projection - Perspective
date: 2021-10-08T04:20:36.992Z
description: 3D-Rendering-Perspective
---

> Never trust a computer you can't throw out a window.
>
> <footer>Steve Wozniak</footer>

---

As seen in the previous project, orthographic projection gives a clear visualization of 3D objects on a 2D screen. However, it does not reflect the way we actually see things and so is not as useful in computer graphics applications intended to mimic reality, such as animations or first-person games. Perspective projection is the choice for these cases, as it models objects as we see them in reality, displaying them with <i>perspective</i>, which varies at different viewing angles and positions.

The perspective projection algorithm is similar to orthographic projection. A point $P$ in 3D scene space has coordinates $(x, y, z)$ and is projected onto the canvas at point $P'$, with coordinates $(x', y')$. Figure 1 shows point $P'$ lying on the canvas plane, viewed from the side. Points $P$, $P'$, and the camera are colinear and form one side of a triangle. The other two sides are the horizontal plane and the planes perpendicular to the horizontal that contain points $P$ and $P'$. A set of similar triangles is constructed, as they share three congruent angles.

The value we want to find is $P'.y$, the height of the projected point above the horizontal. $P'.z$ is a set constant since the canvas is always the same distance away from the camera (for this project, at least).

![Side Diagram of perspective projection](Fig-1.png)
*Fig. 1 – Side Diagram of Perspective Projection*

By the definition of similar triangles, the sides of the two triangles form equal ratios, giving

$$
\frac{P.y}{P.z} = \frac{P'.y}{P'.z}
$$

Solving for $P'.y$ gives 

$$
P'.y = \frac{P'.z \cdot P.y}{P.z}
$$

There are a few things that must be changed about this relationship before it can be implemented. It makes things easy if we define $P'.z := 1$, which lets us leave it out of the calculation. Additionally, by convention, the camera view points down the negative $z$ axis, so we should write $-P.z$ instead of $P.z$. These properties of similar triangles resulting from a projection onto the canvas apply to the $x$ coordinates too, where the plane of figure 1 is rotated $90 \degree$ about the $z$ axis. Finally, we can compute the $x$ and $y$ coordinates of the point to be displayed on the screen:

$$
P'.x = \frac{P.x}{-P.z}
$$

$$
P'.y = \frac{P.y}{-P.z}
$$

That's all that's needed to make a 3D object projected onto a 2D canvas with perspective projection. I made an array storing coordinates of a cube and drew lines connecting adjacent verticies to create a cube projection. As an added functionality we can introduce another term $d$ in the denominator, which we can change with user input.

$$
P'.x = \frac{P.x}{d - P.z}
$$

$$
P'.y = \frac{P.y}{d - P.z}
$$

A larger value of $d$ means that the coordinates on the canvas are smaller. We are effectively zooming out by increasing the distance from the camera to $P$ in the calculations.

As mentioned in the orthographic projection project, in all mainstream graphics applications, these calculations are performed through matrix multiplication, which can encode other information like transformations and is hardware-optimized. This matrix has a dimension of 4x4, meaning that the 3D coordinates must be expressed with four values. This is accomplished by converting them to homogenous coordinates $(x, y, z, w)$ such that in converting homogenous to Cartesian coordinates, each coordinate is divided by $w$.

$$
(x, y, z, w) \rightarrow(\frac{x}{w}, \frac{y}{w}, \frac{z}{w})
$$

Since in perspective projection, obtaining the projected coordinates is done through dividing coordinates by $-z$ of point $P$, we can set $w = -z$. The coordinates are then multiplied by the matrix and converted back to Cartesian coordinates where they are divided by $w = -z$.


$$
\begin{bmatrix}
1 & 0 & 0 & 0 \\
0 & 1 & 0 & 0 \\
0 & 0 & -1 & 0 \\
0 & 0 & -1 & 0 \\
\end{bmatrix}
\begin{bmatrix}
x \\
y \\
z \\
w \\
\end{bmatrix}
=
\begin{bmatrix}
x \\
y \\
-z \\
w=-z \\
\end{bmatrix}
\rightarrow (\frac{x}{-z}, \frac{y}{-z}, 1)
$$

There are many more aspects of perspective projection, including clipping planes, normalizing the $z$ coordinate to retain depth information, and changing the field of view. They all stem from the same principles and are extensions of the basic geometry used to find the projected coordinates on the canvas.

For further reading, I suggest 
<a href="https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/building-basic-perspective-projection-matrix"
target="_blank">Scratchapixel</a>, which goes into more depth and includes the extensions mentioned above.

<iframe width="560" height="315" src="https://www.youtube.com/embed/n0EWsYSBvXU" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>