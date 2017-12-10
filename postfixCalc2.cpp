#include <iostream>
#include "llStack.h"
#include "llStack.cpp"
////////////////////////////////////////////////////////
//  Macros and methods for magically making tests easier.
//  method must return void and have no arguments.
//  Call using macro Test.  IE
//     Test(<someMethodName>);
//
//   In your g method, use "Assert( boolean ) " for your test
//
/////////////////////////////////////////////////////////
#include <stdexcept>
#include <string>
int maxPoints = 0;
int myPoints = 0;
#define Test( X , Y )  testOne ( #X, &X, Y);
// Calls testOne func passing in paramaters  magically
void testOne( std::string funcName, void (*fname)() , int points) {
maxPoints += points;
try {
fname();
}
catch ( std::logic_error err) {
std::cout << "ERROR in "<<funcName << err.what()<< std::endl;
return;
}
myPoints += points;
std::cout << funcName <<std::endl;
}
#define Assert( X )  \
if (!(X)) \
{string s = "  at line "+std::to_string(__LINE__);; \
throw std::logic_error( s ); }
void printPoints()
{
if ( maxPoints ) {
std::cout<< "Score "<<myPoints<<" out of "<< maxPoints<<std::endl;
}
}
///////////////////////////////////////////////////////////
//  End of testing magic.
///////////////////////////////////////////////////////////
using namespace std;
////////////////////////////////////////////////////////////
//  Simply create a list.  Verify length and count is as
//  expected
//
////////////////////////////////////////////////////////////
void createStack()
{
LLStack<string>  stack ;
Assert( stack.empty());
Assert( stack.size() == 0);
}
///////////////////////////////////////////////////////////
//  Push an item on the stack.  Verify that it is not
//  empty and that the length is 1
///////////////////////////////////////////////////////////
void singlePush()
{
LLStack<int> stack;
stack.push(1);
Assert( stack.empty() == false);
Assert( stack.size() == 1);
}
//////////////////////////////////////////////////////////
//  PUsh and retrieve 4 values.  Check Top and Pop
//
//////////////////////////////////////////////////////////
void pushFour()
{
LLStack<int> stack;
stack.push(1);
stack.push(2);
stack.push(3);
stack.push(4);
Assert( stack.size() == 4);
Assert( stack.top() == 4);
stack.pop();
Assert( stack.top() == 3);
stack.pop();
Assert( stack.top() == 2);
stack.pop();
Assert( stack.top() == 1);
stack.pop();
Assert( stack.empty());
Assert( stack.size() == 0);
}
//////////////////////////////////////////////////////////
//  Verify we can change the value gotten on Top for a
//  fundamental type ( int)
//////////////////////////////////////////////////////////
void verifyTopModifyInt()
{
LLStack<int> istack;
istack.push(1);
istack.push(2);
int & topInt = istack.top();
Assert( topInt == 2);
topInt = 4;
Assert( istack.top() == 4);
}
/////////////////////////////////////////////////////////
//  Verify we can change the value on a top when it is
//  an object ( string)
////////////////////////////////////////////////////////
void verifyTopModString()
{
LLStack<string> stack;
stack.push("Hi");
stack.push("Mom");
string & topOb = stack.top();
Assert( topOb == "Mom");
topOb = "Dad";
Assert( stack.top() == "Dad");
}
///////////////////////////////////////////////////////
//  Verify we are throwing a proper exception
//  on a top call if nothing in the stack.
//////////////////////////////////////////////////////
void verifyExceptionCall()
{
LLStack<int> stack;
try {
int val = stack.top();
// Should not get here ever.
Assert(false);
}
catch ( logic_error ex) {
// This is where we want to be
}
// Add one and try again
stack.push(1);
try {
int val = stack.top();
Assert( val == 1);
}
catch ( logic_error ex) {
// Shoudl not be throwing
Assert(false);
}
}
///////////////////////////////////////////////////
//  TEst for proper copy constructor
//
///////////////////////////////////////////////////
void verifyCopyConstructorValues()
{
LLStack<string> * stack = new LLStack<string>();;
stack->push("AA");
stack->push("BB");
stack->push("CC");
LLStack<string>  stack2( *stack);
Assert( stack2.size() == 3);
Assert( stack2.top() == "CC");
stack2.pop();
Assert( stack2.top() == "BB");
stack2.pop();
Assert( stack2.top() == "AA");
stack2.pop();
Assert( stack2.empty());
Assert( stack2.size() == 0);
}
/////////////////////////////////////////////////
// Test for proper operator = if they are both the same
//  object.
/////////////////////////////////////////////////////
void verifyOperatorEqualSameObject()
{
LLStack<int> stack1;
stack1.push(1);
stack1.push(2);
stack1 = stack1;
Assert( stack1.size() == 2);
Assert( stack1.top() == 2);
}
//////////////////////////////////////////////////
//  TEst for copy constructor as deep copy
//  Will just check for address of top reference
/////////////////////////////////////////////////
void verifyCopyConstructorAddress()
{
LLStack<string>  * stack = new LLStack<string>();
stack->push("AA");
stack->push("BB");
LLStack<string>  stack2( * stack);
// Check the address of the item are different.
Assert( & stack2.top() != &(stack->top()));
// Check the values are the same.
Assert( stack2.top() == stack->top());
stack->pop();
stack2.pop();
Assert( & (stack2.top()) != &(stack->top()));
Assert( stack2.top() == stack->top());
// Note - leaking memory here on purpose with stack, as
// if they did not do the copy constructor properly
// we do not want to try and delete twice.
}
///////////////////////////////////////////////////
//  TEst for proper operator =
//  We are using 'New' with a memory leak on purpose
//  as if there is an issue with the operator =
//  we con't want to delet memory twice
//
///////////////////////////////////////////////////
void verifyOperatorEqual()
{
LLStack<string> * stack = new LLStack<string>();
stack->push("AA");
stack->push("BB");
stack->push("CC");
LLStack<string> * stack2 = new LLStack<string>();
stack2->push("DD");
(*stack2) = (*stack);
Assert( stack2->size() == 3);
Assert( stack2->top() == "CC");
Assert( & ( stack2->top()) != &(stack->top()));
stack->pop();
stack2->pop();
Assert( stack2->top() == stack->top());
Assert( & ( stack2->top()) != &(stack->top()));
}
int main () {
Test(createStack, 1);
Test(singlePush, 1);
Test(pushFour, 2);
Test (verifyTopModifyInt, 1);
Test(verifyTopModString, 1);
Test(verifyExceptionCall, 2);
Test ( verifyCopyConstructorValues, 1);
Test ( verifyCopyConstructorAddress, 1);
Test(verifyOperatorEqual, 2);
Test (verifyOperatorEqualSameObject, 1);
cout << "Tests Complete"<<endl;
printPoints();
}
