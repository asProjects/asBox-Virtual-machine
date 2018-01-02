#include"vm.h"
#include"inst_set.h"
#include"implementation.h"



Value::Value(DataType reqType, uint8_t& pData):type(reqType)
{
	if (type == DataType::type_int)
	{
		intValue = *reinterpret_cast<int*>(&pData);
	}
	else if (type == DataType::type_char)
	{
		charValue = *reinterpret_cast<char*>(&pData);
	}
	else
	{
		doubleValue = *reinterpret_cast<double*>(&pData);
	}
}

Value::Value(int32_t val):intValue(val)
{
	
}

Value::Value(char val):charValue(val)
{

}

Value::Value(double val):doubleValue(val)
{

}

Value::Value(uint8_t val):binValue(val)
{

}

void VM::push(Value val)
{
	dataStack.push(val);
}

Value VM::pop()
{
	auto ret = dataStack.top();
	dataStack.pop();

	return ret;
}

void VM::Interpret(vector<Instruction> bytecode)
{

	for (auto i=0;i<bytecode.size();i++)
	{
		switch (bytecode[i].opcode)
		{
		case OpCodes::load_int:
			push(Value(DataType::type_int, bytecode[*reinterpret_cast<int*>(&bytecode[++i].bin)].bin));
			i += 3;
			break;

		case OpCodes::load_char:
			push(Value(DataType::type_char, bytecode[*reinterpret_cast<int*>(&bytecode[++i].bin)].bin));
			break;

		case OpCodes::load_double:
			push(Value(DataType::type_double, bytecode[*reinterpret_cast<int*>(&bytecode[++i].bin)].bin));
			i += 7;
			break;

		case OpCodes::store_int:
			auto a = pop();

			auto intPtr = reinterpret_cast<int*>(&bytecode[*reinterpret_cast<int*>(&bytecode[++i].bin)].bin);
			*intPtr = a.intValue;
			break;

		case OpCodes::store_char:
			auto a = pop();

			auto charPtr = reinterpret_cast<char*>(&bytecode[*reinterpret_cast<int*>(&bytecode[++i].bin)].bin);
			*charPtr = a.charValue;
			break;

		case OpCodes::store_double:
			auto a = pop();

			auto doublePtr = reinterpret_cast<double*>(&bytecode[*reinterpret_cast<int*>(&bytecode[++i].bin)].bin);
			*doublePtr = a.doubleValue;
			break;

		case OpCodes::add:
			auto b = pop();

			auto a = pop();

			if (a.type == DataType::type_char || b.type == DataType::type_char)
			{
				break;
			}

			if (a.type == DataType::type_int && b.type == DataType::type_int)
			{
				push(a.intValue + b.intValue);
			}
			else if (a.type == DataType::type_int && b.type == DataType::type_double)
			{
				push(a.intValue + b.doubleValue);
			}
			else
			{
				push(b.intValue + a.doubleValue);
			}
		
			break;

		case OpCodes::subtract:
			auto b = pop();

			auto a = pop();

			if (a.type == DataType::type_char || b.type == DataType::type_char)
			{
				break;
			}

			if (a.type == DataType::type_int && b.type == DataType::type_int)
			{
				push(a.intValue - b.intValue);
			}
			else if (a.type == DataType::type_int && b.type == DataType::type_double)
			{
				push(a.intValue - b.doubleValue);
			}
			else
			{
				push(a.doubleValue - b.intValue);
			}

			break;

		case OpCodes::multiply:
			auto b = pop();

			auto a = pop();

			if (a.type == DataType::type_char || b.type == DataType::type_char)
			{
				break;
			}

			if (a.type == DataType::type_int && b.type == DataType::type_int)
			{
				push(a.intValue * b.intValue);
			}
			else if (a.type == DataType::type_int && b.type == DataType::type_double)
			{
				push(a.intValue * b.doubleValue);
			}
			else
			{
				push(a.doubleValue*b.intValue);
			}

			break;

		case OpCodes::divide:
			auto b = pop();

			auto a = pop();

			if (a.type == DataType::type_char || b.type == DataType::type_char)
			{
				break;
			}

			if(b.binValue==0x0)

			if (a.type == DataType::type_int && b.type == DataType::type_int)
			{
				push(a.intValue / b.intValue);
			}
			else if (a.type == DataType::type_int && b.type == DataType::type_double)
			{
				push(a.intValue / b.doubleValue);
			}
			else
			{
				push(a.doubleValue / b.intValue);
			}

			break;

		case OpCodes::cond_eq:
			auto b = pop();

			auto a = pop();

			
			push(a.binValue == b.binValue ? 1 : 0);
			break;

		case OpCodes::cond_gt:
			auto b = pop();

			auto a = pop();

			push(a.binValue > b.binValue ? 1 : 0);
			break;

		case OpCodes::cond_lt:
			auto b = pop();

			auto a = pop();

			push(a.binValue < b.binValue ? 1 : 0);
			break;

		case OpCodes::set_health:
			auto b = pop();

			auto a = pop();

			setHealth(a.intValue, b.intValue);
			break;

		case OpCodes::inst_set_wisdom:
			auto b = pop();

			auto a = pop();

			setWisdom(a.intValue, b.intValue);
			break;

		case OpCodes::inst_set_agility:
			auto b = pop();

			auto a = pop();

			setAgility(a.intValue, b.intValue);
			break;

		case OpCodes::inst_get_health:
			auto a = pop();

			push(getHealth(a.intValue));
			break;

		case OpCodes::inst_get_wisdom:
			auto a = pop();

			push(getWisdom(a.intValue));
			break;

		case OpCodes::inst_get_agility:
			auto a = pop();

			push(getAgility(a.intValue));
			break;

		case OpCodes::inst_play_sound:
			auto a = pop();

			playSound(a.intValue);
			break;

		case OpCodes::inst_spawn_paticles:
			auto a = pop();

			spawnParticle(a.intValue);
			break;

		case OpCodes::inst_branch:

			i = *reinterpret_cast<int*>(&bytecode[i + 1].bin);
			break;

		case OpCodes::inst_branch_equal:
			auto a = pop();

			if (a.binValue == 1)
			{
				i = *reinterpret_cast<int*>(&bytecode[i + 1].bin);
			}
			else
			{
				i+=3;
			}

			break;

		case OpCodes::inst_branch_not_equal:
			auto a = pop();

			if (a.binValue == 0)
			{
				i = *reinterpret_cast<int*>(&bytecode[i + 1].bin);
			}
			else
			{
				i += 3;
			}

			break;
		default:
			break;
		}
	}
}