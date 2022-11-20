# SOUP Component List

## Introduction
Every used tool or library or copied code parts is per se a SOUP component. Cause it can not be garuenteed that a new version from legacy components act as suggested and already known. Every SOUP components in this software project is listed here. To remove a component from this list depends on following rule:

* generally available and regulary used

And will then be named in the [Software Component List](SCL.md) or [Concept Design Document](CDD.md)

## Components
| Component Name | Version | Source | Licence | Use                    | Risk                                                      |
| -------------- | ------- | ------ | ------- | ---------------------- | --------------------------------------------------------- |
| meson          | ...     | ...    | ...     | simulation / baremetal | high - not controllable which compiler will be use        |
| clang          | ...     | ...    | ...     | simulation / baremetal | high - not controllable which compilerversion will be use |
| STM32 - HAL    | ...     | STM    | ...     | baremetal              | moderate - will be validate during development phase      |