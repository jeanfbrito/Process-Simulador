#include <stdio.h>
#include <conio.h>

struct process {
int pid;
int cycles_required;
enum { CPU, HD, IMPRESSORA, VIDEO } device_required;
int device_cycles;
enum  { CRIADO, APTO, EXECUTANDO, BLOQUEADO, DESTRUIDO } state;
};

main ()
{
int nproc=20, vtemp=2,i=0,x;

struct process procs[nproc];

for(x=0; x<nproc; x++){
    procs[x].pid = x;
    procs[x].cycles_required = (100 + rand() %200); // define os cyclos de CPU necessarios 100~300
    procs[x].device_required = CPU;
    procs[x].state = CRIADO;
}

for(x=0; x<nproc; x++){
    printf("\npid=%d ciclos=%d", procs[x].pid, procs[x].cycles_required);
}

getch();
return(0);

}
