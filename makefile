build:
	docker compose up --build

run:
	docker-compose up

daemon:
	docker compose up -d

update:
	./scripts/update.sh
