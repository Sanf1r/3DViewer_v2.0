# 3DViewer_v2.0

Implementation of 3DViewer v2.0.

Tested on MacOS Big Sur 11.6.6.

Made on July 08 2023 as part of my education in School 21 :)

https://github.com/Sanf1r/3DViewer_v2.0/assets/100280376/7eb8d2a0-eb4b-4cce-b9be-a4beccc9ecaa

## Introduction

This project implements an application for viewing 3D wireframe models in C++ in the object-oriented programming paradigm, implementing the same functions as the previously developed application in 3DViewer v1.0 project.
In additional implements mouse control of rotate and Design patterns: momento, singleton, strategy and facade.

## Information

### Design patterns

Each human activity, such as cooking or nuclear physics experiments, has a set of established practices that deal with basic elementary tasks. They do not require an individual approach and are usually resolved by well-established approaches developed over time, based on the experience of previous cooks or nuclear physicists. For example, baking a pie, even an unusual one, will most likely require dough whose cooking technology is known in advance and usually does not need some creativity. It's the same with programming, when designing you often have elementary tasks that a huge number of programmers have faced before you, and their experience has developed into established design patterns.

**Design pattern** describes a frequently repeated application design problem and its way of solving, which is universal to that problem.
In other words, a design pattern for a programmer is nothing but a building block, an elementary unit that is implemented when a typical subtask occurs within a project.

Design patterns are usually divided into three groups: creational, structural and behavioral patterns. See materials for more information about design patterns. \
You have already encountered the use of established practices (patterns) in application design in the SmartCalc v2.0 project (MVC pattern). Just as a reminder, MVC in some form or another is one of the most common solutions in terms of code structuring during UI application development.
The user interface and the business logic with its controller are usually split into two different global domains: the interface domain and the business logic domain.

The interface domain is only responsible for displaying the interface and passing commands to the business logic domain. Data loaded from a file should not be stored in the interface domain.

The business logic domain is responsible for the main functionality of the system. This is where the loaded data is stored and all the operations with it are performed. This domain is also where the rendering is done.
