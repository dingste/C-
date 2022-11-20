# Software Development Plan

## Introduction
The document describes the processes, activities and artifacts of software development for the project enECMO. It is based on the requirements of the EN 62304 and the Design Control Procedure as required by ISO 13485:2016 of AC Aircontrols GmbH. 
!!! ToDo
    Need link to the document describing this procedure.

All the aforementioned processes, activities and artifacts need the Market Requirement Document (MRD) as (design) input.

!!! ToDo
    Need link to the MRD.

### Scope
This document is intended for

 * The software development department of ELK GmbH (see Roles and Responsibilities)
 * Persons, who are involved in the certification of the device as medical device

This documents focusses on software related requirements derived from project specifications. However, this document does not replace development plans by other stakeholders or participants in the development process (e.g. hardware related processes).

### Roles and Responsibilities

| Role                    | Responsibility                                        | Certificated             |
| ----------------------- | ----------------------------------------------------- | ------------------------ |
| Project Management      | Jannis Sommer                                         | EN62304                  |
| Requirements Management | Jannis Sommer<br>Matthias Breier                      | EN62304<br>EN62304       |
| Software Management     | Matthias Breier                                       | EN62304                  |
| Developer               | Dieter Steuten<br>Matthias Breier<br>Thomas Schneider | EN62304<br>EN62304<br>-- |
| External Developer      | @GED {  }<br>@AC { Jan Consbruch }                    | --<br>EN62304            |
| Project Verification    | Jannis Sommer                                         | EN62304                  |


### Software Project Management
Although the different development stages (i.e. requirement definition, system specification, implementation, tests, verification, validation, etc.) are defined hierarchically, methods and techniques from agile software development are used during the project. In most of the cases this implies tight feedback loops at each and between development stages. Nevertheless, tasks and milestones have been defined in advance which ensure the proper execution and verification of all phases described in Life Cycle Model. 

All development tasks are formulated as *tickets* in the project's ticket system. Each ticket is assigned to a responsible person for this task.

### Software Safety Classification
The overall safety classification of the systems developed in this part of the project is class C. Therefore, this plan is designed according to EN 62304 Class C requirements unless otherwise stated.

## Life Cycle Model

Typically the life cycle model covers all stages of a product, i.e.

1. Creation
2. Maintenance
3. Decommissioning

In the IEC 62304 the scope of the life cycle model emphasizes the creation stage of the software. The maintenance process is referenced at a different part of the standard. 

### Development Phases

```plantuml format="svg"
rectangle "Software Requirements" as software_requirements
rectangle "Software Test" as software_test
rectangle "Software\nRelease Candidate" as release_candidate
rectangle "Software\nTest Candidate" as test_candidate
storage "Development" {
    storage "Implementation" as implementation
    storage "Integration" as integration
    storage "Test (Components)" as components_test
    storage "review (Architecture)" as architecture_review
    storage "review (Code)" as code_review
}

components_test --> architecture_review
implementation --> integration
architecture_review --> code_review
code_review --> implementation
integration --> components_test
architecture_review -r-> software_requirements
components_test --> software_test : "Ready For Testing "
software_requirements --> implementation : "Ready for Implementation"
software_test -r-> release_candidate : "Ready for Release"
software_test -l-> test_candidate : "Ready For Design Transfer"
'test_candidate --> software_requirements
```

The development process comprises three phases: input phase, development phase and output phase. The process is organized hierarchically, thus it is carried out only from *input phase* over *development phase* to *output phase*. The only exception is problems encountered during development phase which can only be resolved by changing system specifications. In that case the software development process must be initialized again with the modified design input and starts again in the input phase. 
The process refers to *development items*. These items comprises subgroups of related software requirements which are fulfilled by implementing the functionality they describe. In that way it is possible to deliver software releases with a well defined scope (i.e. development items) which can be employed in subsequent system developing phases (e.g. integration tests, validation, etc.) at several predefined points in time during the development of the whole software. Thus, several benefits of using agile methodology (e.g. tight feedback loops) may be enjoyed in the development process.


