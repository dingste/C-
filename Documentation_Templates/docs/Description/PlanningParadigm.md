
Developing a new system to solve a certain problem requires a lot of planning and conceptualizing. The complexity of this process usually grows rather fast so it is reasonable to think about the developing process itself before the actual developing and planning takes place. These _meta-thoughts_ are documented in the following for the enECMO project development process.

Usually we start with the motivation of the project. This is normally the problem you want to solve. In our case this can be coined as

> We want to support the lung of a patient to help him or her to heal or even survive.

In some publications this is known as _business requirement_ or as the reason _why_ we are developing a specific system. It it rather vague but it limits the scope of the project. In our project this, for example, implies that we do not want to create a defibrillator. The next steps are essentially breaking this requirement down until we gain specific tasks we can work on. All these tasks combined form the solution for the main or paramount requirement. The actual project development is the process to define each step on the way to the task level - and back. The main requirement is usually not standing alone. It is accompanied by so called _non-functional requirements_, for example regulatory requirements (such as norms, laws and directives we have to follow) and financial requirements (e.g. the budget we can use). They play part in the specifications we create later on in the development process.

The next step is to identify the _functional requirements_ of the project. They answer the question _what_ we want to do in the project. In our case the main functional requirement would be

> Blood needs to be oxygenated and carbon dioxide has to be removed.

Of course there could be several main requirements on the same level of abstraction. From here on we divide this big chunks in smaller chunks, for example:

> 1. Blood needs to be transported out of the patient
> 2. Blood needs to be transported to oxygenator
> 3. Blood needs to be transported back into patient

It depends on the project how many divisions are needed. The goal should be that each chunk on the final level of subdivision describes a functionality as precisely as possible. This could be for example

> Blood pressure has to be measured before the entrance of the oxygenator.

Important is that

1. Every function of the system we want to develop is covered by an explicit functional requirement.  
2. The relation between different functions is clearly visible due to their position in the subdivision scheme

After identifying the required functions the next step is to fill these requirement with life. Therefore, we have to answer the question _how_ we want to fulfill the functional requirement. This is done by specifying the so called _technical requirements_. At this level we specify technical implementations which are employed to fulfil functional requirements, for example:

> Blood is transported via a pump through polypropylene tubes

This has the advantage that we find the optimal solution for meeting all the given requirements without bias towards a certain technology.

Normally, this is a iterative process. Only in very small projects all requirements can be identified in one iteration. In most cases we have to enter several rounds of requirement finding as certain aspects emerge only if we think about them in detail. For example, the diameter for the tubes transporting blood may play a more important role than thought of in the beginning. This may only have emerged in first experiments while evaluating for example different pump mechanisms.

All these process descriptions are very generic for every project in the context of medical (requirement) engineering. This document is embedded in the documentation of the development process for the (embedded) software controlling an ECMO system. There are some specifics which only apply to the software development process, but the basic principals are valid throughout all phases and stages of the whole project. Furthermore, as the attribute _embedded_ implies, there is a strong connection between hardware and software. Thus, there are requirements originating in the software realm which have an impact on hardware specifications. For example, a functional component in the software might have to be implemented redundantly to mitigate a risk identified by risk management. This might result in a functional requirement, that a component must be processed independently which can only be meet by a separate processing unit which implies, for example, a second microcontroller running this component.

In the process of refining functional requirements for the software components we regard each component essential as black box with data input and data output. Thus, our design approach is data driven. Because of that we try to be as specific as possible regarding the data as early as possible to facilitate functional requirement refinement. We define early the technical features of the data, for example if it is a integer or floating point number with a certain range of valid values. Therefore, our interfaces can be defined early in a rather fine level of granularity.