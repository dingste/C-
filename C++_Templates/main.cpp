#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Base/Definitions.hpp"
#include "Ingoing/Ingoing.hpp"
#include "Processing/Processing.hpp"
#include "Outgoing/Outgoing.hpp"

Ingoing_New_Instance;
Ingoing_Data_Create;

Processing_New_Instance;
Processing_Data_Create;

Outgoing_New_Instance;
Outgoing_Data_Create;

static bool sequence = true; 

void onEnd(){
    Ingoing_Del_Instance;
    Processing_Del_Instance;
    Outgoing_Del_Instance;
}

void main(){
    while (sequence){
        Ingoing_Data_Reference.foo = 1;

        Ingoing_I(Ingoing_Data_Reference);
        sequence = Ingoing_P(sequence);
        
        Processing_Data_Reference = Ingoing_O();
        
        Processing_I(Processing_Data_Reference);
        sequence = Processing_P(sequence);
        
        Outgoing_Data_Reference = Processing_O();

        Outgoing_I(Outgoing_Data_Reference);
        sequence = Outgoing_P(sequence);
        Outgoing_O();
    }
    onEnd();
}
