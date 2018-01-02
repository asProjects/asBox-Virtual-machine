#pragma once
#include<memory>
#include<cstdint>

#include"inst_set.h"

enum class DataType :uint8_t
{
	type_int,
	type_str,
	type_double
};

union Instruction
{
	OpCodes opcode;
	uint8_t addr;
};

struct Value
{
	DataType type;

	union
	{
		uint8_t binValue;
		int32_t intValue;
		char* strValue;
		double doubleValue;
	};

	Value(DataType reqType, uint8_t& pData);
	Value(int32_t val);
	Value(char* val);
	Value(double val);
	Value(uint8_t val);

};

class StackMemory
{
private:

	Value *buffer;

	std::size_t stackSize;
	std::size_t stackPtr;

public:
	using Marker = std::uint8_t;

	Marker currMarker;
};

