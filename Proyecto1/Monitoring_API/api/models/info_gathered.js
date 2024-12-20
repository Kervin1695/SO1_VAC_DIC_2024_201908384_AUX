const pool = require('../config');

class RAM_Info{
    static async insertRAMInfo(data){
        try{
            const now = newDate();
            let datestamp = now.toISOString().slice(0, 19).replace('T', ' ');
            const [rows, fields] = await pool.query('INSERT INTO RAM (maquina_id, Total, Free, Used, Percentage_used, datestamp) VALUES (?, ?, ?, ?, ?)', [data.maquina_id, data.total_ram, data.free_ram, data.used_ram, data.percentage_used, datestamp]);
            console.log('Data inserted');
            return rows;
        }catch(err){
            console.log(err);
        }
    }

    static async getRAMInfo(){
        try{
            const [rows, fields] = await pool.query('SELECT * FROM RAM');
            return rows;
        }catch(err){
            console.log(err);
        }
    }

    static async getRAMInfoById(id){
        try{
            const [rows, fields] = await pool.query('SELECT * FROM RAM WHERE id = ?', [id]);
            return rows;
        }catch(err){
            console.log(err);
        }
    }
}

class CPU_Info{
    static async insertCPUInfo(data){
        try{
            const now = new Date();
            let datestamp = now.toISOString().slice(0, 19).replace('T', ' ');
            const [rows, fields] = await pool.query('INSERT INTO CPU (maquina_id, Percentage_used, datestamp) VALUES (?, ?, ?)', [data.maquina_id, data.percentage_used, datestamp]);
            
            console.log('Data inserted');
            return rows;
        }catch(err){
            console.log(err);
        }
    }

    static async getCPUInfo(){
        try{
            const [rows, fields] = await pool.query('SELECT * FROM CPU');
            return rows;
        }catch(err){
            console.log(err);
        }
    }

    static async getCPUInfoById(id){
        try{
            const [rows, fields] = await pool.query('SELECT * FROM CPU WHERE maquina_id = ?', [id]);
            return rows;
        }catch(err){
            console.log(err);
        }
    }

    static async insertCPUProcessesInfo(data){
        try{
            const now = new Date();
            let datestamp = now.toISOString().slice(0, 19).replace('T', ' ');

            for (task in data.body.tasks) {
                const [rows, fields] = await pool.query('INSERT INTO CPU_Processes (pid, cpu_id, name_p, user, state_p, ram_usage, percentage_used, timestamp) VALUES (?, ?, ?, ?, ?, ?, ?, ?)', [task.pid, data.maquina_id, task.name, task.user, task.state, task.ram_usage, task.percentage_used, datestamp]);
            }
            console.log('Data inserted');

            return;
        }catch(err){
            console.log(err);
        }
    }

    static async getCPUProcessesInfo(){
        try{
            const [rows, fields] = await pool.query('SELECT * FROM CPU_Processes');
            return rows;
        }catch(err){
            console.log(err);
        }
    }

    static async getCPUProcessesInfoById(id){
        try{
            const [rows, fields] = await pool.query('SELECT * FROM CPU_Processes WHERE cpu_id = ?', [id]);
            return rows;
        }catch(err){
            console.log(err);
        }
    }
}

module.exports = {RAM_Info, CPU_Info};