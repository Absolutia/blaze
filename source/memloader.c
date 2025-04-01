#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>

#define ALLMEMORY 0
#define RAM 1
#define SWAP 2
#define DISABLED 3

size_t requested_memory[3];
size_t available_memory[3];
uint8_t prot_thresholds[3];
struct sysinfo info;

struct loader_flags{
	uint64_t memory_protection_type : 2;	//Free memory checks
	uint64_t mmap : 1;			//Memory-map file (recommended for read-only files)
	uint64_t stream : 1;			//Stream data into/out of memory
};

struct meminfo{
	size_t totalram;
	size_t freeram;
	size_t sharedram;
	size_t bufferram;
	size_t usedram;
	size_t totalswap;
	size_t freeswap;
	size_t usedswap;
	size_t freemem;
};

void get_memory_stats(struct sysinfo *info, struct meminfo *mem){
	sysinfo(info);

	mem->totalram = info->totalram * info->mem_unit;
	mem->freeram = info->freeram * info->mem_unit;
	mem->sharedram = info->sharedram * info->mem_unit;
	mem->bufferram = info->bufferram * info->mem_unit;
	mem->totalswap = info->totalswap * info->mem_unit;
	mem->freeswap = info->freeswap * info->mem_unit;

	mem->usedram = mem->totalram - mem->freeram;
	mem->usedswap = mem->totalswap - mem->freeswap;

	mem->freemem = mem->freeram + mem->freeswap;
	mem->usedmem = mem->usedram + mem->usedswap;

	return;
}

void pack_arrays(size_t available[], struct meminfo *mem){
	available[ALLMEMORY] = mem->freemem;
	available[RAM] = mem->freeram;
	available[SWAP] = mem->freeswap;
	return;
}

bool enforce_protection_thresholds(size_t requested[], size_t available[], uint8_t protection[], struct loader_flags *flags){
	for(i = 0; i < 3; i++){
		if(protection[i] > 100){
			protection[i] = 100;
		}
	}
	if(flags->memory_protection_type == ALLMEM){
		for(i = 0; i < 3; i++){
			if(requested[i] > available[i] * protection[i] / 100){
				return true; //Protection tripped
			}
		}
	}else if(flags->memory_protection_type == RAM){
		if(requested[RAM] > available[RAM] * protection[RAM] / 100){
			return true;
		}
	}else if(flags->memory_protection_type == SWAP){
		if(requested[SWAP] > available[SWAP] * protection[SWAP] / 100){
			return true;
		}
	}else if(flags->memory_protection_type == DISABLED){
		return false;
	}
}
