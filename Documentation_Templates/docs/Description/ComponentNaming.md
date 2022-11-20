### Component naming

One of the biggest challenges in planning a project or creating a concept is naming items in this project/concept properly. Normally we handle a project in a divide and conquer manner, meaning we try to identify very holistic, abstract thought objects which help us divide our main problem in smaller, more manageable chunks. For example, if we want to develop a car, we could divide it in a propulsion *part*, a steering *part* and a passenger housing *part*. The problem here is finding a suitable naming for "*part*". Normally, this is done for each level of abstraction in the planning process. This is mandatory for communication with other project members or external stakeholders, so that everyone is "on the same page" and to avoid confusion. 

Conventionally terms like *system*, *subsystem*, *module*, *unit*, *component* or *item* are used for this task. Unfortunately, these terms are used rather ambiguously, at least to our experience. The hierarchy in our divide and conquer approach cannot be transported well using these terms. For example, is a unit part of a component, or the other way round? Additionally, people tend to have problems memorizing the concepts related to these terms, especially when they are used differently from project to project.

In this project we use a very distinct naming scheme which employs a very well known concept of ordering which is otherwise completely unrelated to software development: geographic categories. In our hierarchy the root is a **planet**, which could be mapped to a *system* in conventional lingo. The planet is followed by **continent**, **state**, **county**, **city**, **district**, **street** and **house**, in this order. It may not be intuitively on first glance but has big advantages: the abstraction level is directly clear and the naming can be remembered more easily as it is unexpected and thus causes a greater engagement.

Following the aforementioned concept, the naming scheme comprises two parts: the *functional* description and the *abstraction level*. The former describes the abstract functionality which this entity employs (for example "measurement" or "engine"), the latter the abstraction level where the functionality is positioned (for example "state" or "district").