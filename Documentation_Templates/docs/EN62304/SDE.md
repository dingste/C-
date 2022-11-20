# Software Development Environment

## Introduction
### Purpose
This document describes the methods, tools, and supporting items that are used to develop and maintain the software for the device.

### Intended audience
This document is intended for following audience: For software developers working on this project.

### Scope
The scope of this document is the description of the build and release process

## Software configuration
### Maintenance issues and problem resolution
Issues and problems are logged in Plan.io (Based on Redmine) issue-tracker in the project https://projekte.elk.de/projects/enmodes-ecmo

### Sourcecode control
The source-code of the software is stored into the following repository that provides version control: git@projekte.elk.de:elk/enecmo-device-firmware.git Only registered Developers and Maintainer from Plan.io are allowed to read and modify the content of this repository.

![GitWorkflow](../Diagrams/rendered/GitWorkflow.svg)

| name    | into branch                            | outof branch    |
| ------- | -------------------------------------- | --------------- |
| master  | main and starting branch               | none - infinity |
| issue   | feature, bug, etc with plan.io task-id | task finish     |
| release | on demand for release                  | none - infinity |

!!! Todo
    description of git commands: pull / push / checkout -b <issue>

### Release control
Release control based on atomic release number by git. Human readable revision number are set via tags in git. For every release this tag number is identified and documented in the release notes.

### Versioning scheme
The following version scheme will be used for releases: 
**major.minor** (1.0  1.1  2.0  2.1  2.2)
The major number increments when major changes are applied. The minor number increments when a bug is fixed, or a minor feature is added, mostly for so called nightly builds.

## Directory structure
| Directory                                                 | Description                                                |
| --------------------------------------------------------- | ---------------------------------------------------------- |
| ContinuousDrivenDevelopment                               | root                                                       |
| ContinuousDrivenDevelopment\docs                          | *all* documents as markdown                                |
| ContinuousDrivenDevelopment\skeleton\Templates            | implementation templates for Components                    |
| ContinuousDrivenDevelopment\skeleton\Components           | implementation of requirements as pseudo classes           |
| ContinuousDrivenDevelopment\skeleton\Workplace\Baremetal  | implementation of requirements for target: system hardware |
| ContinuousDrivenDevelopment\skeleton\Workplace\Simulation | implementation of requirements for target: virtual         |


## Software artifacts

### Build description
Building depends on scope and use cases. (see [Software Component List (SCL)](SCL.md))

### Release description
Release depends on scope and use cases. (see [Software Component List (SCL)](SCL.md))
Furthermore, a dedicate release is describe as a process. The release process includes generation of documentation. 
Defenitly: a 'Release' is hardware independed.

### Deployment description (for baremetal builds)
A deployment is the implementation of a named release on hardware. Moreover it describes the process of integration. 

The deployment of systemwide firmware fragments are handled like the update procedure. In this manner it is process save, cause of full description of what and how firmware is deployed and useable.  

### Update description
Cause of only one access point for users, to inject new firmware (else which microprocessor is affected), in fact the HMI outside of medical class c regulation, the GatewaySafety module has to control all phase of updating the system. E.g. 
![Hirachie](../Diagrams/rendered/UpdateHirachie.svg) 
We provide one holistic binary file, which will be transfer from HMI to GatewaySafety. In wich way this file is transfered to HMI is out of scope. Procedure, protocol and further technical details are described at (TODO: "CLASS NAME").
![Process](../Diagrams/rendered/UpdateProcedure.svg)
