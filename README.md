Code ReadMe based on current status on main branch.

TO MAKE: $ cmake -DGeant4_DIR=$G4DIR ../ make -jN (where N is desired no. of cores -- more relevant in MT mode) ./Base to run UI or ./Base MACRO_NAME.mac for batch mode with desired macro file

To make on Barkla: cmake -D CMAKE_C_COMPILER=$CC -D CMAKE_CXX_COMPILER=$CXX ../

make -jN (N is number of cores, 1 is usually fine)

Code contains a user-defined messenger system to determine the geometry setup. Target/scintillator layers can be chosen & set via messengers. The primary particle generator can be set this way too. 

The idea is to generate electrons to generate x-rays but this is open to the users desire.
