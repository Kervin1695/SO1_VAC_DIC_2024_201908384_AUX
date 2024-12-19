const pool = require('../db/connection');

// Guardar datos desde el agente
exports.saveData = async (req, res) => {
    const { machine_id, cpu_usage, ram_usage, processes } = req.body;

    try {
        // Guardar el estado de CPU y RAM
        await pool.query(
            'INSERT INTO system_status (machine_id, cpu_usage, ram_usage, timestamp) VALUES (?, ?, ?, NOW())',
            [machine_id, cpu_usage, ram_usage]
        );

        // Guardar la lista de procesos
        for (const process of processes) {
            await pool.query(
                'INSERT INTO processes (machine_id, pid, name, user, status, ram_usage, timestamp) VALUES (?, ?, ?, ?, ?, ?, NOW())',
                [machine_id, process.pid, process.name, process.user, process.status, process.ram_usage]
            );
        }

        res.status(200).json({ message: 'Datos guardados correctamente' });
    } catch (error) {
        console.error(error);
        res.status(500).json({ message: 'Error al guardar datos' });
    }
};

// Obtener datos de CPU y RAM para Grafana
exports.getData = async (req, res) => {
    const { machine_id } = req.query;

    try {
        const [rows] = await pool.query(
            'SELECT cpu_usage, ram_usage, timestamp FROM system_status WHERE machine_id = ? ORDER BY timestamp DESC LIMIT 100',
            [machine_id]
        );
        res.status(200).json(rows);
    } catch (error) {
        console.error(error);
        res.status(500).json({ message: 'Error al obtener datos' });
    }
};

// Obtener procesos para Grafana
exports.getProcesses = async (req, res) => {
    const { machine_id } = req.query;

    try {
        const [rows] = await pool.query(
            'SELECT pid, name, user, status, ram_usage FROM processes WHERE machine_id = ? ORDER BY timestamp DESC LIMIT 100',
            [machine_id]
        );
        res.status(200).json(rows);
    } catch (error) {
        console.error(error);
        res.status(500).json({ message: 'Error al obtener procesos' });
    }
};
