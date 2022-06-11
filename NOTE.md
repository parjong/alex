# Goal

Let's reduce time to write boilterplate code!

## Minimal Usecase

Let's allow users to set up Github Actions workflow with the following command:
```
# Inject boilerplate to any existing project
$ bplate/inject -o /existing/project -- "github/workflow/pull_request_check"
```

Then, ``bplate`` creates ``/new/project/.github/workflows/check_pull_request.yml`` with basic code (and comments)
```yml
name: 'Check Pull Request'

on:
  pull_reqeust

default:
  shell: bash

jobs:
  check:
    runs-on: ubuntu-18.04
    steps:
      - run: echo 'Please fill in your code'
```

**Key** Let template (not users) remember relevant documents!

## Future Usecase

```
$ blpate/new -o /new/project <<EOL
inject "github/action/js"
inject "github/workflow/pull_request_check"
EOL
```
