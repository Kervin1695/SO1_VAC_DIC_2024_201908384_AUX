const express = require('express');
const { saveData, getData, getProcesses } = require('../controllers/data.controller');

const router = express.Router();

// Ruta para recibir datos desde los agentes
router.post('/data', saveData);

// Ruta para enviar datos a Grafana (CPU y RAM)
router.get('/data', getData);

// Ruta para obtener la lista de procesos
router.get('/processes', getProcesses);

module.exports = router;
