Let's evaluate [poetry](https://python-poetry.org/) for integration!
- https://python-poetry.org/docs/basic-usage/

## HOWTO

### Install poetry/pipx

```
# From https://python-poetry.org/docs/#installation
curl -sSL https://raw.githubusercontent.com/python-poetry/poetry/master/install-poetry.py | python -
```

```
# From https://pypa.github.io/pipx/
python3 -m pip install --user pipx
python3 -m pipx ensurepath
```

### Rock-n-roll with poetry/pipx

```
poetry new demo
```

```
# Apply changes for this tutorial. Please add your code instead!
patch -p1 <tutorial.diff
```

```
cd demo

# Create poetry.lock
poetry install

# Run your script
poetry run python demo/__init__.py

# Build .whl
#
# Ref: https://python-poetry.org/docs/cli/#build
poetry build -f wheel
# A .whl file is waiting you from dist/
```

```
pipx install dist/demo-*.whl

# You can now use 'awesome' from your environment.
#
# Ref: https://python-poetry.org/docs/pyproject/#scripts
awesome
Hello, World
```
