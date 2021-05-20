/* Creator: John Kucera (originated from Dr. Duane J. Jarc)
* Filename: types.h (for Project 4)
* Date: May 4, 2021
* Code Description: types.h is the header file for types.cc. It contains
* function prototypes for the type checking functions in types.cc. Additionally,
* it contains enumerated type definitions for each variable type.
*/

typedef char* CharPtr;

enum Types {MISMATCH, INT_TYPE, BOOL_TYPE, REAL_TYPE};

void checkAssignment(Types lValue, Types rValue, string message);
Types checkArithmetic(Types left, Types right);
Types checkLogical(Types left, Types right);
Types checkRelational(Types left, Types right);
void storeReturnType(Types returnType);
void checkReturnType(Types currentType);
Types checkRemainder(Types left, Types right);
Types checkIf(Types ifCheck);
void checkThenElse(Types currentThen, Types currentElse);
Types checkCaseExpression(Types caseCheck);
void storeFirstWhen(Types whenStore);
void checkCaseWhen(Types currentWhen, string location);
