---
title: Inverse Kinematics
date: 2021-09-04T09:28:36.992Z
description: very epic
---

> The most important tool of the theoretical physicist is his wastebasket.
> 
> <footer>Albert Einstein</footer>

---

Kinematics solvers are divided into two main categories: forward and inverse. Forward kinematics attempts to find a target point from a set of conditions, which in this example are joint angles for an arm. This is relatively simple to implement using basic trigonometry. Inverse kinematics, as its name suggests, does the opposite. Given a target point, what set of conditions (i.e., joint angles) will lead to that target point?

Inverse kinematics (IK) is an important problem in fields like robotics, where joint angles must be calculated to move the end of an arm to a known desired location.

Implementing inverse kinematics is not as easy as forward kinematics. Some exact methods use computationally expensive operations that may not guarantee a solution in all cases. However, an algorithm published in 2011 provides a numerical solution that is both fast and easy to implement called FABRIK, which is used in this project. FABRIK stands for Forward And Backward Reaching Inverse Kinematics and works by repeatedly iterating forward and backward along the joint-arm system, finding differences in the positions of points and their target points and updating them accordingly.

