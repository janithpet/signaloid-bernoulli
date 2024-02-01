[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-dark-v6.png#gh-dark-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=https://github.com/janithpet/signaloid-bernoulli#gh-dark-mode-only)
[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-light-v6.png#gh-light-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=https://github.com/janithpet/signaloid-bernoulli#gh-light-mode-only)

# Calculating Lift using Bernoilli's Principle
## Problem Setup
The problem at hand is to use Bernoulli's Principle to calculate the lift generated by a wing by making velocity measures using pitot-tubes. However, since little else is specified, we make the following assumptions:

### Assumptions about the fluid
- The fluid is air.
- The fluid (air) is incompressible.
- The fluid (air) is inviscid.
- The air density is assumed to be a known constant of 1.225 $kg/m^3$.

### Assumptions about the wing and simulated 'test' setup
- The airfoil is NACA-6412. We assumed this to calculate what realistic fluid velocities above and below the airfoil are. The NACA-6412 airfoil looks like:
  <img width="874" alt="image" src="https://github.com/janithpet/signaloid-bernoulli/assets/22471198/adae13cd-c746-4313-a2d1-bf0a870520a5">
- The surface area of the airfoil is $1$ $m^2$.
- The wing is assumed to be setup in such a way that 3D effects are neglegible. Therefore, the wing is treated as if it is 2D.
- The air speed is constant at 0.1Ma $\sim$ $34.3$ $ms^{-1}$.
- The airfoil is at an angle of attack of $5^\circ$.
- Two pitot-tubes of the same specification are attached to the top and bottom of the airfoil (at approximately 30% of the chord length); see section below for an analysis if this assumption.

### Assumptions about the pitot-tubes
- They operate using a differential pressure sensor. Therefore, they can directly measure the difference between the static pressure and the stagnation pressure (see [Bernoulli's Principle](#bernoullis-principle) section below).
- They have a 0.5% full-scale error [[1]](https://www.surreysensors.com/article/uncertain-pitot-static-probe/).
- They have a rangoe 0-250Pa [[1]](https://www.surreysensors.com/article/uncertain-pitot-static-probe/).

## Theory
### Bernoulli's Principle
Bernoulli's Principle is a key relationship in fluid dynamics that can be derived from the conservation of energy. It is generally applied to ideal fluids that are incompressible and inviscid. If we assume that any variations in height is neglegible, then Bernoulli's Principle simply states the sum of the static and dynamic pressures are constant:

$$P^{static} + P^{dynamic} = P^{stagnation} = constant,$$
where
- $P^{static}$ is the static pressure of the fluid. This is the pressure value we obtain if we measure the pressure of a moving fluid.
- $P^{dynamic}$ is the dynamic pressure of the fluid. This is the 'kinetic energy' component of the fluid. If the velocity of the fluid at a point is $u$, then the dynamic pressure is

$$P^{dynamic} = \frac{1}{2}\rho u^2,$$
where $\rho$ is the density of the fluid.

- $P^{stagnation}$ is the stagnation pressure of the fluid. This is the pressure value we obtain if we measure the pressure of a fluid that is not moving. This is also called the 'total pressure' of the fluid.

### Pitot-tubes
A pitot-tube is a device that measures the velocity of a fluid at a point. It does this by measuring the difference $\Delta p_{pitot}$ between the static pressure $P^{static}$ and the stagnation pressure $P^{stagnation}$. This gives us the dynamic pressure from which the velocity of the fluid $u$ is given by:

$$u = \sqrt{\frac{2\Delta p_{pitot}}{\rho}}.$$

### Measuring lift using Bernoulli's Principle
A simple model of how a wing works is that the airfoil causes the air to move faster above the wing than below it. Let $u_{top}$ and $u_{bottom}$ be the velocities of the air above and below the wing respectively. Then, Bernoulli's Principle gives us:

$$P_{\text{static, top}} + \frac{1}{2}\rho u_{top}^2 = P_{\text{static, bottom}} + \frac{1}{2}\rho u_{bottom}^2.$$

Therefore, the difference in pressure between the top and bottom of the wing, $\Delta p_{wing}$ is given by:

$$\Delta p_{wing} = P_{\text{static, top}} - P_{\text{static, bottom}} = \frac{1}{2}\rho (u_{bottom}^2 - u_{top}^2).$$

Since $u_{bottom} < u_{top} \implies \Delta p_{wing} < 0$, i.e. the pressure below the wing is higher than the pressure above the wing. This pressure difference acts on the surface area of the wing an upward force that is called lift.

Note: This simple model is known to give sufficiently correct results [\[2](https://www1.grc.nasa.gov/beginners-guide-to-aeronautics/bernoulli-and-newton/),[3\]](https://www3.eng.cam.ac.uk/outreach/Project-resources/Wind-turbine/howwingswork.pdf), but isn't necessarily the most physically-correct model [[3]](https://www3.eng.cam.ac.uk/outreach/Project-resources/Wind-turbine/howwingswork.pdf).

## Incorporating measurement uncertainty


## Usage

### Local
To run this code locally, first clone the repository. Then, run
```bash
make run
```

The output of this looks:

<img width="349" alt="image" src="https://github.com/janithpet/signaloid-bernoulli/assets/22471198/496f2a8a-56eb-434d-b973-092073c32f8e">

*The `local` version of this code doesn't contain any uncertainty because it is generally only used to debug. All distributions of uncertain values are collapsed to their mean values.*

Other `make` commands include `make clean` to remove all generated files, `make docs` to generate the documentation and `make build` to build the object files and final executable.

### Signaloid Cloud Developer Platform
To run on the Signaloid Cloud Developer Platform, simply click on the `Add to Signaloid` button on top of this README. This will add this repository to your Signaloid Cloud Developer Platform account. You can then run the code by clicking on the `Run` button on the repository page.

## Implementation Details
For documentation, follow the docstrings in the code, or open the documentation in `docs/html/index.html` of this repository.

In the rest of this section, we detail how we obtained the values of the velocities of the air and the uncertainty in the measuring devices.

### The velocities of the air
The velocity of the air above and below the airfoil was determined using [Xfoil [4]](https://web.mit.edu/drela/Public/web/xfoil/). We obtained the distributions of the coefficient of pressure $C_p$ on the airfoil on the top and bottom surfaces. The velocities were then calculated using the following formula [[5]](https://www.mheducation.com/highered/product/fundamentals-aerodynamics-anderson/M9781259129919.html):
$$u = u_\infty \sqrt{1 - C_p},$$
where $u_\infty$ is the free-stream velocity of the air (we assumed this was 0.1Ma). In fact, this equation itself is also derived from Bernoulli's Principle by applying the definition of $C_p$.

The complete simulated values of $C_p$ can be found in `cp.dat`. Accordingly, the top velocity was 54.59 $ms^{-1}$ and the bottom velocity was 26.81 $ms^{-1}$.
### The uncertainty in the measuring devices
- The range of the pitot-tube was obtained as twice the maximum pressure difference that would been caused by the velocities obtained above.
- The uncertainty of the pitot-tube was obtained using [[1]](ttps://www.surreysensors.com/article/uncertain-pitot-static-probe/).

## Are 2 pitot-tubes enough?
In order to check whether the assumption that 2 pitot-tubes are enough, we calculated the simulated lift force generated by this wing using Xfoil. Xfoil provides a value for the coefficient of lift $C_l$ for the airfoil. This value was 1.3623. Given this, the simulated lift $L_{sim}$ can be calculated using the lift equation:

$$L_{sim} = \frac{1}{2}\rho u_\infty^2 S C_l,$$
where $S$ is the surface area of the airfoil. Using $u_\infty = 34.3$ $ms^{-1}$ and $S = 1$ $m^2$, we get $L_{sim} = 985.74$ $N$. The value we obtained (1130.67 $N$) is 14.70% higher.

## Future Work
- Incorporate uncertainty in other parameters, such as the surface area of the airfoil.
- Perhaps there is a better position along the chord of the airfoil to place the pitot-tubes. This could be investigated. The current position was chosen arbitrarily.
- Use more pitot-tubes along the span of the airfoil situated at the same distance from the leading edge, and average the measurements. This can simulate taking multiple measurements of the same quantity (since 3D effects are ignored).
- A more realistic setup could be to make more velocity measurements along the chord of the airfoil, and then integrate along the shape of the airfoil to obtain the lift. This could give a more realistic value of the lift.

## References
[[1] https://www.surreysensors.com/article/uncertain-pitot-static-probe/](https://www.surreysensors.com/article/uncertain-pitot-static-probe/)

[[2] *NASA*; Bernoulli and Newton (Beginner's Guide to Aeronautics)](https://www1.grc.nasa.gov/beginners-guide-to-aeronautics/bernoulli-and-newton/)

[[3] *Babinsky, Holger*; How do wings work?](https://www3.eng.cam.ac.uk/outreach/Project-resources/Wind-turbine/howwingswork.pdf)

[[4] *Drela, Mark*; Xfoil: Subsonic Airfoil Development System](https://web.mit.edu/drela/Public/web/xfoil/)

[[5] *Anderson, John D.* Fundamentals of Aerodynamics](https://www.mheducation.com/highered/product/fundamentals-aerodynamics-anderson/M9781259129919.html)