| Phase       | Actions                                                                                                                                                                                                                                                                                                                                                                                |
| ----------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Input       | Definition of software requirements based on system specifications. The latter is supported by software prototypes (coined *walking skeleton*).                                                                                                                                                                                                                                        |
| Development | Actual software development with short development cycles based on agile methodology with tests and architecture reviews which may lead to refined software requirements.                                                                                                                                                                                                              |
| Output      | Generation of either a *test candidate* or a *release candidate*.<br> The *test candidate* contains development items which needs to be validated and thus form an input for the next system development stages (e.g. integration). <br>The *release candidate* is based on a former test candidate, is well tested and well documented thus forms the end of the development process. |


### Milestones
There are four planned milestones which act as a quality gateway for each development item: before passing in the next phase of the project, design reviews shall be made for each of the milestone to ensure that the previous phase of was completed successfully. The last milestones are at least described in 'Software Artifacts' at [Software Development Environment (SDE)](SDE.md). 

| Milestone                 | Quality Gateway                                                                                                                                                                        |
| ------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Ready For Implementation  | One or more Software Requirements are specified                                                                                                                                        |
| Ready For Testing         | The development item is ready for testing as soon as all of its software requirements have been implemented and all open issues have been reviewed and none of them prohibits testing. |
| Ready For Design Transfer | The development item has been tested and the results indicate that it can be verified on a dedicated device, as test candidate                                                         |
| Ready For Release         | Release notes and all documents and tasks have been finished                                                                                                                           |

### Requirements
Software requirements are derived either from market requirements, system requirements or the following sources:

| Requirement scope       | Items                                                                                                                                                               |
| ----------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Functional requirements | Usecases (by [Software Usability Plan](SUP.md))<br> Component functionalities (by [Component Design Document](CDD.md))<br> Constants (e.g. limits, defaults, types) |
| Technical requirements  | Sensors<br>Actuators<br>Coding language <br> Target systems (e.g. CPU, Memory size) <br> Hardware Interfaces (e.g. SPI, I2C, RS232) <br> Building system            |
| Regulatory requirements | Risk controls which software must follows<br>SOUP software                                                                                                          |


#### Updates of Requirements
The software requirements shall be updated throughout the development process, including but not limited to these events:

 * User requirements / system requirements changes
 * Usability consideration
 * New risk identification
  
