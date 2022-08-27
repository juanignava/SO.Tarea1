create-image:

	docker build -t dockerclient .

run-image:

	docker run --rm -ti -p8080:8080 --network="host" dockerclient


