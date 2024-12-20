const mysql = require('mysql2');

const pool = mysql.createPool({
  host: 'localhost',
  user: 'localhost',
  password: 'localhost_password',
  database: 'System_Monitoring'
});

module.exports = pool;