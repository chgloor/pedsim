

PedSim Behavior and Background
==============================

Here follows a small introduction to the technique used in the code of
PEDSIM.

The simulation core takes care of the physical
aspects of the system, such as interaction of the agents with the
environment or with each other.  Typical simulation techniques for such
problems are:

- In _microscopic simulations_ each particle is represented individually.
- In macroscopic or _field-based simulations_, particles are aggregated into fields.  The corresponding mathematical models are partial differential equations, which need to be discretized for computer implementations.
- It is possible to combine microscopic and field-based methods, which is sometimes called <b>smooth particle hydrodynamics</b>. In SPH, the individuality of each particle is maintained.  During each time step, particles are aggregated to field quantities such as density, then velocities are computed from these densities, and then each individual particle is moved according to these macroscopic velocities.
- As a fourth method, somewhat on the side, exist the queuing simulations from operations research.  Here, particles move in a networks of queues, where each queue has a service rate.  Once a particle is served, it moves into the next queue.

For PEDSIM, we need to maintain individual particles, since
they need to be able to make individual decisions, such as route
choices, throughout the simulation.  This immediately rules out
field-based methods.  We also need a realistic representation of
inter-pedestrian interactions, which rules out both the queue models
and the SPH models.

For microscopic simulations, there are essentially two techniques:
methods based on _coupled differential equations_, and _cellular automata
(CA)_ models.  In our situation, it is important that agents can move
in arbitrary directions without artifacts caused by the modeling
technique, which essentially rules out CA techniques.
A generic coupled differential equation model for pedestrian movement
is the _social force model_ by [Helbing et al.](http://www.helbing.org/), 
see e.g. [this paper](http://www.cs.uu.nl/docs/vakken/mcrs/papers/10.pdf).

\f[
	m_i \, \frac{d\mathbf{v}_i}{dt} =
	m_i \, \frac{\mathbf{v}_i^0 - \mathbf{v}_i}{\tau_i}
	+ \sum_{j\ne i}{\mathbf{f}_{ij}}
	+ \sum_{W}{\mathbf{f}_{iW}}
\f]

where _m_ is the mass of the pedestrian and _v_ its velocity.
_v0_ is its desired velocity; in consequence, the first term on
the RHS models exponential approach to that desired velocity, with
a time constant _tau_.  The second term on the RHS models
pedestrian interaction, and the third models interaction of the
pedestrian with the environment.  The _social force model_ should be
considered as an example on how to model the pedestrian interaction.
It is easy to understand and simple to implement.  However,  a future
implementation of PEDSIM might use a different model.

Pedestrians interact with each other, which includes avoiding
collisions (short range interaction), and attraction to enemies  (long
range, which represents the "will" of the agents.  This attraction to
enemies is just an example and should be replaced by some more
complicated and meaningful functions).  Also avoidance of objects like
trees is implemented.


This simulation also works close to obstacles, as are found
e.g. close to buildings. Also the simulation of the inside of
buildings is possible, which allows the usage of the
same framework for e.g. evacuation simulation.

Any mobility simulation system does not just consist of the mobility
simulation itself (which controls the physical constraints of the
agents in a virtual world), but also of modules that compute higher
level strategies of the agents. In fact, it makes sense to consider
the physical and the mental world completely separately.

- The <b>Physical Layer</b> (the mobility simulation) takes care of
the physical aspects of the system, such as movement of the agents,
interaction of the agents with the environment, or interactions
between the agents.

- The <b>Mental Layers</b> implement the humans intelligence (well,
at least a part of it), which improves the agent's behavior. Actually,
if the mental layer strategy are very sophisticated, there is no need
for the _social force model_ in the physical simulation - all the
forces can be set to zero. The <b>Look Ahead</b> mental strategy tells each
agent to look for other agents in front of him, an count the ones at
the left side and the ones at the right side. It then will walk into
the direction where less other agents are. Collisions with walls and other pedestrians
are avoided by the pedestrian itself, and not by a constraint by the
underlying physical model.
Another example for a mental layer module is a <b>Route Generator</b>. It is not enough to
have agents walk around randomly; for realistic applications it is
necessary to generate plausible routes for each pedestrian. Being able
to compute routes, as the route generator does, only makes sense if
one knows the destinations for the agents. A technique in
transportation research is to generate a (say) day-long chain of
activities for each agent, and each activity's specific location.
There exist very sophisticated mental layer modules. There is for
example a <b>View Analyzer Module</b>, which describes to the system what individual
agents "see" as they move through the landscape. The agents field-of-view is
analyzed, and events are sent to the system describing what the agent
sees.

