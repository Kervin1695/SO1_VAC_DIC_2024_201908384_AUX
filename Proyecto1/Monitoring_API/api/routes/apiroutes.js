const express = require('express');
const info_gath = require('../models/info_gathered');

const router = express.Router();

router.post('/ram', async (req, res) => {
    const ramData = {
        maquina_id: req.body.maquina_id,
        total_ram: req.body.total_ram,
        free_ram: req.body.free_ram,
        used_ram: req.body.used_ram,
        percentage_used: req.body.percentage_used
    };

    const ram = await info_gath.RAM_Info.insertRAMInfo(ramData);

    res.json(ram);
});

router.post('/cpu', async (req, res) => {
    const cpuData = {
        maquina_id: req.body.maquina_id,
        percentage_used: req.body.percentage_used,
        tasks: req.body.tasks
    };
    const cpu = await info_gath.CPU_Info.insertCPUInfo(cpuData);
    const CPU_Processes = await info_gath.CPU_Info.insertCPUProcesses(cpuData);
    res.json(cpu);
});


