#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/seq_file.h>
#include <linux/mm.h>
#include <linux/sysinfo.h>


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Module to get RAM information");
MODULE_AUTHOR("Kervin Cardona - 201908384");
MODULE_VERSION("1.0");

/*JSON con la informacion de la memoria RAM*/

static int create_File_RAM_Info(struct seq_file * archivo, void *v) {
    // struct sysinfo mySysInfo;
    // si_meminfo(&mySysInfo);
    // seq_printf(archivo, "{\n");
    // seq_printf(archivo, "\"total\": %lu,\n", (mySysInfo.totalram * mySysInfo.mem_unit) / (1024 * 1024));
    // seq_printf(archivo, "\"free\": %lu,\n", (mySysInfo.freeram * mySysInfo.mem_unit) / (1024 * 1024));
    // seq_printf(archivo, "\"used\": %lu,\n", ((mySysInfo.totalram - mySysInfo.freeram) * mySysInfo.mem_unit) / (1024 * 1024));
    // seq_printf(archivo, "\"shared\": %lu,\n", (mySysInfo.sharedram * mySysInfo.mem_unit) / (1024 * 1024));
    // seq_printf(archivo, "\"buffer\": %lu,\n", (mySysInfo.bufferram * mySysInfo.mem_unit) / (1024 * 1024));
    // seq_printf(archivo, "\"cached\": %lu\n", ((mySysInfo.totalram - mySysInfo.freeram - mySysInfo.bufferram) * mySysInfo.mem_unit) / (1024 * 1024));
    // seq_printf(archivo, "\"percentage_used\": %lu\n", ((mySysInfo.totalram - mySysInfo.freeram) * 100) / (mySysInfo.totalram));
    // seq_printf(archivo, "}\n");
    // return 0;

    struct sysinfo info;
    // Variables para almacenar la informacion de la memoria
    long total_ram, free_ram, used_ram, percentage_used;
    // Variables para almacenar la informacion de la memoria
    si_meminfo(&info);
    // Obtenemos la informacion de la memoria
    total_ram = (info.totalram * info.mem_unit) / (1024 * 1024);
    // Convertimos la informacion de la memoria a MB
    free_ram = (info.freeram * info.mem_unit) / (1024 * 1024);
    used_ram = total_ram - free_ram;
    percentage_used = (used_ram * 100) / total_ram;
    // Calculamos la cantidad de memoria usada y el porcentaje de memoria usada
    seq_printf(archivo, "{\n");
    seq_printf(archivo, "\"total_ram\": %ld,\n", total_ram);
    seq_printf(archivo, "\"free_ram\": %ld,\n", free_ram);
    seq_printf(archivo, "\"used_ram\": %ld,\n", used_ram);
    seq_printf(archivo, "\"percentage_used\": %ld\n", percentage_used);
    seq_printf(archivo, "}\n");
    // Escribimos la informacion en el archivo
    return 0;
}

static int open_File_RAM_Info(struct inode *inode, struct file *file) {
    return single_open(file, create_File_RAM_Info, NULL);
}

static const struct proc_ops operaciones = {
    .proc_open = open_File_RAM_Info,
    .proc_read = seq_read
};

static int _insert(void) {
    proc_create("ram_201908384", 0, NULL, &operaciones);
    printk(KERN_INFO "RAM Module loaded\n");
    return 0;
}

static void _remove(void) {
    remove_proc_entry("ram_201908384", NULL);
    printk(KERN_INFO "RAM Module removed\n");
}

module_init(_insert);
module_exit(_remove);


