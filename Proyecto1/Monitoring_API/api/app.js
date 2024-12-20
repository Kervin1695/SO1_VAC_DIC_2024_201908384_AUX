const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');
const apiRoutes = require('./routes/apiroutes');

const app = express();
const PORT = 3000;

app.use(cors());
app.use(bodyParser.json());
app.set('view engine', 'ejs');

app.use(express.json());

app.get('/', (req, res) => {
    res.render('index');
});

app.post('/cpu', (req, res) => {
    if (err) {
        express.response.status(500).send('Error');
    }

    const cpuData = {
        maquina_id: req.body.maquina_id,
        percentage_used: req.body.percentage_used
    };

    info_gath.CPU_Info.insertCPUInfo(cpuData);
    
});

app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});


