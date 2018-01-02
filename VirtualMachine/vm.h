#pragma once
#include<cstdint>
#include<vector>
#include<stack>

using namespace std;

enum class DataType :uint8_t;

union Instruction;

struct Value;

class VMCore
{
	stack<Value> dataStack;



	Value pop();
	void push(Value val);
public:
	void Interpret(vector<Instruction> bytecode);
};