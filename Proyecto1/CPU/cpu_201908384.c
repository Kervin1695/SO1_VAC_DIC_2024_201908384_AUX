#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/seq_file.h>
#include <linux/stat.h>
#include <linux/string.h>
#include <linux/uaccess.h>
#include <linux/mm.h>
#include <linux/sysinfo.h>
#include <linux/sched/task.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Module to get RAM information");
MODULE_AUTHOR("Kervin Cardona - 201908384");
MODULE_VERSION("1.0");

static int calculate_CPU_Percentage_Use(void){
    struct file *archivo;
    char fileRead[256];

    int user, nice, idle, iowait, irq, softirq, steal, guest, guest_nice;
    // Variables para almacenar la informacion de la CPU
    //Donde user es el tiempo que la CPU ha pasado en modo user
    //nice es el tiempo que la CPU ha pasado en modo user con prioridad baja
    //idle es el tiempo que la CPU ha pasado en modo ocioso
    //io wait es el tiempo que la CPU ha pasado esperando a que se complete una operacion de entrada/salida
    //irq es el tiempo que la CPU ha pasado atendiendo interrupciones de hardware
    //softirq es el tiempo que la CPU ha pasado atendiendo interrupciones de software
    //steal es el tiempo que la CPU ha pasado en modo oc
    //guest es el tiempo que la CPU ha pasado ejecutando una maquina virtual
    //guest_nice es el tiempo que la CPU ha pasado ejecutando una maquina virtual con prioridad baja
    int total, percentage;

    archivo = filp_open("/proc/stat", O_RDONLY, 0);
    if (archivo == NULL){
        printk(KERN_INFO "Error al abrir el archivo\n");
        return -1;
    }
    //Abrimos el archivo /proc/stat

    memset(fileRead, 0, 256);
    //Limpiamos la variable fileRead
    kernel_read(archivo, fileRead, 256, &archivo->f_pos);
    //Leemos el archivo y guardamos la informacion en la variable fileRead

    sscanf(fileRead, "cpu %d %d %d %d %d %d %d %d %d", &user, &nice, &idle, &iowait, &irq, &softirq, &steal, &guest, &guest_nice);

    total = user + nice + idle + iowait + irq + softirq + steal + guest + guest_nice;

    percentage = (total - idle) * 100 / total;

    filp_close(archivo, NULL);

    return percentage;
}

static int create_File_CPU_Info(struct seq_file * archivo, void *v) {
    int percentage = calculate_CPU_Percentage_Use();
    
    if (percentage == -1){
        seq_printf(archivo, "{\"error\": \"Error al obtener la informacion de la CPU\"}\n");
        return 0;
    } else {
        seq_printf(archivo, "{\n");
        seq_printf(archivo, "\"percentage_used\": %d,\n", percentage);
        seq_printf(archivo, "\"tasks\": [\n");
        
        struct task_struct *task;
        int ram;
        bool first_task = true;

        for_each_process(task){
            if (!first_task){
                seq_printf(archivo, ",\n");
            }

            seq_printf(archivo, "{\n");
            seq_printf(archivo, "\"pid\": %d,\n", task->pid);
            seq_printf(archivo, "\"name\": \"%s\",\n", task->comm);
            seq_printf(archivo, "\"state\": %d,\n", task->__state);
            seq_printf(archivo, "\"user\": %d,\n", task->cred->uid.val);

            if (task->mm){
                ram = (get_mm_rss(task->mm) << PAGE_SHIFT) / (1024 * 1024);
                seq_printf(archivo, "\"ram\": %d,\n", ram);
            } else {
                seq_printf(archivo, "\"ram\": null,\n");
            }

            seq_printf(archivo, "\"father\": %d\n", task->parent->pid);
            seq_printf(archivo, "    }");
            first_task = false;
        }

        seq_printf(archivo, "\n  ]\n");
        seq_printf(archivo, "}\n");
        
    }

    return 0;
}

static int open_File_CPU_Info(struct inode *inode, struct file *file) {
    return single_open(file, create_File_CPU_Info, NULL);
}

static const struct proc_ops operaciones = {
    .proc_open = open_File_CPU_Info,
    .proc_read = seq_read
};

static int _insert(void) {
    proc_create("cpu_201908384", 0, NULL, &operaciones);
    printk(KERN_INFO "Modulo CPU insertado\n");
    return 0;
}

static void _remove(void) {
    remove_proc_entry("cpu_201908384", NULL);
    printk(KERN_INFO "Modulo CPU removido\n");
}

module_init(_insert);
module_exit(_remove);
