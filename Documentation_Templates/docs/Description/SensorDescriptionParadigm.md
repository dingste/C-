### Preface
This chapter describes some aspects as sensors can be seen. These different aspects are covered by different logical units. This also means that the different aspects define different levels of abstraction.
This description may also be a paradigm sheet to describe each of the used sensors in a unique way.

### Physical sensor / Hardware

#### Description
This is the real physical sensor; its description basically is the data sheet as provided by the manufacturer containing information about
- intended use of the sensor
- physical aspects as there are:
  <br>- principle of measuring
  <br>- physical interface(s), i.e. how the measured physical value is represented (voltage, current, serial interface etc.)
  <br>- measuring limits
  <br>- environment limits / requirements (ambient temperature, humidity and so on)
  <br>-....
- algorithm to retrieve real physical value from representation
- ...

In our case this abstraction level is represented by Blood Unit (BU)

#### Technical Requirements

| ID | Description |
| --- | --- |
| xx | physical sensor |

#### Functional Requirements

| ID | Description |
| --- | --- |
| xx | provides sensor data as physical data (voltage, current, digital etc.) |

### Physical sensor / Software = Sensor driver
This is software's point of view, i.e.
- physical interface as required by the sensor (ADC, UART, etc.)
- interface driver: initializing and retrieving the sensor value as provided by the sensor itself
- calculating the physical value from the provided sensor representation
- providing this sensor value to other units

In our case this abstraction level (driver layer) is represented by Measurement Unit (MU).

#### Technical Requirements

| ID | Description |
| --- | --- |
| xx | physical sensor |
| xx | appropriate hardware interface according to sensor's requirements |
| xx | interface to the upper units |

#### Functional Requirements

| ID | Description |
| --- | --- |
| xx | gets sensor data from physical value via hardware interface depending on how the sensor provides the date (ADC, UART etc.) |
| xx | transforms physical sensor data (ADC-/UART-Data etc.) to physical value (f.e. Temp[°C]) |
| xx | additionally check for error and/or plausibility |
| xx | provides sensor value (and error results) to other units |

### Logical sensor / Software = Sensor API
This is the application's point of view, i.e.
- retrieving the sensor value from the driver layer
- proofing against other conditions and requirements:
  <br>- error conditions
  <br>- application requirements
  <br>- interfering conditions with other sensors
  <br>- plausibility checks
  <br>-....
- generating error / emergency messages
- providing this proofed sensor value to other units

In our case this abstraction level (driver layer) is represented by Gateway Safety Unit (GSU).

#### Technical Requirements

| ID | Description |
| --- | --- |
| xx | interface to the sensor driver; this may be a hardware interface (if the driver resides on an other module) or a software interface (driver and API are on the same module) |

#### Functional Requirements

| ID | Description |
| --- | --- |
| xx | gets sensor data via interface |
| xx | more proofing for error and/or plausibility, i.e. if there are dependencies between sensors |
| xx | thus provides proofed values for each sensor |

### Conclusion
This approach is more vertical as the in the opposite to [Component Overview](../ComponentOverview) representing logical layers which is more a horizontal viewpoint.
The following diagram may illustrate this a bit more:

![General Sensor Description](../Diagrams/GeneralSensorDescription.svg)

 It is important to see that this is a logical point of view; the real implementation of course depends on hardware design. So it is possible to implement the sensor driver and the sensor API on the same hardware module or on different hardware modules depending on other requirements or design specifications!
