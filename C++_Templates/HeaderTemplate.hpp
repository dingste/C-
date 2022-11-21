/*! \brief NAME
 * 
 * Decleration as a component
 * also providing its Interface
 *
 * File:   NAME.hpp
 * Author: Dieter Steuten
 *
 */

/// ```plantuml format="svg"
/// ```
///
/// #### Description
///
///
/// #### Technical Requirements
///
/// | ID  | Description                                                                    |
/// | --- | ------------------------------------------------------------------------------ |
/// | STR-xx  |                |
///
///
/// #### Functional Requirements
///
/// | ID  | Description                                                             |
/// | --- | ----------------------------------------------------------------------- |
/// | SFR-xx  |  |
///

#ifndef I_NAME_H
#define I_NAME_H

/* --- Includes --- */
#include <stdint.h>
#include "IPO/IPO.hpp"
//derivate includes

/* --- type --- */
struct T_NAME{
    bool change_request = false;
    int foo = 0; // put **ALL** processable data in here
    //derivate _Data_Create
    bool operator!=(const T_NAME &pre) { 
        return (foo != pre.foo
            //derivate _nq 
        ) ? true : false;    
    }
};

/* --- Interface --- */
class I_NAME : public I_IPO<T_NAME> {
public:
    virtual ~I_NAME() {
        //derivate _Del_Instance
    }

    /* the **howto access** */
    const T_NAME &O() override {        return data;    }
    void I(const T_NAME &outter) override {
        if (data != outter) {
            data = outter;
            data.change_request = true;
            //derivate _forward
        }
    }
    // override in concrete class virtual bool P(bool) = 0;
    
   protected:
    T_NAME data = T_NAME();
    //derivate _New_Instance
};

/* --- Decleration --- */
class NAME : public I_NAME {
public:
    NAME();
    virtual ~NAME(){    /* delete the 'new's (if exists) directly here .. for more readiness */  };

protected:
    /* mandatory I_IPO */
    bool P(bool) override; /* collect all to be do in this function */

    /* optional I_NAME */

private:    /* - use of further components (the 'new's) - */
    /* - Member - */

    /* - declaration of own private processing functions - */
};

/* get an easier access to derivate Input-Processing-Output Class */
#define NAME_Data_Create T_NAME NAME_Data_Reference = T_NAME()
#define NAME_New_Instance I_NAME *NAME_Object_Reference = new NAME()
#define NAME_Del_Instance delete NAME_Object_Reference
#define NAME_I(d) NAME_Object_Reference->I(d)
#define NAME_P(cr) NAME_Object_Reference->P(cr)
#define NAME_O data.NAME_Data_Reference = NAME_Object_Reference->O()
#define NAME_nq (NAME_Data_Reference != pre.NAME_Data_Reference)
#define NAME_condition (data.NAME_Data_Reference != outter.NAME_Data_Reference)
#define NAME_assign data.NAME_Data_Reference = outter.NAME_Data_Reference
#define NAME_forward                          \
    if (NAME_condition) {                     \
        NAME_assign;                          \
        NAME_I(outter.NAME_Data_Reference); \
    }
#define NAME_byte_in NAME_Data_Reference << T_NAME()
#define NAME_byte_out T_NAME() >> NAME_Data_Reference 
    
#endif
