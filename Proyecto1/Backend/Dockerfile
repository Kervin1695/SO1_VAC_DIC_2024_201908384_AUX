# Etapa de construcción
FROM golang:latest AS builder

# Establecer directorio de trabajo
WORKDIR /app

# Copiar los archivos del proyecto
COPY . .

# Descargar dependencias y compilar
RUN go mod tidy
RUN go build -o main .

# Crear imagen final
FROM debian:bullseye

# Copiar el binario construido
COPY --from=builder /app/main /main

# Exponer el puerto en el que escucha el servidor
EXPOSE 5200

# Ejecutar la aplicación
CMD ["/main"]
