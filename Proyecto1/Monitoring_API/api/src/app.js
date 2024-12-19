const express = require('express');
const bodyParser = require('body-parser');
require('dotenv').config();

const apiRoutes = require('./routes/api.routes');

const app = express();
const PORT = process.env.PORT || 3000;

// Middlewares
app.use(bodyParser.json());
app.use('/api', apiRoutes);

// Inicia el servidor
app.listen(PORT, () => {
    console.log(`API corriendo en el puerto ${PORT}`);
});
