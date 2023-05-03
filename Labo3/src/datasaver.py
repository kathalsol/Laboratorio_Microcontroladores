#!/usr/bin/env python3
import serial #Paquete de comunicacion arduino / python

baud = 9600
samples = 29 

file = open("datos.csv", 'w') 
file.close()
print("Se leyó el archivo")


ser = serial.Serial("/tmp/ttyS1", baud) #Comunicacion con el arduino: puerto ttyS1
print("Conexión exitosa")

file = open("datos.csv", 'w') #Archivo csv
print("Se creó el archivo csv")

contador  = 0

while (1):
    getData = str(ser.readline())
    data = getData[2:][:-5] 
    print(data)

    if contador == 4:
        file = open("datos.csv", "a")
        file.write(data + "\n")
        contador = 0
    else:
        file.write(data + ",")
        contador+=1