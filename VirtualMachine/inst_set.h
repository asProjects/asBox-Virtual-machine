#pragma once
enum class OpCodes :uint8_t
{
	//syetm calls
	print_int = 0x00,
	print_double = 0x01,
	print_string = 0x02,
	read_int = 0x03,
	read_double = 0x04,
	read_string = 0x05,
	get_wisdom = 0x06,
	exit = 0x07,

	//load instructions
	load_int = 0x08,
	load_char = 0x09,
	load_double = 0x0A,

	//arithematic instruction
	add = 0x0B,
	subtract = 0x0C,
	multiply = 0x0D,
	divide = 0x0E,

	//conditional instructions
	cond_eq = 0x0F,
	cond_gt = 0x10,
	cond_lt = 0x11,

	//control flow
	branch = 0x12,
	branch_equal = 0x13,
	branch_not_equal = 0x14,

	//store instructions
	store_int = 0x15,
	store_char = 0x16,
	store_double = 0x17
};

