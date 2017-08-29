#pragma once
enum class OpCodes :uint8_t
{
	//syetm calls
	inst_set_health = 0x00,
	inst_set_wisdom = 0x01,
	inst_set_agility = 0x02,
	inst_play_sound = 0x03,
	inst_spawn_paticles = 0x04,
	inst_get_health = 0x05,
	inst_get_wisdom = 0x06,
	inst_get_agility = 0x07,

	//load instructions
	inst_load_int = 0x08,
	inst_load_char = 0x09,
	inst_load_double = 0x0A,

	//arithematic instruction
	inst_add = 0x0B,
	inst_subtract = 0x0C,
	inst_multiply = 0x0D,
	inst_divide = 0x0E,

	//conditional instructions
	inst_cond_eq = 0x0F,
	inst_cond_gt = 0x10,
	inst_cond_lt = 0x11,

	//control flow
	inst_branch = 0x12,
	inst_branch_equal = 0x13,
	inst_branch_not_equal = 0x14,

	//store instructions
	inst_store_int = 0x15,
	inst_store_char = 0x16,
	inst_store_double = 0x17
};

