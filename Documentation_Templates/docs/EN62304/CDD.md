# Concept Design Document

This document describes how the specifications of the product is implemented in the actual software with the help of the [Coding Conventions Document](CCD.md). The results of this process is presented in the following.

## System Design
Following the design of this system in software development is only possible by following the [Coding Conventions Document](CCD.md). It is mandatory to know, where naming conventions stem from. In this document this naming scheme is ubiquitously.

## Architecture
The architecture is determined by the software requirements first. Depending on change requests and/or new technologies emerging during the main development phase, changes in the architecture may appear.
To handle the aforementioned issues, we use a top-down approach. First, we use the [intended use](../Description/IntendedUse.md) as a base to define a minimal architecture. Every new detail or change will be included into this concept from bottom-up into the architecture. 

![Architecture](../Diagrams/rendered/CDDArchitecture.svg)

## Design Reviews
If a detail is such critical or has an impact on overall architecture (in this case also on [intended use](../Description/IntendedUse.md)), the change management process or risk management plan will be new initialized by the project lead.

!!! Todo
    Add link/reference to Risk Management Plan.

## Components
In the following all components of the software architecture are listed together with a description of their design and purpose.

{%
   include-markdown "../skeleton_md/architecture.md"
%}
