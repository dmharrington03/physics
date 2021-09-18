---
title: Inverse Kinematics
date: 2021-09-04T09:28:36.992Z
description: very epic
---

> The most important tool of the theoretical physicist is his wastebasket.
> 
> <footer>Albert Einstein</footer>

---

### Background

Kinematics solvers are divided into two main categories: forward and inverse. Forward kinematics attempts to find a target point from a set of conditions, which in this example are joint angles for an arm. This is relatively simple to implement using basic trigonometry. Inverse kinematics, as its name suggests, does the opposite. Given a target point, what set of conditions (i.e., joint angles) will lead to that target point?

Inverse kinematics (IK) is an important problem in fields like robotics, where joint angles must be calculated to move the end of an arm to a known desired location.

Implementing inverse kinematics is not as easy as forward kinematics. Some exact methods use computationally expensive operations that may not guarantee a solution in all cases. However, an algorithm published in 2011 provides a numerical solution that is both fast and easy to implement called FABRIK, which we'll use in this project. FABRIK stands for Forward And Backward Reaching Inverse Kinematics and works by repeatedly iterating forward and backward along the joint-arm system, finding differences in the positions of points and their target points and updating those positions accordingly.

### Algorithm

For an in-depth explanation of FABRIK and how it works, I recommend [this video](https://www.youtube.com/watch?v=UNoX65PRehA) by EgoMoose.

FABRIK simplifies the problem of IK by dividing it into multiple smaller problems of points on a line. Each line segment has two points on either end, $P_A$ and $P_B$. It iteratively goes through each point, comparing it to a target point, and updates the position of the previous point to be in the direction of the target point while keeping the same segment length. The first cycles "backwards", from the green point to the red point. It then repeats "forwards" from the red point to the green. This is repeated until the difference between the target point and the end point is smaller than some set value.

The basic process for the backward pass is outlined in figure 1.

![diagram of steps of FABRIK](fig_1.png)
*Fig. 1 - FABRIK Backward Pass Algorithm Outline*

The steps, where $P_T$ is the target point.
1. Find the displacement vector, $\overrightarrow{D}$, from $P_T$ to $P_A$.
2. Normalize vector $\overrightarrow{D}$, so it has a magnitude of one, denoted by $\hat{D}$.
3. Multiply $\hat{D}$ by the scalar length of segment $AB$. Moving along this vector from point $P_T$ is where the new location of $P_A$ will be, denoted by $P'_A$. Move $P_B$ to $P_T$ to get $P'_B$. Segment $A'B'$ has the same length as $AB$.
4. Repeat, setting the new $P_T$ to $P'_A$, the new $P_B$ to the original $P_A$, and $P_A$ to the next point down the arm.

The process is almost the same for the forward pass. At the end of the backward pass, the first point on the left will have moved from the original $P_0$, according to the algorithm. If you want the end to move, this is fine, but for a stationary point like in our simulation, another pass is required, this time with $P_T$ set to the original position of $P_0$ and iterating from left to right (or whatever the opposite direction of the backward pass happens to be). It is therefore necessary to keep track of the original $P_0$, so I made a separate variable to hold its coordinates.

### Implementation Notes

Coming soon