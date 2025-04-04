#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>

#define ALLMEMORY 0
#define RAM 1
#define SWAP 2
#define DISABLED 3

size_t req_memory[3];
size_t avail_memory[3];
uint8_t prot_thresh[3];
struct sysinfo info;

typedef struct{
	size_t memory_protection_type : 2;	//Free memory checks
	size_t mmap : 1;			//Memory-map file (recommended for read-only files)
	size_t stream : 1;			//Stream data into/out of memory
	size_t *object;				//Objects to be loaded
	size_t *target;				//Target buffer (optional)
} loader_t;

typedef struct{
	size_t totalram;
	size_t freeram;
	size_t sharedram;
	size_t bufferram;
	size_t usedram;
	size_t totalswap;
	size_t freeswap;
	size_t usedswap;
	size_t freemem;
} mem_t;

void get_memory_stats(struct sysinfo *info, mem_t *mem, size_t avail[]){
	sysinfo(info);

	mem->totalram = info->totalram * info->mem_unit;
	avail[RAM] = mem->freeram = info->freeram * info->mem_unit;
	mem->sharedram = info->sharedram * info->mem_unit;
	mem->bufferram = info->bufferram * info->mem_unit;
	mem->totalswap = info->totalswap * info->mem_unit;
	avail[SWAP] = mem->freeswap = info->freeswap * info->mem_unit;

	mem->usedram = mem->totalram - mem->freeram;
	mem->usedswap = mem->totalswap - mem->freeswap;

	avail[ALLMEMORY] = mem->freemem = mem->freeram + mem->freeswap;
	mem->usedmem = mem->usedram + mem->usedswap;

	return;
}

bool enforceprot(size_t req[], size_t avail[], uint8_t prot[], loader_t *flags){
	for(i = 0; i < 3; i++){
		if(prot[i] > 100){
			prot[i] = 100;
		}
	}
	switch(flags->mem_prot_type){
		case ALLMEM:
			for(i = 0; i < 3; i++){
				if(req[i] > avail[i] * prot[i] / 100){
					return true;
				}
			}
		case RAM:
			if(req[RAM] > avail[RAM] * prot[i] / 100){
				return true;
			}
		case SWAP:
			if(req[SWAP] > avail[SWAP] * prot[i] / 100){
				return true;
			}
		case DISABLED:
			return false;
	}
}
