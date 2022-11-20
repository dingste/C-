### Variable and type naming

#### Variables and arguments
Variable names shall be as short and concise as possible. Mentioning of the data or container type in the name shall be avoided ((e.g. *therapyNamesVector* should be better *therapyNames*). Regular variables or function argument names shall start with a lower case letter. All other elements of a composed name shall be highlighted by camel case notation (e.g. *maxMotorSpeed*). 

#### Types
Type names shall be written with a prefix "T_", e.g. *T_MotorParameters*. 

#### Constants and Magic Numbers
Constant variables shall be named using upper case words connected by underscores (e.g. *MOTOR_MAXIMUM_SETTING*). Constants shall be collected in special *structs* to avoid polluting the global namespace. These structs shall be named with a leading "C_", e.g. *C_SensorLimits. All constant values shall be defined this way, thus covering all values which would appear as "magic numbers" (unknown provenance) throughout the code.