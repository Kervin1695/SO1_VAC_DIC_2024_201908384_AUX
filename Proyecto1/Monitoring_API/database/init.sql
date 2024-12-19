-- Crear la base de datos si no existe
CREATE DATABASE IF NOT EXISTS monitoring;

USE monitoring;

-- Crear tabla system_status
CREATE TABLE IF NOT EXISTS system_status (
    id INT AUTO_INCREMENT PRIMARY KEY,
    machine_id VARCHAR(255),
    cpu_usage FLOAT,
    ram_usage FLOAT,
    timestamp DATETIME
);

-- Crear tabla processes
CREATE TABLE IF NOT EXISTS processes (
    id INT AUTO_INCREMENT PRIMARY KEY,
    machine_id VARCHAR(255),
    pid INT,
    name VARCHAR(255),
    user VARCHAR(255),
    status VARCHAR(50),
    ram_usage FLOAT,
    timestamp DATETIME
);
