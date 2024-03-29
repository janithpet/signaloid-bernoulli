[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-dark-v6.png#gh-dark-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=https://github.com/janithpet/signaloid-bernoulli#gh-dark-mode-only)
[<img src="https://assets.signaloid.io/add-to-signaloid-cloud-logo-light-v6.png#gh-light-mode-only" alt="[Add to signaloid.io]" height="30">](https://signaloid.io/repositories?connect=https://github.com/janithpet/signaloid-bernoulli#gh-light-mode-only)

# Calculating Lift using Bernoulli's Principle
This repository contains an implementation of a simple model of lift that uses Bernoulli's Principle. The model incorporates uncertainty in some measurements using the tools provided by the [Signaloid Cloud Developer Platform](https://signaloid.io).

We ran experiments to verify the effects of different choices available for cores on the [Signaloid Cloud Developer Platform](https://signaloid.io). The results of these can be seen in the [Results](#results) section.

## Usage
This repository can be run locally on your own machine (tested on macOS 14.0) and on the [Signaloid Cloud Developer Platform](https://signaloid.io).

### Local
To run this code locally, first clone the repository. Then, run the following from the root of the repository:
```bash
make run
```

*This assumes that you have a copy of `gcc` and `make` installed on your machine. If you do not have these, please refer to [`Makefile`](Makefile) to see the build setup for this repository and translate that to your build system.*

The output of this should look like:

<img width="288" alt="image" src="https://github.com/janithpet/signaloid-bernoulli/assets/22471198/03b81de1-bdaf-4b4b-835c-8eefb754cd24">

*The `local` version of this code doesn't contain any uncertainty because it is generally only used to debug. All distributions of uncertain values are collapsed to their mean values.*

Other `make` commands include `make clean` to remove all generated files, `make docs` to generate the documentation, and `make build` to build the object files and final executable without running it.

### Signaloid Cloud Developer Platform
To run on the [Signaloid Cloud Developer Platform](https://signaloid.io), simply click on the [`add to signaloid.io`](https://signaloid.io/repositories?connect=https://github.com/janithpet/signaloid-bernoulli#gh-dark-mode-only) button on the top of this README. Assuming you already have an account set up, this will add this repository to your [Signaloid Cloud Developer Platform](https://signaloid.io) account. You can then run the code by clicking on the `Run` button on this repository's card on the [Repository page](https://signaloid.io/repositories).

The output on the C0-S+ core looks like:

<img width="509" alt="image" src="https://github.com/janithpet/signaloid-bernoulli/assets/22471198/f27f8340-d24f-4331-84d4-6a3483e5eeb7">

## Problem Setup
The problem at hand is to use Bernoulli's Principle to calculate the lift generated by a wing by making velocity measures using pitot tubes. However, since little else is specified, we make the following assumptions:

### Assumptions about the fluid
- The fluid is air.
- The fluid (air) is incompressible.
- The fluid (air) is inviscid.
- The experiments are carried out at sea level; at any other height, the air density (see point below) will be different.
- The air density is assumed to be a known constant of 1.225 $kgm^{-3}$. The number chosen is the standard value for air at sea level; typically we would expect this number to be different while air is flowing, but since we are assuming the fluid is incompressible, we thought this value was good enough.

### Assumptions about the wing and simulated 'test' setup
- The airfoil is NACA-6412. We assumed an arbitrary airfoil to calculate realistic fluid velocities above and below the airfoil. The NACA-6412 airfoil looks like:
  <img width="874" alt="image" src="https://github.com/janithpet/signaloid-bernoulli/assets/22471198/adae13cd-c746-4313-a2d1-bf0a870520a5">
- The surface area of the airfoil is $1$ $m^2$.
- The wing is assumed to be set up in such a way that 3D effects are negligible. Therefore, the wing is treated as if it is 2D.
- The air speed is constant at 0.1Ma $\sim$ $34.3$ $ms^{-1}$.
- The airfoil is at an angle of attack of $5^\circ$.
- Two pitot tubes of the same specification are attached to the top and bottom of the airfoil (at approximately 30% of the chord length); see the [section below](#are-2-pitot-tubes-enough) for an analysis of this assumption.

### Assumptions about the pitot tubes
- They operate using a differential pressure sensor. Therefore, they can directly measure the difference between the static pressure and the stagnation pressure (see the [Bernoulli's Principle](#bernoullis-principle) section below).
- They have a 0.5% full-scale error [[1]](https://www.surreysensors.com/article/uncertain-pitot-static-probe/).
- They have a range $0$ - $3650$ $Pa$.

## Theory
### Bernoulli's Principle
Bernoulli's Principle is a key relationship in fluid dynamics that can be derived from the conservation of energy [[5]](https://www.mheducation.com/highered/product/fundamentals-aerodynamics-anderson/M9781259129919.html). It is generally applied to ideal fluids that are incompressible and inviscid. If we assume that any variations in height are negligible, then Bernoulli's Principle states that the sum of the static and dynamic pressures are constant:

$$p + p^{dyn} = p^{stag} = constant,$$
where
- $p$ is the static pressure of the fluid. This is the pressure value we obtain if we measure the pressure of a moving fluid.
- $p^{dyn}$ is the dynamic pressure of the fluid. This is the *kinetic energy* component of the equation; it is the *pressure due to motion*. If the velocity of the fluid at a point is $u$, then the dynamic pressure is

$$p^{dyn} = \frac{1}{2}\rho u^2,$$
where $\rho$ is the density of the fluid.

- $p^{stag}$ is the stagnation pressure of the fluid. This is the pressure value we obtain if we measure the pressure of the fluid when it is not moving. This is also called the *total pressure* of the fluid.

### Pitot tubes
A pitot tube is a device that measures the velocity of a moving fluid at a point. It does this by measuring the difference $\Delta p_{pitot} = p^{stag} - p$ between the stagnation pressure $p^{stag}$ and the static pressure $p$. According to Bernoulli's Principle, this gives us the dynamic pressure of the fluid at the measured point. Therefore, $u$ is given by:

$$u = \sqrt{\frac{2\Delta p_{pitot}}{\rho}}.$$

### Measuring lift using Bernoulli's Principle
A simple model of how a wing works is that the wing causes the air to move faster above the wing than below it. Let $u_{top}$ and $u_{bottom}$ be the velocities of the air above and below the wing respectively. Then, Bernoulli's Principle gives us:

$$p_{top} + \frac{1}{2}\rho u_{top}^2 = p_{bottom} + \frac{1}{2}\rho u_{bottom}^2.$$

Therefore, the difference in pressure between the top and bottom of the wing, $\Delta p_{wing}$ is given by:

$$\Delta p_{wing} = p_{top} - p_{bottom} = \frac{1}{2}\rho (u_{bottom}^2 - u_{top}^2).$$
Since $u_{bottom} < u_{top} \implies \Delta p_{wing} < 0$, i.e. the pressure below the wing is higher than the pressure above the wing. This pressure difference acts on the surface area of the wing an upward force that is called lift. Since $\text{force} = \text{pressure}\times\text{area}$, we can calculate the lift $L$ generated by the wing using:

$$L = \Delta p_{wing} \times S = \frac{1}{2}\rho S(u_{top}^2 - u_{bottom}^2),$$
where $S$ is the surface area ($\text{chord length} \times \text{span}$) of the wing.

*This simple model is known to give approximately correct results [\[2](https://www1.grc.nasa.gov/beginners-guide-to-aeronautics/bernoulli-and-newton/),[3\]](https://www3.eng.cam.ac.uk/outreach/Project-resources/Wind-turbine/howwingswork.pdf), but isn't necessarily the most physically-correct model of how lift is generated [[3]](https://www3.eng.cam.ac.uk/outreach/Project-resources/Wind-turbine/howwingswork.pdf).*

## Incorporating measurement uncertainty
Measurements are inherently uncertain. We therefore incorporate uncertainty in the measurement of velocity using the pitot tubes. See [the section on assumptions](#assumptions-about-the-pitot-tubes) for the uncertainty values we used.

In the implementation, we incorporate uncertainty using the [Signaloid UxHw Hardware API](https://docs.signaloid.io/docs/hardware-api/). We use the function `UxHwDoubleUniformDist` function to add uniform noise.

## Implementation Details
For documentation, follow the docstrings in the code (see the [`src/`](src) and [`local-include/`](local-include) folders), or open the documentation in [`docs/html/index.html`](docs/html/index.html) of this repository.

In the rest of this section, we detail how we obtained the values of the velocities of the air and the uncertainty in the measuring devices.

### The velocities of the air
The velocity of the air above and below the airfoil was determined using [Xfoil [4]](https://web.mit.edu/drela/Public/web/xfoil/). We obtained the distributions of the Coefficient of Pressure $C_p$ on the airfoil on the top and bottom surfaces. The velocities were then calculated using the following formula [[5]](https://www.mheducation.com/highered/product/fundamentals-aerodynamics-anderson/M9781259129919.html):
$$u = u_\infty \sqrt{1 - C_p},$$
where $u_\infty$ is the free-stream velocity of the air (we assumed this was 0.1Ma). In fact, this equation itself is also derived from Bernoulli's Principle by applying the definition of $C_p$.

The complete simulated values of $C_p$ can be found in [`data/cp.dat`](data/cp.dat). Accordingly, the top velocity was 54.59 $ms^{-1}$ and the bottom velocity was 26.81 $ms^{-1}$.

### The uncertainty in the measuring devices
- The range of the pitot tube was obtained as twice the maximum pressure difference that would resulted from the velocities obtained above.
- The uncertainty of the pitot tube was obtained using [[1]](ttps://www.surreysensors.com/article/uncertain-pitot-static-probe/).

## Results
To analyse the effects of the choice of cores that the [Signaloid Cloud Developer Platform](https://signaloid.io) offers, we ran the code in this repository on the core configurations in the table below. We also ran a local Monte Carlo simulation (with 1,000,000 Monte Carlo samples) to obtain a *ground truth* distribution of the calculated lift.  We then computed the Wassserstein distance [[6]](https://link.springer.com/chapter/10.1007/978-3-540-71050-9_6#citeas) between the distributions obtained from the different Signaloid cores and the ground truth distribution.

The table below shows the results of these experiments.

<center>

| Core | Representation Size / Number of Samples | Autocorrelation | Wasserstein Distance |
|------|----------------------------------------|-----------------|----------------------|
| Athens (C0) | 4 | Yes | 1.014 |
| Athens (C0)| 64 | Yes | 0.097 |
| Athens (C0)| 256 | Yes | 0.036 |
| Athens (C0)| 2048 | Yes | 0.018 |
| Athens (C0)| 8192 | Yes | 0.011 |
| Athens (C0)| 8192 | No | 3.651 |
| Local | 1,000,000 | N.A.| N.A.|

</center>

Images of the plots of the probability distributions for each of the cases above can be seen in the [`plots/`](plots) folder.

### Analysis
- As the representation size increases, the Wasserstein distance to the ground truth decreases.
- For this particular problem, it was beneficial to turn autocorrelation tracking on, since we can see that the Wasserstein distance for a representation size of 8192 is higher when it is turned off.

## Are 2 pitot tubes enough?
In order to check whether the assumption that 2 pitot tubes are enough, we calculated the simulated lift force generated by this wing using Xfoil. Xfoil provides a value for the coefficient of lift $C_l$ for the airfoil. This value was 1.3623. Given this, the simulated lift $L_{sim}$ can be calculated using the lift equation:

$$L_{sim} = \frac{1}{2}\rho u_\infty^2 S C_l.$$
Using $u_\infty = 34.3$ $ms^{-1}$ and $S = 1$ $m^2$, we get $L_{sim} = 985.74$ $N$. The value we obtained (1385.07 $N$) is 40.51% higher. This suggests that this model is not very good.

## Future Work
- Incorporate uncertainty in other parameters, such as the surface area of the airfoil and the air density.
- Perhaps there is a better position along the chord of the airfoil to place the pitot tubes. This could be investigated. The current position was chosen arbitrarily.
- Use more pitot tubes along the span of the airfoil situated at the same distance from the leading edge, and average the measurements. This can simulate taking multiple measurements of the same quantity (since 3D effects are ignored).
- A more realistic setup could be to make more velocity measurements along the chord of the airfoil, and then integrate along the shape of the airfoil to obtain the lift. This could give a more realistic value of the lift.

## References
[[1] https://www.surreysensors.com/article/uncertain-pitot-static-probe/](https://www.surreysensors.com/article/uncertain-pitot-static-probe/)

[[2] *NASA*; Bernoulli and Newton (Beginner's Guide to Aeronautics)](https://www1.grc.nasa.gov/beginners-guide-to-aeronautics/bernoulli-and-newton/)

[[3] *Babinsky, Holger*; How do wings work?](https://www3.eng.cam.ac.uk/outreach/Project-resources/Wind-turbine/howwingswork.pdf)

[[4] *Drela, Mark*; Xfoil: Subsonic Airfoil Development System](https://web.mit.edu/drela/Public/web/xfoil/)

[[5] *Anderson, John D.* Fundamentals of Aerodynamics](https://www.mheducation.com/highered/product/fundamentals-aerodynamics-anderson/M9781259129919.html)

[[6] *Villani, C.* The Wasserstein distances](https://link.springer.com/chapter/10.1007/978-3-540-71050-9_6#citeas)

## Known Issues
- The doxygen documentation of the main page is slightly broken because it doesn't seem to easily parse the Latex equations, nor does it handle images correctly.
- The [`docs/`](docs) folder can be automated into a Github Action so that any changes to the documentation is automatically updated.
