#pragma once

struct CVirtualMachineStack {
	int size;
	int unk_0x4;
	int unk_0x8;
	uint8_t* stack_data_types; //0xc
	int* stack_data_values; //0x10
	char unk_0x14[0x214];
};

struct CScriptLog {
	CExoString* script_name;
};

struct CVirtualMachine_s {
	uint32_t field_0;
	uint32_t field_4;
	uint32_t field_8;
	int32_t vm_execute_script_stack_size;
    char unknown1[0x160];
	CVirtualMachineStack vm_stack; //0x170;
	CNWVirtualMachineCommands* vm_cmd; //0x398
	char unknown3[0x2c]; //0x39C
	CExoArrayList<void*> vm_logs; //0x3C8
};
