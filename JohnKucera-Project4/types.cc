/* Creator: John Kucera (originated from Dr. Duane J. Jarc)
* Filename: types.cc (for Project 4)
* Date: May 4, 2021
* Code Description: types.cc is the file that contains type checking functions
* and prints messgaes for the respective semantic errors that can occur.
*/

#include <string>
#include <vector>

using namespace std;

#include "types.h"
#include "listing.h"

Types storedReturnType;
Types firstWhen;

void checkAssignment(Types lValue, Types rValue, string message)
{
	if (lValue != MISMATCH && rValue != MISMATCH) {
		if (lValue == BOOL_TYPE && (rValue == INT_TYPE || rValue == REAL_TYPE)) {
			appendError(GENERAL_SEMANTIC, "Type Mismatch on " + message);
		}
		if (rValue == BOOL_TYPE && (lValue == INT_TYPE || lValue == REAL_TYPE)) {
			appendError(GENERAL_SEMANTIC, "Type Mismatch on " + message);
		}
		if (lValue == INT_TYPE && rValue == REAL_TYPE) {
			appendError(GENERAL_SEMANTIC, "Narrowing Variable Initialization is Illegal");
		}
	}
}

Types checkArithmetic(Types left, Types right)
{
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	if (left == BOOL_TYPE || right == BOOL_TYPE) {
		appendError(GENERAL_SEMANTIC, "Numeric Type Required");
		return MISMATCH;
	}
	if ((left == REAL_TYPE && right == INT_TYPE) ||
			(left == INT_TYPE && right == REAL_TYPE)) {
		return REAL_TYPE;
	}
	return INT_TYPE;
}


Types checkLogical(Types left, Types right)
{
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	if (left != BOOL_TYPE || right != BOOL_TYPE)
	{
		appendError(GENERAL_SEMANTIC, "Boolean Type Required");
		return MISMATCH;
	}
		return BOOL_TYPE;
	return MISMATCH;
}

Types checkRelational(Types left, Types right)
{
	if (checkArithmetic(left, right) == MISMATCH)
		return MISMATCH;
	return BOOL_TYPE;
}

void storeReturnType(Types returnType) {
	storedReturnType = returnType;
}

void checkReturnType(Types currentType)
{
	if (storedReturnType == INT_TYPE && currentType == REAL_TYPE) {
		appendError(GENERAL_SEMANTIC, "Narrowing Function Return is Illegal");
	}
	if (currentType == BOOL_TYPE && (storedReturnType == INT_TYPE || storedReturnType == REAL_TYPE)) {
		appendError(GENERAL_SEMANTIC, "Type Mismatch on Function Return");
	}
	if (storedReturnType == BOOL_TYPE && (currentType == INT_TYPE || currentType == REAL_TYPE)) {
		appendError(GENERAL_SEMANTIC, "Type Mismatch on Function Return");
	}
}

Types checkRemainder(Types left, Types right)
{
	if (left == MISMATCH || right == MISMATCH) {
		return MISMATCH;
	}
	if (left != INT_TYPE || right != INT_TYPE) {
		appendError(GENERAL_SEMANTIC, "Integer Type Required");
		return MISMATCH;
	}
	return INT_TYPE;
}

Types checkIf(Types ifCheck)
{
	if (ifCheck != BOOL_TYPE)
		appendError(GENERAL_SEMANTIC, "If Condition must be Boolean Type");
		return MISMATCH;
	return BOOL_TYPE;
}

void checkThenElse(Types currentThen, Types currentElse)
{
	if (currentThen != currentElse) {
		appendError(GENERAL_SEMANTIC, "Type Mismatch on Then and Else Statements");
	}
}

Types checkCaseExpression(Types caseCheck)
{
	if (caseCheck != INT_TYPE) {
		appendError(GENERAL_SEMANTIC, "Case Expression must be Integer Type");
		return MISMATCH;
	}
	return INT_TYPE;
}

void storeFirstWhen(Types whenStore)
{
	firstWhen = whenStore;
}

void checkCaseWhen(Types currentWhen, string location)
{
	if (firstWhen != currentWhen) {
		appendError(GENERAL_SEMANTIC, "Type Mismatch on " + location + " Statement");
	}
}
