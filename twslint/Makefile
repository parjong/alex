all: lint

lint:
	poetry run pylint twslint

test_only_txt:
	poetry run python -c 'from twslint.app import entrypoint; entrypoint()' --rcfile example.only_txt_files.twslintrc examples README.rst
	git diff
	git stash
	git stash drop

test_txt_and_md:
	poetry run python -c 'from twslint.app import entrypoint; entrypoint()' --rcfile example.txt_and_md_files.twslintrc examples README.rst
	git diff
	git stash
	git stash drop
