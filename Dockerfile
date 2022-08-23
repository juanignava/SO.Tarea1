FROM ubuntu
WORKDIR /usr/tarea
COPY Client ./Client
RUN apt update
RUN apt install -y build-essential
RUN apt-get install -y manpages-dev
EXPOSE 8080
RUN cd Client
RUN pwd
RUN ls
RUN gcc Client/client.c -o Client/client
