/* Creator: John Kucera (originated from Dr. Duane J. Jarc)
* Filename: listing.h (for Project 4)
* Date: May 4, 2021
* Code Description: listing.h is the header file for listing.cc. It contains
* function prototypes for the four functions in listing.cc. Additionally, it
* contains enumerated type definitions for each compilation error that can occur.
*/

enum ErrorCategories {LEXICAL, SYNTAX, GENERAL_SEMANTIC, DUPLICATE_IDENTIFIER,
	UNDECLARED};

void firstLine();
void nextLine();
int lastLine();
void appendError(ErrorCategories errorCategory, string message);
