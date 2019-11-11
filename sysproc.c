#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;

  addr = myproc()->sz;
  if(n < 0){
    if(growproc(n) < 0)
      return -1;
  }
  else{
    myproc()->sz = addr + n;
  }
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_count_virtual_pages(void)
{
  return PGROUNDUP(myproc()->sz) / PGSIZE;
}

int
sys_count_physical_pages(void)
{
  int count = 0;
  pde_t *pgdir = myproc()->pgdir;
  pde_t *pde;
  pte_t *pgtab;

  for(int i = 0; i < NPDENTRIES; ++i){
    pde = &pgdir[i];
    if(*pde & PTE_P){
      pgtab = (pte_t*)P2V(PTE_ADDR(*pde));
      for(int j = 0; j < NPTENTRIES; ++j){
        if(pgtab[j] & PTE_P){
          ++count;
        }
      }
    }
  }
  return count;
}
