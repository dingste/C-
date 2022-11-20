# Develop paradigm

We already introduced [basic planning concepts](../../Description/PlanningParadigm) before. Besides them there are some thought patterns which are very specific to the development of embedded software in contrast to a off the shelf software running on a PC. In most cases embedded software monitors and controls physical systems. It processes sensor data and decides on this how to set the actuators of the system. In most cases it communicates with the outside world (out of the perspective of the system) to present measured and/or processed data and allows for changing settings of the control part of the system. This whole concept implies a more or less unique representation of physical components in the software. For example, there is normally a component just controlling a motor and offering only functions for driving it to other software components. This implies that inside one project there are hardly any overlaps between different software components. Thus, many design patterns of software development which imply reusability of code and functions are not applicable here.

The most important patterns are *loose coupling* and *concisely defined, unique responsibility*. Each component needs a well defined interface which encapsulate its data and accessible functions. This simplifies the required (unit) tests and integration of the components in the whole system. Furthermore, every technical requirement can be mapped to one specific component. These components are virtual entities, they may be run on several microcontrollers in parallel (especially for components implementing communication requirements).




## Loose coupling
![PStructure](../Diagrams/rendered/PStructure.svg)


## Test
Test of _technical_ aspects only by Interfaces
Test of _functional_ aspects only by explizit business logic (ergo test logic)