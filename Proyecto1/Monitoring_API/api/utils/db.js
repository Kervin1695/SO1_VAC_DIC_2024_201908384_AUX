const mysql = require('mysql2/promise');

const pool = mysql.createPool({
    host: 'database',
    user: 'root',
    password: 'passwordroot',
    database: 'MonitoringAPI_db',
    waitForConnections: true,
    connectionLimit: 10,
    queueLimit: 0
});

module.exports = pool;