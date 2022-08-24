CC=gcc
SRC=server.c logger.c
OUT=server
FLAGS=
SERVICE=DocServer.service
SYSTEMD_PATH=/etc/systemd/system
CFG_FILE=server-config.txt
BIN_PATH=/usr/bin/doc-server

service-start:
		@$(CC) -o $(OUT) $(SRC) $(FLAGS)
		@sudo mkdir -p $(BIN_PATH)/f
		@sudo chmod 644 $(BIN_PATH)/f
		@sudo cp $(OUT) $(BIN_PATH)
		@sudo cp $(CFG_FILE) $(BIN_PATH)
		@sudo chmod +x $(BIN_PATH)/$(OUT)
		@sudo chmod +r $(BIN_PATH)/$(CFG_FILE)
		@sudo cp $(SERVICE) $(SYSTEMD_PATH)
		@sudo chmod 644 $(SYSTEMD_PATH)/$(SERVICE)
		@sudo ln -sf $(SYSTEMD_PATH)/$(SERVICE) /etc/systemd/system/multi-user.target.wants/$(SERVICE)
		@sudo systemctl daemon-reload
		@sudo systemctl start $(SERVICE)

service-status:
		@sudo systemctl status $(SERVICE)

service-stop:
		@sudo systemctl stop $(SERVICE)

check-log:
		@cat /var/log/doc-server.log
