CREATE DATABASE MonitoringAPI_db;

USE MonitoringAPI_db;

CREATE TABLE Maquina (
    id VARCHAR(40) PRIMARY KEY,
);

CREATE TABLE CPU (
    maquina_id INT PRIMARY KEY,
    Percentage_used VARCHAR(255) NOT NULL,
    dateStamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (maquina_id) REFERENCES Maquina(id)
);

CREATE TABLE RAM (
    maquina_id INT PRIMARY KEY,
    Total INT NOT NULL,
    Free INT NOT NULL,
    Used INT NOT NULL,
    Percentage_used VARCHAR(255) NOT NULL,
    dateStamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (maquina_id) REFERENCES Maquina(id)
);

CREATE TABLE CPU_Processes (
    pid INT AUTO_INCREMENT PRIMARY KEY,
    cpu_id INT,
    name_p VARCHAR(255) NOT NULL,
    user VARCHAR(255) NOT NULL,
    state_p VARCHAR(255) NOT NULL,
    ram_usage DECIMAL(5, 2) NOT NULL,
    Percentage_used VARCHAR(255) NOT NULL,
    FOREIGN KEY (cpu_id) REFERENCES CPU(maquina_id)
);

