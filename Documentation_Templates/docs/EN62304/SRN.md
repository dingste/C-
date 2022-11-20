# Software Release Notes (0.01)

## Introduction

First release of some kind of firmwares. Explicite build for simulation (on linux-pc) and STM32F7 development board. Validation of so far skeleton, baremetal boilerplate and EN62304 SDP.
    
## Release Identification

commit #7915cb2d 

### Solved Issues

Self defined Reqs from software department.

#### Technical Requirements
 
| ID           | Description                                                                    |
| ------------ | ------------------------------------------------------------------------------ |
| STR-2 | Engine Processing State accesable from Engine Continent                                                |
| STR-3  | Engine Continent connection to Gateway and Safety Continent                                     |
| STR-4  | Engine Continent connection to Physical Continent                                               |
| STR-5  | Engine Continent provide interface for therapy control and monitoring at low level as fall-back |
| STR-6  | Engine Continent provide signals about this unit                                                |
| STR-7 | Alarm United Sates list of all possible systemwide alarms                                         |
| STR-8 | Alarm United Sates format of an possible alarm                                                    |
| STR-9 | include and use of a State Machine                                             |
| STR-10 | Gateway and Safety Continent transport way to User Interaction Continent                                    |
| STR-11 | Engine Sensors State derivate from Measurement Continent                                            |
| STR-12 | Physical Sensors State derivate from Measurement Continent                                            |
| STR-13  | Measurement Continent connection to GSU                                                              |
| STR-14  | Measurement Continent connection to PC                                                               |
| STR-15  | Physical Continent connection to MC                                                               |
| STR-16  | Physical Continent connection to EC                                                               |
| STR-17  | Blood State resist in PC                                                                   |
| STR-18  | Blood State connection of patient sensors about blood                                      |
| STR-19  | Gas State resist in PC                                                                   |
| STR-20  | Gas State connection of gas blender sensors                                              |
| STR-21 | User Interaction Continent transport way to GSC                                                           |
 
#### Functional Requirements
 
| ID           | Description                                                                                          |
| ------------ | ---------------------------------------------------------------------------------------------------- |
| SFR-7 | Engine Processing State process values from liter per minute or similar to enging understandable                             |
| SFR-8 | Engine Processing State process values from enging understandable to measurement continent understandable                    |
| SFR-9  | Engine Continent  transmit (send) **generated engine data** as well defined protocol to Physical Continent             |
| SFR-10  | Engine Continent  transmit (send) **raw sensor data** as well defined protocol to MU                                   |
| SFR-11  | Engine Continent  transmit (receive) systemspecific therapy data/engine control from Gateway and Safety Continent      |
| SFR-12  | Engine Continent  transmit (receive) enginespecific control from medical Technican                                     |
| SFR-13  | Engine Continent  direct signaling of alarm etc by engine sensors                                                      |
| SFR-14 | Alarm United Sates notification of alarm                                                                                |
| SFR-15 | Alarm United Sates throw/assertion/store of alarm                                                                       |
| SFR-16 | Alarm United Sates mark of named alarm as readed and acknowlidge                                                        |
| Req-TVS-F-01 | receive user action to change a system state                                                         |
| Req-TVS-F-02 | notify of successfull change of system state                                                         |
| Req-TVS-F-03 | send current system state                                                                            |
| SFR-17 | Gateway and Safety Continent  transmit (receive) user settings as well defined protocol                                            |
| SFR-18 | Gateway and Safety Continent  plausibly check of user settings                                                                     |
| SFR-19 | Gateway and Safety Continent  generate therapy data/schema for following components                                                |
| SFR-20 | Gateway and Safety Continent  convert processing data from Measurement Continent for user                                          |
| SFR-21 | Gateway and Safety Continent  plausibly check of Measurement Continent compare to therapy                                          |
| SFR-22 | Gateway and Safety Continent  transmit (send) sensor/therapy data as well defined protocol                                         |
| SFR-23 | Gateway and Safety Continent  transmit (send) engine as well defined protocol                                                      |
| SFR-24 | Gateway and Safety Continent  transmit (send) alarms as well defined protocol                                                      |
| SFR-25 | Engine Sensors State process data                                                                                         |
| SFR-26 | Physical Sensors State process data                                                                                         |
| SFR-26  | Measurement Continent transmit (send) **all sensor data** as well defined protocol                                         |
| SFR-27  | Measurement Continent transmit (send) **generated data** as well defined protocol                                          |
| SFR-29  | Measurement Continent transmit (receive) collect all raw sensor data trough pysical continent (including engine continent) |
| SFR-30  | Physical Continent transmit (send) **accepted motor data** as well defined protocol from EC to MC                       |
| SFR-31  | Physical Continent transmit (send) **raw sensor data (patient)** as well defined protocol to MC                         |
| SFR-32  | Physical Continent use of pump(s)                                                                                       |
| SFR-33  | Blood State collect real sensor data at patient                                                                  |
| SFR-34  | Gas State collect real sensor data at patient about gas                                                        |
| SFR-35 | User Interaction Continent transmit (send) user setttings as well defined protocol                                              |
| SFR-36 | User Interaction Continent transmit (receive) sensor data as well defined protocol                                              |
| SFR-37 | User Interaction Continent transmit (receive) alarms as well defined protocol                                                   |

### Unresolved Issues

Not all Reqs are defined. A lot of projectr elevant issues aren't currently adressed.

## Remarks

GUI is minimal (in functionality and size)