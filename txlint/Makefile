all: lint test

lint:
	poetry run pylint txlint

test:
	poetry run python -c 'from txlint.app import entrypoint; entrypoint()' --rcfile tutorial/example.txlintrc