In case the software requirements changes:

 * The design and specification shall be updated accordingly
 * A risk review shall be performed (see [Software Risk Management](SDP.md#software-risk-management))

### Software Identification
All software code is submitted to a Git repository. During build process the build numbers will be attributed to the build software. See also [Software Development Environment (SDE)](SDE.md) document.

## Quality System
The quality system according to ISO 13485 is here:
!!! Note
    Insert link to QM handbook of AirControls

### Software Documentation Plan

```plantuml format="svg"
rectangle "Market Requirement Document (MRD)" as MRD
rectangle "Continuous-Driven Development Document (CDDD)" as CDDD #A9DCDF
rectangle "Generated Documents (EN 62304)" as GD
rectangle "Software Development Plan (SDP)" as SDP

MRD --> CDDD
SDP --> CDDD
CDDD --> GD
```

The software documentation system employed in this project is centered around the so called *Continuous-Driven Development Document (CDDD)*. It is actually a collection of smaller documents and fractional texts, graphs and source code extracts which are used to generate all the documents needed for project management and regulatory purposes. It is a "living" document meaning that all changes in the project are directly reflected in the documentation system. This ensures that the documentation is always synchronized with changes in the project structure, requirements, source code, etc. 

The content of the CDDD is derived from the MRD and interacts with the SDP (this part of the document) which is generated by it as well. 

From the CDDD all documents needed for project management and for regulatory purposes (including the documentation required by the IEC EN 62304). It is under version control so a baseline can easily be created for each development step.

#### Deliverable Documentation
The documentation shall be generated as EN 62304 compliant documentation guide for medical software of class C forces. Documentation is produced synchronized to Quality Gateway "Ready For Testing". Deliverable Documentation is this revision-safe PDF.


### Software Development Standards and Methods
The software is developed using a hybrid approach employing agile method and the v-model (as already mentioned in [life cycle model](SDP.md#life-cycle-model)). The agile approach with continuous integration will ensure higher quality and usability of the software, while the v-model will ensure that milestones and quality gateways are defined as well as a document in according with EN 62304.

#### Deliverable Software
The software shall be implemented as defined by software specifications and is only available for further developing steps *after* it passed the defined software tests. Deliverable software is the current/newest release candidate. 

#### Traceability
All requirements and specifications of the project are tracked by MatrixALM, in which the relationship between every requirement and specification is documented. Each software specification results in one or multiple tickets in Planio, whose ticket tracking functionality is used in this project. All source code changes are tracked by the version control system Git and referenced to Planio tickets. Thus, each source code line can be traced back to a specification respectively requirement (and vice versa).
!!! note
    Insert reference to MatrixALM.

### Change control
During the development and integration phase all changes to the software source code will be done in an agile manner. Once the software is in testing (after the "Ready For Testing" milestone has been reached):

 * All changes must be propagated via the ticket system. The assignment and approval of a change will be done by the software lead
 * The change comment provided when committing source code into repository shall reference to ID of the change in the ticket system

## Software Usability Plan
{%
   include-markdown "SUP.md"
%}

## Software Risk Management
The risk management for the *device* is done according to the Risk Management Plan of the device.
Software risks are minimized by identifying faulty behavior through tests and analysis described in the [Test and Analysis Specification (TAS)](TAS.md) document.

!!! Todo
    Add link/reference to Risk Management Plan of AC.

## Software Verification Plan
Software verification for each development item is performed in the development and output phase described in the [development phases](SDP.md#development-phases) mentioned above. 

### Verification Activities
| Activity             | Verification                                                                          |
| -------------------- | ------------------------------------------------------------------------------------- |
| Code Reviews         | One or more software developers review software source code for quality and anomalies |
| Software Integration | Continuous integration and testing  of  software  on  target hardware                 |
| Design Transfer      | Manual verification and shared responsibilities with other stakeholders               |


### Test and Verification
For each test performed according to the software system and integration test plans, test records shall be maintained. See [Test and Analysis Report (TAR)](TAR.md).

### Regression tests
Manual testing shall be performed after integration on the target device. If manual tests fail the issues need to be analyzed. If the software must be changed the tests must be repeated.

### Acceptance criteria
The following issues will prevent a release to integration:

 * Issues which increase the probability or severity of risks
 * Issues related to risk control measures (invalidating them)
 * Issues which introduce new risks
 * Issues which results in a decrease of safety related functions

For all other issues an analyze shall be made what the cause and possible effects are. This shall be documented and the project manager of the device will decide if they are acceptable or prevent the device from being deliverable as release candidate.

## Software of unknown provenance (SOUP)
All SOUP items shall be listed providing the following data: name, identification, version control method for SOUP item, usage location in software system/item/unit, possible risks. See [SOUP Component List (SOL)](SOL.md) for this data.

## Tools
All tools which are build in-house are controlled like the other source code. For the tools employed on development/build machines see [Software Development Environment (SDE)](SDE.md) for further information.

## Software Problem Resolution Process
The Software Problem Resolution Process describes how problems with the product are captured and analyzed. If the analysis indicates that the software issue, it shall be investigated by the software team to:

* Find cause(s)
* Evaluate the relevance for safety/risk
* And if required logged as issue in the ticketing software

The project manager and the software lead shall discuss if a new software shall be build. Relevant  parties  shall  be  notified  necessary  by  the  project  manager  according  to  the  Market Requirement Document 
!!! note
    Insert missing reference to MRD here

## Software Maintenance Plan
Monitoring and documenting of feedback for the whole product is done according to [Software Usability Plan](SUP.md). If issues and ideas arrive from within the software team they are logged in the ticketing software and if needed escalated to the project manager.

 * All software releases are build following this plan
 * Change requests after SW release are collected, analyzed and approved for the device.
 * Changes to the software are communicated to product release notes.

## Software Design Transfer Plan
Once the software is cleared for design transfer phase, release notes are created and handed to the project manager. The release notes contain:

 * References to the produced deliverables (including identification of the version)
 * Lists of known anomalies
 * Verification summery

## System Integration Plan
There  is  no  explicit  step  to  integrate  software  into  overall device scope. Instead there is a continuous integration process which builds and integrates the software system after each change. All tests and other verification activities are done for the integrated software with or without the hardware and are reported by [Test and Analysis Report (TAR)](TAR.md).
