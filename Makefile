# Comandos para hacer que el cliente funcione

# para correr el Dockerfile (dockerclient es el nombre de la imagen)

docker build -t dockerclient 

# despues de correr eso se crea la imagen en docker que de hecho se puede comprobar con

docker images

# por ultimo se puede correr un contenedor a partir de esa imagen 

docker run --rm -ti -p8080:8080 -network="host" dockerclient

# ya estando dentro de docker

cd cliente

./client


# y se usa la interfaz para enviar archivos