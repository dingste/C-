# Description
To garuantee a minimal set of coding details and styles, some kind of templates can be very helpfull.
Also a script to create sourcecode files with correct naming and derivation, can handle this templates.

## Example Header (in C++):


``` C++
/*! \brief NAME
 * 
 * Decleration as a component
 * also providing its Interface
 *
 * File:   NAME.hpp
 * Author: Dieter Steuten 
 *
 */

#ifndef NAME_H
#define NAME_H

/* --- Includes --- */
#include <stdint.h>


/* --- Interface --- */
class I_NAME {
   public:
    virtual ~I_NAME() {}

    /* the **how** */
    /* describe class accessing function as good as can be **here** examples: */
    virtual bool onSomething()      = 0;        // component simple signals on event "Something" for others
    virtual void doSomething(FOO)   = 0;        // component slot to process "FOO" on event "Something" from others
    virtual FOO provideSomething()  = 0;        // transportation of "FOO" to other component as an object
};

/* --- Decleration --- */
class NAME : public I_NAME {
   public: /* only own de-/constructor are public */
    NAME();
    virtual ~NAME();

   protected: /* provide data only via interfaces and via protected access */
    /* I_NAME */
    bool onSomething() override;
    void doSomething(FOO foo) override;
    FOO provideSomething() override;

   private: /* everything else, to handle and/or manipulating of data in the scope of this class */
    /* - use of Components */
    /* Access to Components NAME depend on, via interface */
    I_OTHER* _OTHER; // without implementation **here**! e.g.  | _OTHER = new OTHER(); |  only into implementation file (cpp)

    /* - Member - */
    
    /* - copy-constructor - */
    NAME(const NAME&);             // for **example** oblivous copy-constructor
    NAME& operator=(const NAME&);  // for **example** oblivous copy-constructor

    /* - Functions - */
    /* derivate from functional requirements 
     * more or less these functions came from pool of [/Develop/Functions/Readme.md] */
};

#endif
```

## Example Implementation (in C++):


``` C++
/*! \brief NAME
 * 
 * Implementation of a component
 *
 * File:   NAME.cpp
 * Author: Dieter Steuten
 *
 */

/* --- Includes --- */
#include "NAME.hpp"

/* --- CPP regular --- */
NAME::NAME() {}
NAME::~NAME() {}

/* --- protected functionalities --- */
bool NAME::onSomething() { return false; }
void NAME::doSomething(FOO foo) {}
FOO NAME::provideSomething(){return foo;} 
```