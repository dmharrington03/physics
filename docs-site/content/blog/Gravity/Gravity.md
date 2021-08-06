---
title: Gravity
date: 2021-07-10T09:28:36.992Z
description: very epic
---

> Nothing happens until something moves
> 
> <footer>Albert Einstein</footer>

---

Gravity is classically one of the four fundamental forces. Yet such a complicated and strange force is expressed simply by an equation derived by Isaac Newton in the 17th century.

$$
F = G\frac{m_1m_2}{r^2}
$$

This equation relates the masses and radii of two objects to the force of gravity attracting them. In a solar system, these objects are the stars and planets, and that is what this simulation will focus on.

In reality, every object attracts every other object due to gravity. However, both to experiment with the simple side of orbital mechanics and reduce the computational load, we can just calculate the forces between the sun and planets and ignore the planet-planet interactions.

Another assumption we can make is that the sun is not affected by the planets' gravitational pull. In our solar system, the sun is about a million times as massive as the Earth, so the Earth's effect on it is comparatively small.

It is convenient to create a planet class that inherits from SFML's CircleShape class. It will hold a mass, velocity vector, and allow use of the inherited position setters, getters, and drawing to the window.


